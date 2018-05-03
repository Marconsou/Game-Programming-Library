#include "ApplicationWin32.h"

using namespace std;
using namespace GPL;

ApplicationWin32::ApplicationWin32(const bool using_joystick) :
using_joystick(using_joystick)
{

}

ApplicationWin32::~ApplicationWin32()
{
	if (this->handle_mutex)
	{
		if (!ReleaseMutex(this->handle_mutex))
			Log::Warning(__FUNCTION__,"ReleaseMutex");

		if (!CloseHandle(this->handle_mutex))
			Log::Warning(__FUNCTION__,"CloseHandle");
	}

	if (this->handle_window)
	{
		if (!DestroyWindow(this->handle_window))
			Log::Warning(__FUNCTION__,"DestroyWindow");

		if (!UnregisterClass(this->window_class_name.c_str(),this->window_class.hInstance))
			Log::Warning(__FUNCTION__,"UnregisterClass");
	}
}

void ApplicationWin32::SetTitle(const string& title) const
{
	SetWindowText(this->handle_window,title.c_str());
}

const HWND& ApplicationWin32::GetHandleWindow() const
{
	return this->handle_window;
}

bool ApplicationWin32::IsActivated() const
{
	return !((IsIconic(this->handle_window)) || (GetForegroundWindow() != this->handle_window));
}

bool ApplicationWin32::IsRunning() const
{
	return (this->msg.message != WM_QUIT);
}

void ApplicationWin32::Quit() const
{
	PostQuitMessage(0);
}

void ApplicationWin32::CreateApplication(unique_ptr<Input>& input,const string& title,const int application_width,const int application_height,const bool windowed,const int icon_id)
{
	this->window_class_name = title;

	this->CheckForMultipleInstances();

	const HINSTANCE handle_instance = this->ModuleHandle();

	HICON handle_icon = this->LoadApplicationIcon(handle_instance,icon_id);

	this->CreateApplicationWindow(handle_instance,handle_icon,title,application_width,application_height,windowed);

	this->CreateInput(input);

	this->SetShowCursor(false);

	ShowWindow(this->handle_window,SW_HIDE);
	SetForegroundWindow(this->handle_window);
}

void ApplicationWin32::CheckForMultipleInstances()
{
	//Cria um Mutex para verificar outra instância desta aplicação
	this->handle_mutex = CreateMutex(nullptr,true,this->window_class_name.c_str());

	//Instância desta aplicação já existe e finalizando-a
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		if (!CloseHandle(this->handle_mutex))
			Log::Error(__FUNCTION__,"CloseHandle");

		//Restaurando a instância principal
		const HWND& handle_window = FindWindow(this->window_class_name.c_str(),nullptr);

		if (handle_window)
		{
			ShowWindow(handle_window,SW_SHOW);
			SetForegroundWindow(handle_window);
		}

		exit(EXIT_SUCCESS);
	}
}

HINSTANCE ApplicationWin32::ModuleHandle() const
{
	const HINSTANCE& handle_instance = GetModuleHandle(nullptr);
	if (!handle_instance)
		Log::Error(__FUNCTION__,"GetModuleHandle");

	return handle_instance;
}

HICON ApplicationWin32::LoadApplicationIcon(const HINSTANCE& handle_instance,const int icon_id) const
{
	HICON handle_icon = nullptr;
	if (icon_id == 0)
		handle_icon = LoadIcon(nullptr,IDI_APPLICATION);
	else
		handle_icon = LoadIcon(handle_instance,MAKEINTRESOURCE(icon_id));

	if (!handle_icon)
		Log::Error(__FUNCTION__,"LoadIcon");

	return handle_icon;
}

void ApplicationWin32::CreateApplicationWindow(const HINSTANCE& handle_instance,const HICON& handle_icon,const string& title,const int application_width,const int application_height,const bool windowed)
{
	this->window_class.style = 0;
	this->window_class.lpfnWndProc = static_cast<WNDPROC>(&ApplicationWin32::WndProc);
	this->window_class.cbClsExtra = 0;
	this->window_class.cbWndExtra = 0;
	this->window_class.hInstance = handle_instance;
	this->window_class.hIcon = handle_icon;
	this->window_class.hCursor = LoadCursor(nullptr,IDC_ARROW);
	this->window_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	this->window_class.lpszMenuName = nullptr;
	this->window_class.lpszClassName = this->window_class_name.c_str();

	//Registrando Window Class
	if (!RegisterClass(&this->window_class))
		Log::Error(__FUNCTION__,"RegisterClass");

	//Propriedades da janela
	RECT window_rect;
	DWORD window_style;
	this->AdjustWindowProperties(window_rect,window_style,application_width,application_height,windowed);

	//Criando a janela da aplicação
	this->handle_window = CreateWindow(this->window_class_name.c_str(),title.c_str(),window_style,window_rect.left,window_rect.top,window_rect.right,window_rect.bottom,nullptr,nullptr,handle_instance,this);
	if (!this->handle_window)
		Log::Error(__FUNCTION__,"CreateWindow");
}

void ApplicationWin32::CreateInput(unique_ptr<Input>& input)
{
	input = make_unique<InputWin32>(this->using_joystick);
	this->pointer_input = input.get();

	InputWin32& input_win32 = static_cast<InputWin32&>(*input);

	input_win32.RegisterKeyboardRawInput(this->handle_window);
	input_win32.RegisterMouseRawInput(this->handle_window);

	if (this->using_joystick)
	{
		input_win32.CreateDirectInput();
		input_win32.CreateJoystickDirectInput(this->handle_window);
	}
}

void ApplicationWin32::AdjustWindowProperties(RECT& window_rect,DWORD& window_style,const int application_width,const int application_height,const bool windowed) const
{
	//Dimensões padrões
	window_style = WS_POPUP;
	window_rect.left = 0;
	window_rect.top = 0;
	window_rect.right = application_width;
	window_rect.bottom = application_height;

	//Correção da posição da janela
	if (windowed)
	{
		//Estilos da janela
		window_style += WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;

		//Ajustando o tamanho da janela (Tela-Borda-Titulo)
		if (!AdjustWindowRect(&window_rect,window_style,false))
			Log::Error(__FUNCTION__,"AdjustWindowRect");

		//Centralizando a janela da aplicação
		window_rect.right -= window_rect.left;
		window_rect.bottom -= window_rect.top;
		window_rect.left = (max(GetSystemMetrics(SM_CXSCREEN),application_width) - application_width) / 2;
		window_rect.top = (max(GetSystemMetrics(SM_CYSCREEN),application_height) - application_height) / 2;
	}
}

void ApplicationWin32::MouseShowStateUpdate() const
{
	RECT rect;
	if (!GetClientRect(this->handle_window,&rect))
		Log::Error(__FUNCTION__,"GetClientRect");

	const int mouse_x = this->pointer_input->GetMouseX();
	const int mouse_y = this->pointer_input->GetMouseY();
	const bool outside_client_area = ((mouse_x < rect.left) || (mouse_x > rect.right) || (mouse_y < rect.top) || (mouse_y > rect.bottom));

	if ((this->GetShowCursor()) || (outside_client_area) || (!this->IsActivated()))
	{
		while (ShowCursor(true) < 0) {}
	}
	else
	{
		while (ShowCursor(false) > 0) {}
	}
}

void ApplicationWin32::ChangeApplicationSettings(const int application_width,const int application_height,const bool windowed,const int virtual_width,const int virtual_height)
{
	//Mantendo a posição do Mouse proporcional a resolução virtual
	this->pointer_input->SetMouseResolutionRatio(static_cast<float>(virtual_width) / static_cast<float>(application_width),static_cast<float>(virtual_height) / static_cast<float>(application_height));

	//Propriedades da janela
	RECT window_rect;
	DWORD window_style;
	this->AdjustWindowProperties(window_rect,window_style,application_width,application_height,windowed);

	//Alterando o estilo da janela, posição e dimensões
	if (!SetWindowLongPtr(this->handle_window,GWL_STYLE,window_style))
		Log::Error(__FUNCTION__,"SetWindowLongPtr");

	if (!SetWindowPos(this->handle_window,HWND_TOPMOST,window_rect.left,window_rect.top,window_rect.right,window_rect.bottom,SWP_SHOWWINDOW | SWP_FRAMECHANGED))
		Log::Error(__FUNCTION__,"SetWindowPos");
}

bool ApplicationWin32::ProcessMessages()
{
	//Verificar se a aplicação recebeu alguma mensagem para ser processada
	bool message_received = false;
	if (PeekMessage(&this->msg,nullptr,0,0,PM_REMOVE))
	{
		TranslateMessage(&this->msg);
		DispatchMessage(&this->msg);
		message_received = true;
	}

	this->MouseShowStateUpdate();

	if (!message_received)
	{
		this->CheckApplicationState();

		if (this->IsActivated())
		{
			static_cast<InputWin32&>(*this->pointer_input).AcquireJoystickDirectInput();
			return true;
		}
		else
		{
			WaitMessage();
			return false;
		}
	}
	return false;
}

LRESULT ApplicationWin32::WMProcess(const UINT message,const WPARAM wParam,const LPARAM lParam)
{
	InputWin32& input_win32 = static_cast<InputWin32&>(*this->pointer_input);

	if (message == WM_INPUT)
	{
		RAWINPUT raw_input;
		UINT size = sizeof(RAWINPUT);
		if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam),RID_INPUT,&raw_input,&size,sizeof(RAWINPUTHEADER)) == -1)
			Log::Error(__FUNCTION__,"GetRawInputData");

		if (raw_input.header.dwType == RIM_TYPEKEYBOARD)
			input_win32.OnKeyboardWMInput(raw_input.data.keyboard);

		if (raw_input.header.dwType == RIM_TYPEMOUSE)
			input_win32.OnMouseWMInput(raw_input.data.mouse);

		return 0;
	}
	else if (message == WM_CHAR)
	{
		if ((wParam >= ' ') || (wParam == '\b'))
		{
			input_win32.OnKeyboardWMChar(wParam);
			return 0;
		}
	}
	else if (message == WM_DEVICECHANGE)
	{
		input_win32.CreateJoystickDirectInput(this->handle_window);
		return 0;
	}
	else if ((message == WM_CLOSE) || (message == WM_DESTROY))
	{
		this->Quit();
		return 0;
	}
	else if (message == WM_SYSCOMMAND)
	{
		if ((wParam == SC_SCREENSAVE) || (wParam == SC_MONITORPOWER) || (wParam == SC_KEYMENU))
			return 0;
	}
	return DefWindowProc(this->handle_window,message,wParam,lParam);
}

LRESULT CALLBACK ApplicationWin32::WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	ApplicationWin32* application_win32 = nullptr;
	if (message == WM_CREATE)
	{
		application_win32 = static_cast<ApplicationWin32*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);

		if ((!SetWindowLongPtr(hWnd,GWLP_USERDATA,reinterpret_cast<LONG_PTR>(application_win32))) && (GetLastError()))
			Log::Error(__FUNCTION__,"SetWindowLongPtr");
	}
	else
	{
		application_win32 = reinterpret_cast<ApplicationWin32*>(GetWindowLongPtr(hWnd,GWLP_USERDATA));
		if (!application_win32)
			return DefWindowProc(hWnd,message,wParam,lParam);
	}
	application_win32->handle_window = hWnd;
	return application_win32->WMProcess(message,wParam,lParam);
}
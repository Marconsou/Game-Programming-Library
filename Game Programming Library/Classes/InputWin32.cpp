#include "InputWin32.h"

using namespace std;
using namespace GPL;

InputWin32::InputWin32(const bool using_joystick) :
Input(make_unique<KeyboardRawInput>(),make_unique<MouseRawInput>(),using_joystick ? make_unique<JoystickDirectInput>() : nullptr)
{

}

InputWin32::~InputWin32()
{
	//Remover o JoystickDirectInput antes do DirectInput
	this->GetJoystick().reset();
}

void InputWin32::RegisterKeyboardRawInput(const HWND& handle_window)
{
	static_cast<KeyboardRawInput&>(*this->GetKeyboard()).RegisterKeyboardRawInput(handle_window);
}

void InputWin32::RegisterMouseRawInput(const HWND& handle_window)
{
	static_cast<MouseRawInput&>(*this->GetMouse()).RegisterMouseRawInput(handle_window);
}

void InputWin32::CreateDirectInput()
{
	if (FAILED(DirectInput8Create(GetModuleHandle(nullptr),DIRECTINPUT_VERSION,IID_IDirectInput8,reinterpret_cast<void**>(&this->direct_input),nullptr)))
		Log::Error(__FUNCTION__,"DirectInput8Create");
}

void InputWin32::CreateJoystickDirectInput(const HWND& handle_window)
{
	if (this->GetJoystick())
		static_cast<JoystickDirectInput&>(*this->GetJoystick()).CreateJoystickDirectInput(handle_window,this->direct_input);
}

void InputWin32::OnKeyboardWMChar(const WPARAM wParam)
{
	static_cast<KeyboardRawInput&>(*this->GetKeyboard()).OnWMChar(wParam);
}

void InputWin32::OnKeyboardWMInput(const RAWKEYBOARD& raw_keyboard)
{
	static_cast<KeyboardRawInput&>(*this->GetKeyboard()).OnWMInput(raw_keyboard);
}

void InputWin32::OnMouseWMInput(const RAWMOUSE& raw_mouse)
{
	static_cast<MouseRawInput&>(*this->GetMouse()).OnWMInput(raw_mouse);
}

void InputWin32::AcquireJoystickDirectInput()
{
	if (this->GetJoystick())
		static_cast<JoystickDirectInput&>(*this->GetJoystick()).Acquire();
}
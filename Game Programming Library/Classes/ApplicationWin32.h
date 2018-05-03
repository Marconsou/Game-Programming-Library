#ifndef APPLICATIONWIN32_H
#define APPLICATIONWIN32_H

#include "Application.h"
#include "InputWin32.h"

namespace GPL
{
	class ApplicationWin32 : public Application
	{
	public:
		GPL_DLL ApplicationWin32(const bool using_joystick = false);
		GPL_DLL ~ApplicationWin32();
		const HWND& GetHandleWindow() const;
		GPL_DLL void CreateApplication(std::unique_ptr<Input>& input,const std::string& title,const int application_width,const int application_height,const bool windowed,const int icon_id) override;
		GPL_DLL void SetTitle(const std::string& title) const override;
		bool IsActivated() const override;
		GPL_DLL bool IsRunning() const override;
		GPL_DLL void Quit() const override;
		GPL_DLL void ChangeApplicationSettings(const int application_width,const int application_height,const bool windowed,const int virtual_width,const int virtual_height) override;
		GPL_DLL bool ProcessMessages() override;
	private:
		const bool using_joystick{};
		std::string window_class_name;
		Input* pointer_input{};
		HWND handle_window{};
		HANDLE handle_mutex{};
		WNDCLASS window_class;
		MSG msg;
		void CheckForMultipleInstances();
		HINSTANCE ModuleHandle() const;
		HICON LoadApplicationIcon(const HINSTANCE& handle_instance,const int icon_id) const;
		void CreateApplicationWindow(const HINSTANCE& handle_instance,const HICON& handle_icon,const std::string& title,const int application_width,const int application_height,const bool windowed);
		void CreateInput(std::unique_ptr<Input>& input);
		void AdjustWindowProperties(RECT& window_rect,DWORD& window_style,const int application_width,const int application_height,const bool windowed) const;
		void MouseShowStateUpdate() const;
		LRESULT WMProcess(const UINT message,const WPARAM wParam,const LPARAM lParam);
		static LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
	};
}

#endif
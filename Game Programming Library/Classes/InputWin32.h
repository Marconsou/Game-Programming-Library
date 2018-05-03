#ifndef INPUTWIN32_H
#define INPUTWIN32_H

#include "Input.h"
#include "KeyboardRawInput.h"
#include "MouseRawInput.h"
#include "JoystickDirectInput.h"

namespace GPL
{
	class InputWin32 : public Input
	{
	public:
		GPL_DLL explicit InputWin32(const bool using_joystick);
		~InputWin32();
		void RegisterKeyboardRawInput(const HWND& handle_window);
		void RegisterMouseRawInput(const HWND& handle_window);
		void CreateDirectInput();
		void CreateJoystickDirectInput(const HWND& handle_window);
		void OnKeyboardWMChar(const WPARAM wParam);
		void OnKeyboardWMInput(const RAWKEYBOARD& raw_keyboard);
		void OnMouseWMInput(const RAWMOUSE& raw_mouse);
		void AcquireJoystickDirectInput();
	private:
		CComPtr<IDirectInput8> direct_input;
	};
}

#endif
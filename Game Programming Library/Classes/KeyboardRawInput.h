#ifndef KEYBOARDRAWINPUT_H
#define KEYBOARDRAWINPUT_H

#include <Windows.h>
#include "Log.h"
#include "Keyboard.h"

namespace GPL
{
	class KeyboardRawInput : public Keyboard
	{
	public:
		void RegisterKeyboardRawInput(const HWND& handle_window);
		void OnWMChar(const WPARAM wParam);
		void OnWMInput(const RAWKEYBOARD& raw_keyboard);
	private:
		const HWND* pointer_handle_window{};
		void CheckKeyboardKey(const RAWKEYBOARD& raw_keyboard,const KeyboardKey keyboard_key);
		void MapKeyboardKeys() override;
	};
}

#endif
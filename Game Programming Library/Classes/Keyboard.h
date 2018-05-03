#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "InputDevice.h"

namespace GPL
{
	enum class KeyboardKey
	{
		Unknown,
		Backspace,
		Tab,
		Clear,
		Enter,
		LeftShift,
		RightShift,
		LeftControl,
		RightControl,
		LeftAlt,
		RightAlt,
		PauseBreak,
		CapsLock,
		Esc,
		Space,
		PageUp,
		PageDown,
		End,
		Home,
		Left,
		Up,
		Right,
		Down,
		PrintScreen,
		Insert,
		Delete,
		Key0,
		Key1,
		Key2,
		Key3,
		Key4,
		Key5,
		Key6,
		Key7,
		Key8,
		Key9,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		LeftSystem,
		RightSystem,
		Menu,
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
		Multiply,
		Add,
		Subtract,
		Decimal,
		Divide,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		NumLock,
		ScrollLock,
		SemiColon,
		Equal,
		Comma,
		Minus,
		Period,
		Slash,
		GraveAccent,
		LeftBracket,
		Backslash,
		RightBracket,
		SingleQuote,
		Max,
	};

	class Keyboard : public InputDevice<KeyboardKey>
	{
	public:
		Keyboard();
		virtual ~Keyboard() = 0 {};
		size_t GetLastCharacterTyped();
	protected:
		void SetLastCharacterTyped(const size_t last_character_typed);
		KeyboardKey GetKeyboardKey(const int id);
		void AddKeyboardKey(const int id,const KeyboardKey keyboard_key);
		void MapInputNames() override;
		virtual void MapKeyboardKeys() = 0;
	private:
		size_t last_character_typed{};
		std::unordered_map<int,KeyboardKey> keyboard_key_map;
	};
}

#endif
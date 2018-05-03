#include "KeyboardRawInput.h"

using namespace std;
using namespace GPL;

void KeyboardRawInput::RegisterKeyboardRawInput(const HWND& handle_window)
{
	RAWINPUTDEVICE raw_input_device;
	raw_input_device.usUsagePage = 1;
	raw_input_device.usUsage = 6;
	raw_input_device.dwFlags = 0;
	raw_input_device.hwndTarget = handle_window;

	if (!RegisterRawInputDevices(&raw_input_device,1,sizeof(raw_input_device)))
		Log::Error(__FUNCTION__,"RegisterRawInputDevices");

	this->pointer_handle_window = &handle_window;

	this->MapKeyboardKeys();
}

void KeyboardRawInput::OnWMChar(const WPARAM wParam)
{
	this->SetLastCharacterTyped(wParam);
}

void KeyboardRawInput::OnWMInput(const RAWKEYBOARD& raw_keyboard)
{
	const USHORT vk = raw_keyboard.VKey;
	const bool e0 = ((raw_keyboard.Flags & RI_KEY_E0) != 0);

	if (vk == VK_SHIFT)
	{
		const bool right_shift = (raw_keyboard.MakeCode == 0x36);
		const bool left_shift = (raw_keyboard.MakeCode == 0x2A);

		if (right_shift)
			this->CheckKeyboardKey(raw_keyboard,KeyboardKey::RightShift);
		else if (left_shift)
			this->CheckKeyboardKey(raw_keyboard,KeyboardKey::LeftShift);
	}
	else if (vk == VK_MENU)
	{
		if (e0)
			this->CheckKeyboardKey(raw_keyboard,KeyboardKey::RightAlt);
		else
			this->CheckKeyboardKey(raw_keyboard,KeyboardKey::LeftAlt);
	}
	else if (vk == VK_CONTROL)
	{
		if (e0)
			this->CheckKeyboardKey(raw_keyboard,KeyboardKey::RightControl);
		else
			this->CheckKeyboardKey(raw_keyboard,KeyboardKey::LeftControl);
	}
	else if ((vk >= VK_BACK) && (vk <= VK_OEM_CLEAR))
		this->CheckKeyboardKey(raw_keyboard,this->GetKeyboardKey(vk));
}

void KeyboardRawInput::CheckKeyboardKey(const RAWKEYBOARD& raw_keyboard,const KeyboardKey keyboard_key)
{
	const bool key_down = ((raw_keyboard.Flags & RI_KEY_MAKE) == RI_KEY_MAKE);
	const bool key_up = ((raw_keyboard.Flags & RI_KEY_BREAK) == RI_KEY_BREAK);

	if (key_down)
	{
		if ((this->IsInputStateReleased(keyboard_key)) || (this->IsInputStateReleasedOnce(keyboard_key)))
			this->AddInputEventPressedOnce(keyboard_key);
	}

	if (key_up)
	{
		if ((this->IsInputStatePressed(keyboard_key)) || (this->IsInputStatePressedOnce(keyboard_key)))
			this->AddInputEventReleasedOnce(keyboard_key);
	}
}

void KeyboardRawInput::MapKeyboardKeys()
{
	this->AddKeyboardKey(0,KeyboardKey::Unknown);
	this->AddKeyboardKey(VK_BACK,KeyboardKey::Backspace);
	this->AddKeyboardKey(VK_TAB,KeyboardKey::Tab);
	this->AddKeyboardKey(VK_CLEAR,KeyboardKey::Clear);
	this->AddKeyboardKey(VK_RETURN,KeyboardKey::Enter);
	this->AddKeyboardKey(VK_LSHIFT,KeyboardKey::LeftShift);
	this->AddKeyboardKey(VK_RSHIFT,KeyboardKey::RightShift);
	this->AddKeyboardKey(VK_LCONTROL,KeyboardKey::LeftControl);
	this->AddKeyboardKey(VK_RCONTROL,KeyboardKey::RightControl);
	this->AddKeyboardKey(VK_LMENU,KeyboardKey::LeftAlt);
	this->AddKeyboardKey(VK_RMENU,KeyboardKey::RightAlt);
	this->AddKeyboardKey(VK_PAUSE,KeyboardKey::PauseBreak);
	this->AddKeyboardKey(VK_CAPITAL,KeyboardKey::CapsLock);
	this->AddKeyboardKey(VK_ESCAPE,KeyboardKey::Esc);
	this->AddKeyboardKey(VK_SPACE,KeyboardKey::Space);
	this->AddKeyboardKey(VK_PRIOR,KeyboardKey::PageUp);
	this->AddKeyboardKey(VK_NEXT,KeyboardKey::PageDown);
	this->AddKeyboardKey(VK_END,KeyboardKey::End);
	this->AddKeyboardKey(VK_HOME,KeyboardKey::Home);
	this->AddKeyboardKey(VK_LEFT,KeyboardKey::Left);
	this->AddKeyboardKey(VK_UP,KeyboardKey::Up);
	this->AddKeyboardKey(VK_RIGHT,KeyboardKey::Right);
	this->AddKeyboardKey(VK_DOWN,KeyboardKey::Down);
	this->AddKeyboardKey(VK_SNAPSHOT,KeyboardKey::PrintScreen);
	this->AddKeyboardKey(VK_INSERT,KeyboardKey::Insert);
	this->AddKeyboardKey(VK_DELETE,KeyboardKey::Delete);
	this->AddKeyboardKey('0',KeyboardKey::Key0);
	this->AddKeyboardKey('1',KeyboardKey::Key1);
	this->AddKeyboardKey('2',KeyboardKey::Key2);
	this->AddKeyboardKey('3',KeyboardKey::Key3);
	this->AddKeyboardKey('4',KeyboardKey::Key4);
	this->AddKeyboardKey('5',KeyboardKey::Key5);
	this->AddKeyboardKey('6',KeyboardKey::Key6);
	this->AddKeyboardKey('7',KeyboardKey::Key7);
	this->AddKeyboardKey('8',KeyboardKey::Key8);
	this->AddKeyboardKey('9',KeyboardKey::Key9);
	this->AddKeyboardKey('A',KeyboardKey::A);
	this->AddKeyboardKey('B',KeyboardKey::B);
	this->AddKeyboardKey('C',KeyboardKey::C);
	this->AddKeyboardKey('D',KeyboardKey::D);
	this->AddKeyboardKey('E',KeyboardKey::E);
	this->AddKeyboardKey('F',KeyboardKey::F);
	this->AddKeyboardKey('G',KeyboardKey::G);
	this->AddKeyboardKey('H',KeyboardKey::H);
	this->AddKeyboardKey('I',KeyboardKey::I);
	this->AddKeyboardKey('J',KeyboardKey::J);
	this->AddKeyboardKey('K',KeyboardKey::K);
	this->AddKeyboardKey('L',KeyboardKey::L);
	this->AddKeyboardKey('M',KeyboardKey::M);
	this->AddKeyboardKey('N',KeyboardKey::N);
	this->AddKeyboardKey('O',KeyboardKey::O);
	this->AddKeyboardKey('P',KeyboardKey::P);
	this->AddKeyboardKey('Q',KeyboardKey::Q);
	this->AddKeyboardKey('R',KeyboardKey::R);
	this->AddKeyboardKey('S',KeyboardKey::S);
	this->AddKeyboardKey('T',KeyboardKey::T);
	this->AddKeyboardKey('U',KeyboardKey::U);
	this->AddKeyboardKey('V',KeyboardKey::V);
	this->AddKeyboardKey('W',KeyboardKey::W);
	this->AddKeyboardKey('X',KeyboardKey::X);
	this->AddKeyboardKey('Y',KeyboardKey::Y);
	this->AddKeyboardKey('Z',KeyboardKey::Z);
	this->AddKeyboardKey(VK_LWIN,KeyboardKey::LeftSystem);
	this->AddKeyboardKey(VK_RWIN,KeyboardKey::RightSystem);
	this->AddKeyboardKey(VK_APPS,KeyboardKey::Menu);
	this->AddKeyboardKey(VK_NUMPAD0,KeyboardKey::Numpad0);
	this->AddKeyboardKey(VK_NUMPAD1,KeyboardKey::Numpad1);
	this->AddKeyboardKey(VK_NUMPAD2,KeyboardKey::Numpad2);
	this->AddKeyboardKey(VK_NUMPAD3,KeyboardKey::Numpad3);
	this->AddKeyboardKey(VK_NUMPAD4,KeyboardKey::Numpad4);
	this->AddKeyboardKey(VK_NUMPAD5,KeyboardKey::Numpad5);
	this->AddKeyboardKey(VK_NUMPAD6,KeyboardKey::Numpad6);
	this->AddKeyboardKey(VK_NUMPAD7,KeyboardKey::Numpad7);
	this->AddKeyboardKey(VK_NUMPAD8,KeyboardKey::Numpad8);
	this->AddKeyboardKey(VK_NUMPAD9,KeyboardKey::Numpad9);
	this->AddKeyboardKey(VK_MULTIPLY,KeyboardKey::Multiply);
	this->AddKeyboardKey(VK_ADD,KeyboardKey::Add);
	this->AddKeyboardKey(VK_SUBTRACT,KeyboardKey::Subtract);
	this->AddKeyboardKey(VK_DECIMAL,KeyboardKey::Decimal);
	this->AddKeyboardKey(VK_DIVIDE,KeyboardKey::Divide);
	this->AddKeyboardKey(VK_F1,KeyboardKey::F1);
	this->AddKeyboardKey(VK_F2,KeyboardKey::F2);
	this->AddKeyboardKey(VK_F3,KeyboardKey::F3);
	this->AddKeyboardKey(VK_F4,KeyboardKey::F4);
	this->AddKeyboardKey(VK_F5,KeyboardKey::F5);
	this->AddKeyboardKey(VK_F6,KeyboardKey::F6);
	this->AddKeyboardKey(VK_F7,KeyboardKey::F7);
	this->AddKeyboardKey(VK_F8,KeyboardKey::F8);
	this->AddKeyboardKey(VK_F9,KeyboardKey::F9);
	this->AddKeyboardKey(VK_F10,KeyboardKey::F10);
	this->AddKeyboardKey(VK_F11,KeyboardKey::F11);
	this->AddKeyboardKey(VK_F12,KeyboardKey::F12);
	this->AddKeyboardKey(VK_NUMLOCK,KeyboardKey::NumLock);
	this->AddKeyboardKey(VK_SCROLL,KeyboardKey::ScrollLock);
	this->AddKeyboardKey(VK_OEM_1,KeyboardKey::SemiColon);
	this->AddKeyboardKey(VK_OEM_PLUS,KeyboardKey::Equal);
	this->AddKeyboardKey(VK_OEM_COMMA,KeyboardKey::Comma);
	this->AddKeyboardKey(VK_OEM_MINUS,KeyboardKey::Minus);
	this->AddKeyboardKey(VK_OEM_PERIOD,KeyboardKey::Period);
	this->AddKeyboardKey(VK_OEM_2,KeyboardKey::Slash);
	this->AddKeyboardKey(VK_OEM_3,KeyboardKey::GraveAccent);
	this->AddKeyboardKey(VK_OEM_4,KeyboardKey::LeftBracket);
	this->AddKeyboardKey(VK_OEM_5,KeyboardKey::Backslash);
	this->AddKeyboardKey(VK_OEM_6,KeyboardKey::RightBracket);
	this->AddKeyboardKey(VK_OEM_7,KeyboardKey::SingleQuote);
}
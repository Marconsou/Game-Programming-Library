#include "Keyboard.h"

using namespace std;
using namespace GPL;

Keyboard::Keyboard() :
InputDevice(static_cast<size_t>(KeyboardKey::Max))
{
	this->MapInputNames();
}

void Keyboard::SetLastCharacterTyped(const size_t last_character_typed)
{
	this->last_character_typed = last_character_typed;
}

size_t Keyboard::GetLastCharacterTyped()
{
	const size_t last_character_typed = this->last_character_typed;
	this->last_character_typed = 0;
	return (this->GetEnabled() ? last_character_typed : 0);
}

KeyboardKey Keyboard::GetKeyboardKey(const int id)
{
	return this->keyboard_key_map[id];
}

void Keyboard::AddKeyboardKey(const int id,const KeyboardKey keyboard_key)
{
	this->keyboard_key_map.insert(pair<int,KeyboardKey>(id,keyboard_key));
}

void Keyboard::MapInputNames()
{
	this->AddInputName(KeyboardKey::Unknown,"Unknown");
	this->AddInputName(KeyboardKey::Backspace,"Backspace");
	this->AddInputName(KeyboardKey::Tab,"Tab");
	this->AddInputName(KeyboardKey::Clear,"Clear");
	this->AddInputName(KeyboardKey::Enter,"Enter");
	this->AddInputName(KeyboardKey::LeftShift,"L-Shift");
	this->AddInputName(KeyboardKey::RightShift,"R-Shift");
	this->AddInputName(KeyboardKey::LeftControl,"L-Control");
	this->AddInputName(KeyboardKey::RightControl,"R-Control");
	this->AddInputName(KeyboardKey::LeftAlt,"L-Alt");
	this->AddInputName(KeyboardKey::RightAlt,"R-Alt");
	this->AddInputName(KeyboardKey::PauseBreak,"Pause Break");
	this->AddInputName(KeyboardKey::CapsLock,"Caps Lock");
	this->AddInputName(KeyboardKey::Esc,"Esc");
	this->AddInputName(KeyboardKey::Space,"Space");
	this->AddInputName(KeyboardKey::PageUp,"Page Up");
	this->AddInputName(KeyboardKey::PageDown,"Page Down");
	this->AddInputName(KeyboardKey::End,"End");
	this->AddInputName(KeyboardKey::Home,"Home");
	this->AddInputName(KeyboardKey::Left,"Left");
	this->AddInputName(KeyboardKey::Up,"Up");
	this->AddInputName(KeyboardKey::Right,"Right");
	this->AddInputName(KeyboardKey::Down,"Down");
	this->AddInputName(KeyboardKey::PrintScreen,"Print Screen");
	this->AddInputName(KeyboardKey::Insert,"Insert");
	this->AddInputName(KeyboardKey::Delete,"Delete");
	this->AddInputName(KeyboardKey::Key0,"0");
	this->AddInputName(KeyboardKey::Key1,"1");
	this->AddInputName(KeyboardKey::Key2,"2");
	this->AddInputName(KeyboardKey::Key3,"3");
	this->AddInputName(KeyboardKey::Key4,"4");
	this->AddInputName(KeyboardKey::Key5,"5");
	this->AddInputName(KeyboardKey::Key6,"6");
	this->AddInputName(KeyboardKey::Key7,"7");
	this->AddInputName(KeyboardKey::Key8,"8");
	this->AddInputName(KeyboardKey::Key9,"9");
	this->AddInputName(KeyboardKey::A,"A");
	this->AddInputName(KeyboardKey::B,"B");
	this->AddInputName(KeyboardKey::C,"C");
	this->AddInputName(KeyboardKey::D,"D");
	this->AddInputName(KeyboardKey::E,"E");
	this->AddInputName(KeyboardKey::F,"F");
	this->AddInputName(KeyboardKey::G,"G");
	this->AddInputName(KeyboardKey::H,"H");
	this->AddInputName(KeyboardKey::I,"I");
	this->AddInputName(KeyboardKey::J,"J");
	this->AddInputName(KeyboardKey::K,"K");
	this->AddInputName(KeyboardKey::L,"L");
	this->AddInputName(KeyboardKey::M,"M");
	this->AddInputName(KeyboardKey::N,"N");
	this->AddInputName(KeyboardKey::O,"O");
	this->AddInputName(KeyboardKey::P,"P");
	this->AddInputName(KeyboardKey::Q,"Q");
	this->AddInputName(KeyboardKey::R,"R");
	this->AddInputName(KeyboardKey::S,"S");
	this->AddInputName(KeyboardKey::T,"T");
	this->AddInputName(KeyboardKey::U,"U");
	this->AddInputName(KeyboardKey::V,"V");
	this->AddInputName(KeyboardKey::W,"W");
	this->AddInputName(KeyboardKey::X,"X");
	this->AddInputName(KeyboardKey::Y,"Y");
	this->AddInputName(KeyboardKey::Z,"Z");
	this->AddInputName(KeyboardKey::LeftSystem,"L-System");
	this->AddInputName(KeyboardKey::RightSystem,"R-System");
	this->AddInputName(KeyboardKey::Menu,"Menu");
	this->AddInputName(KeyboardKey::Numpad0,"Numpad0");
	this->AddInputName(KeyboardKey::Numpad1,"Numpad1");
	this->AddInputName(KeyboardKey::Numpad2,"Numpad2");
	this->AddInputName(KeyboardKey::Numpad3,"Numpad3");
	this->AddInputName(KeyboardKey::Numpad4,"Numpad4");
	this->AddInputName(KeyboardKey::Numpad5,"Numpad5");
	this->AddInputName(KeyboardKey::Numpad6,"Numpad6");
	this->AddInputName(KeyboardKey::Numpad7,"Numpad7");
	this->AddInputName(KeyboardKey::Numpad8,"Numpad8");
	this->AddInputName(KeyboardKey::Numpad9,"Numpad9");
	this->AddInputName(KeyboardKey::Multiply,"*");
	this->AddInputName(KeyboardKey::Add,"+");
	this->AddInputName(KeyboardKey::Subtract,"-");
	this->AddInputName(KeyboardKey::Decimal,".");
	this->AddInputName(KeyboardKey::Divide,"/");
	this->AddInputName(KeyboardKey::F1,"F1");
	this->AddInputName(KeyboardKey::F2,"F2");
	this->AddInputName(KeyboardKey::F3,"F3");
	this->AddInputName(KeyboardKey::F4,"F4");
	this->AddInputName(KeyboardKey::F5,"F5");
	this->AddInputName(KeyboardKey::F6,"F6");
	this->AddInputName(KeyboardKey::F7,"F7");
	this->AddInputName(KeyboardKey::F8,"F8");
	this->AddInputName(KeyboardKey::F9,"F9");
	this->AddInputName(KeyboardKey::F10,"F10");
	this->AddInputName(KeyboardKey::F11,"F11");
	this->AddInputName(KeyboardKey::F12,"F12");
	this->AddInputName(KeyboardKey::NumLock,"Num Lock");
	this->AddInputName(KeyboardKey::ScrollLock,"Scroll Lock");
	this->AddInputName(KeyboardKey::SemiColon,";");
	this->AddInputName(KeyboardKey::Equal,"=");
	this->AddInputName(KeyboardKey::Comma,",");
	this->AddInputName(KeyboardKey::Minus,"-");
	this->AddInputName(KeyboardKey::Period,".");
	this->AddInputName(KeyboardKey::Slash,"/");
	this->AddInputName(KeyboardKey::GraveAccent,"`");
	this->AddInputName(KeyboardKey::LeftBracket,"[");
	this->AddInputName(KeyboardKey::Backslash,"\\");
	this->AddInputName(KeyboardKey::RightBracket,"]");
	this->AddInputName(KeyboardKey::SingleQuote,"'");
}
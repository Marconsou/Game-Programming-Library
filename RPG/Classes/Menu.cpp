#include "Menu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

Menu::Menu(const size_t size) :
	creation_index(0),
	default_font_small(GameState::GetGame<GameRPG>().GetVideo().GetFont(FontQlassikBoldSmallFileID)),
	default_font_medium(GameState::GetGame<GameRPG>().GetVideo().GetFont(FontQlassikBoldMediumFileID)),
	controls(size)
{

}

Menu::~Menu()
{
	this->on_close(*this);
}

float Menu::GetDefaultEdgeDistance() const
{
	return 3.0f;
}

const Font& Menu::GetDefaultFontSmall() const
{
	return this->default_font_small;
}

const Font& Menu::GetDefaultFontMedium() const
{
	return this->default_font_medium;
}

size_t Menu::GetControlTotal() const
{
	return this->controls.size();
}

void Menu::ResizeControls(const size_t size)
{
	this->controls.resize(size);
}

void Menu::EnableControls(const bool enable)
{
	for (size_t i = 0; i < this->controls.size(); i++)
		this->controls[i]->SetEnabled(enable);
}

void Menu::VisibleControls(const bool visible)
{
	for (size_t i = 0; i < this->controls.size(); i++)
		this->controls[i]->SetVisible(visible);
}

void Menu::ControlsUpdate(const bool add_controls)
{
	//Adicionar ou remover os controles
	void (Control::*PointerActionControl)() = ((add_controls) ? (&Control::AddControl) : (&Control::RemoveControl));

	//Controls
	for (size_t i = 0; i < this->controls.size(); i++)
		(this->controls[i].get()->*PointerActionControl)();
}

void Menu::Update()
{

}

void Menu::Show()
{

}

void Menu::GeneralOnClick(const Control& control)
{
	GameState::GetGame<GameRPG>().GetAudio().PlaySoundFromBuffer(SoundClickFileID);
}

void Menu::ExtractInformation(const string& text_string,const vector<int>& values,vector<string>& strings,vector<Color>& colors)
{
	//Separa os textos corretamente
	size_t character_index = 0;
	size_t value_index = 0;
	size_t i = 0;
	const size_t tag_size = 3;
	for (i = 0; i < text_string.size(); i++)
	{
		//Detectou um símbolo para os valores
		if ((text_string[i] == '{') && (text_string[i + tag_size - 1] == '}'))
		{
			//Adicionar o texto antes do símbolo do valor
			strings.push_back(text_string.substr(character_index,i - character_index));
			colors.push_back(Color::White);
			character_index = i + tag_size;

			//Adicionar o valor e com uma cor diferente
			strings.push_back(Convert::NumberToString(values[value_index]));
			colors.push_back(Color::Yellow);
			value_index++;
		}
	}
	//Se não tiver nenhum valor para copiar
	if (value_index == 0)
		i = text_string.size();

	//Copiar o restante do texto, que poderá ser todo se não tiver valores adicionados
	strings.push_back(text_string.substr(character_index,i - character_index));
	colors.push_back(Color::White);
}
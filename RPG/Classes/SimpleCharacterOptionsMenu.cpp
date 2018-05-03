#include "SimpleCharacterOptionsMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

SimpleCharacterOptionsMenu::SimpleCharacterOptionsMenu(const Point2D<float>& position,const bool& change_window_position,const float contents_window_width,const int buttons_before_back_button,const size_t size_added,const int inner_block_quantity_w,const int inner_block_quantity_h) :
	Menu(SimpleCharacterOptionsMenuControlMax + size_added),
	position(position),
	change_window_position(change_window_position),
	buttons_before_back_button(buttons_before_back_button),
	window_speed_x(0.0f)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Options Window
	Window& options_window = this->CreateControl<Window>();
	game.SetWindow(options_window,inner_block_quantity_w,inner_block_quantity_h);
	options_window.SetPosition(-options_window.GetW(),50.0f);
	options_window.AddControl();

	//Back Button
	Button& back_button = this->CreateControl<Button>();
	back_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(BackTextID),Color::Gold);
	back_button.SetKeyboardKeyShortcut(KeyboardKey::Esc);
	back_button.AddEventOnClick(&SimpleCharacterOptionsMenu::BackOnClick,*this);
	back_button.SetEnabled(false);
	back_button.AddControl();

	//Atualizar as posições dos controles
	this->PositionUpdate();
}

const Point2D<float>& SimpleCharacterOptionsMenu::GetPosition() const
{
	return this->position;
}

bool SimpleCharacterOptionsMenu::GetChangeWindowPosition() const
{
	return this->change_window_position;
}

float SimpleCharacterOptionsMenu::GetOptionsWindowX() const
{
	return this->GetControl<Window>(OptionsWindow).GetX();
}

float SimpleCharacterOptionsMenu::GetOptionsWindowY() const
{
	return this->GetControl<Window>(OptionsWindow).GetY();
}

float SimpleCharacterOptionsMenu::GetOptionsWindowW() const
{
	return this->GetControl<Window>(OptionsWindow).GetW();
}

float SimpleCharacterOptionsMenu::GetBackButtonX() const
{
	return this->GetControl<Window>(BackButton).GetX();
}

float SimpleCharacterOptionsMenu::GetBackButtonH() const
{
	return this->GetControl<Window>(BackButton).GetH();
}

void SimpleCharacterOptionsMenu::Update()
{
	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void SimpleCharacterOptionsMenu::PositionUpdate()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Atualizar todos os dados do herói
	game.GetHero().CharacterStatsUpdate();

	//Desabilitar os botões quando necessário
	const bool enable = game.GetHero().GetPickedItem().IsEmpty();

	Button& back_button = this->GetControl<Button>(BackButton);
	if (back_button.GetEnabled())
		back_button.SetEnabled(enable);

	//Movimentar as janelas
	if (this->change_window_position)
	{
		Window& options_window = this->GetControl<Window>(OptionsWindow);

		const float value_max = 50.0f;
		const bool options_window_movement_done = (options_window.GetX() == value_max);
		if (!options_window_movement_done)
		{
			this->window_speed_x += 1.0f;
			options_window.SetPosition(min(options_window.GetX() + this->window_speed_x,value_max),50.0f);

			//Buttons
			const float space = 10.0f;
			back_button.SetPosition(options_window.GetX() + space,options_window.GetY() + (this->buttons_before_back_button * (back_button.GetH() + 1.0f)) + space);
		}

		//Habilitar os botões ao terminar a movimentação
		if (enable)
			back_button.SetEnabled(options_window_movement_done);
	}
}
void SimpleCharacterOptionsMenu::BackOnClick(const Control& control)
{
	GameState::GetGame<GameRPG>().GetAudio().PlaySoundFromBuffer(SoundCancelFileID);
	GameState::AddGameState(nullptr,GameStateAction::DeleteCurrentGameState);
}
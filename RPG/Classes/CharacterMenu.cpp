#include "CharacterMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

CharacterMenu::CharacterMenu(const bool full_character_options_menu) :
	Menu(CharacterMenuControlMax),
	change_window_position(false),
	contents_window_speed_x(0.0f),
	options_window_w(0.0f)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Contents Window
	Window& contents_window = this->CreateControl<Window>();
	game.SetWindow(contents_window,25,22);
	contents_window.SetPosition(static_cast<float>(game.GetVideo().GetVirtualWidth()),50.0f);
	contents_window.AddControl();
	this->position.SetX(contents_window.GetX());
	this->position.SetY(contents_window.GetY());

	//Atualizar as posições dos controles
	this->PositionUpdate();

	//Tipo do Character Options Menu
	unique_ptr<SimpleCharacterOptionsMenu> character_options_menu = (full_character_options_menu) ? 
		make_unique<FullCharacterOptionsMenu>(this->position,this->change_window_position,contents_window.GetW()) :
		make_unique<SimpleCharacterOptionsMenu>(this->position,this->change_window_position,contents_window.GetW());

	this->options_window_w = static_cast<SimpleCharacterOptionsMenu*>(this->AddSubGameState(move(character_options_menu)))->GetOptionsWindowW();

	//Information Menu
	this->AddSubGameState(make_unique<InformationMenu>(this->change_window_position));
}

const Point2D<float>& CharacterMenu::GetPosition() const
{
	return this->position;
}

void CharacterMenu::Update()
{
	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void CharacterMenu::PositionUpdate()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Atualizar todos os dados do herói
	game.GetHero().CharacterStatsUpdate();

	//Desabilitar os botões quando necessário
	const bool enable = game.GetHero().GetPickedItem().IsEmpty();

	//Movimentar as janelas
	static Interval change_position_timer(0.015f);
	this->change_window_position = change_position_timer.Action(game.GetTimer());
	if (this->change_window_position)
	{
		const float contents_window_value_max = 50.0f + this->options_window_w;

		Window& contents_window = this->GetControl<Window>(ContentsWindow);
		if (this->position.GetX() != contents_window_value_max)
		{
			this->contents_window_speed_x -= 4.0f;

			this->position.SetX(max(this->position.GetX() + this->contents_window_speed_x,contents_window_value_max));
			contents_window.SetPosition(this->position.GetX(),this->position.GetY());
		}
	}
}
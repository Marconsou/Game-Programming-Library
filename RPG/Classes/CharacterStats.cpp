#include "CharacterStats.h"

using namespace std;
using namespace GPL;
using namespace RPG;

CharacterStats::CharacterStats(const Point2D<float>& position) :
	Menu(CharacterStatsControlMax),
	position(position),
	page_quantity(0,5)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Previous Page Button
	Button& previous_page_button = this->CreateControl<Button>();
	previous_page_button.SetButton(game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,65.0f,0.0f);
	previous_page_button.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
	previous_page_button.NewToolTipTextLine(game.GetDatabase().GetLanguageText(PreviousPageDescriptionTextID),Color::White);
	previous_page_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	previous_page_button.AddEventOnClick(&CharacterStats::PreviousPageOnClick,*this);
	previous_page_button.SetKeyboardKeyShortcut(KeyboardKey::PageDown);
	previous_page_button.AddControl();

	//Next Page Button
	Button& next_page_button = this->CreateControl<Button>();
	next_page_button.SetButton(game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,82.0f,0.0f);
	next_page_button.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
	next_page_button.NewToolTipTextLine(game.GetDatabase().GetLanguageText(NextPageDescriptionTextID),Color::White);
	next_page_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	next_page_button.AddEventOnClick(&CharacterStats::NextPageOnClick,*this);
	next_page_button.SetKeyboardKeyShortcut(KeyboardKey::PageUp);
	next_page_button.AddControl();

	//Atualizando página
	this->PageControlsUpdate();

	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void CharacterStats::Update()
{
	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void CharacterStats::PositionUpdate()
{
	Button& previous_page_button = this->GetControl<Button>(this->GetControlTotal() - CharacterStatsControlMax + PreviousPageButton);
	Button& next_page_button = this->GetControl<Button>(this->GetControlTotal() - CharacterStatsControlMax + NextPageButton);

	previous_page_button.SetPosition(this->position.GetX() + 35.0f,this->position.GetY() + 400.0f);
	next_page_button.SetPosition(previous_page_button.GetX() + previous_page_button.GetW() + 9.0f,previous_page_button.GetY());
}

void CharacterStats::PageControlsUpdate()
{
	//Remover a página atual
	this->RemoveSubGameStates();

	//Main Stats
	if (this->page_quantity.GetCurrent() == 0)
		this->AddSubGameState(make_unique<CharacterStatsMainStats>(this->position,19));

	//Elemental Properties
	else if (this->page_quantity.GetCurrent() == 1)
		this->AddSubGameState(make_unique<CharacterStatsElementalProperties>(this->position,17));

	//Status Properties
	else if (this->page_quantity.GetCurrent() == 2)
		this->AddSubGameState(make_unique<CharacterStatsStatusProperties>(this->position,12));

	//Natural Properties
	else if (this->page_quantity.GetCurrent() == 3)
		this->AddSubGameState(make_unique<CharacterStatsNaturalProperties>(this->position,8));

	//General Abilities
	else if (this->page_quantity.GetCurrent() == 4)
		this->AddSubGameState(make_unique<CharacterStatsGeneralAbilities>(this->position,16));
}

void CharacterStats::PreviousPageOnClick(const Control& control)
{
	this->page_quantity.Previous();
	this->PageControlsUpdate();
}

void CharacterStats::NextPageOnClick(const Control& control)
{
	this->page_quantity.Next();
	this->PageControlsUpdate();
}
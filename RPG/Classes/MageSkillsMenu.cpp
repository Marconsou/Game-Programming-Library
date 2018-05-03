#include "MageSkillsMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

MageSkillsMenu::MageSkillsMenu() :
	ClassSkillsMenu(GameState::GetGame<GameRPG>().GetDatabase().GetMageSkillLevel(),GameState::GetGame<GameRPG>().GetVideo().GetTexture(TextureMageSkillsFileID))
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Skill Buttons
	int index_added = 1;
	//SkillButton* skill_button = &this->GetControl<SkillButton>(index_added);
	//skill_button->SetPosition(460.0f,302.0f,true);
	index_added += 2;

	this->SkillButtonToolTipUpdate();
}

void MageSkillsMenu::Update()
{
	ClassSkillsMenu::Update();
}

void MageSkillsMenu::SkillButtonToolTipUpdate()
{
	
}
#include "WarriorSkillsMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

WarriorSkillsMenu::WarriorSkillsMenu() :
	ClassSkillsMenu(GameState::GetGame<GameRPG>().GetDatabase().GetWarriorSkillLevel(),GameState::GetGame<GameRPG>().GetVideo().GetTexture(TextureWarriorSkillsFileID))
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Skill Buttons
	int index_added = 1;
	SkillButton* skill_button = &this->GetControl<SkillButton>(index_added);
	skill_button->SetPosition(460.0f,302.0f,true);
	index_added += 2;

	this->SkillButtonToolTipUpdate();
}

void WarriorSkillsMenu::Update()
{
	ClassSkillsMenu::Update();
}

void WarriorSkillsMenu::SkillButtonToolTipUpdate()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Atualizar dados do ToolTip
	this->BaseToolTipUpdate(CutMasteryTextID);

	//Cut Mastery
	int index_added = 1;
	SkillButton* skill_button = &this->GetControl<SkillButton>(index_added);

	const SkillLevel* current_skill_level = &skill_button->GetSkill().GetCurrentSkillLevel();
	const SkillLevel* next_skill_level = &skill_button->GetSkill().GetNextSkillLevel();

	skill_button->NewToolTipTextLine(game.GetDatabase().GetLanguageText(CutMasteryDescriptionTextID),Color::White);
	skill_button->NewToolTipTextLine(game.GetDatabase().GetLanguageText(MeleeWeaponOnlyTextID),Color::White);

	if (current_skill_level)
	{
		skill_button->NewToolTipTextLine(game.GetDatabase().GetLanguageText(CurrentSkillLevelTextID),Color::Gold);
		skill_button->AddToolTipTextLine(" " + game.GetDatabase().GetLanguageText(PhysicalDamageTextID),Color::Yellow);
		skill_button->AddToolTipTextLine(" +" + Convert::NumberToString(current_skill_level->GetPhysicalDamagePercentage()) + "% ",Color::White);
		skill_button->AddToolTipTextLine(game.GetDatabase().GetLanguageText(CriticalStrikeTextID),Color::Yellow);
		skill_button->AddToolTipTextLine(" +" + Convert::NumberToString(current_skill_level->GetStatsBasic().GetCriticalStrike()) + "%",Color::White);
	}

	if (!skill_button->GetSkill().SkillIsLevelMax())
	{
		if (current_skill_level)
		{
			skill_button->NewToolTipTextLine(game.GetDatabase().GetLanguageText(NextSkillLevelTextID),Color::Gold);
			skill_button->AddToolTipTextLine(" " + game.GetDatabase().GetLanguageText(PhysicalDamageTextID),Color::Yellow);
		}
		else
			skill_button->NewToolTipTextLine(" " + game.GetDatabase().GetLanguageText(PhysicalDamageTextID),Color::Yellow);

		skill_button->AddToolTipTextLine(" +" + Convert::NumberToString(next_skill_level->GetPhysicalDamagePercentage()) + "% ",Color::White);
		skill_button->AddToolTipTextLine(game.GetDatabase().GetLanguageText(CriticalStrikeTextID),Color::Yellow);
		skill_button->AddToolTipTextLine(" +" + Convert::NumberToString(next_skill_level->GetStatsBasic().GetCriticalStrike()) + "%",Color::White);
	}
	index_added += 2;
}
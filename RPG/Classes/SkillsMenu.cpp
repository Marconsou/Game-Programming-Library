#include "SkillsMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

SkillsMenu::SkillsMenu(const float x,const float y) :
	Menu(1)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Skill Points Label
	Label& skill_points = this->CreateControl<Label>();

	skill_points.SetPosition(x,y);
	skill_points.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
	skill_points.NewToolTipTextLine(game.GetDatabase().GetLanguageText(SkillPointsDescriptionTextID),Color::White);
	skill_points.AddControl();

	//Warrior Skills Menu
	if (game.GetHero().IsWarrior())
		this->AddSubGameState(make_unique<WarriorSkillsMenu>());

	//Mage Skills Menu
	else if (game.GetHero().IsMage())
		this->AddSubGameState(make_unique<MageSkillsMenu>());
}

void SkillsMenu::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	const Hero& hero = game.GetHero();

	//Skill Points Label
	Label& skill_points = this->GetControl<Label>(0);

	skill_points.SetText(this->GetDefaultFontSmall(),game.GetDatabase().GetLanguageText(SkillPointsTextID),Color::Yellow);
	skill_points.AddText(" " + Convert::NumberToString(hero.GetSP()),(hero.GetSP()) ? Color::Green : Color::Red);
}
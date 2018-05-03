#include "CharacterStatsNaturalProperties.h"

using namespace GPL;
using namespace RPG;

CharacterStatsNaturalProperties::CharacterStatsNaturalProperties(const Point2D<float>& position,const size_t size) :
	CharacterStatsPage(position,size)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	int index = 1;
	for (int i = 0; i <= MPRegenTextID - CriticalStrikeTextID; i++)
		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(CriticalStrikeDescriptionTextID + i)));

	index = 1;
	this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(TwoHandsAttackDescriptionTextID));
	this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(TwoHandsAttackDescriptionTextID));

	index = 4;
	this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(TwoHandsAttackDescriptionTextID));
	this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(TwoHandsAttackDescriptionTextID));
}

void CharacterStatsNaturalProperties::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	Hero& hero = game.GetHero();
	StatsBasic& stats_basic = hero.GetStats().GetStatsBasic();
	const Database& database = game.GetDatabase();

	float y = this->GetY();
	const float x = this->GetX();
	int index = 0;

	this->SetStatsLabel(index,x,y,database.GetLanguageText(NaturalPropertiesTextID),Color::Green,true);
	this->SetStatsLabel(index,x,y,database.GetLanguageText(CriticalStrikeTextID),Convert::NumberToString(stats_basic.GetCriticalStrike()) + "%" + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(hero.GetCriticalStrikeSecondary()) + "%": ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(QuickStrikeTextID),Convert::NumberToString(stats_basic.GetQuickStrike()) + "%" + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(hero.GetQuickStrikeSecondary()) + "%": ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(CounterStrikeTextID),Convert::NumberToString(stats_basic.GetCounterStrike()) + "%");
	this->SetStatsLabel(index,x,y,database.GetLanguageText(HPStealTextID),Convert::NumberToString(stats_basic.GetHPSteal()) + "%" + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(hero.GetHPStealSecondary()) + "%" : ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(MPStealTextID),Convert::NumberToString(stats_basic.GetMPSteal()) + "%" + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(hero.GetMPStealSecondary()) + "%" : ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(HPRegenTextID),Convert::NumberToString(stats_basic.GetHPRegen()));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(MPRegenTextID),Convert::NumberToString(stats_basic.GetMPRegen()));
}
#include "CharacterStatsStatusProperties.h"

using namespace GPL;
using namespace RPG;

CharacterStatsStatusProperties::CharacterStatsStatusProperties(const Point2D<float>& position,const size_t size) :
	CharacterStatsPage(position,size)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	int index = 1;
	this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(StatusEffectDescriptionTextID));

	//Attack
	for (int i = 0; i <= BlindnessAttackTextID - WoundAttackTextID; i++)
	{
		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(i + WoundDescriptionTextID)));
		index--;

		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(StatusAttackDescriptionTextID));
		index--;

		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(StatusEffectRequiredDescriptionTextID));
		index--;

		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(TwoHandsAttackDescriptionTextID));
	}

	//Defense
	for (int i = 0; i <= BlindnessDefenseTextID - WoundDefenseTextID; i++)
	{
		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(i + WoundDescriptionTextID)));
		index--;

		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(StatusDefenseDescriptionTextID));
	}
}

void CharacterStatsStatusProperties::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	Hero& hero = game.GetHero();
	StatusNegative& status_attack = hero.GetStats().GetStatusAttack();
	StatusNegative& status_attack_secondary = hero.GetStatusAttackSecondary();
	StatusNegative& status_defense = hero.GetStats().GetStatusDefense();
	const Database& database = game.GetDatabase();

	float y = this->GetY();
	const float x = this->GetX();
	int index = 0;

	this->SetStatsLabel(index,x,y,database.GetLanguageText(StatusPropertiesTextID),Color::Green,true);
	this->SetStatsLabel(index,x,y,database.GetLanguageText(StatusEffectTextID),database.GetLanguageText(static_cast<LanguageTextID>(OffTextID + static_cast<int>(hero.GetStats().GetStatsBasic().GetStatusEffect()))),Color::Yellow,hero.GetStats().GetStatsBasic().GetStatusEffect() ? Color::Green : Color::Red,true);
	this->SetStatsLabel(index,x,y,database.GetLanguageText(WoundAttackTextID),Convert::NumberToString(status_attack.GetWound()) + "%" + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(status_attack_secondary.GetWound()) + "%": ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(SlownessAttackTextID),Convert::NumberToString(status_attack.GetSlowness()) + "%" + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(status_attack_secondary.GetSlowness()) + "%" : ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(TirednessAttackTextID),Convert::NumberToString(status_attack.GetTiredness()) + "%" + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(status_attack_secondary.GetTiredness()) + "%" : ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(HeadacheAttackTextID),Convert::NumberToString(status_attack.GetHeadache()) + "%" + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(status_attack_secondary.GetHeadache()) + "%" : ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(BlindnessAttackTextID),Convert::NumberToString(status_attack.GetBlindness()) + "%" + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(status_attack_secondary.GetBlindness()) + "%" : ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(WoundDefenseTextID),Convert::NumberToString(status_defense.GetWound()) + "%");
	this->SetStatsLabel(index,x,y,database.GetLanguageText(SlownessDefenseTextID),Convert::NumberToString(status_defense.GetSlowness()) + "%");
	this->SetStatsLabel(index,x,y,database.GetLanguageText(TirednessDefenseTextID),Convert::NumberToString(status_defense.GetTiredness()) + "%");
	this->SetStatsLabel(index,x,y,database.GetLanguageText(HeadacheDefenseTextID),Convert::NumberToString(status_defense.GetHeadache()) + "%");
	this->SetStatsLabel(index,x,y,database.GetLanguageText(BlindnessDefenseTextID),Convert::NumberToString(status_defense.GetBlindness()) + "%");
}
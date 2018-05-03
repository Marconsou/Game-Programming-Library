#include "CharacterStatsElementalProperties.h"

using namespace GPL;
using namespace RPG;

CharacterStatsElementalProperties::CharacterStatsElementalProperties(const Point2D<float>& position,const size_t size) :
	CharacterStatsPage(position,size)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	int index = 1;
	this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(ElementalEffectDescriptionTextID));

	//Damage
	for (int i = 0; i <= DarkDamageTextID - FireDamageTextID; i++)
	{
		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(ElementalDamageDescriptionTextID));
		index--;

		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(ElementalEffectRequiredDescriptionTextID));
		index--;

		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(TwoHandsAttackDescriptionTextID));
	}

	//Resist
	for (int i = 0; i <= DarkResistTextID - FireResistTextID; i++)
		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(ElementalResistDescriptionTextID));

	//Absorb
	for (int i = 0; i <= DarkAbsorbTextID - FireAbsorbTextID; i++)
		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(ElementalAbsorbDescriptionTextID));
}

void CharacterStatsElementalProperties::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	Hero& hero = game.GetHero();
	Elemental& elemental_damage = hero.GetStats().GetElementalDamage();
	Elemental& elemental_damage_secondary = hero.GetElementalDamageSecondary();
	Elemental& elemental_resist = hero.GetStats().GetElementalResist();
	Elemental& elemental_absorb = hero.GetStats().GetElementalAbsorb();
	const Database& database = game.GetDatabase();

	float y = this->GetY();
	const float x = this->GetX();
	int index = 0;

	this->SetStatsLabel(index,x,y,database.GetLanguageText(ElementalPropertiesTextID),Color::Green,true);
	this->SetStatsLabel(index,x,y,database.GetLanguageText(ElementalEffectTextID),database.GetLanguageText(static_cast<LanguageTextID>(OffTextID + static_cast<int>(hero.GetStats().GetStatsBasic().GetElementalEffect()))),Color::Yellow,hero.GetStats().GetStatsBasic().GetElementalEffect() ? Color::Green : Color::Red,true);
	this->SetStatsLabel(index,x,y,database.GetLanguageText(FireDamageTextID),Convert::NumberToString(elemental_damage.GetFire()) + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(elemental_damage_secondary.GetFire()) : ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(IceDamageTextID),Convert::NumberToString(elemental_damage.GetIce()) + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(elemental_damage_secondary.GetIce()) : ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(LightningDamageTextID),Convert::NumberToString(elemental_damage.GetLightning()) + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(elemental_damage_secondary.GetLightning()) : ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(LightDamageTextID),Convert::NumberToString(elemental_damage.GetLight()) + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(elemental_damage_secondary.GetLight()) : ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(DarkDamageTextID),Convert::NumberToString(elemental_damage.GetDark()) + (hero.TwoHandsAttack() ? " " + Convert::NumberToString(elemental_damage_secondary.GetDark()) : ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(FireResistTextID),Convert::NumberToString(elemental_resist.GetFire()) + "%");
	this->SetStatsLabel(index,x,y,database.GetLanguageText(IceResistTextID),Convert::NumberToString(elemental_resist.GetIce()) + "%");
	this->SetStatsLabel(index,x,y,database.GetLanguageText(LightningResistTextID),Convert::NumberToString(elemental_resist.GetLightning()) + "%");
	this->SetStatsLabel(index,x,y,database.GetLanguageText(LightResistTextID),Convert::NumberToString(elemental_resist.GetLight()) + "%");
	this->SetStatsLabel(index,x,y,database.GetLanguageText(DarkResistTextID),Convert::NumberToString(elemental_resist.GetDark()) + "%");
	this->SetStatsLabel(index,x,y,database.GetLanguageText(FireAbsorbTextID),Convert::NumberToString(elemental_absorb.GetFire()) + "%",Color::Yellow,elemental_resist.GetFire() >= 100 ? Color::Green : Color::Gray);
	this->SetStatsLabel(index,x,y,database.GetLanguageText(IceAbsorbTextID),Convert::NumberToString(elemental_absorb.GetIce()) + "%",Color::Yellow,elemental_resist.GetIce() >= 100 ? Color::Green : Color::Gray);
	this->SetStatsLabel(index,x,y,database.GetLanguageText(LightningAbsorbTextID),Convert::NumberToString(elemental_absorb.GetLightning()) + "%",Color::Yellow,elemental_resist.GetLightning() >= 100 ? Color::Green : Color::Gray);
	this->SetStatsLabel(index,x,y,database.GetLanguageText(LightAbsorbTextID),Convert::NumberToString(elemental_absorb.GetLight()) + "%",Color::Yellow,elemental_resist.GetLight() >= 100 ? Color::Green : Color::Gray);
	this->SetStatsLabel(index,x,y,database.GetLanguageText(DarkAbsorbTextID),Convert::NumberToString(elemental_absorb.GetDark()) + "%",Color::Yellow,elemental_resist.GetDark() >= 100 ? Color::Green : Color::Gray);
}
#include "CharacterStatsMainStats.h"

using namespace GPL;
using namespace RPG;

CharacterStatsMainStats::CharacterStatsMainStats(const Point2D<float>& position,const size_t size) :
	CharacterStatsPage(position,size)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	int index = 0;
	for (size_t i = NameDescriptionTextID; i <= AttributePointsDescriptionTextID; i++)
		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(i)));

	index = PhysicalDamageTextID - ClassTextID + 1;
	this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(TwoHandsAttackDescriptionTextID)));

	index = HitTextID - ClassTextID + 1;
	this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(TwoHandsAttackDescriptionTextID)));

	//Adicionar os controles restantes que não são Labels
	this->ResizeControls(this->GetControlTotal() + CharacterStatsMainStatsControlAdded);

	//Strength Button
	Button& strength_button = this->CreateControl<Button>();
	strength_button.SetButton(game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,33.0f,33.0f);
	strength_button.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
	strength_button.NewToolTipTextLine(game.GetDatabase().GetLanguageText(AddStrengthDescriptionTextID),Color::White);
	strength_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	strength_button.AddEventOnClick(&CharacterStatsMainStats::AddStrengthOnClick,*this);
	strength_button.AddControl();

	//Intelligence Button
	Button& intelligence_button = this->CreateControl<Button>();
	intelligence_button.SetButton(game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,33.0f,33.0f);
	intelligence_button.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
	intelligence_button.NewToolTipTextLine(game.GetDatabase().GetLanguageText(AddIntelligenceDescriptionTextID),Color::White);
	intelligence_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	intelligence_button.AddEventOnClick(&CharacterStatsMainStats::AddIntelligenceOnClick,*this);
	intelligence_button.AddControl();

	//Agility Button
	Button& agility_button = this->CreateControl<Button>();
	agility_button.SetButton(game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,33.0f,33.0f);
	agility_button.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
	agility_button.NewToolTipTextLine(game.GetDatabase().GetLanguageText(AddAgilityDescriptionTextID),Color::White);
	agility_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	agility_button.AddEventOnClick(&CharacterStatsMainStats::AddAgilityOnClick,*this);
	agility_button.AddControl();

	//Portrait Picture Box
	PictureBox& portrait_picture_box = this->CreateControl<PictureBox>();
	portrait_picture_box.SetSprite(game.GetHero().GetCharacter()->GetCharacterTexture(),game.GetHero().GetCharacter()->GetW(),38.0f,0.0f,10.0f);
	portrait_picture_box.AddControl();

	//Exp Bar
	const Rect<float> background_texture_rect(125.0f,100.0f,108.0f,14.0f);
	const Rect<float> bar_texture_rect(125.0f,119.0f,100.0f,8.0f);
	const Point2D<float> bar_position_relative(4.0f,3.0f);
	Bar& exp_bar = this->CreateControl<Bar>();
	exp_bar.SetBar(game.GetVideo().GetTexture(TextureCommonFileID),Color::Black,Color::Null,Color::Orange,background_texture_rect,bar_texture_rect,bar_position_relative);
	exp_bar.SetShowBackgroundBar(false);
	exp_bar.AddControl();

	//HP Bar
	Bar& hp_bar = this->CreateControl<Bar>();
	hp_bar.SetBar(game.GetVideo().GetTexture(TextureCommonFileID),Color::Black,Color::Null,Color::Green,background_texture_rect,bar_texture_rect,bar_position_relative);
	hp_bar.SetShowBackgroundBar(false);
	hp_bar.AddControl();

	//MP Bar
	Bar& mp_bar = this->CreateControl<Bar>();
	mp_bar.SetBar(game.GetVideo().GetTexture(TextureCommonFileID),Color::Black,Color::Null,Color::Blue,background_texture_rect,bar_texture_rect,bar_position_relative);
	mp_bar.SetShowBackgroundBar(false);
	mp_bar.AddControl();

	//Attribute Buttons
	this->AttributeButtonsUpdate();

	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void CharacterStatsMainStats::Update()
{
	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void CharacterStatsMainStats::PositionUpdate()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	Hero& hero = game.GetHero();
	Stats& stats = hero.GetStats();
	StatsBasic& stats_basic = stats.GetStatsBasic();
	const Database& database = game.GetDatabase();

	float y = this->GetY();
	const float x = this->GetX();
	int index = 0;

	Button& strength_button = this->GetControl<Button>(this->GetControlTotal() - CharacterStatsMainStatsControlAdded + StrengthButton);
	Button& intelligence_button = this->GetControl<Button>(this->GetControlTotal() - CharacterStatsMainStatsControlAdded + IntelligenceButton);
	Button& agility_button = this->GetControl<Button>(this->GetControlTotal() - CharacterStatsMainStatsControlAdded + AgilityButton);

	Bar& exp_bar = this->GetControl<Bar>(this->GetControlTotal() - CharacterStatsMainStatsControlAdded + ExpBar);
	Bar& hp_bar = this->GetControl<Bar>(this->GetControlTotal() - CharacterStatsMainStatsControlAdded + HPBar);
	Bar& mp_bar = this->GetControl<Bar>(this->GetControlTotal() - CharacterStatsMainStatsControlAdded + MPBar);

	this->SetStatsLabel(index,x,y,stats.GetName(),Color::Green);
	this->GetControl<PictureBox>(this->GetControlTotal() - CharacterStatsMainStatsControlAdded + PortraitPictureBox).SetPosition(x,y);
	this->SetStatsLabel(index,x + hero.GetCharacter()->GetW(),y,database.GetLanguageText(ClassTextID),database.GetLanguageText(static_cast<LanguageTextID>(NewGameMenuWarriorClassNameTextID + (hero.GetClassType() * 3))));
	this->SetStatsLabel(index,x + hero.GetCharacter()->GetW(),y,database.GetLanguageText(LevelTextID),Convert::NumberToString(stats.GetLevel()));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(ExperienceTextID),Convert::NumberToString(hero.GetExp()));
	exp_bar.SetPosition(x + 180.0f,y,true);
	this->SetStatsLabel(index,x,y,database.GetLanguageText(NextLevelTextID),Convert::NumberToString(hero.GetNextLevel()));
	hp_bar.SetPosition(x + 85.0f,y + 3.0f);
	this->SetStatsLabel(index,x,y,database.GetLanguageText(HPTextID),Convert::NumberToString(stats_basic.GetHP()) + "/" + Convert::NumberToString(stats_basic.GetHPMax()));
	mp_bar.SetPosition(x + 85.0f,y + 3.0f);
	this->SetStatsLabel(index,x,y,database.GetLanguageText(MPTextID),Convert::NumberToString(stats_basic.GetMP()) + "/" + Convert::NumberToString(stats_basic.GetMPMax()));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(PhysicalDamageTextID),Convert::NumberToString(stats_basic.GetPhysicalDamageMin()) + "-" + Convert::NumberToString(stats_basic.GetPhysicalDamageMax()) + " " + (hero.TwoHandsAttack() ? Convert::NumberToString(hero.GetPhysicalDamageMinSecondary()) + "-" + Convert::NumberToString(hero.GetPhysicalDamageMaxSecondary()) : ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(PhysicalResistTextID),Convert::NumberToString(stats_basic.GetPhysicalResist()) + "%");
	this->SetStatsLabel(index,x,y,database.GetLanguageText(MagicalDamageTextID),Convert::NumberToString(stats_basic.GetMagicalDamageMin()) + "-" + Convert::NumberToString(stats_basic.GetMagicalDamageMax()));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(MagicalResistTextID),Convert::NumberToString(stats_basic.GetMagicalResist()) + "%");
	this->SetStatsLabel(index,x,y,database.GetLanguageText(HitTextID),Convert::NumberToString(stats_basic.GetHit()) + "% " + (hero.TwoHandsAttack() ? Convert::NumberToString(hero.GetHitSecondary()) + "%" : ""));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(EvadeTextID),Convert::NumberToString(stats_basic.GetEvade()) + "%");
	this->SetStatsLabel(index,x,y,database.GetLanguageText(SpeedTextID),Convert::NumberToString(stats_basic.GetSpeed()));
	this->SetStatsLabel(index,x,y,database.GetLanguageText(MovementTextID),database.GetLanguageText(static_cast<LanguageTextID>(SlowTextID + hero.GetMovement())));

	//Strength
	const float tab_space = 20.0f;
	const Label* label = &this->GetStatsLabel(index);
	this->SetStatsLabel(index,x + tab_space,y,database.GetLanguageText(StrengthTextID),Convert::NumberToString(hero.GetStrength()));
	strength_button.SetPosition(label->GetX() + (strength_button.GetW() / 2.0f) - tab_space,label->GetY() + (label->GetH() / 2.0f),true);

	//Intelligence
	label = &this->GetStatsLabel(index);
	this->SetStatsLabel(index,x + tab_space,y,database.GetLanguageText(IntelligenceTextID),Convert::NumberToString(hero.GetIntelligence()));
	intelligence_button.SetPosition(label->GetX() + (intelligence_button.GetW() / 2.0f) - tab_space,label->GetY() + (label->GetH() / 2.0f),true);

	//Agility
	label = &this->GetStatsLabel(index);
	this->SetStatsLabel(index,x + tab_space,y,database.GetLanguageText(AgilityTextID),Convert::NumberToString(hero.GetAgility()));
	agility_button.SetPosition(label->GetX() + (agility_button.GetW() / 2.0f) - tab_space,label->GetY() + (label->GetH() / 2.0f),true);

	//Attribute Points
	this->SetStatsLabel(index,x,y,database.GetLanguageText(AttributePointsTextID),Convert::NumberToString(hero.GetAP()),Color::Yellow,(hero.GetAP()) ? Color::Green : Color::Red);

	//HP Bar
	hp_bar.SetPercentage(stats_basic.GetHP(),stats_basic.GetHPMax());

	//MP Bar
	mp_bar.SetPercentage(stats_basic.GetMP(),stats_basic.GetMPMax());

	//Exp Bar
	exp_bar.SetPercentage(hero.GetExp() - hero.CalculatePreviousExp(),hero.GetNextLevel() - hero.CalculatePreviousExp());
}

void CharacterStatsMainStats::AttributeButtonsUpdate()
{
	const bool enable_attribute_button = (GameState::GetGame<GameRPG>().GetHero().GetAP() > 0);

	this->GetControl<Button>(this->GetControlTotal() - CharacterStatsMainStatsControlAdded + StrengthButton).SetEnabled(enable_attribute_button);
	this->GetControl<Button>(this->GetControlTotal() - CharacterStatsMainStatsControlAdded + IntelligenceButton).SetEnabled(enable_attribute_button);
	this->GetControl<Button>(this->GetControlTotal() - CharacterStatsMainStatsControlAdded + AgilityButton).SetEnabled(enable_attribute_button);
}

void CharacterStatsMainStats::AddStrengthOnClick(const Control& control)
{
	GameState::GetGame<GameRPG>().GetHero().AddStrength();
	this->AttributeButtonsUpdate();
}

void CharacterStatsMainStats::AddIntelligenceOnClick(const Control& control)
{
	GameState::GetGame<GameRPG>().GetHero().AddIntelligence();
	this->AttributeButtonsUpdate();
}

void CharacterStatsMainStats::AddAgilityOnClick(const Control& control)
{
	GameState::GetGame<GameRPG>().GetHero().AddAgility();
	this->AttributeButtonsUpdate();
}
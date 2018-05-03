#include "FullCharacterOptionsMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

FullCharacterOptionsMenu::FullCharacterOptionsMenu(const Point2D<float>& position,const bool& change_window_position,const float contents_window_width) :
	SimpleCharacterOptionsMenu(position,change_window_position,contents_window_width,APToSpendPictureBox - InventoryButton,FullCharacterOptionsMenuControlMax,4,5),
	contents_window_width(contents_window_width),
	ap_to_spend_picture_box_control_added(false),
	sp_to_spend_picture_box_control_added(false),
	last_sub_menu_selected(NoSelection)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Inventory Button
	Button& inventory_button = this->CreateControl<Button>();
	inventory_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(InventoryTextID),Color::Gold);
	inventory_button.SetKeyboardKeyShortcut(KeyboardKey::I);
	inventory_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	inventory_button.AddEventOnClick(&FullCharacterOptionsMenu::InventoryOnClick,*this);
	inventory_button.SetEnabled(false);
	inventory_button.AddControl();

	//Skills Button
	Button& skills_button = this->CreateControl<Button>();
	skills_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(SkillsTextID),Color::Gold);
	skills_button.SetKeyboardKeyShortcut(KeyboardKey::S);
	skills_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	skills_button.AddEventOnClick(&FullCharacterOptionsMenu::SkillsOnClick,*this);
	skills_button.SetEnabled(false);
	skills_button.AddControl();

	//Quests Button
	Button& quests_button = this->CreateControl<Button>();
	quests_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(QuestsTextID),Color::Gold);
	quests_button.SetKeyboardKeyShortcut(KeyboardKey::Q);
	quests_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	quests_button.AddEventOnClick(&FullCharacterOptionsMenu::QuestsOnClick,*this);
	quests_button.SetEnabled(false);
	quests_button.AddControl();

	//Achievements Button
	Button& achievements_button = this->CreateControl<Button>();
	achievements_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(AchievementsTextID),Color::Gold);
	achievements_button.SetKeyboardKeyShortcut(KeyboardKey::A);
	achievements_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	achievements_button.AddEventOnClick(&FullCharacterOptionsMenu::AchievementsOnClick,*this);
	achievements_button.SetEnabled(false);
	achievements_button.AddControl();

	//AP To Spend Picture Box
	PictureBox& ap_to_spend_picture_box = this->CreateControl<PictureBox>();
	ap_to_spend_picture_box.SetSprite(game.GetVideo().GetTexture(TextureCommonFileID),12.0f,12.0f,50.0f,33.0f);
	ap_to_spend_picture_box.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
	ap_to_spend_picture_box.NewToolTipTextLine(game.GetDatabase().GetLanguageText(AttributePointsDescriptionTextID),Color::White);

	//SP To Spend Picture Box
	PictureBox& sp_to_spend_picture_box = this->CreateControl<PictureBox>();
	sp_to_spend_picture_box.SetSprite(game.GetVideo().GetTexture(TextureCommonFileID),12.0f,12.0f,50.0f,33.0f);
	sp_to_spend_picture_box.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
	sp_to_spend_picture_box.NewToolTipTextLine(game.GetDatabase().GetLanguageText(SkillPointsDescriptionTextID),Color::White);

	//Sub Menu padrão
	this->SelectSubMenu(InventorySelection);

	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void FullCharacterOptionsMenu::Update()
{
	SimpleCharacterOptionsMenu::Update();

	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void FullCharacterOptionsMenu::PositionUpdate()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Atualizar todos os dados do herói
	game.GetHero().CharacterStatsUpdate();

	//Desabilitar os botões quando necessário
	const bool enable = game.GetHero().GetPickedItem().IsEmpty();

	Button& inventory_button = this->GetControl<Button>(InventoryButton);
	if (inventory_button.GetEnabled())
		inventory_button.SetEnabled(enable);

	Button& skills_button = this->GetControl<Button>(SkillsButton);
	if (skills_button.GetEnabled())
		skills_button.SetEnabled(enable);

	Button& quests_button = this->GetControl<Button>(QuestsButton);
	if (quests_button.GetEnabled())
		quests_button.SetEnabled(enable);

	Button& achievements_button = this->GetControl<Button>(AchievementsButton);
	if (achievements_button.GetEnabled())
		achievements_button.SetEnabled(enable);

	PictureBox& ap_to_spend_picture_box = this->GetControl<PictureBox>(APToSpendPictureBox);
	PictureBox& sp_to_spend_picture_box = this->GetControl<PictureBox>(SPToSpendPictureBox);

	//Movimentar as janelas
	if (this->GetChangeWindowPosition())
	{
		const float value_max = 50.0f;
		const bool options_window_movement_done = (this->GetOptionsWindowX() == value_max);

		const float space = 10.0f;
		const float x = this->GetBackButtonX();
		const float height = this->GetBackButtonH() + 1.0f;

		//Buttons
		inventory_button.SetPosition(x,this->GetOptionsWindowY() + space);
		skills_button.SetPosition(x,inventory_button.GetY() + height);
		quests_button.SetPosition(x,skills_button.GetY() + height);
		achievements_button.SetPosition(x,quests_button.GetY() + height);

		//Picture Box
		ap_to_spend_picture_box.SetPosition(inventory_button.GetX() + inventory_button.GetW() + ap_to_spend_picture_box.GetW(),inventory_button.GetY() + (inventory_button.GetH() / 2.0f),true);
		sp_to_spend_picture_box.SetPosition(skills_button.GetX() + skills_button.GetW() + sp_to_spend_picture_box.GetW(),skills_button.GetY() + (skills_button.GetH() / 2.0f),true);

		//Habilitar os botões ao terminar a movimentação
		if (enable)
		{
			inventory_button.SetEnabled(options_window_movement_done);
			skills_button.SetEnabled(options_window_movement_done);
			quests_button.SetEnabled(options_window_movement_done);
			achievements_button.SetEnabled(options_window_movement_done);
		}
	}

	//Mostra ícone indicando que tem pontos de atributos para gastar
	this->SpendIconPictureBoxUpdate(game.GetHero().GetAP(),this->ap_to_spend_picture_box_control_added,ap_to_spend_picture_box);

	//Mostra ícone indicando que tem pontos de habilidades para gastar
	this->SpendIconPictureBoxUpdate(game.GetHero().GetSP(),this->sp_to_spend_picture_box_control_added,sp_to_spend_picture_box);
}

void FullCharacterOptionsMenu::SpendIconPictureBoxUpdate(const int value,bool& control_added,PictureBox& picture_box)
{
	//Mostra ícone indicando que tem pontos para gastar
	if (value > 0)
	{
		if (!control_added)
		{
			picture_box.AddControl();
			control_added = true;
		}
	}
	else
	{
		if (control_added)
		{
			picture_box.RemoveControl();
			control_added = false;
		}
	}
}

void FullCharacterOptionsMenu::SelectSubMenu(FullCharacterOptionsMenuSelection sub_menu_selection)
{
	//Se não for o mesmo
	if (this->last_sub_menu_selected != sub_menu_selection)
	{
		this->last_sub_menu_selected = sub_menu_selection;

		const float x = this->GetPosition().GetX() + 15.0f;
		const float y = this->GetPosition().GetY() + 15.0f;

		//Remover o atual selecionado
		this->RemoveSubGameStates();

		//Inventory
		if (this->last_sub_menu_selected == InventorySelection)
			this->AddSubGameState(make_unique<CharacterInventoryMenu>(this->GetPosition()));

		//Skills
		else if (this->last_sub_menu_selected == SkillsSelection)
			this->AddSubGameState(make_unique<SkillsMenu>(x,y));

		//Quests
		else if (this->last_sub_menu_selected == QuestsSelection)
			this->AddSubGameState(make_unique<QuestsMenu>(x,y,this->contents_window_width / 2.0f));

		//Achievements
		else if (this->last_sub_menu_selected == AchievementsSelection)
			this->AddSubGameState(make_unique<AchievementsMenu>(x,y));
	}
}

void FullCharacterOptionsMenu::InventoryOnClick(const Control& control)
{
	this->SelectSubMenu(InventorySelection);
}

void FullCharacterOptionsMenu::SkillsOnClick(const Control& control)
{
	this->SelectSubMenu(SkillsSelection);
}

void FullCharacterOptionsMenu::QuestsOnClick(const Control& control)
{
	this->SelectSubMenu(QuestsSelection);
}

void FullCharacterOptionsMenu::AchievementsOnClick(const Control& control)
{
	this->SelectSubMenu(AchievementsSelection);
}
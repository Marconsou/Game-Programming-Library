#include "BattleItems.h"

using namespace std;
using namespace GPL;
using namespace RPG;

BattleItems::BattleItems(const Point2D<float>& position,const bool opening_from_shop_menu) :
	Menu(GameState::GetGame<GameRPG>().GetHero().GetBattleItems().size() + 1),
	position(position)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Battle Items Label
	Label& battle_items_label = this->CreateControl<Label>();

	//Battle Items Buttons
	for (size_t i = 1; i < this->GetControlTotal(); i++)
	{
		ItemButton& iterator = this->CreateControl<ItemButton>();

		const int battle_item_index = i - 1;

		iterator.SetItemButton(*game.GetHero().GetBattleItems()[battle_item_index],false,opening_from_shop_menu);
		iterator.AddEventOnMouseClick(&BattleItems::BattleItemsOnMouseClick,*this);
		iterator.AddControl();
	}

	battle_items_label.SetText(this->GetDefaultFontSmall(),game.GetDatabase().GetLanguageText(BattleItemsTextID),Color::Gold);
	battle_items_label.AddControl();

	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void BattleItems::Update()
{
	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void BattleItems::PositionUpdate()
{
	//Battle Items Label
	Label& battle_items_label = this->GetControl<Label>(0);
	
	const float add_y = 420.0f;
	const float x = this->position.GetX() + 15.0f;
	const float y = this->position.GetY() + 40.0f;

	for (size_t i = 1; i < this->GetControlTotal(); i++)
	{
		ItemButton& iterator = this->GetControl<ItemButton>(i);

		const int battle_item_index = i - 1;

		const float item_distance = (iterator.GetW() + 1.0f);

		iterator.SetPosition(x + (item_distance * battle_item_index),y + add_y);
	}

	battle_items_label.SetPosition(x,y + add_y - battle_items_label.GetH());
}

void BattleItems::BattleItemsOnMouseClick(Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	static_cast<ItemButton&>(control).ItemOnMouseClick(mouse_button,mouse_x,mouse_y,false,true);
}
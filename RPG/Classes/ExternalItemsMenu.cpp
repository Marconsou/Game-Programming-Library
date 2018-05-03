#include "ExternalItemsMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

ExternalItemsMenu::ExternalItemsMenu(const Point2D<float>& position,vector<unique_ptr<Item>>& items,const string& menu_text,const bool can_put_quest_item,const bool is_shop_item) :
	Menu(items.size() + 1),
	position(position),
	can_put_quest_item(can_put_quest_item),
	items(items)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Menu Text Label
	Label& menu_text_label = this->CreateControl<Label>();
	menu_text_label.SetText(this->GetDefaultFontSmall(),menu_text,Color::Green);
	menu_text_label.AddControl();

	for (size_t i = 0; i < this->items.size(); i++)
	{
		ItemButton& iterator = this->CreateControl<ItemButton>();

		iterator.SetItemButton(*this->items[i],is_shop_item,is_shop_item);
		iterator.AddEventOnMouseClick(&ExternalItemsMenu::ItemOnMouseClick,*this);
		iterator.AddControl();
	}

	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void ExternalItemsMenu::Update()
{
	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void ExternalItemsMenu::PositionUpdate()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Menu Text Label
	size_t index = 0;
	Label& menu_text_label = this->GetControl<Label>(index);
	index++;

	menu_text_label.SetPosition(this->position.GetX() + 15.0f,this->position.GetY() + 15.0f);

	float x = menu_text_label.GetX();
	float y = menu_text_label.GetY() + menu_text_label.GetH() + 10.0f;

	const float initial_x = x;

	for (size_t i = index; i < this->GetControlTotal(); i++)
	{
		ItemButton& iterator = this->GetControl<ItemButton>(i);

		const int mod = (i - index) % 10;
		const float item_distance = (iterator.GetW() + 1.0f);

		x = initial_x + (mod * item_distance);
		if ((mod == 0) && (i != 1))
		{
			x = initial_x;
			y += item_distance;
		}

		iterator.SetPosition(x,y);
	}
}

void ExternalItemsMenu::ItemOnMouseClick(Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	static_cast<ItemButton&>(control).ItemOnMouseClick(mouse_button,mouse_x,mouse_y,this->can_put_quest_item);
}
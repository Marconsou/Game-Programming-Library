#include "ChestInventoryMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

ChestInventoryMenu::ChestInventoryMenu(const Point2D<float>& position,vector<unique_ptr<Item>>& items,const string& menu_text,const bool can_put_quest_item) :
	InventoryMenu(position,false)
{
	this->AddSubGameState(make_unique<ExternalItemsMenu>(position,items,menu_text,can_put_quest_item,false));
}
#include "ShopInventoryMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

ShopInventoryMenu::ShopInventoryMenu(const Point2D<float>& position,vector<unique_ptr<Item>>& items,const string& menu_text) :
	InventoryMenu(position,true)
{
	this->AddSubGameState(make_unique<ExternalItemsMenu>(position,items,menu_text,false,true));
}
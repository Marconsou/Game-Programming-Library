#include "InventoryMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

InventoryMenu::InventoryMenu(const Point2D<float>& position,const bool opening_from_shop_menu)
{
	this->AddSubGameState(make_unique<Inventory>(position,opening_from_shop_menu));
	this->AddSubGameState(make_unique<BattleItems>(position,opening_from_shop_menu));
}
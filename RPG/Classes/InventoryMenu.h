#ifndef INVENTORYMENU_H
#define INVENTORYMENU_H

#include "Inventory.h"
#include "BattleItems.h"

namespace RPG
{
	class InventoryMenu : public Menu
	{
	public:
		//Construtor
		InventoryMenu(const GPL::Point2D<float>& position,const bool opening_from_shop_menu);

		//Destrutor
		virtual ~InventoryMenu() = 0 {};
	};
}

#endif
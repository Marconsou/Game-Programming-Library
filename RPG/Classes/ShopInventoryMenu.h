#ifndef SHOPINVENTORYMENU_H
#define SHOPINVENTORYMENU_H

#include "ExternalItemsMenu.h"
#include "InventoryMenu.h"

namespace RPG
{
	class ShopInventoryMenu : public InventoryMenu
	{
	public:
		//Construtor
		ShopInventoryMenu(const GPL::Point2D<float>& position,std::vector<std::unique_ptr<Item>>& items,const std::string& menu_text);
	};
}

#endif
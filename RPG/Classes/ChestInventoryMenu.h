#ifndef CHESTINVENTORYMENU_H
#define CHESTINVENTORYMENU_H

#include "ExternalItemsMenu.h"
#include "InventoryMenu.h"

namespace RPG
{
	class ChestInventoryMenu : public InventoryMenu
	{
	public:
		//Construtor
		ChestInventoryMenu(const GPL::Point2D<float>& position,std::vector<std::unique_ptr<Item>>& items,const std::string& menu_text,const bool can_put_quest_item);
	};
}

#endif
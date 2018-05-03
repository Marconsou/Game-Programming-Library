#ifndef CHARACTERINVENTORYMENU_H
#define CHARACTERINVENTORYMENU_H

#include "InventoryMenu.h"
#include "CharacterStats.h"

namespace RPG
{
	class CharacterInventoryMenu : public InventoryMenu
	{
	public:
		//Construtor
		CharacterInventoryMenu(const GPL::Point2D<float>& position);
	};
}

#endif
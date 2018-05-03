#ifndef CHESTMENU_H
#define CHESTMENU_H

#include "BaseChest.h"
#include "ChestInventoryMenu.h"
#include "CharacterMenu.h"

namespace RPG
{
	class ChestMenu : public CharacterMenu
	{
	public:
		//Construtor
		ChestMenu(BaseChest& base_chest);
	};
}

#endif
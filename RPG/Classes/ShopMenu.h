#ifndef SHOPMENU_H
#define SHOPMENU_H

#include "Shop.h"
#include "ShopInventoryMenu.h"
#include "CharacterMenu.h"

namespace RPG
{
	class ShopMenu : public CharacterMenu
	{
	public:
		//Construtor
		ShopMenu(Shop& shop);
	};
}

#endif
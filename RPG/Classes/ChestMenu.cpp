#include "ChestMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

ChestMenu::ChestMenu(BaseChest& base_chest) :
	CharacterMenu(false)
{
	this->AddSubGameState(make_unique<ChestInventoryMenu>(this->GetPosition(),base_chest.GetItems(),base_chest.GetMenuText(),base_chest.IsPrivateChest()));
}
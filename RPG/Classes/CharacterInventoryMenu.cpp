#include "CharacterInventoryMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

CharacterInventoryMenu::CharacterInventoryMenu(const Point2D<float>& position) :
	InventoryMenu(position,false)
{
	this->AddSubGameState(make_unique<CharacterStats>(position));
}
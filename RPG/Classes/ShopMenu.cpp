#include "ShopMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

ShopMenu::ShopMenu(Shop& shop) :
	CharacterMenu(false)
{
	ItemButton::SetShopping(true);
	this->AddSubGameState(make_unique<ShopInventoryMenu>(this->GetPosition(),shop.GetItems(),GameState::GetGame<GameRPG>().GetDatabase().GetLanguageText(shop.GetTextID())));
}
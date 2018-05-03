#include "PrivateChest.h"

using namespace std;
using namespace GPL;
using namespace RPG;

PrivateChest::PrivateChest(const ChestType chest_type) :
	BaseChest(chest_type),
	items(nullptr)
{

}

void PrivateChest::SetItems(vector<unique_ptr<Item>>& items)
{
	this->items = &items;
}

vector<unique_ptr<Item>>& PrivateChest::GetItems()
{
	return *this->items;
}

const string& PrivateChest::GetMenuText() const
{
	return BaseChest::GetDatabase().GetLanguageText(PrivateChestTextID);
}

bool PrivateChest::IsPrivateChest() const
{
	return true;
}
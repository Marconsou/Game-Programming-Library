#include "Chest.h"

using namespace std;
using namespace GPL;
using namespace RPG;

Chest::Chest(const ChestType chest_type) :
	BaseChest(chest_type)
{

}

void Chest::AddItem(const Item& item)
{
	this->items.push_back(make_unique<Item>());
	this->items.back()->Copy(item);
}

void Chest::AddItem(const ItemID item_id)
{
	this->AddItem(BaseChest::GetDatabase().GetItems(item_id));
}

void Chest::AddItems(const vector<unique_ptr<Item>>& items)
{
	for (size_t i = 0; i < items.size(); i++)
		this->AddItem(*items[i].get());
}

void Chest::AddItems(const vector<ItemID>& items)
{
	for (size_t i = 0; i < items.size(); i++)
		this->AddItem(items[i]);
}

vector<unique_ptr<Item>>& Chest::GetItems()
{
	return this->items;
}

const string& Chest::GetMenuText() const
{
	return BaseChest::GetDatabase().GetLanguageText(ChestTextID);
}

bool Chest::IsPrivateChest() const
{
	return false;
}
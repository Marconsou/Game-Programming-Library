#include "Shop.h"

using namespace std;
using namespace GPL;
using namespace RPG;

Shop::Shop(const LanguageTextID text_id) :
	text_id(text_id)
{

}

LanguageTextID Shop::GetTextID() const
{
	return this->text_id;
}

vector<unique_ptr<Item>>& Shop::GetItems()
{
	return this->items;
}

void Shop::AddItem(const Item& item)
{
	this->items.push_back(make_unique<Item>());
	this->items.back()->Copy(item);
}
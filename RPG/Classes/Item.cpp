#include "Item.h"

using namespace std;
using namespace RPG;

Item::Item(const ItemIcon icon) :
	source_item(nullptr),
	icon(icon),
	class_type(ItemClassEmpty),
	id(NullItemID),
	sell_price(0),
	find_chance(0),
	required_level(0),
	weight(0),
	hands(0)
{

}

void Item::SetName(const string& name)
{
	this->name = name;
}

const string& Item::GetName() const
{
	if (this->source_item)
		return this->source_item->name;
	return this->name;
}

void Item::SetDescription(const string& description)
{
	this->description = description;
}

const string& Item::GetDescription() const
{
	if (this->source_item)
		return this->source_item->description;
	return this->description;
}

void Item::SetIcon(const ItemIcon icon)
{
	this->icon = icon;
}

ItemIcon Item::GetIcon() const
{
	return this->icon;
}

void Item::SetClassType(const ItemClass class_type)
{
	this->class_type = class_type;
}

ItemClass Item::GetClassType() const
{
	return this->class_type;
}

void Item::SetID(const ItemID id)
{
	this->id = id;
}

ItemID Item::GetID() const
{
	return this->id;
}

void Item::SetSellPrice(const int sell_price)
{
	this->sell_price = sell_price;
}

int Item::GetSellPrice() const
{
	return this->sell_price;
}

int Item::GetBuyPrice() const
{
	return this->sell_price * 4;
}

void Item::SetFindChance(const int find_chance)
{
	this->find_chance = find_chance;
}

int Item::GetFindChance() const
{
	return this->find_chance;
}

void Item::SetRequiredLevel(const int required_level)
{
	this->required_level = required_level;
}

int Item::GetRequiredLevel() const
{
	return this->required_level;
}

void Item::SetWeight(const int weight)
{
	this->weight = weight;
}

int Item::GetWeight() const
{
	return this->weight;
}

void Item::SetHands(const int hands)
{
	this->hands = hands;
}

int Item::GetHands() const
{
	return this->hands;
}

StatsBasic& Item::GetStats()
{
	return this->stats;
}

Elemental& Item::GetElementalDamage()
{
	return this->elemental_damage;
}

Elemental& Item::GetElementalResist()
{
	return this->elemental_resist;
}

Elemental& Item::GetElementalAbsorb()
{
	return this->elemental_absorb;
}

StatusNegative& Item::GetStatusAttack()
{
	return this->status_attack;
}

StatusNegative& Item::GetStatusDefense()
{
	return this->status_defense;
}

StatusNegative& Item::GetStatusNegativeRecovery()
{
	return this->status_negative_recovery;
}

Ability& Item::GetAbility()
{
	return this->ability;
}

void Item::Swap(Item& item)
{
	static Item temporary_item;
	temporary_item.Copy(*this);
	this->Copy(item);
	item.Copy(temporary_item);
}

void Item::Receive(Item& item)
{
	this->Copy(item);
	item.Remove();
}

void Item::Copy(const Item& item)
{
	*this = item;

	//Se não for vazio
	if (!item.IsEmpty())
	{
		//Se o item tem um Source quer dizer que ele não é um item original do banco de dados
		if (item.source_item)
			this->source_item = item.source_item;

		//Item do banco de dados
		else
			this->source_item = &item;
	}
	else
		this->source_item = nullptr;
}

void Item::Remove()
{
	static const Item empty_item;
	this->Copy(empty_item);
}

bool Item::IsEmpty() const
{
	return (this->icon < ItemIconValidItem);
}

bool Item::IsUsable() const
{
	return (this->class_type == ItemClassUsable);
}

bool Item::IsQuestItem() const
{
	return (this->class_type == ItemClassQuestItem);
}

bool Item::IsEquipment() const
{
	return ((this->IsWeapon()) || (this->IsShield()) || (this->IsHelm()) || (this->IsArmor()) || (this->IsGloves()) || (this->IsBoots()) || (this->IsAccessory()));
}

bool Item::IsDagger() const
{
	return (this->class_type == ItemClassDagger);
}

bool Item::IsSword() const
{
	return (this->class_type == ItemClassSword);
}

bool Item::IsAxe() const
{
	return (this->class_type == ItemClassAxe);
}

bool Item::IsMace() const
{
	return (this->class_type == ItemClassMace);
}

bool Item::IsStaff() const
{
	return (this->class_type == ItemClassStaff);
}

bool Item::IsSpear() const
{
	return (this->class_type == ItemClassSpear);
}

bool Item::IsBow() const
{
	return (this->class_type == ItemClassBow);
}

bool Item::IsWeapon() const
{
	for (int i = ItemClassDagger; i <= ItemClassBow; i++)
	{
		if (this->class_type == i)
			return true;
	}
	return false;
}

bool Item::IsShield() const
{
	return (this->class_type == ItemClassShield);
}

bool Item::IsHelm() const
{
	return (this->class_type == ItemClassHelm);
}

bool Item::IsArmor() const
{
	return (this->class_type == ItemClassArmor);
}

bool Item::IsGloves() const
{
	return (this->class_type == ItemClassGloves);
}

bool Item::IsBoots() const
{
	return (this->class_type == ItemClassBoots);
}

bool Item::IsAccessory() const
{
	return (this->class_type == ItemClassAccessory);
}

bool Item::IsOneHandedWeapon() const
{
	return ((this->IsWeapon()) && (this->hands == 1));
}

bool Item::IsTwoHandedWeapon() const
{
	return ((this->IsWeapon()) && (this->hands == 2));
}

bool Item::IsMeleeWeapon() const
{
	return ((!this->IsMissileWeapon()) && (this->IsWeapon()));
}

bool Item::IsMissileWeapon() const
{
	return this->IsBow();
}

bool Item::CheckRequirement(const int level) const
{
	return (this->required_level <= level);
}
#include "Hero.h"

using namespace std;
using namespace GPL;
using namespace RPG;

Hero::Hero(const int strength_hp_max_up,const int intelligence_mp_max_up,const int base_hit,const int agility_hit,const int base_evade,const int agility_evade,const int agility_speed,const int base_critical_strike,const bool dual_weapon) :
	dual_weapon(dual_weapon),
	ap(0),
	sp(0),
	strength(0),
	intelligence(0),
	agility(0),
	exp(0),
	next_level(0),
	physical_damage_min_secondary(0),
	physical_damage_max_secondary(0),
	hit_secondary(0),
	critical_strike_secondary(0),
	quick_strike_secondary(0),
	hp_steal_secondary(0),
	mp_steal_secondary(0),
	strength_hp_max_up(strength_hp_max_up),
	intelligence_mp_max_up(intelligence_mp_max_up),
	base_hit(base_hit),
	agility_hit(agility_hit),
	base_evade(base_evade),
	agility_evade(agility_evade),
	agility_speed(agility_speed),
	base_critical_strike(base_critical_strike),
	movement(HeroMovementSpeedSlow),
	discard_item(ItemIconDiscard),
	inventory(35),
	equipments(8),
	battle_items(10),
	private_chest(100),
	skills(1),
	character(make_shared<Character>(false,true))
{
	///
	this->exp = 4600;
	this->agility = 10;
	this->GetStats().SetGold(100);
	///

	this->picked_item_icon.SetSize(32.0f,32.0f);

	for (size_t i = 0; i < this->inventory.size(); i++)
		this->inventory[i] = make_unique<Item>();

	for (size_t i = 0; i < this->equipments.size(); i++)
	{
		this->equipments[i] = make_unique<Item>();
		this->equipments[i]->SetIcon(static_cast<ItemIcon>(i + ItemIconRightHand));
	}

	for (size_t i = 0; i < this->battle_items.size(); i++)
		this->battle_items[i] = make_unique<Item>();

	for (size_t i = 0; i < this->private_chest.size(); i++)
		this->private_chest[i] = make_unique<Item>();

	Timer::AddSubTimer(this->play_time);
}

Hero::~Hero()
{
	Timer::RemoveSubTimer(this->play_time);
}

bool Hero::GetDualWeapon() const
{
	return this->dual_weapon;
}

int Hero::GetAP() const
{
	return this->ap;
}

int Hero::GetSP() const
{
	return this->sp;
}

int Hero::GetStrength() const
{
	return this->strength;
}

int Hero::GetIntelligence() const
{
	return this->intelligence;
}

int Hero::GetAgility() const
{
	return this->agility;
}

void Hero::SetExp(const int exp)
{
	this->exp = exp;
}

int Hero::GetExp() const
{
	return this->exp;
}

void Hero::SetNextLevel(const int next_level)
{
	this->next_level = next_level;
}

int Hero::GetNextLevel() const
{
	return this->next_level;
}

void Hero::SetPhysicalDamageMinSecondary(const int physical_damage_min_secondary)
{
	this->physical_damage_min_secondary = physical_damage_min_secondary;
}

int Hero::GetPhysicalDamageMinSecondary() const
{
	return this->physical_damage_min_secondary;
}

void Hero::SetPhysicalDamageMaxSecondary(const int physical_damage_max_secondary)	
{
	this->physical_damage_max_secondary = physical_damage_max_secondary;
}

int Hero::GetPhysicalDamageMaxSecondary() const
{
	return this->physical_damage_max_secondary;
}

void Hero::SetHitSecondary(const int hit_secondary)
{
	this->hit_secondary = hit_secondary;
}

int Hero::GetHitSecondary() const
{
	return this->hit_secondary;
}

void Hero::SetCriticalStrikeSecondary(const int critical_strike_secondary)
{
	this->critical_strike_secondary = critical_strike_secondary;
}

int Hero::GetCriticalStrikeSecondary() const
{
	return this->critical_strike_secondary;
}

void Hero::SetQuickStrikeSecondary(const int quick_strike_secondary)
{
	this->quick_strike_secondary = quick_strike_secondary;
}

int Hero::GetQuickStrikeSecondary() const
{
	return this->quick_strike_secondary;
}

void Hero::SetHPStealSecondary(const int hp_steal_secondary)
{
	this->hp_steal_secondary = hp_steal_secondary;
}

int Hero::GetHPStealSecondary() const
{
	return this->hp_steal_secondary;
}

void Hero::SetMPStealSecondary(const int mp_steal_secondary)
{
	this->mp_steal_secondary = mp_steal_secondary;
}

int Hero::GetMPStealSecondary() const
{
	return this->mp_steal_secondary;
}

HeroMovement Hero::GetMovement() const
{
	return this->movement;
}

Elemental& Hero::GetElementalDamageSecondary()
{
	return this->elemental_damage_secondary; 
}

StatusNegative& Hero::GetStatusAttackSecondary()
{
	return this->status_attack_secondary;
}

Stats& Hero::GetStats()
{
	return this->stats;
}

Ability& Hero::GetAbility()
{
	return this->ability;
}

Sprite& Hero::GetPickedItemIcon()
{
	return this->picked_item_icon;
}

Item& Hero::GetPickedItem()
{
	return this->picked_item;
}

Item& Hero::GetDiscardItem()
{
	return this->discard_item;
}

vector<unique_ptr<Item>>& Hero::GetInventory()
{
	return this->inventory;
}

vector<unique_ptr<Item>>& Hero::GetEquipments()
{
	return this->equipments;
}

vector<unique_ptr<Item>>& Hero::GetBattleItems()
{
	return this->battle_items;
}

vector<unique_ptr<Item>>& Hero::GetPrivateChest()
{
	return this->private_chest;
}

vector<unique_ptr<Skill>>& Hero::GetSkills()
{
	return this->skills;
}

vector<Quest>& Hero::GetMainQuests()
{
	return this->main_quests;
}

vector<Quest>& Hero::GetOptionalQuests()
{
	return this->optional_quests;
}

vector<Achievement>& Hero::GetAchievements()
{
	return this->achievements;
}

MapDataState& Hero::GetMapDataState()
{
	return this->map_data_state;
}

shared_ptr<Character>& Hero::GetCharacter()
{
	return this->character;
}

Timer& Hero::GetPlayTime()
{
	return this->play_time;
}

void Hero::AddStrength()
{
	this->strength++;
	this->ap--;
}

void Hero::AddIntelligence()
{
	this->intelligence++;
	this->ap--;
}

void Hero::AddAgility()
{
	this->agility++;
	this->ap--;
}

void Hero::SpendSP()
{
	this->sp--;
}

int Hero::CalculateExp(const int level) const
{
	return ((level + 1) * level * 50);
}

int Hero::CalculatePreviousExp() const
{
	return this->CalculateExp(this->stats.GetLevel() - 1);
}

void Hero::LevelUp()
{
	this->ap += 3;
	this->sp++;
	this->stats.SetLevel(this->stats.GetLevel() + 1);
	this->next_level = this->CalculateExp(this->stats.GetLevel());
}

bool Hero::CheckAndLevelUp()
{
	if (this->exp >= this->next_level)
	{
		this->LevelUp();
		return true;
	}
	return false;
}

bool Hero::AddItemToInventory(const Item& item)
{
	for (size_t i = 0; i < this->inventory.size(); i++)
	{
		Item& iterator = *this->inventory[i];

		if (iterator.IsEmpty())
		{
			iterator.Copy(item);
			return true;
		}
	}
	return false;
}

bool Hero::AddItemToBattleItems(const Item& item)
{
	for (size_t i = 0; i < this->battle_items.size(); i++)
	{
		Item& iterator = *this->battle_items[i];

		if ((iterator.IsEmpty()) && (item.IsUsable()))
		{
			iterator.Copy(item);
			return true;
		}
	}
	return false;
}

bool Hero::InventoryIsNotFull() const
{
	for (size_t i = 0; i < this->inventory.size(); i++)
	{
		if (this->inventory[i]->IsEmpty())
			return true;
	}
	return false;
}

bool Hero::ItemRequirementNotMet(const Item& item) const
{
	return (item.GetRequiredLevel() > this->stats.GetLevel());
}

bool Hero::PickedItemRequirementNotMet() const
{
	return this->ItemRequirementNotMet(this->picked_item);
}

bool Hero::SkillRequirementNotMet(const Skill& skill) const
{
	return (skill.GetRequiredLevel() > this->stats.GetLevel());
}

bool Hero::GoldEnoughToBuy(const Item& item) const
{
	return (this->stats.GetGold() >= item.GetBuyPrice());
}

bool Hero::BuyItemFromShop(const Item& item)
{
	//Se não item vazio e tiver dinheiro suficiente
	if ((!item.IsEmpty()) && (this->GoldEnoughToBuy(item)))
	{
		//Se não tiver espaço no inventário ou se for Usable para tentar colocar nos itens de batalha
		if ((this->AddItemToInventory(item)) || (((item.IsUsable()) && (this->AddItemToBattleItems(item)))))
		{
			this->stats.SetGold(this->stats.GetGold() - item.GetBuyPrice());
			return true;
		}
	}
	return false;
}

bool Hero::SellItemToShop(Item& item)
{
	//Se não item vazio e nem for Quest Item
	if ((!item.IsEmpty()) && (!item.IsQuestItem()))
	{
		this->stats.SetGold(this->stats.GetGold() + item.GetSellPrice());
		item.Remove();
		return true;
	}
	return false;
}

bool Hero::CanEquipPickedItemOnHand(const bool is_left_hand) const
{
	bool can_equip = false;

	Item* current_hand = this->equipments[EquipmentSlotRightHand].get();
	Item* other_hand = this->equipments[EquipmentSlotLeftHand].get();

	if (is_left_hand)
	{
		Item* item = current_hand;
		current_hand = other_hand;
		other_hand = item;
	}

	//Equipando arma de uma mão
	if (!this->dual_weapon)
	{
		//Ao equipar uma arma de uma mão então a outra mão só pode estar vazia ou ser um escudo
		can_equip = ((this->picked_item.IsOneHandedWeapon()) && ((other_hand->IsShield()) || (other_hand->IsEmpty())));
	}
	else
	{
		//Ao equipar uma arma de uma mão então a outra mão só pode estar vazia ou ser um escudo ou uma arma
		can_equip = ((this->picked_item.IsOneHandedWeapon()) && ((other_hand->IsShield()) || (other_hand->IsEmpty()) || (other_hand->IsWeapon())));
	}

	//Equipando uma arma de duas mãos com a atual sendo vazia
	if (!can_equip)
		can_equip = ((this->picked_item.IsTwoHandedWeapon()) && (current_hand->IsEmpty()));

	//Equipando uma arma de duas mãos com a atual tendo equipamento então a outra deve ser vazia
	if (!can_equip)
		can_equip = ((this->picked_item.IsTwoHandedWeapon()) && (!current_hand->IsEmpty()) && (other_hand->IsEmpty()));

	//Equipar um escudo a outra mão não pode ser outro escudo
	if (!can_equip)
		can_equip = ((this->picked_item.IsShield()) && (!other_hand->IsShield()));

	return can_equip;
}

bool Hero::TwoHandsAttack() const
{
	const Item& right_hand = *this->equipments[EquipmentSlotRightHand];
	const Item& left_hand = *this->equipments[EquipmentSlotLeftHand];

	return ((!right_hand.IsTwoHandedWeapon()) && ((right_hand.IsEmpty()) || (right_hand.IsWeapon())) && ((left_hand.IsEmpty()) || (left_hand.IsWeapon())));
}

bool Hero::IsWarrior() const
{
	return this->GetClassType() == HeroClassWarrior;
}

bool Hero::IsMage() const
{
	return this->GetClassType() == HeroClassMage;
}

void Hero::CharacterStatsUpdate()
{
	StatsBasic& stats_basic = stats.GetStatsBasic();

	//Level & Next Level
	this->CheckAndLevelUp();

	//HP Max
	stats_basic.SetHPMax(this->AddEquipmentValue(&Item::GetStats,&StatsBasic::GetHPMax,false,(this->strength * this->strength_hp_max_up) + ((this->stats.GetLevel() - 1))));

	//MP Max
	stats_basic.SetMPMax(this->AddEquipmentValue(&Item::GetStats,&StatsBasic::GetMPMax,false,(this->intelligence * this->intelligence_mp_max_up) + ((this->stats.GetLevel() - 1))));

	//HP
	stats_basic.SetHP(max(min(stats_basic.GetHP(),stats_basic.GetHPMax()),0));

	//MP
	stats_basic.SetMP(max(min(stats_basic.GetMP(),stats_basic.GetMPMax()),0));

	//Physical Damage Min
	int value = 0;
	int value_secondary = 0;
	this->CalculateOffensiveStats(&Item::GetStats,&StatsBasic::GetPhysicalDamageMin,value,value_secondary,true); stats_basic.SetPhysicalDamageMin(value); this->SetPhysicalDamageMinSecondary(value_secondary);

	//Physical Damage Max
	this->CalculateOffensiveStats(&Item::GetStats,&StatsBasic::GetPhysicalDamageMax,value,value_secondary,true); stats_basic.SetPhysicalDamageMax(value); this->SetPhysicalDamageMaxSecondary(value_secondary);

	//Physical Damage
	bool left_hand_update = false;
	const int empty_hand_damage_min = this->strength / 2;
	const int empty_hand_damage_max = (this->strength + this->stats.GetLevel()) / 2;
	const int weapon_equipped_damage_min = (this->strength / 10) + 1;
	const int weapon_equipped_damage_max = (this->strength / 100) + 1;
	const Item& right_hand = *this->equipments[EquipmentSlotRightHand];
	const Item& left_hand = *this->equipments[EquipmentSlotLeftHand];

	//Empty Hand Damage
	if (right_hand.IsEmpty())
	{
		stats_basic.SetPhysicalDamageMin(stats_basic.GetPhysicalDamageMin() + empty_hand_damage_min);
		stats_basic.SetPhysicalDamageMax(stats_basic.GetPhysicalDamageMax() + empty_hand_damage_max);
		left_hand_update = true;
	}
	else if (right_hand.IsWeapon())
	{
		stats_basic.SetPhysicalDamageMin(stats_basic.GetPhysicalDamageMin() + weapon_equipped_damage_min);
		stats_basic.SetPhysicalDamageMax(stats_basic.GetPhysicalDamageMax() + weapon_equipped_damage_max);
		left_hand_update = true;
	}
	else if (right_hand.IsShield())
	{
		if (left_hand.IsEmpty())
		{
			stats_basic.SetPhysicalDamageMin(stats_basic.GetPhysicalDamageMin() + empty_hand_damage_min);
			stats_basic.SetPhysicalDamageMax(stats_basic.GetPhysicalDamageMax() + empty_hand_damage_max);
		}
		else if (left_hand.IsWeapon())
		{
			stats_basic.SetPhysicalDamageMin(stats_basic.GetPhysicalDamageMin() + weapon_equipped_damage_min);
			stats_basic.SetPhysicalDamageMax(stats_basic.GetPhysicalDamageMax() + weapon_equipped_damage_max);
		}
	}
	if (left_hand_update)
	{
		if (left_hand.IsEmpty())
		{
			this->physical_damage_min_secondary += empty_hand_damage_min;
			this->physical_damage_max_secondary += empty_hand_damage_max;
		}
		else if (left_hand.IsWeapon())
		{
			this->physical_damage_min_secondary += weapon_equipped_damage_min;
			this->physical_damage_max_secondary += weapon_equipped_damage_max;
		}
	}

	//Physical Resist
	stats_basic.SetPhysicalResist(this->AddEquipmentValue(&Item::GetStats,&StatsBasic::GetPhysicalResist,true));

	//Magical Damage Min
	stats_basic.SetMagicalDamageMin(this->AddEquipmentValue(&Item::GetStats,&StatsBasic::GetMagicalDamageMin,false,(this->intelligence / 2) + 1));

	//Magical Damage Max
	stats_basic.SetMagicalDamageMax(this->AddEquipmentValue(&Item::GetStats,&StatsBasic::GetMagicalDamageMax,false,((this->intelligence + this->stats.GetLevel()) / 2) + 2));

	//Magical Resist
	stats_basic.SetMagicalResist(this->AddEquipmentValue(&Item::GetStats,&StatsBasic::GetMagicalResist,true));

	//Hit
	this->CalculateOffensiveStats(&Item::GetStats,&StatsBasic::GetHit,value,value_secondary,true,this->base_hit + (this->agility / this->agility_hit)); stats_basic.SetHit(value);	this->SetHitSecondary(value_secondary);

	//Evade
	stats_basic.SetEvade(this->AddEquipmentValue(&Item::GetStats,&StatsBasic::GetEvade,true,this->base_evade + (this->agility / this->agility_evade)));

	//Elemental Effect
	stats_basic.SetElementalEffect(this->CheckEquipmentValue(&Item::GetStats,&StatsBasic::GetElementalEffect));

	//Elemental Damage
	this->CalculateOffensiveStats(&Item::GetElementalDamage,&Elemental::GetFire,value,value_secondary); this->stats.GetElementalDamage().SetFire(value); this->GetElementalDamageSecondary().SetFire(value_secondary);
	this->CalculateOffensiveStats(&Item::GetElementalDamage,&Elemental::GetIce,value,value_secondary); this->stats.GetElementalDamage().SetIce(value); this->GetElementalDamageSecondary().SetIce(value_secondary);
	this->CalculateOffensiveStats(&Item::GetElementalDamage,&Elemental::GetLightning,value,value_secondary); this->stats.GetElementalDamage().SetLightning(value); this->GetElementalDamageSecondary().SetLightning(value_secondary);
	this->CalculateOffensiveStats(&Item::GetElementalDamage,&Elemental::GetLight,value,value_secondary); this->stats.GetElementalDamage().SetLight(value); this->GetElementalDamageSecondary().SetLight(value_secondary);
	this->CalculateOffensiveStats(&Item::GetElementalDamage,&Elemental::GetDark,value,value_secondary); this->stats.GetElementalDamage().SetDark(value); this->GetElementalDamageSecondary().SetDark(value_secondary);

	//Elemental Resist
	Elemental& elemental_resist = this->stats.GetElementalResist();

	elemental_resist.SetFire(this->AddEquipmentValue(&Item::GetElementalResist,&Elemental::GetFire,true));
	elemental_resist.SetIce(this->AddEquipmentValue(&Item::GetElementalResist,&Elemental::GetIce,true));
	elemental_resist.SetLightning(this->AddEquipmentValue(&Item::GetElementalResist,&Elemental::GetLightning,true));
	elemental_resist.SetLight(this->AddEquipmentValue(&Item::GetElementalResist,&Elemental::GetLight,true));
	elemental_resist.SetDark(this->AddEquipmentValue(&Item::GetElementalResist,&Elemental::GetDark,true));

	//Elemental Absorb
	Elemental& elemental_absorb = this->stats.GetElementalAbsorb();

	elemental_absorb.SetFire(this->AddEquipmentValue(&Item::GetElementalAbsorb,&Elemental::GetFire,true));
	elemental_absorb.SetIce(this->AddEquipmentValue(&Item::GetElementalAbsorb,&Elemental::GetIce,true));
	elemental_absorb.SetLightning(this->AddEquipmentValue(&Item::GetElementalAbsorb,&Elemental::GetLightning,true));
	elemental_absorb.SetLight(this->AddEquipmentValue(&Item::GetElementalAbsorb,&Elemental::GetLight,true));
	elemental_absorb.SetDark(this->AddEquipmentValue(&Item::GetElementalAbsorb,&Elemental::GetDark,true));

	//Status Effect
	stats_basic.SetStatusEffect(this->CheckEquipmentValue<StatsBasic>(&Item::GetStats,&StatsBasic::GetStatusEffect));

	//Status Attack
	this->CalculateOffensiveStats(&Item::GetStatusAttack,&StatusNegative::GetWound,value,value_secondary,true); this->stats.GetStatusAttack().SetWound(value); this->GetStatusAttackSecondary().SetWound(value_secondary);
	this->CalculateOffensiveStats(&Item::GetStatusAttack,&StatusNegative::GetSlowness,value,value_secondary,true); this->stats.GetStatusAttack().SetSlowness(value); this->GetStatusAttackSecondary().SetSlowness(value_secondary);
	this->CalculateOffensiveStats(&Item::GetStatusAttack,&StatusNegative::GetTiredness,value,value_secondary,true); this->stats.GetStatusAttack().SetTiredness(value); this->GetStatusAttackSecondary().SetTiredness(value_secondary);
	this->CalculateOffensiveStats(&Item::GetStatusAttack,&StatusNegative::GetHeadache,value,value_secondary,true); this->stats.GetStatusAttack().SetHeadache(value); this->GetStatusAttackSecondary().SetHeadache(value_secondary);
	this->CalculateOffensiveStats(&Item::GetStatusAttack,&StatusNegative::GetBlindness,value,value_secondary,true); this->stats.GetStatusAttack().SetBlindness(value); this->GetStatusAttackSecondary().SetBlindness(value_secondary);

	//Status Defense
	StatusNegative& status_defense = this->stats.GetStatusDefense();

	status_defense.SetWound(this->AddEquipmentValue(&Item::GetStatusDefense,&StatusNegative::GetWound,true));
	status_defense.SetSlowness(this->AddEquipmentValue(&Item::GetStatusDefense,&StatusNegative::GetSlowness,true));
	status_defense.SetTiredness(this->AddEquipmentValue(&Item::GetStatusDefense,&StatusNegative::GetTiredness,true));
	status_defense.SetHeadache(this->AddEquipmentValue(&Item::GetStatusDefense,&StatusNegative::GetHeadache,true));
	status_defense.SetBlindness(this->AddEquipmentValue(&Item::GetStatusDefense,&StatusNegative::GetBlindness,true));

	//Natural Skills
	this->CalculateOffensiveStats(&Item::GetStats,&StatsBasic::GetCriticalStrike,value,value_secondary,true,0,this->base_critical_strike); stats_basic.SetCriticalStrike(value); this->SetCriticalStrikeSecondary(value_secondary);
	this->CalculateOffensiveStats(&Item::GetStats,&StatsBasic::GetQuickStrike,value,value_secondary,true); stats_basic.SetQuickStrike(value); this->SetQuickStrikeSecondary(value_secondary);
	stats_basic.SetCounterStrike(this->AddEquipmentValue(&Item::GetStats,&StatsBasic::GetCounterStrike,true));
	this->CalculateOffensiveStats(&Item::GetStats,&StatsBasic::GetHPSteal,value,value_secondary,true); stats_basic.SetHPSteal(value); this->SetHPStealSecondary(value_secondary);
	this->CalculateOffensiveStats(&Item::GetStats,&StatsBasic::GetMPSteal,value,value_secondary,true); stats_basic.SetMPSteal(value); this->SetMPStealSecondary(value_secondary);
	stats_basic.SetHPRegen(this->AddEquipmentValue(&Item::GetStats,&StatsBasic::GetHPRegen));
	stats_basic.SetMPRegen(this->AddEquipmentValue(&Item::GetStats,&StatsBasic::GetMPRegen));

	//Abilities
	this->ability.SetAnalyzer(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetAnalyzer));
	this->ability.SetTrainer(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetTrainer));
	this->ability.SetBounty(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetBounty));
	this->ability.SetCustomer(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetCustomer));
	this->ability.SetCoward(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetCoward));
	this->ability.SetBrave(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetBrave));
	this->ability.SetRunner(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetRunner));
	this->ability.SetSkinSlicer(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetSkinSlicer));
	this->ability.SetBoneCrusher(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetBoneCrusher));
	this->ability.SetShellDriller(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetShellDriller));
	this->ability.SetHumanEater(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetHumanEater));
	this->ability.SetBeastKiller(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetBeastKiller));
	this->ability.SetUndeadPurifier(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetUndeadPurifier));
	this->ability.SetDemonHunter(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetDemonHunter));
	this->ability.SetDragonSlayer(this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetDragonSlayer));

	//Atualizar as estatísticas únicas da classe do herói, após todas as outras
	this->UniqueStatsUpdate();

	//Movement
	this->HeroMovementStatsUpdate();
}

void Hero::HeroMovementStatsUpdate(int movement)
{
	StatsBasic& stats_basic = stats.GetStatsBasic();

	//Speed
	stats_basic.SetSpeed(this->AddEquipmentValue(&Item::GetStats,&StatsBasic::GetSpeed,false,this->agility * this->agility_speed));

	for (size_t i = 0; i < this->equipments.size(); i++)
		stats_basic.SetSpeed(stats_basic.GetSpeed() - this->equipments[i]->GetWeight());
	stats_basic.SetSpeed(max(stats_basic.GetSpeed(),1));

	//Aumentar um nível do movimento se tiver a habilidade
	if (this->CheckEquipmentValue(&Item::GetAbility,&Ability::GetRunner))
		movement++;

	//Diminuir um nível do movimento se tiver pouca velocidade
	if (stats_basic.GetSpeed() <= 1)
		movement--;

	//Atualizando o estado movimento final
	this->movement = static_cast<HeroMovement>(movement);

	//Slow
	if (movement == HeroMovementSpeedSlow)
		this->character->MovementSpeedSlow();

	//Normal
	else if (movement == HeroMovementSpeedNormal)
		this->character->MovementSpeedNormal();

	//Fast
	else if (movement == HeroMovementSpeedFast)
		this->character->MovementSpeedFast();
}
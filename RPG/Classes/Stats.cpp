#include "Stats.h"

using namespace std;
using namespace RPG;

Stats::Stats() :
	level(0),
	gold(0)
{

}

void Stats::SetName(const string& name)
{
	this->name = name;
}

const string& Stats::GetName() const
{
	return this->name;
}

void Stats::SetLevel(const int level)
{
	this->level = level;
}

int Stats::GetLevel() const
{
	return this->level;
}

void Stats::SetGold(const int gold)
{
	this->gold = gold;
}

int Stats::GetGold() const
{
	return this->gold;
}

StatsBasic& Stats::GetStatsBasic()
{
	return this->stats_basic;
}

Elemental& Stats::GetElementalDamage()
{
	return this->elemental_damage;
}

Elemental& Stats::GetElementalResist()
{
	return this->elemental_resist;
}

Elemental& Stats::GetElementalAbsorb()
{
	return this->elemental_absorb;
}

StatusNegative& Stats::GetStatusAttack()
{
	return this->status_attack;
}

StatusNegative& Stats::GetStatusDefense()
{
	return this->status_defense;
}

StatusNegative& Stats::GetStatusNegativeChange()
{
	return this->status_negative_change;
}
#include "SkillLevel.h"

using namespace RPG;

SkillLevel::SkillLevel() :
action_time(100),
physical_damage_percentage(0),
magical_damage_percentage(0)
{

}

void SkillLevel::SetActionTime(const int action_time)
{
	this->action_time = action_time;
}

int SkillLevel::GetActionTime() const
{
	return this->action_time;
}

void SkillLevel::SetPhysicalDamagePercentage(const int physical_damage_percentage)
{
	this->physical_damage_percentage = physical_damage_percentage;
}

int SkillLevel::GetPhysicalDamagePercentage() const
{
	return this->physical_damage_percentage;
}

void SkillLevel::SetMagicalDamagePercentage(const int magical_damage_percentage)
{
	this->magical_damage_percentage = magical_damage_percentage;
}

int SkillLevel::GetMagicalDamagePercentage() const
{
	return this->magical_damage_percentage;
}

StatsBasic& SkillLevel::GetStatsBasic()
{
	return this->stats_basic;
}

const StatsBasic& SkillLevel::GetStatsBasic() const
{
	return this->stats_basic;
}

Elemental& SkillLevel::GetElementalDamageMin()
{
	return this->elemental_damage_min;
}

Elemental& SkillLevel::GetElementalDamageMax()
{
	return this->elemental_damage_max;
}

Elemental& SkillLevel::GetElementalDamagePercentage()
{
	return this->elemental_damage_percentage;
}

Elemental& SkillLevel::GetElementalDamageBonusLimit()
{
	return this->elemental_damage_bonus_limit;
}

Elemental& SkillLevel::GetElementalResist()
{
	return this->elemental_resist;
}

Elemental& SkillLevel::GetElementalAbsorb()
{
	return this->elemental_absorb;
}

StatusNegative& SkillLevel::GetStatusAttack()
{
	return this->status_attack;
}

StatusNegative& SkillLevel::GetStatusAttackBonusLimit()
{
	return this->status_attack_bonus_limit;
}

StatusNegative& SkillLevel::GetStatusDefense()
{
	return this->status_defense;
}

StatusNegative& SkillLevel::GetStatusChange()
{
	return this->status_change;
}
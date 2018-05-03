#include "StatsBasic.h"

using namespace RPG;

StatsBasic::StatsBasic() :
	elemental_effect(false),
	status_effect(false),
	hp(0),
	mp(0),
	hp_max(0),
	mp_max(0),
	physical_damage_min(0),
	physical_damage_max(0),
	magical_damage_min(0),
	magical_damage_max(0),
	physical_resist(0),
	magical_resist(0),
	hit(0),
	evade(0),
	speed(0),
	critical_strike(0),
	quick_strike(0),
	counter_strike(0),
	hp_steal(0),
	mp_steal(0),
	hp_regen(0),
	mp_regen(0)
{

}

void StatsBasic::SetElementalEffect(const bool elemental_effect)
{
	this->elemental_effect = elemental_effect;
}

bool StatsBasic::GetElementalEffect() const
{
	return this->elemental_effect;
}

void StatsBasic::SetStatusEffect(const bool status_effect)
{
	this->status_effect = status_effect;
}

bool StatsBasic::GetStatusEffect() const
{
	return this->status_effect;
}

void StatsBasic::SetHP(const int hp)
{
	this->hp = hp;
}

int StatsBasic::GetHP() const
{
	return this->hp;
}

void StatsBasic::SetMP(const int mp)
{
	this->mp = mp;
}

int StatsBasic::GetMP() const
{
	return this->mp;
}

void StatsBasic::SetHPMax(const int hp_max)
{
	this->hp_max = hp_max;
}

int StatsBasic::GetHPMax() const
{
	return this->hp_max;
}

void StatsBasic::SetMPMax(const int mp_max)
{
	this->mp_max = mp_max;
}

int StatsBasic::GetMPMax() const
{
	return this->mp_max;
}

void StatsBasic::SetPhysicalDamageMin(const int physical_damage_min)
{
	this->physical_damage_min = physical_damage_min;
}

int StatsBasic::GetPhysicalDamageMin() const
{
	return this->physical_damage_min;
}

void StatsBasic::SetPhysicalDamageMax(const int physical_damage_max)
{
	this->physical_damage_max = physical_damage_max;
}

int StatsBasic::GetPhysicalDamageMax() const
{
	return this->physical_damage_max;
}

void StatsBasic::SetMagicalDamageMin(const int magical_damage_min)
{
	this->magical_damage_min = magical_damage_min;
}

int StatsBasic::GetMagicalDamageMin() const
{
	return this->magical_damage_min;
}

void StatsBasic::SetMagicalDamageMax(const int magical_damage_max)
{
	this->magical_damage_max = magical_damage_max;
}

int StatsBasic::GetMagicalDamageMax() const
{
	return this->magical_damage_max;
}

void StatsBasic::SetPhysicalResist(const int physical_resist)
{
	this->physical_resist = physical_resist;
}

int StatsBasic::GetPhysicalResist() const
{
	return this->physical_resist;
}

void StatsBasic::SetMagicalResist(const int magical_resist)
{
	this->magical_resist = magical_resist;
}

int StatsBasic::GetMagicalResist() const
{
	return this->magical_resist;
}

void StatsBasic::SetHit(const int hit)
{
	this->hit = hit;
}

int StatsBasic::GetHit() const
{
	return this->hit;
}

void StatsBasic::SetEvade(const int evade)
{
	this->evade = evade;
}

int StatsBasic::GetEvade() const
{
	return this->evade;
}

void StatsBasic::SetSpeed(const int speed)
{
	this->speed = speed;
}

int StatsBasic::GetSpeed() const
{
	return this->speed;
}

void StatsBasic::SetCriticalStrike(const int critical_strike)
{
	this->critical_strike = critical_strike;
}

int StatsBasic::GetCriticalStrike() const
{
	return this->critical_strike;
}

void StatsBasic::SetQuickStrike(const int quick_strike)
{
	this->quick_strike = quick_strike;
}

int StatsBasic::GetQuickStrike() const
{
	return this->quick_strike;
}

void StatsBasic::SetCounterStrike(const int counter_strike)
{
	this->counter_strike = counter_strike;
}

int StatsBasic::GetCounterStrike() const
{
	return this->counter_strike;
}

void StatsBasic::SetHPSteal(const int hp_steal)
{
	this->hp_steal = hp_steal;
}

int StatsBasic::GetHPSteal() const
{
	return this->hp_steal;
}

void StatsBasic::SetMPSteal(const int mp_steal)
{
	this->mp_steal = mp_steal;
}

int StatsBasic::GetMPSteal() const
{
	return this->mp_steal;
}

void StatsBasic::SetHPRegen(const int hp_regen)
{
	this->hp_regen = hp_regen;
}

int StatsBasic::GetHPRegen() const
{
	return this->hp_regen;
}

void StatsBasic::SetMPRegen(const int mp_regen)
{
	this->mp_regen = mp_regen;
}

int StatsBasic::GetMPRegen() const
{
	return this->mp_regen;
}
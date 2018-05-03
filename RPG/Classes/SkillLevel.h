#ifndef SKILLLEVEL_H
#define SKILLLEVEL_H

#include "StatsBasic.h"
#include "Elemental.h"
#include "StatusNegative.h"

namespace RPG
{
	class SkillLevel
	{
	private:
		//Custo do tempo de ação da habilidade
		int action_time;

		//Dano físico baseado em porcentagem
		int physical_damage_percentage;

		//Dano mágico baseado em porcentagem
		int magical_damage_percentage;

		//Atributos básicos
		StatsBasic stats_basic;

		//Dano elemental mínimo
		Elemental elemental_damage_min;

		//Dano elemental máximo
		Elemental elemental_damage_max;

		//Dano elemental baseado em porcentagem
		Elemental elemental_damage_percentage;

		//Dano elemental limite do bonus
		Elemental elemental_damage_bonus_limit;

		//Resistência elemental
		Elemental elemental_resist;

		//Absorção elemental
		Elemental elemental_absorb;

		//Chance de mudança de estado no ataque
		StatusNegative status_attack;

		//Chance de mudança de estado no ataque limite do bonus
		StatusNegative status_attack_bonus_limit;

		//Chance de mudança de estado na defesa
		StatusNegative status_defense;

		//Mudanca de estado
		StatusNegative status_change;
	public:
		//Construtor
		SkillLevel();

		//Alterar Action Time
		void SetActionTime(const int action_time);

		//Pegar Action Time
		int GetActionTime() const;

		//Alterar Physical Damage Percentage
		void SetPhysicalDamagePercentage(const int physical_damage_percentage);

		//Pegar Physical Damage Percentage
		int GetPhysicalDamagePercentage() const;

		//Alterar Magical Damage Percentage
		void SetMagicalDamagePercentage(const int magical_damage_percentage);

		//Pegar Magical Damage Percentage
		int GetMagicalDamagePercentage() const;

		//Pegar Stats Basic
		StatsBasic& GetStatsBasic();


		const StatsBasic& GetStatsBasic() const;

		//Pegar Elemental Damage Min
		Elemental& GetElementalDamageMin();

		//Pegar Elemental Damage Max
		Elemental& GetElementalDamageMax();

		//Pegar Elemental Damage Percentage
		Elemental& GetElementalDamagePercentage();

		//Pegar Elemental Damage Bonus Limit
		Elemental& GetElementalDamageBonusLimit();

		//Pegar Elemental Resist
		Elemental& GetElementalResist();

		//Pegar Elemental Absorb
		Elemental& GetElementalAbsorb();

		//Pegar Status Attack
		StatusNegative& GetStatusAttack();

		//Pegar Status Attack Bonus Limit
		StatusNegative& GetStatusAttackBonusLimit();

		//Pegar Status Defense
		StatusNegative& GetStatusDefense();

		//Pegar Status Change
		StatusNegative& GetStatusChange();
	};
}

#endif
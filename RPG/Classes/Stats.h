#ifndef STATS_H
#define STATS_H

#include <string>
#include "StatsBasic.h"
#include "Elemental.h"
#include "StatusNegative.h"
#include "Ability.h"

namespace RPG
{
	class Stats
	{
	private:
		//Nome
		std::string name;

		//N�vel
		int level;

		//Dinheiro
		int gold;

		//Atributos b�sicos
		StatsBasic stats_basic;

		//Dano Elemental
		Elemental elemental_damage;

		//Resist�ncia Elemental
		Elemental elemental_resist;

		//Absor��o Elemental
		Elemental elemental_absorb;

		//Mudan�a de estado para ataque
		StatusNegative status_attack;

		//Mudan�a de estado para defesa
		StatusNegative status_defense;

		//Mudan�a de estado
		StatusNegative status_negative_change;
	public:
		//Construtor
		Stats();

		//Alterar Name
		void SetName(const std::string& name);

		//Pegar Name
		const std::string& GetName() const;

		//Alterar Level
		void SetLevel(const int level);

		//Pegar Level
		int GetLevel() const;

		//Alterar Gold
		void SetGold(const int gold);

		//Pegar Gold
		int GetGold() const;

		//Pegar Stats Basic
		StatsBasic& GetStatsBasic();

		//Pegar Elemental Damage
		Elemental& GetElementalDamage();

		//Pegar Elemental Resist
		Elemental& GetElementalResist();

		//Pegar Elemental Absorb
		Elemental& GetElementalAbsorb();

		//Pegar Status Attack
		StatusNegative& GetStatusAttack();

		//Pegar Status Defense
		StatusNegative& GetStatusDefense();

		//Pegar Status Negative Change
		StatusNegative& GetStatusNegativeChange();
	};
}

#endif
#ifndef STATSBASIC_H
#define STATSBASIC_H

namespace RPG
{
	class StatsBasic
	{
	private:
		//Ativar o uso de dano elemental
		bool elemental_effect;

		//Ativar o uso de efeito de estado
		bool status_effect;

		//Pontos de vida atual
		int hp;

		//Pontos de mágica atual
		int mp;

		//Pontos de vida máxima
		int hp_max;

		//Pontos de mágica máxima
		int mp_max;

		//Dano físico mínimo
		int physical_damage_min;

		//Dano físico máximo
		int physical_damage_max;

		//Dano mágico mínimo
		int magical_damage_min;

		//Dano mágico máximo
		int magical_damage_max;

		//Resistência física
		int physical_resist;

		//Resistência mágica
		int magical_resist;

		//Chance de acertar
		int hit;

		//Chance de esquivar
		int evade;

		//Velocidade em batalha
		int speed;

		//Chance de causar dano crítico
		int critical_strike;

		//Chance de atacar mais uma vez
		int quick_strike;

		//Chance de contra-atacar
		int counter_strike;

		//Valor em % do dano físico para roubar HP
		int hp_steal;

		//Valor em % do dano físico para roubar MP
		int mp_steal;

		//Valor para regeneração de HP
		int hp_regen;

		//Valor para regeneração de MP
		int mp_regen;
	public:
		//Construtor
		StatsBasic();

		//Alterar Elemental Effect
		void SetElementalEffect(const bool elemental_effect);

		//Pegar Elemental Effect
		bool GetElementalEffect() const;

		//Alterar Status Effect
		void SetStatusEffect(const bool status_effect);

		//Pegar Status Effect
		bool GetStatusEffect() const;

		//Alterar HP
		void SetHP(const int hp);

		//Pegar HP
		int GetHP() const;

		//Alterar MP
		void SetMP(const int mp);

		//Pegar MP
		int GetMP() const;

		//Alterar HP Max
		void SetHPMax(const int hp_max);

		//Pegar HP Max
		int GetHPMax() const;

		//Alterar MP Max
		void SetMPMax(const int mp_max);

		//Pegar MP Max
		int GetMPMax() const;

		//Alterar Physical Damage Min
		void SetPhysicalDamageMin(const int physical_damage_min);

		//Pegar Physical Damage Min
		int GetPhysicalDamageMin() const;

		//Alterar Physical Damage Max
		void SetPhysicalDamageMax(const int physical_damage_max);

		//Pegar Physical Damage Max
		int GetPhysicalDamageMax() const;

		//Alterar Magical Damage Min
		void SetMagicalDamageMin(const int magical_damage_min);

		//Pegar Magical Damage Min
		int GetMagicalDamageMin() const;

		//Alterar Magical Damage Max
		void SetMagicalDamageMax(const int magical_damage_max);

		//Pegar Magical Damage Max
		int GetMagicalDamageMax() const;

		//Alterar Physical Resist
		void SetPhysicalResist(const int physical_resist);

		//Pegar Physical Resist
		int GetPhysicalResist() const;

		//Alterar Magical Resist
		void SetMagicalResist(const int magical_resist);

		//Pegar Magical Resist
		int GetMagicalResist() const;

		//Alterar Hit
		void SetHit(const int hit);

		//Pegar Hit
		int GetHit() const;

		//Alterar Evade
		void SetEvade(const int evade);

		//Pegar Evade
		int GetEvade() const;

		//Alterar Speed
		void SetSpeed(const int speed);

		//Pegar Speed
		int GetSpeed() const;

		//Alterar Critical Strike
		void SetCriticalStrike(const int critical_strike);

		//Pegar Critical Strike
		int GetCriticalStrike() const;

		//Alterar Quick Strike
		void SetQuickStrike(const int quick_strike);

		//Pegar Quick Strike
		int GetQuickStrike() const;

		//Alterar Counter Strike
		void SetCounterStrike(const int counter_strike);

		//Pegar Counter Strike
		int GetCounterStrike() const;

		//Alterar HP Steal
		void SetHPSteal(const int hp_steal);

		//Pegar HP Steal
		int GetHPSteal() const;

		//Alterar MP Steal
		void SetMPSteal(const int mp_steal);

		//Pegar MP Steal
		int GetMPSteal() const;

		//Alterar HP Regen
		void SetHPRegen(const int hp_regen);

		//Pegar HP Regen
		int GetHPRegen() const;

		//Alterar MP Regen
		void SetMPRegen(const int mp_regen);

		//Pegar MP Regen
		int GetMPRegen() const;
	};
}

#endif
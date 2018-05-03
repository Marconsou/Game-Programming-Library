#ifndef SKILL_H
#define SKILL_H

#include <algorithm>
#include <vector>
#include "SkillLevel.h"

namespace RPG
{
	//Classe da habilidade
	enum SKillClass
	{
		SKillClassNatural = 0,
		SKillClassActive,
	};

	class Skill
	{
	private:
		//N�vel atual
		int level;

		//N�vel exigente para aprender
		int required_level;

		//N�vel atual da habilidade
		const SkillLevel* current_skill_level;

		//Pr�ximo n�vel da habilidade
		const SkillLevel* next_skill_level;
	public:
		//Construtor
		Skill(const std::vector<SkillLevel>& skill_levels,const int required_level,const int level);

		//Destrutor
		virtual ~Skill() = 0 {};

		//Pegar Level
		int GetLevel() const;

		//Pegar Required Level
		int GetRequiredLevel() const;

		//Pegar Current Skill Level
		const SkillLevel& GetCurrentSkillLevel() const;

		//Pegar Next Skill Level
		const SkillLevel& GetNextSkillLevel() const;

		//Verificar se a habilidade foi aprendida
		bool SkillLearned() const;

		//Verificar se a habilidade esta no n�vel m�ximo
		bool SkillIsLevelMax() const;

		//Aumentar n�vel
		void LevelUp(const std::vector<SkillLevel>& skill_levels,const int level = 1);

		//Verificar se � da classe Natural
		bool IsNatural() const;

		//Verificar se � da classe Active
		bool IsActive() const;

		//Pegar Class Type
		virtual SKillClass GetClassType() const = 0;
	};
}

#endif
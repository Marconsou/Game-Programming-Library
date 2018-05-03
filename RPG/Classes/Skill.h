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
		//Nível atual
		int level;

		//Nível exigente para aprender
		int required_level;

		//Nível atual da habilidade
		const SkillLevel* current_skill_level;

		//Próximo nível da habilidade
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

		//Verificar se a habilidade esta no nível máximo
		bool SkillIsLevelMax() const;

		//Aumentar nível
		void LevelUp(const std::vector<SkillLevel>& skill_levels,const int level = 1);

		//Verificar se é da classe Natural
		bool IsNatural() const;

		//Verificar se é da classe Active
		bool IsActive() const;

		//Pegar Class Type
		virtual SKillClass GetClassType() const = 0;
	};
}

#endif
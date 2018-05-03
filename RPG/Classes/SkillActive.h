#ifndef SKILLACTIVE_H
#define SKILLACTIVE_H

#include "Skill.h"

namespace RPG
{
	class SkillActive : public Skill
	{
	private:
		//Alvos atingidos pela área do efeito da habilidade
		bool single_target;
	public:
		//Construtor
		SkillActive(const std::vector<SkillLevel>& skill_levels,const int required_level = 1,const int level = 0);

		//Alterar Single Target
		void SetSingleTarget(const bool single_target);

		//Pegar Single Target
		bool GetSingleTarget() const;

		//Pegar Class Type
		virtual SKillClass GetClassType() const;
	};
}

#endif
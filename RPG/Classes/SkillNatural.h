#ifndef SKILLNATURAL_H
#define SKILLNATURAL_H

#include "Skill.h"

namespace RPG
{
	class SkillNatural : public Skill
	{
	public:
		//Construtor
		SkillNatural(const std::vector<SkillLevel>& skill_levels,const int required_level = 1,const int level = 0);

		//Pegar Class Type
		virtual SKillClass GetClassType() const;
	};
}

#endif
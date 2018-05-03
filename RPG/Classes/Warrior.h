#ifndef WARRIOR_H
#define WARRIOR_H

#include "SkillNatural.h"
#include "SkillActive.h"
#include "Hero.h"

namespace RPG
{
	class Warrior : public Hero
	{
	protected:
		//Atualizar as estat�sticas �nicas da classe do her�i
		virtual void UniqueStatsUpdate();
	public:
		//Construtor
		Warrior(const std::vector<std::vector<SkillLevel>>& skill_levels);

		//Pegar Class Type
		virtual HeroClass GetClassType() const;
	};
}

#endif
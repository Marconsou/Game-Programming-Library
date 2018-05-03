#ifndef MAGE_H
#define MAGE_H

#include "SkillNatural.h"
#include "SkillActive.h"
#include "Hero.h"

namespace RPG
{
	class Mage : public Hero
	{
	protected:
		//Atualizar as estatísticas únicas da classe do herói
		virtual void UniqueStatsUpdate();
	public:
		//Construtor
		Mage(const std::vector<std::vector<SkillLevel>>& skill_levels);

		//Pegar Class Type
		virtual HeroClass GetClassType() const;
	};
}

#endif
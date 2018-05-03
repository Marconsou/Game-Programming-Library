#ifndef SKILLBUTTON_H
#define SKILLBUTTON_H

#include "Button.h"
#include "Skill.h"

namespace RPG
{
	class SkillButton : public GPL::Button
	{
	private:
		//Referência de uma habilidade
		Skill* skill;
	public:
		//Construtor
		SkillButton();

		//Alterar Skill
		void SetSkill(Skill& skill,const GPL::Texture& texture,const int skill_index);

		//Pegar Skill
		Skill& GetSkill();
	};
}

#endif
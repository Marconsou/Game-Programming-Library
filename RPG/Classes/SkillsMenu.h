#ifndef SKILLSMENU_H
#define SKILLSMENU_H

#include "WarriorSkillsMenu.h"
#include "MageSkillsMenu.h"

namespace RPG
{
	class SkillsMenu : public Menu
	{
	private:
		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		SkillsMenu(const float x,const float y);
	};
}

#endif
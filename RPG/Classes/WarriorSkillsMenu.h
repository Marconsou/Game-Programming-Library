#ifndef WARRIORSKILLSMENU_H
#define WARRIORSKILLSMENU_H

#include "ClassSkillsMenu.h"

namespace RPG
{
	class WarriorSkillsMenu : public ClassSkillsMenu
	{
	private:
		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();

		//Atualizar o ToolTip dos botões das habilidades
		virtual void SkillButtonToolTipUpdate();
	public:
		//Construtor
		WarriorSkillsMenu();
	};
}

#endif
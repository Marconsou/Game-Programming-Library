#ifndef MAGESKILLSMENU_H
#define MAGESKILLSMENU_H

#include "ClassSkillsMenu.h"

namespace RPG
{
	class MageSkillsMenu : public ClassSkillsMenu
	{
	private:
		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();

		//Atualizar o ToolTip dos botões das habilidades
		virtual void SkillButtonToolTipUpdate();
	public:
		//Construtor
		MageSkillsMenu();
	};
}

#endif
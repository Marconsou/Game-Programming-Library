#ifndef MAGESKILLSMENU_H
#define MAGESKILLSMENU_H

#include "ClassSkillsMenu.h"

namespace RPG
{
	class MageSkillsMenu : public ClassSkillsMenu
	{
	private:
		//Atualizar dados e a l�gica de todo o conte�do
		virtual void Update();

		//Atualizar o ToolTip dos bot�es das habilidades
		virtual void SkillButtonToolTipUpdate();
	public:
		//Construtor
		MageSkillsMenu();
	};
}

#endif
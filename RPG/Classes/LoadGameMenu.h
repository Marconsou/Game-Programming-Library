#ifndef LOADGAMEMENU_H
#define LOADGAMEMENU_H

#include "Menu.h"

namespace RPG
{
	class LoadGameMenu : public Menu
	{
	private:
		//IDs dos controles do Load Game Menu
		enum LoadGameMenuControlID
		{
			
			LoadGameMenuControlMax,
		};

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		LoadGameMenu();
	};
}

#endif
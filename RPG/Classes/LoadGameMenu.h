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

		//Atualizar dados e a l�gica de todo o conte�do
		virtual void Update();
	public:
		//Construtor
		LoadGameMenu();
	};
}

#endif
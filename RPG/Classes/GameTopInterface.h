#ifndef GAMETOPINTERFACE_H
#define GAMETOPINTERFACE_H

#include "ColorChanger.h"
#include "Menu.h"

namespace RPG
{
	class GameTopInterface : public Menu
	{
	private:
		//Cursor do Mouse
		GPL::Sprite cursor;

		//Mostrar a recente conquista desbloqueada
		void ShowRecentAchievementUnlocked();

		//Mostrar o cursor
		void ShowCursor();

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();

		//Mostrar todo o conteúdo
		virtual void Show();
	public:
		//Construtor
		GameTopInterface();
	};
}

#endif
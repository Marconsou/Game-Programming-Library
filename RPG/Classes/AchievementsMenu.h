#ifndef ACHIEVEMENTSMENU_H
#define ACHIEVEMENTSMENU_H

#include "Label.h"
#include "Menu.h"

namespace RPG
{
	class AchievementsMenu : public Menu
	{
	private:
		//IDs dos controles do Achievements Menu
		enum AchievementsMenuControlID
		{
			AchievementLabel = 0,
			AchievementDialogueBox,
			AchievementPercentageLabel,
			AchievementsMenuControlMax,
		};

		//Evento geral para On Click
		void GeneralOnClick(const GPL::Control& control);

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		AchievementsMenu(const float x,const float y);
	};
}

#endif
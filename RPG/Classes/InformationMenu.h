#ifndef INFORMATIONMENU_H
#define INFORMATIONMENU_H

#include "Label.h"
#include "PictureBox.h"
#include "Menu.h"

namespace RPG
{
	class InformationMenu : public Menu
	{
	private:
		//IDs dos controles do Information Menu
		enum InformationMenuControlID
		{
			InformationWindow = 0,
			GoldPictureBox,
			TimerPictureBox,
			GoldLabel,
			TimerLabel,
			InformationMenuControlMax,
		};

		//Refer�ncia para mudar posi��o das janelas de forma sincronizada
		const bool& change_window_position;

		//Velocidade da acelera��o da janela de informa��es
		float window_speed_y;


		static GPL::Interval colon_timer_interval;

		//Atualizar as posi��es dos controles
		void PositionUpdate();

		//Atualizar dados e a l�gica de todo o conte�do
		virtual void Update();
	public:
		//Construtor
		InformationMenu(const bool& change_window_position);
	};
}

#endif
#ifndef MAPMENU_H
#define MAPMENU_H

#include "PauseMenu.h"
#include "CharacterMenu.h"

namespace RPG
{
	class MapMenu : public Menu
	{
	private:
		//IDs dos controles do Map Menu
		enum MapMenuControlID
		{
			MapNameLabel = 0,
			CommandWindow,
			CharacterMenuButton,
			PauseMenuButton,
			MapMenuControlMax,
		};

		//ID do texto do nome do mapa
		const LanguageTextID map_name_text_id;

		//Mostrando o nome do mapa de pois de um certo tempo e lentamente
		bool showing_map_name;

		//Velocidade da acelera��o da janela de comandos
		float command_window_speed_y;

		//Atualizar a janela
		void UpdateWindow();

		//Evento do bot�o Character Menu
		void CharacterMenuOnClick(const GPL::Control& control);

		//Evento do bot�o Pause Menu
		void PauseMenuOnClick(const GPL::Control& control);

		//Pausar todo o conte�do
		void Pausing() override;

		//Resumir todo o conte�do pausado
		void Resuming() override;
		
		//Atualizar dados e a l�gica de todo o conte�do
		void Update() override;
	public:
		//Construtor
		MapMenu(const LanguageTextID map_name_text_id);
	};
}

#endif
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

		//Velocidade da aceleração da janela de comandos
		float command_window_speed_y;

		//Atualizar a janela
		void UpdateWindow();

		//Evento do botão Character Menu
		void CharacterMenuOnClick(const GPL::Control& control);

		//Evento do botão Pause Menu
		void PauseMenuOnClick(const GPL::Control& control);

		//Pausar todo o conteúdo
		void Pausing() override;

		//Resumir todo o conteúdo pausado
		void Resuming() override;
		
		//Atualizar dados e a lógica de todo o conteúdo
		void Update() override;
	public:
		//Construtor
		MapMenu(const LanguageTextID map_name_text_id);
	};
}

#endif
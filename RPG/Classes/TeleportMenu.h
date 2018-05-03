#ifndef TELEPORTMENU_H
#define TELEPORTMENU_H

#include "Menu.h"

namespace RPG
{
	class TeleportMenu : public Menu
	{
	private:
		//ID do mapa atual
		const MapID current_map_id;

		//Área selecionada
		int selected_area;

		//Fechar Teleport Menu
		void Close();

		//Evento do botão Back
		void BackOnClick(const GPL::Control& control);

		//Algum opção de mapa selecionada
		void MapAreaOnOptionSelected(const GPL::Control& control,const int option_selected_index);

		//Back selecionado
		void BackOnOptionSelected(const GPL::Control& control,const int option_selected_index);

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		TeleportMenu(const MapID current_map_id);

		//Pegar Selected Area
		int GetSelectedArea() const;
	};
}

#endif
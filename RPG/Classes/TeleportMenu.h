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

		//�rea selecionada
		int selected_area;

		//Fechar Teleport Menu
		void Close();

		//Evento do bot�o Back
		void BackOnClick(const GPL::Control& control);

		//Algum op��o de mapa selecionada
		void MapAreaOnOptionSelected(const GPL::Control& control,const int option_selected_index);

		//Back selecionado
		void BackOnOptionSelected(const GPL::Control& control,const int option_selected_index);

		//Atualizar dados e a l�gica de todo o conte�do
		virtual void Update();
	public:
		//Construtor
		TeleportMenu(const MapID current_map_id);

		//Pegar Selected Area
		int GetSelectedArea() const;
	};
}

#endif
#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "OptionsMenu.h"

namespace RPG
{
	class PauseMenu : public Menu
	{
	private:
		//Índice da última opção selecionada
		int last_option_selected_index;

		//Atualizar dados do Dialogue Box
		void DialogueBoxUpdate();

		//Evento da opção Exit
		void ExitOnClick(const GPL::Control& control);

		//Opção selecionada
		void GeneralOnOptionSelected(const GPL::Control& control,const int option_selected_index);

		//Resumir todo o conteúdo pausado
		void Resuming() override;

		//Atualizar dados e a lógica de todo o conteúdo
		void Update() override;
	public:
		//Construtor
		PauseMenu();
	};
}

#endif
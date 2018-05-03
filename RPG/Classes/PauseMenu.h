#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "OptionsMenu.h"

namespace RPG
{
	class PauseMenu : public Menu
	{
	private:
		//�ndice da �ltima op��o selecionada
		int last_option_selected_index;

		//Atualizar dados do Dialogue Box
		void DialogueBoxUpdate();

		//Evento da op��o Exit
		void ExitOnClick(const GPL::Control& control);

		//Op��o selecionada
		void GeneralOnOptionSelected(const GPL::Control& control,const int option_selected_index);

		//Resumir todo o conte�do pausado
		void Resuming() override;

		//Atualizar dados e a l�gica de todo o conte�do
		void Update() override;
	public:
		//Construtor
		PauseMenu();
	};
}

#endif
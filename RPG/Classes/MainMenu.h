#ifndef MAINMENU_H
#define MAINMENU_H

#include "NewGameMenu.h"
#include "LoadGameMenu.h"
#include "OptionsMenu.h"

namespace RPG
{
	class MainMenu : public Menu
	{
	private:
		//Atualizar dados do Dialogue Box
		void DialogueBoxUpdate();

		//Evento da op��o Exit
		void ExitOnClick(const GPL::Control& control);

		//New Game selecionado
		void NewGameOnOptionSelected(const GPL::Control& control,const int option_selected_index);

		//Load Game selecionado
		void LoadGameOnOptionSelected(const GPL::Control& control,const int option_selected_index);

		//Options selecionado
		void OptionsOnOptionSelected(const GPL::Control& control,const int option_selected_index);

		//Resumir todo o conte�do pausado
		void Resuming() override;

		//Atualizar dados e a l�gica de todo o conte�do
		void Update() override;
	public:
		//Construtor
		MainMenu();
	};
}

#endif
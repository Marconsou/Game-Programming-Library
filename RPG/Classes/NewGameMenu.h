#ifndef NEWGAMEMENU_H
#define NEWGAMEMENU_H

#include "TextBox.h"
#include "ClassSelector.h"
#include "MapManager.h"

namespace RPG
{
	class NewGameMenu : public Menu
	{
	private:
		//IDs dos controles do New Game Menu
		enum NewGameMenuControlID
		{
			MenuTextLabel = 0,
			AvatarTextLabel,
			PreviousAvatarButton,
			NextAvatarButton,
			CursorSelectorPictureBox,
			WarriorSelector,
			MageSelector,
			NameInputWindow,
			NameInputTextBox,
			NameInputLabel,
			ConfirmButton,
			BackButton,
			NewGameMenuControlMax,
		};

		//Começando um novo jogo
		bool starting_new_game;

		//Referência para o Class Selector selecionado
		ClassSelector* class_selector_selected;

		//Atualizar a posicão do Cursor Selector
		void CursorSelectorPositionUpdate();

		//Novo jogo
		void NewGame();

		//Evento do Class Selector
		void ClassSelectorOnClick(GPL::Control& control);

		//Evento do botão Previous Avatar
		void PreviousAvatarOnClick(const GPL::Control& control);

		//Evento do botão Next Avatar
		void NextAvatarOnClick(const GPL::Control& control);

		//Evento do botão Confirm
		void ConfirmOnClick(const GPL::Control& control);

		//Evento da botão Back
		void BackOnClick(const GPL::Control& control);

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		NewGameMenu();
	};
}

#endif
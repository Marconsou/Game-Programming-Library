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

		//Come�ando um novo jogo
		bool starting_new_game;

		//Refer�ncia para o Class Selector selecionado
		ClassSelector* class_selector_selected;

		//Atualizar a posic�o do Cursor Selector
		void CursorSelectorPositionUpdate();

		//Novo jogo
		void NewGame();

		//Evento do Class Selector
		void ClassSelectorOnClick(GPL::Control& control);

		//Evento do bot�o Previous Avatar
		void PreviousAvatarOnClick(const GPL::Control& control);

		//Evento do bot�o Next Avatar
		void NextAvatarOnClick(const GPL::Control& control);

		//Evento do bot�o Confirm
		void ConfirmOnClick(const GPL::Control& control);

		//Evento da bot�o Back
		void BackOnClick(const GPL::Control& control);

		//Atualizar dados e a l�gica de todo o conte�do
		virtual void Update();
	public:
		//Construtor
		NewGameMenu();
	};
}

#endif
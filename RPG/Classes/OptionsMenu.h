#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "OptionsMenuGameplay.h"
#include "OptionsMenuVideo.h"
#include "OptionsMenuAudio.h"

namespace RPG
{
	class OptionsMenu : public Menu
	{
	private:
		//IDs dos controles do Options Menu
		enum OptionsMenuControlID
		{
			MenuTextLabel = 0,
			ContentsWindow,
			OptionsMenuWindow,
			OptionsActionWindow,
			GameplayButton,
			VideoButton,
			AudioButton,
			ConfirmButton,
			ApplyButton,
			DefaultButton,
			BackButton,
			OptionsMenuControlMax,
		};

		enum class OptionsSubMenu
		{
			Gameplay,
			Video,
			Audio,
			Max,
		};

		//Último Menu do Options selecionado
		GPL::GameState* last_game_state_selected{};


		OptionsMenuGameplay& GetSubMenuGameplay();


		OptionsMenuVideo& GetSubMenuVideo();


		OptionsMenuAudio& GetSubMenuAudio();


		//Carregar o conteúdo do Menu
		void LoadContents(const bool load_once);


		void ChangeSubMenu(const OptionsSubMenu sub_menu);

		//Aplicar configurações
		void Apply();

		//Voltar ao menu anterior deletando os Game States do Options Menu
		void Back();

		//Evento do botão Gameplay
		void GameplayOnClick(const GPL::Control& control);

		//Evento do botão Video
		void VideoOnClick(const GPL::Control& control);

		//Evento do botão Audio
		void AudioOnClick(const GPL::Control& control);

		//Evento do botão Confirm
		void ConfirmOnClick(const GPL::Control& control);

		//Evento do botão Apply
		void ApplyOnClick(const GPL::Control& control);

		//Evento do botão Default
		void DefaultOnClick(const GPL::Control& control);

		//Evento da botão Back
		void BackOnClick(const GPL::Control& control);
	public:
		//Construtor
		OptionsMenu();

		//Ativar o Menu padrão
		void ActivateDefaultMenu();
	};
}

#endif
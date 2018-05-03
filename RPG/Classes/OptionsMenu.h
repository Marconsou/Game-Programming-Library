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

		//�ltimo Menu do Options selecionado
		GPL::GameState* last_game_state_selected{};


		OptionsMenuGameplay& GetSubMenuGameplay();


		OptionsMenuVideo& GetSubMenuVideo();


		OptionsMenuAudio& GetSubMenuAudio();


		//Carregar o conte�do do Menu
		void LoadContents(const bool load_once);


		void ChangeSubMenu(const OptionsSubMenu sub_menu);

		//Aplicar configura��es
		void Apply();

		//Voltar ao menu anterior deletando os Game States do Options Menu
		void Back();

		//Evento do bot�o Gameplay
		void GameplayOnClick(const GPL::Control& control);

		//Evento do bot�o Video
		void VideoOnClick(const GPL::Control& control);

		//Evento do bot�o Audio
		void AudioOnClick(const GPL::Control& control);

		//Evento do bot�o Confirm
		void ConfirmOnClick(const GPL::Control& control);

		//Evento do bot�o Apply
		void ApplyOnClick(const GPL::Control& control);

		//Evento do bot�o Default
		void DefaultOnClick(const GPL::Control& control);

		//Evento da bot�o Back
		void BackOnClick(const GPL::Control& control);
	public:
		//Construtor
		OptionsMenu();

		//Ativar o Menu padr�o
		void ActivateDefaultMenu();
	};
}

#endif
#include "PauseMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

PauseMenu::PauseMenu() :
	Menu(1),
	last_option_selected_index(-1)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	game.GetHero().GetPlayTime().Pause(true);

	DialogueBox& dialogue_box = this->CreateControl<DialogueBox>();
	dialogue_box.SetDialogueBox(this->GetDefaultFontMedium(),0,50.0f,10.0f,10.0f);
	dialogue_box.AddOption(game.GetDatabase().GetLanguageText(ResumeButtonTextID),Color::Gold);
	dialogue_box.AddOption(game.GetDatabase().GetLanguageText(OptionsMenuButtonTextID),Color::Gold);
	dialogue_box.AddOption(game.GetDatabase().GetLanguageText(ExitButtonTextID),Color::Gold);
	dialogue_box.AddOptionEventOnClick(0,&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	dialogue_box.AddOptionEventOnClick(1,&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	dialogue_box.AddOptionEventOnClick(2,&PauseMenu::ExitOnClick,*this);
	dialogue_box.AddOptionEventOnOptionSelected(0,&PauseMenu::GeneralOnOptionSelected,*this);
	dialogue_box.AddOptionEventOnOptionSelected(1,&PauseMenu::GeneralOnOptionSelected,*this);
	dialogue_box.AddOptionEventOnOptionSelected(2,&PauseMenu::GeneralOnOptionSelected,*this);
	dialogue_box.AddOptionKeyShortcut(0,KeyboardKey::Esc);
	dialogue_box.AddOptionKeyShortcut(1,KeyboardKey::O);
	dialogue_box.AddOptionKeyShortcut(2,KeyboardKey::X);

	this->DialogueBoxUpdate();
}

void PauseMenu::Resuming()
{
	GameState::Resuming();
	this->DialogueBoxUpdate();
}

void PauseMenu::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Centralizar no meio da tela
	DialogueBox& dialogue_box = this->GetControl<DialogueBox>(0);
	dialogue_box.SetPosition(game.GetVideo().GetVirtualWidth() / 2.0f,game.GetVideo().GetVirtualHeight() / 2.0f,true);

	//Dialogue Box já foi removido quer dizer que já foi fechado completamente
	if (dialogue_box.IsRemoved())
	{
		//Os eventos seguintes deve ocorrer aqui pois está deletando o próprio Menu, sendo assim não poderá estar no próprio On Remove do Dialogue Box
		//Resume
		if (this->last_option_selected_index == 0)
		{
			game.GetHero().GetPlayTime().Pause(false);

			//Pause Menu
			GameState::AddGameState(nullptr,GameStateAction::DeleteCurrentGameState);
		}

		//Saindo do jogo atual
		if (game.GetScreenEffect().FadeOutEnd())
		{
			//Exit
			if (this->last_option_selected_index == 2)
			{
				game.FinishCurrentGame();
				game.GetScreenEffect().StartFadeInScreen(ScreenEffectFadeMode::Fast);
				game.GetAudio().PlayMusicFromPlaylist(MusicTitleMusicFileID,false);

				//Pause Menu
				GameState::AddGameState(nullptr,GameStateAction::DeleteCurrentGameState);

				//Mapa atual
				GameState::AddGameState(nullptr,GameStateAction::DeleteCurrentGameState);

				//Map Manager
				GameState::AddGameState(nullptr,GameStateAction::DeleteCurrentGameState);
			}
		}
	}
}

void PauseMenu::DialogueBoxUpdate()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Atualizar e adicionar o Dialogue Box
	DialogueBox& dialogue_box = this->GetControl<DialogueBox>(0);
	game.SetDialogueBox(dialogue_box);
	dialogue_box.SetOptionText(0,game.GetDatabase().GetLanguageText(ResumeButtonTextID),Color::Gold);
	dialogue_box.SetOptionText(1,game.GetDatabase().GetLanguageText(OptionsMenuButtonTextID),Color::Gold);
	dialogue_box.SetOptionText(2,game.GetDatabase().GetLanguageText(ExitButtonTextID),Color::Gold);
	dialogue_box.AddControl();
}

void PauseMenu::ExitOnClick(const Control& control)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	game.GetAudio().PlaySoundFromBuffer(SoundCancelFileID);
	game.GetScreenEffect().StartFadeOutScreen(ScreenEffectFadeMode::Fast);
}

void PauseMenu::GeneralOnOptionSelected(const Control& control,const int option_selected_index)
{
	if (option_selected_index == 1)
	{
		OptionsMenu* options_menu = static_cast<OptionsMenu*>(GameState::AddGameState(make_unique<OptionsMenu>(),GameStateAction::PauseCurrentGameState));
		options_menu->ActivateDefaultMenu();
	}
	this->last_option_selected_index = option_selected_index;
}
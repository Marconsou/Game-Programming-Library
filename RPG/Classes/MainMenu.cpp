#include "MainMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

MainMenu::MainMenu() :
	Menu(1)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	ItemButton::SetGame(game);

	game.GetAudio().PlayMusicFromPlaylist(MusicTitleMusicFileID);

	DialogueBox& dialogue_box = this->CreateControl<DialogueBox>();
	dialogue_box.SetDialogueBox(this->GetDefaultFontMedium(),0,75.0f,10.0f,10.0f);
	dialogue_box.AddOption(game.GetDatabase().GetLanguageText(NewGameMenuButtonTextID),Color::Gold);
	dialogue_box.AddOption(game.GetDatabase().GetLanguageText(LoadGameMenuButtonTextID),Color::Gold);
	dialogue_box.AddOption(game.GetDatabase().GetLanguageText(OptionsMenuButtonTextID),Color::Gold);
	dialogue_box.AddOption(game.GetDatabase().GetLanguageText(ExitButtonTextID),Color::Gold);
	dialogue_box.AddOptionEventOnClick(0,&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	dialogue_box.AddOptionEventOnClick(1,&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	dialogue_box.AddOptionEventOnClick(2,&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	dialogue_box.AddOptionEventOnClick(3,&MainMenu::ExitOnClick,*this);
	dialogue_box.AddOptionEventOnOptionSelected(0,&MainMenu::NewGameOnOptionSelected,*this);
	dialogue_box.AddOptionEventOnOptionSelected(1,&MainMenu::LoadGameOnOptionSelected,*this);
	dialogue_box.AddOptionEventOnOptionSelected(2,&MainMenu::OptionsOnOptionSelected,*this);
	dialogue_box.AddOptionKeyShortcut(0,KeyboardKey::N);
	dialogue_box.AddOptionKeyShortcut(1,KeyboardKey::L);
	dialogue_box.AddOptionKeyShortcut(2,KeyboardKey::O);
	dialogue_box.AddOptionKeyShortcut(3,KeyboardKey::Esc);

	this->DialogueBoxUpdate();
}

void MainMenu::Resuming()
{
	GameState::Resuming();
	this->DialogueBoxUpdate();
}

void MainMenu::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Centralizar no meio da tela
	DialogueBox& dialogue_box = this->GetControl<DialogueBox>(0);
	dialogue_box.SetPosition(game.GetVideo().GetVirtualWidth() / 2.0f,game.GetVideo().GetVirtualHeight() / 2.0f,true);

	//Fechando o jogo
	if ((dialogue_box.IsRemoved()) && (game.GetScreenEffect().FadeOutEnd()))
		GameState::AddGameState(nullptr,GameStateAction::DeleteCurrentGameState);
}

void MainMenu::DialogueBoxUpdate()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Atualizar e adicionar o Dialogue Box
	DialogueBox& dialogue_box = this->GetControl<DialogueBox>(0);
	game.SetDialogueBox(dialogue_box);
	dialogue_box.SetOptionText(0,game.GetDatabase().GetLanguageText(NewGameMenuButtonTextID),Color::Gold);
	dialogue_box.SetOptionText(1,game.GetDatabase().GetLanguageText(LoadGameMenuButtonTextID),Color::Gold);
	dialogue_box.SetOptionText(2,game.GetDatabase().GetLanguageText(OptionsMenuButtonTextID),Color::Gold);
	dialogue_box.SetOptionText(3,game.GetDatabase().GetLanguageText(ExitButtonTextID),Color::Gold);
	dialogue_box.AddControl();
}

void MainMenu::ExitOnClick(const Control& control)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	game.GetAudio().PlaySoundFromBuffer(SoundCancelFileID);
	game.GetScreenEffect().StartFadeOutScreen(ScreenEffectFadeMode::Fast);
}

void MainMenu::NewGameOnOptionSelected(const Control& control,const int option_selected_index)
{
	GameState::AddGameState(make_unique<NewGameMenu>(),GameStateAction::PauseCurrentGameState);
}

void MainMenu::LoadGameOnOptionSelected(const Control& control,const int option_selected_index)
{
	//GameState::AddGameState(make_shared<LoadGameMenu>(),GameStateAction::PauseCurrentGameState);
	GameState::AddGameState(nullptr,GameStateAction::DeleteCurrentGameState);
}

void MainMenu::OptionsOnOptionSelected(const Control& control,const int option_selected_index)
{
	OptionsMenu* options_menu = static_cast<OptionsMenu*>(GameState::AddGameState(make_unique<OptionsMenu>(),GameStateAction::PauseCurrentGameState));
	options_menu->ActivateDefaultMenu();
}
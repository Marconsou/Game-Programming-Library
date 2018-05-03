#include "OptionsMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

OptionsMenu::OptionsMenu() :
	Menu(OptionsMenuControlMax)
{
	//Menu Text Label
	Label& menu_text_label = this->CreateControl<Label>();

	//Contents Window
	Window& contents_window = this->CreateControl<Window>();

	//Options Menu Window
	Window& options_menu_window = this->CreateControl<Window>();

	//Options Action Window
	Window& options_action_window = this->CreateControl<Window>();

	//Gameplay Button
	Button& gameplay_button = this->CreateControl<Button>();

	//Video Button
	Button& video_button = this->CreateControl<Button>();

	//Audio Button
	Button& audio_button = this->CreateControl<Button>();

	//Confirm Button
	Button& confirm_button = this->CreateControl<Button>();

	//Apply Button
	Button& apply_button = this->CreateControl<Button>();

	//Default Button
	Button& default_button = this->CreateControl<Button>();

	//Back Button
	Button& back_button = this->CreateControl<Button>();

	this->LoadContents(true);

	this->AddSubGameState(make_unique<OptionsMenuGameplay>(contents_window.GetX(),contents_window.GetY()));
	this->AddSubGameState(make_unique<OptionsMenuVideo>(contents_window.GetX(),contents_window.GetY()));
	this->AddSubGameState(make_unique<OptionsMenuAudio>(contents_window.GetX(),contents_window.GetY()));
}

OptionsMenuGameplay& OptionsMenu::GetSubMenuGameplay()
{
	return static_cast<OptionsMenuGameplay&>(this->GetSubGameState(static_cast<size_t>(OptionsSubMenu::Gameplay)));
}

OptionsMenuVideo& OptionsMenu::GetSubMenuVideo()
{
	return static_cast<OptionsMenuVideo&>(this->GetSubGameState(static_cast<size_t>(OptionsSubMenu::Video)));
}

OptionsMenuAudio& OptionsMenu::GetSubMenuAudio()
{
	return static_cast<OptionsMenuAudio&>(this->GetSubGameState(static_cast<size_t>(OptionsSubMenu::Audio)));
}

void OptionsMenu::LoadContents(const bool load_once)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	game.GetConfiguration().LoadFromFile();

	//Menu Text Label
	Label& menu_text_label = this->GetControl<Label>(MenuTextLabel);
	menu_text_label.SetText(game.GetVideo().GetFont(FontPerspectiveSansBlackItalicFileID),game.GetDatabase().GetLanguageText(OptionsMenuButtonTextID),Color::Gold);
	menu_text_label.SetPosition(game.GetVideo().GetVirtualWidth() / 2.0f,(game.GetVideo().GetVirtualHeight() / 2.0f) - 250.0f,true);
	menu_text_label.AddControl();

	//Contents Window
	Window& contents_window = this->GetControl<Window>(ContentsWindow);
	game.SetWindow(contents_window,17,10);
	if (load_once)
	{
		contents_window.SetPosition(game.GetVideo().GetVirtualWidth() / 2.0f,(game.GetVideo().GetVirtualHeight() / 2.0f) - 50.0f,true);
		contents_window.AddControl();
	}

	//Options Menu Window
	Window& options_menu_window = this->GetControl<Window>(OptionsMenuWindow);
	game.SetWindow(options_menu_window,3,3);
	if (load_once)
	{
		options_menu_window.SetPosition(contents_window.GetX() - options_menu_window.GetW(),contents_window.GetY());
		options_menu_window.AddControl();
	}

	//Options Action Window
	Window& options_action_window = this->GetControl<Window>(OptionsActionWindow);
	game.SetWindow(options_action_window,17,0);
	if (load_once)
	{
		options_action_window.SetPosition(contents_window.GetX() + (contents_window.GetW() / 2.0f) - (options_action_window.GetW() / 2.0f),contents_window.GetY() + contents_window.GetH());
		options_action_window.AddControl();
	}

	//Gameplay Button
	Button& gameplay_button = this->GetControl<Button>(GameplayButton);
	gameplay_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuGameplayTextID),Color::Gold);
	if (load_once)
	{
		gameplay_button.SetPosition(options_menu_window.GetX() + 10.0f,options_menu_window.GetY() + 10.0f);
		gameplay_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
		gameplay_button.AddEventOnClick(&OptionsMenu::GameplayOnClick,*this);
		gameplay_button.AddControl();
	}

	//Video Button
	Button& video_button = this->GetControl<Button>(VideoButton);
	video_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuVideoTextID),Color::Gold);
	if (load_once)
	{
		video_button.SetPosition(gameplay_button.GetX(),gameplay_button.GetY() + gameplay_button.GetH() + 1.0f);
		video_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
		video_button.AddEventOnClick(&OptionsMenu::VideoOnClick,*this);
		video_button.AddControl();
	}

	//Audio Button
	Button& audio_button = this->GetControl<Button>(AudioButton);
	audio_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuAudioTextID),Color::Gold);
	if (load_once)
	{
		audio_button.SetPosition(video_button.GetX(),video_button.GetY() + video_button.GetH() + 1.0f);
		audio_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
		audio_button.AddEventOnClick(&OptionsMenu::AudioOnClick,*this);
		audio_button.AddControl();
	}

	//Confirm Button
	Button& confirm_button = this->GetControl<Button>(ConfirmButton);
	confirm_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(ConfirmTextID),Color::Gold);
	confirm_button.SetPosition(options_action_window.GetX() + ((options_action_window.GetW() * 1.0f) / 5.0f),options_action_window.GetY() + (options_action_window.GetH() / 2.0f),true);
	if (load_once)
	{
		confirm_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
		confirm_button.AddEventOnClick(&OptionsMenu::ConfirmOnClick,*this);
		confirm_button.SetKeyboardKeyShortcut(KeyboardKey::Enter);
		confirm_button.AddControl();
	}

	//Apply Button
	Button& apply_button = this->GetControl<Button>(ApplyButton);
	apply_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(OptionsMenuApplyTextID),Color::Gold);
	apply_button.SetPosition(options_action_window.GetX() + ((options_action_window.GetW() * 2.0f) / 5.0f),options_action_window.GetY() + (options_action_window.GetH() / 2.0f),true);
	if (load_once)
	{
		apply_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
		apply_button.AddEventOnClick(&OptionsMenu::ApplyOnClick,*this);
		apply_button.AddControl();
	}

	//Default Button
	Button& default_button = this->GetControl<Button>(DefaultButton);
	default_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(DefaultTextID),Color::Gold);
	default_button.SetPosition(options_action_window.GetX() + ((options_action_window.GetW() * 3.0f) / 5.0f),options_action_window.GetY() + (options_action_window.GetH() / 2.0f),true);
	if (load_once)
	{
		default_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
		default_button.AddEventOnClick(&OptionsMenu::DefaultOnClick,*this);
		default_button.AddControl();
	}

	//Back Button
	Button& back_button = this->GetControl<Button>(BackButton);
	back_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(BackTextID),Color::Gold);
	back_button.SetPosition(options_action_window.GetX() + ((options_action_window.GetW() * 4.0f) / 5.0f),confirm_button.GetY() + (confirm_button.GetH() / 2.0f),true);
	if (load_once)
	{
		back_button.AddEventOnClick(&OptionsMenu::BackOnClick,*this);
		back_button.SetKeyboardKeyShortcut(KeyboardKey::Esc);
		back_button.AddControl();
	}
}

void OptionsMenu::ActivateDefaultMenu()
{
	this->ChangeSubMenu(OptionsSubMenu::Gameplay);
}

void OptionsMenu::ChangeSubMenu(const OptionsSubMenu sub_menu)
{
	for (size_t i = 0; i < static_cast<size_t>(OptionsSubMenu::Max); i++)
	{
		if (i != static_cast<size_t>(sub_menu))
			this->HideSubGameState(i);
	}

	GameState& game_state = this->GetSubGameState(static_cast<size_t>(sub_menu));

	if (this->last_game_state_selected != &game_state)
	{
		this->ShowSubGameState(static_cast<size_t>(sub_menu));
		this->last_game_state_selected = &game_state;
	}
}

void OptionsMenu::Apply()
{
	this->GetSubMenuGameplay().SaveConfiguration();
	this->GetSubMenuVideo().SaveConfiguration();
	this->GetSubMenuAudio().SaveConfiguration();

	this->LoadContents(false);

	const Window& contents_window = this->GetControl<Window>(ContentsWindow);

	this->GetSubMenuGameplay().LoadContents(false,contents_window.GetX(),contents_window.GetY());
	this->GetSubMenuVideo().LoadContents(false,contents_window.GetX(),contents_window.GetY());
	this->GetSubMenuAudio().LoadContents(false,contents_window.GetX(),contents_window.GetY());
}

void OptionsMenu::Back()
{
	GameState::AddGameState(nullptr,GameStateAction::DeleteCurrentGameState);
}

void OptionsMenu::GameplayOnClick(const Control& control)
{
	this->ChangeSubMenu(OptionsSubMenu::Gameplay);
}

void OptionsMenu::VideoOnClick(const Control& control)
{
	this->ChangeSubMenu(OptionsSubMenu::Video);
}

void OptionsMenu::AudioOnClick(const Control& control)
{
	this->ChangeSubMenu(OptionsSubMenu::Audio);
}

void OptionsMenu::ConfirmOnClick(const Control& control)
{
	this->Apply();
	this->Back();
}

void OptionsMenu::ApplyOnClick(const Control& control)
{
	this->Apply();
}

void OptionsMenu::DefaultOnClick(const Control& control)
{
	this->GetSubMenuGameplay().DefaultConfiguration();
	this->GetSubMenuVideo().DefaultConfiguration();
	this->GetSubMenuAudio().DefaultConfiguration();
	this->Apply();
}

void OptionsMenu::BackOnClick(const Control& control)
{
	this->Back();
	GameState::GetGame<GameRPG>().GetAudio().PlaySoundFromBuffer(SoundCancelFileID);
}
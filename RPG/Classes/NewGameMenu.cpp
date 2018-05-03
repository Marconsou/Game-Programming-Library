#include "NewGameMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

NewGameMenu::NewGameMenu() :
	Menu(NewGameMenuControlMax),
	starting_new_game(false),
	class_selector_selected(nullptr)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Menu Text Label
	Label& menu_text_label = this->CreateControl<Label>();
	menu_text_label.SetText(game.GetVideo().GetFont(FontPerspectiveSansBlackItalicFileID),game.GetDatabase().GetLanguageText(NewGameMenuButtonTextID),Color::Gold);
	menu_text_label.SetPosition(game.GetVideo().GetVirtualWidth() / 2.0f,(game.GetVideo().GetVirtualHeight() / 2.0f) - 250.0f,true);
	menu_text_label.AddControl();

	//Avatar Text Label
	Label& avatar_text_label = this->CreateControl<Label>();
	avatar_text_label.SetText(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(NewGameMenuAvatarTextID),Color::Gold);
	avatar_text_label.SetPosition(menu_text_label.GetX() + (menu_text_label.GetW() / 2.0f),menu_text_label.GetY() + (menu_text_label.GetH() / 2.0f) + 225.0f,true);
	avatar_text_label.AddControl();

	//Previous Avatar Button
	Button& previous_avatar_button = this->CreateControl<Button>();
	previous_avatar_button.SetButton(game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,65.0f,0.0f);
	previous_avatar_button.SetPosition(avatar_text_label.GetX(),avatar_text_label.GetY() + avatar_text_label.GetH());
	previous_avatar_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	previous_avatar_button.AddEventOnClick(&NewGameMenu::PreviousAvatarOnClick,*this);
	previous_avatar_button.AddControl();

	//Next Avatar Button
	Button& next_avatar_button = this->CreateControl<Button>();
	next_avatar_button.SetButton(game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,82.0f,0.0f);
	next_avatar_button.SetPosition(avatar_text_label.GetX() + avatar_text_label.GetW() - 16.0f,previous_avatar_button.GetY());
	next_avatar_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	next_avatar_button.AddEventOnClick(&NewGameMenu::NextAvatarOnClick,*this);
	next_avatar_button.AddControl();

	//Cursor Selector Picture Box
	PictureBox& cursor_selector_picture_box = this->CreateControl<PictureBox>();
	cursor_selector_picture_box.SetAnimationFrame(game.GetTimer(),game.GetVideo().GetTexture(TextureSelectorFileID),19.0f,16.0f,3,0.125f,1);
	cursor_selector_picture_box.AddControl();

	//Warrior Selector
	ClassSelector& warrior_selector = this->CreateControl<ClassSelector>();
	warrior_selector.SetSelected(true);
	warrior_selector.SetClassSelector(game.GetVideo(),TextureWarrior0FileID);
	warrior_selector.SetPosition(menu_text_label.GetX() + (menu_text_label.GetW() / 2.0f) - 40.0f,menu_text_label.GetY() + (menu_text_label.GetH() / 2.0f) + 125.0f,true);
	warrior_selector.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	warrior_selector.AddEventOnClick(&NewGameMenu::ClassSelectorOnClick,*this);
	warrior_selector.SetToolTip(this->GetDefaultFontMedium(),this->GetDefaultEdgeDistance(),Color::Blue);
	warrior_selector.NewToolTipTextLine(game.GetDatabase().GetLanguageText(NewGameMenuWarriorClassNameTextID),Color::Gold);
	warrior_selector.NewToolTipTextLine(game.GetDatabase().GetLanguageText(NewGameMenuWarriorDescription0TextID),Color::White,ToolTipTextAlign::Left);
	warrior_selector.NewToolTipTextLine(game.GetDatabase().GetLanguageText(NewGameMenuWarriorDescription1TextID),Color::White,ToolTipTextAlign::Left);
	warrior_selector.AddControl();
	this->class_selector_selected = &warrior_selector;
	this->CursorSelectorPositionUpdate();

	//Mage Selector
	ClassSelector& mage_selector = this->CreateControl<ClassSelector>();
	mage_selector.SetClassSelector(game.GetVideo(),TextureMage0FileID);
	mage_selector.SetPosition(warrior_selector.GetX() + 75.0f,warrior_selector.GetY());
	mage_selector.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	mage_selector.AddEventOnClick(&NewGameMenu::ClassSelectorOnClick,*this);
	mage_selector.SetToolTip(this->GetDefaultFontMedium(),this->GetDefaultEdgeDistance(),Color::Blue);
	mage_selector.NewToolTipTextLine(game.GetDatabase().GetLanguageText(NewGameMenuMageClassNameTextID),Color::Gold);
	mage_selector.NewToolTipTextLine(game.GetDatabase().GetLanguageText(NewGameMenuMageDescription0TextID),Color::White,ToolTipTextAlign::Left);
	mage_selector.NewToolTipTextLine(game.GetDatabase().GetLanguageText(NewGameMenuMageDescription1TextID),Color::White,ToolTipTextAlign::Left);
	mage_selector.AddControl();

	//Name Input Window
	Window& name_input_window = this->CreateControl<Window>();
	game.SetWindow(name_input_window,12,4);
	name_input_window.SetPosition(game.GetVideo().GetVirtualWidth() / 2.0f,(game.GetVideo().GetVirtualHeight() / 2.0f) + 100.0f,true);
	name_input_window.AddControl();

	//Name Input Text Box
	TextBox& name_input_text_box = this->CreateControl<TextBox>();
	name_input_text_box.SetTextBox(this->GetDefaultFontMedium(),TextBoxInputType::NameInput,15,3.0f,Color::White,Color::White,Color(0.0f,0.0f,0.0f,0.25f),Color::Gold);
	name_input_text_box.SetBackgroundText(game.GetDatabase().GetLanguageText(NewGameMenuNameInputDefaultTextID),Color::Gray);
	name_input_text_box.SetPosition(name_input_window.GetX() + (name_input_window.GetW() / 2.0f),name_input_window.GetY() + (name_input_window.GetH() / 2.0f) - 30.0f,true);
	name_input_text_box.GainFocus(true);
	name_input_text_box.AddControl();

	//Name Input Label
	Label& name_input_label = this->CreateControl<Label>();
	name_input_label.SetText(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(NewGameMenuNameInputErrorTextID),Color::Red);
	name_input_label.SetPosition(name_input_text_box.GetX() + (name_input_text_box.GetW() / 2.0f),name_input_text_box.GetY() + (name_input_text_box.GetH() / 2.0f) + 40.0f,true);
	name_input_label.AddControl();

	//Confirm Button
	Button& confirm_button = this->CreateControl<Button>();
	confirm_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(ConfirmTextID),Color::Gold);
	confirm_button.SetPosition(name_input_window.GetX() + (name_input_window.GetW() / 4.0f),name_input_label.GetY() + (name_input_label.GetH() / 2.0f) + 30.0f,true);
	confirm_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	confirm_button.AddEventOnClick(&NewGameMenu::ConfirmOnClick,*this);
	confirm_button.SetKeyboardKeyShortcut(KeyboardKey::Enter);
	confirm_button.AddControl();

	//Back Button
	Button& back_button = this->CreateControl<Button>();
	back_button.SetButton(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(BackTextID),Color::Gold);
	back_button.SetPosition(name_input_window.GetX() + (name_input_window.GetW() / 2.0f) + (name_input_window.GetW() / 4.0f),confirm_button.GetY() + (confirm_button.GetH() / 2.0f),true);
	back_button.AddEventOnClick(&NewGameMenu::BackOnClick,*this);
	back_button.SetKeyboardKeyShortcut(KeyboardKey::Esc);
	back_button.AddControl();
}

void NewGameMenu::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Novo jogo começará em breve
	if (this->starting_new_game)
	{
		//Aguardar a tela escurecer
		if (game.GetScreenEffect().FadeOutEnd())
		{
			//Começar o novo jogo
			this->NewGame();
		}
	}
	else
	{
		Label& name_input_label = this->GetControl<Label>(NameInputLabel);
		Button& confirm_button = this->GetControl<Button>(ConfirmButton);
		Button& back_button = this->GetControl<Button>(BackButton);

		//Mensagem indicando problema no nome
		static ColorChanger color_changer(Color::Red,Color(0.5f,0.0f,0.0f,1.0f),0.020f,0.5f);
		name_input_label.SetVisible(!confirm_button.GetEnabled());
		if (name_input_label.GetVisible())
			name_input_label.SetTextColor(color_changer.RunColorChanger(game.GetTimer()));

		//Tamanho mínimo para o nome
		TextBox& name_input_text_box = this->GetControl<TextBox>(NameInputTextBox);
		confirm_button.SetEnabled(name_input_text_box.GetString().size() >= 3);
	}
}

void NewGameMenu::CursorSelectorPositionUpdate()
{
	PictureBox& cursor_selector_picture_box = this->GetControl<PictureBox>(CursorSelectorPictureBox);
	cursor_selector_picture_box.SetPosition(this->class_selector_selected->GetX() + (this->class_selector_selected->GetW() / 2.0f),this->class_selector_selected->GetY() - (cursor_selector_picture_box.GetH() * 2.0f),true);
}

void NewGameMenu::NewGame()
{
	//Criando herói e outros dados para o novo jogo
	GameState::GetGame<GameRPG>().StartNewGame(static_cast<FileID>(this->class_selector_selected->GetTextureID()),this->GetControl<TextBox>(NameInputTextBox).GetString());

	//Carregar o gerenciador de mapas
	MapManager* map_manager = static_cast<MapManager*>(GameState::AddGameState(make_unique<MapManager>(),GameStateAction::DeleteCurrentGameState));

	//Carregar o primeiro mapa (Deve ser fora do Construtor do Map Manager para evitar conflitos com o Game States)
	map_manager->CreateMap(MapArea00ID,1,1);
}

void NewGameMenu::ClassSelectorOnClick(Control& control)
{
	//Deselecionando o Class Selector atual
	this->class_selector_selected->SetSelected(false);

	//Selecionando o Class Selector que foi clicado
	this->class_selector_selected = static_cast<ClassSelector*>(&control);
	this->class_selector_selected->SetSelected(true);

	//Atualizar a posicão do Cursor Selector
	this->CursorSelectorPositionUpdate();
}

void NewGameMenu::PreviousAvatarOnClick(const Control& control)
{
	this->class_selector_selected->PreviousAvatar();
}

void NewGameMenu::NextAvatarOnClick(const Control& control)
{
	this->class_selector_selected->NextAvatar();
}

void NewGameMenu::ConfirmOnClick(const Control& control)
{
	this->starting_new_game = true;

	this->GetControl<Button>(PreviousAvatarButton).SetEnabled(false);
	this->GetControl<Button>(NextAvatarButton).SetEnabled(false);
	this->GetControl<Button>(NameInputTextBox).SetEnabled(false);
	this->GetControl<Button>(ConfirmButton).SetEnabled(false);
	this->GetControl<Button>(BackButton).SetEnabled(false);
	this->GetControl<ClassSelector>(WarriorSelector).SetEnabled(false);
	this->GetControl<ClassSelector>(MageSelector).SetEnabled(false);

	GameState::GetGame<GameRPG>().GetScreenEffect().StartFadeOutScreen(ScreenEffectFadeMode::Fast);
}

void NewGameMenu::BackOnClick(const Control& control)
{
	GameState::AddGameState(nullptr,GameStateAction::DeleteCurrentGameState);
	GameState::GetGame<GameRPG>().GetAudio().PlaySoundFromBuffer(SoundCancelFileID);
}
#include "MapMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

MapMenu::MapMenu(const LanguageTextID map_name_text_id) :
	Menu(MapMenuControlMax),
	map_name_text_id(map_name_text_id),
	showing_map_name(false),
	command_window_speed_y(0.0f)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Map Name
	const Color& map_name_color = Color::Gold;
	Label& map_name_label = this->CreateControl<Label>();
	map_name_label.SetText(game.GetVideo().GetFont(FontNewRockerRegularFileID),game.GetDatabase().GetLanguageText(map_name_text_id),Color(map_name_color.GetRed(),map_name_color.GetGreen(),map_name_color.GetBlue(),0.0f));
	map_name_label.SetPosition(25.0f,25.0f);
	map_name_label.AddControl();

	//Command Window
	Window& command_window = this->CreateControl<Window>();
	command_window.SetPosition(25.0f,static_cast<float>(game.GetVideo().GetVirtualHeight()));
	this->UpdateWindow();
	command_window.AddControl();

	//Character Menu Button
	Button& character_menu_button = this->CreateControl<Button>();
	character_menu_button.SetButton(game.GetVideo().GetTexture(TextureCommonFileID),32.0f,32.0f,0.0f,66.0f);
	character_menu_button.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
	character_menu_button.NewToolTipTextLine(game.GetDatabase().GetLanguageText(CharacterMenuButtonDescriptionTextID),Color::White);
	character_menu_button.SetKeyboardKeyShortcut(KeyboardKey::C);
	character_menu_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	character_menu_button.AddEventOnClick(&MapMenu::CharacterMenuOnClick,*this);
	character_menu_button.SetEnabled(false);
	character_menu_button.AddControl();

	//Pause Menu Button
	Button& pause_menu_button = this->CreateControl<Button>();
	pause_menu_button.SetButton(game.GetVideo().GetTexture(TextureCommonFileID),32.0f,32.0f,0.0f,99.0f);
	pause_menu_button.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
	pause_menu_button.NewToolTipTextLine(game.GetDatabase().GetLanguageText(PauseMenuButtonDescriptionTextID),Color::White);
	pause_menu_button.SetKeyboardKeyShortcut(KeyboardKey::Esc);
	pause_menu_button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
	pause_menu_button.AddEventOnClick(&MapMenu::PauseMenuOnClick,*this);
	pause_menu_button.SetEnabled(false);
	pause_menu_button.AddControl();
}

void MapMenu::Pausing()
{
	GameState::Pausing();
	this->VisibleControls(false);
}

void MapMenu::Resuming()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	GameState::Resuming();
	this->VisibleControls(true);

	//Map Name Label
	this->GetControl<Label>(MapNameLabel).SetTextString(game.GetDatabase().GetLanguageText(map_name_text_id));

	//Command Window
	this->UpdateWindow();

	//Character Menu
	Button& character_menu_button = this->GetControl<Button>(CharacterMenuButton);
	character_menu_button.ClearToolTip();
	character_menu_button.NewToolTipTextLine(game.GetDatabase().GetLanguageText(CharacterMenuButtonDescriptionTextID),Color::White);

	//Pause Menu
	Button& pause_menu_button = this->GetControl<Button>(PauseMenuButton);
	pause_menu_button.ClearToolTip();
	pause_menu_button.NewToolTipTextLine(game.GetDatabase().GetLanguageText(PauseMenuButtonDescriptionTextID),Color::White);
}

void MapMenu::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	static Interval change_position_timer(0.015f);
	if (change_position_timer.Action(game.GetTimer()))
	{
		Window& command_window = this->GetControl<Window>(CommandWindow);
		Button& character_menu_button = this->GetControl<Button>(CharacterMenuButton);
		Button& pause_menu_button = this->GetControl<Button>(PauseMenuButton);

		const float command_window_value_max = static_cast<float>(game.GetVideo().GetVirtualHeight() - command_window.GetH() - 25.0f);
		if (command_window.GetY() != command_window_value_max)
		{
			//Command Window
			this->command_window_speed_y += 1.0f;
			command_window.SetPosition(command_window.GetX(),max(command_window.GetY() - this->command_window_speed_y,command_window_value_max));

			//Character Menu Button
			const float button_space = 5.0f;
			character_menu_button.SetPosition(command_window.GetX() + (command_window.GetW() / 2.0f) - (character_menu_button.GetW() / 2.0f) - button_space,command_window.GetY() + (command_window.GetH() / 2.0f),true);

			//Pause Menu Button
			pause_menu_button.SetPosition(command_window.GetX() + (command_window.GetW() / 2.0f) + (pause_menu_button.GetW() / 2.0f) + button_space,command_window.GetY() + (command_window.GetH() / 2.0f),true);
		}
		else
		{
			//Temporizador para depois que a janela chegar no seu local final, depois deste tempo começar a mostrar o nome do mapa
			static Interval map_name_timer(1.0f);

			//Se o botão não estiver habilitado ainda
			if (!character_menu_button.GetEnabled())
			{
				character_menu_button.SetEnabled(true);
				pause_menu_button.SetEnabled(true);
				map_name_timer.Synchronize(game.GetTimer());
			}

			//Passou o tempo então começar a mostrar o nome do mapa
			if (map_name_timer.Action(game.GetTimer()))
				this->showing_map_name = true;

			//Mostrando o nome do mapa utilizando transparência
			if (this->showing_map_name)
			{
				Label& map_name_label = this->GetControl<Label>(MapNameLabel);
				const Color& color = map_name_label.GetTextColor();

				//Enquanto não for for visível totalmente
				if (color.GetAlpha() != 1.0f)
					map_name_label.SetTextColor(Color(color.GetRed(),color.GetGreen(),color.GetBlue(),min(color.GetAlpha() + 0.025f,1.0f)));
				else
					this->showing_map_name = false;
			}
		}
	}
}

void MapMenu::UpdateWindow()
{
	GameState::GetGame<GameRPG>().SetWindow(this->GetControl<Window>(CommandWindow),3,1);
}

void MapMenu::CharacterMenuOnClick(const Control& control)
{
	GameState::AddGameState(make_unique<CharacterMenu>(true),GameStateAction::PauseCurrentGameState);
}

void MapMenu::PauseMenuOnClick(const Control& control)
{
	GameState::AddGameState(make_unique<PauseMenu>(),GameStateAction::PauseCurrentGameState);
}
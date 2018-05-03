#include "MainMenu.h"

using namespace std;
using namespace GPL;
using namespace TT;

MainMenu::MainMenu()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();
	const Video& video = game.GetVideo();
	Audio& audio = game.GetAudio();

	audio.PlayMusicFromPlaylist(static_cast<int>(FileID::MusicMainTheme));

	const Font& font = video.GetFont(static_cast<int>(FileID::FontTahoma));

	this->background.SetTexture(video.GetTexture(static_cast<int>(FileID::TextureBackground)));
	this->background.SetSize(static_cast<float>(video.GetVirtualWidth()),static_cast<float>(video.GetVirtualHeight()));

	this->window.SetWindow(14,18);
	this->window.SetPosition(static_cast<float>(video.GetVirtualWidth() / 2.0f),static_cast<float>(video.GetVirtualHeight() / 2.0f),true);
	this->window.AddControl();

	this->about.SetText(video.GetFont(static_cast<int>(FileID::FontSegoeUIBold)),"Developed by Marcelo Contarini. Original game and credits to: ",Color::White);
	this->about.SetPosition(40.0f,25.0f);
	this->about.AddControl();

	this->squaresoft_logo.SetSprite(video.GetTexture(static_cast<int>(FileID::TextureSquaresoftLogo)),200.0f,19.0f,0.0f,0.0f);
	this->squaresoft_logo.SetPosition(this->about.GetX() + this->about.GetW() + (this->squaresoft_logo.GetW() / 2.0f) + 10.0f,this->about.GetY() + (this->about.GetH() / 2.0f),true);
	this->squaresoft_logo.AddControl();

	this->controls_info.SetText(video.GetFont(static_cast<int>(FileID::FontSegoeUIBold)),"Controls: [Directionals: W, A, S, D] [Confirm: N] [Cancel: M] [End Match: ESC] [Joystick Support]",Color::Green);
	this->controls_info.SetPosition(5.0f,video.GetVirtualHeight() - (this->controls_info.GetH()) - 15.0f);
	this->controls_info.AddControl();
	
	this->info.SetText(video.GetFont(static_cast<int>(FileID::FontSegoeUIBold)),"INFO.",Color::Silver);
	this->info.SetPosition(this->window.GetX() + 10.0f,this->window.GetY());
	this->info.AddControl();

	this->music_on.SetText(font,"On",Color::Green);
	this->music_off.SetText(font,"Off",Color::Red);
	this->music_on.AddControl();

	float x = this->window.GetX() + 10.0f;
	float y = this->window.GetY() + 25.0f;

	this->rules_title.SetText(font,"Rules:",Color::Platinum);
	this->rules_title.SetPosition(x,y);
	this->rules_title.AddControl();

	x += 50.0f;
	y += this->rules_title.GetH() + 15;

	vector<string> rules_string;
	rules_string.push_back("Open");
	rules_string.push_back("Random");
	/*rules_string.push_back("Sudden Death");*/
	rules_string.push_back("Elemental (No AI)");
	/*rules_string.push_back("Same");
	rules_string.push_back("Same Wall");
	rules_string.push_back("Plus");*/

	for (auto& iterator : rules_string)
	{
		this->rules_stars.push_back(make_unique<PictureBox>());

		PictureBox& star = *this->rules_stars.back();

		float initial_x = x;

		star.SetSprite(video.GetTexture(static_cast<int>(FileID::TextureInterface)),23.0f,26.0f,2.0f,40.0f);
		star.SetPosition(x + 8.0f,y - 5.0f);

		x += star.GetW() + 10.0f;

		this->rules.push_back(make_unique<Label>());

		Label& rule = *this->rules.back();

		rule.SetText(font,iterator,Color::Platinum);
		rule.SetPosition(x,y);
		rule.AddControl();

		x = initial_x;
		y += rule.GetH() + 10;
	}

	x += 10.0f;
	y += 25.0f;

	vector<string> options_string;
	options_string.push_back("Music:");
	options_string.push_back("Difficulty Level:");
	options_string.push_back("Information");
	options_string.push_back("Play vs. Human");
	options_string.push_back("Play vs. Computer");
	options_string.push_back("Computer vs. Computer");
	options_string.push_back("Quit");

	for (auto& iterator : options_string)
	{
		this->options.push_back(make_unique<Label>());

		Label& option = *this->options.back();

		option.SetText(font,iterator,Color::Platinum);
		option.SetPosition(x,y);
		option.AddControl();

		y += option.GetH() + 10;
	}

	Label& music_label = *this->options.front();

	x = music_label.GetX() + music_label.GetW() + 5.0f;
	y = music_label.GetY();

	this->music_on.SetPosition(x,y);
	this->music_off.SetPosition(x,y);



	Label& difficulty_level_label = *this->options[1];

	x = difficulty_level_label.GetX() + difficulty_level_label.GetW() + 7.0f;
	y = difficulty_level_label.GetY();

	for (int i = 0; i < game.GetDifficultyLevel().GetTotal(); i++)
	{
		this->difficulty_level_stars.push_back(make_unique<PictureBox>());

		PictureBox& star = *this->difficulty_level_stars.back();

		star.SetSprite(video.GetTexture(static_cast<int>(FileID::TextureInterface)),23.0f,26.0f,2.0f,40.0f);
		star.SetPosition(x,y - 5.0f);

		x += star.GetW();

		if (i <= game.GetDifficultyLevel().GetCurrent())
		{
			star.AddControl();
		}
	}

	this->cursor.SetSprite(video.GetTexture(static_cast<int>(FileID::TextureInterface)),60.0f,35.0f,0.0f,0.0f);
	this->cursor.AddControl();

	this->options_quantity.SetTotal(rules_string.size() + options_string.size());
	this->options_quantity.SetCurrent(this->options_quantity.GetTotal() - 3);

	this->information_dialogue_box.SetDialogueBox(font,10,400.0f,15.0f,15.0f,0.015f,options_string.front(),Color::Silver);
	this->information_dialogue_box.SetWindow();
	this->information_dialogue_box.AddText("Triple Triad is played on a three-by-three (3x3) square grid of blank spaces, where cards will be placed as the game progresses. ",Color::Platinum);
	this->information_dialogue_box.AddText("The cards depict various characters, monsters, and bosses from the game. ",Color::Platinum);
	this->information_dialogue_box.AddText("Each card has four numbers (known as Ranks) placed in top left corner; each number corresponds to one of the four sides of the card. ",Color::Platinum);
	this->information_dialogue_box.AddText("These numbers range from one to nine, the letter A representing ten. ",Color::Platinum);
	this->information_dialogue_box.AddText("On the top right of the card there is sometimes an elemental symbol representing the card's element. ",Color::Platinum);
	this->information_dialogue_box.AddText("The elements are Earth, Fire, Water, Poison, Holy, Lightning, Wind, and Ice. ",Color::Platinum);
	this->information_dialogue_box.AddText("There are two card colors, pink (the opponent's cards) and blue (the player's cards). ",Color::Platinum);
	this->information_dialogue_box.AddText("In a basic game of Triple Triad, each player has five cards. ",Color::Platinum);
	this->information_dialogue_box.AddText("A coin-flip decision is made to decide which of the two players will begin. ",Color::Platinum);
	this->information_dialogue_box.AddText("The player who wins the coin toss may then choose a card to play anywhere on the grid. ",Color::Platinum);
	this->information_dialogue_box.AddText("After the first card is played, the opposing player may then play a card on any unoccupied space on the board. ",Color::Platinum);
	this->information_dialogue_box.AddText("The game continues with players' turns alternating in this fashion. ",Color::Platinum);
	this->information_dialogue_box.AddText("To win, a majority of the total ten cards played (including the one card that is not placed on the board) must be of the player's card color. ",Color::Platinum);
	this->information_dialogue_box.AddText("To do this, the player must capture cards. ",Color::Platinum);
	this->information_dialogue_box.AddText("To capture a card, the player must place cards adjacent to an opponent's card, whereupon the 'ranks' of the sides where the two cards touch will be compared. ",Color::Platinum);
	this->information_dialogue_box.AddText("If the rank of the opponent's card is higher than the player's card, the player's card will be captured and turned into the opponent's color. ",Color::Platinum);
	this->information_dialogue_box.AddText("If, however, it is the player's rank that is higher, the opponent's card will be captured and changed into the player's color instead. ",Color::Platinum);
	this->information_dialogue_box.AddText("Capturing can only occur during that player's turn, and no other opponent can capture a card during said turn. ",Color::Platinum);
	this->information_dialogue_box.AddText("A 'draw' will occur if the player and the opponent possess equal numbers of cards in their color on the board. ",Color::Platinum);
	this->information_dialogue_box.AddText("Depending on alternate card rules, this can be defined by a 'sudden death' scenario where the first person to capture a card in a new game wins, or by playing until a winner is defined. ",Color::Platinum);
}

void MainMenu::ControlsUpdate(const bool add_controls)
{
	void (Control::*PointerActionControl)() = ((add_controls) ? (&Control::AddControl) : (&Control::RemoveControl));

	(this->window.*PointerActionControl)();
	(this->about.*PointerActionControl)();
	(this->squaresoft_logo.*PointerActionControl)();
	(this->controls_info.*PointerActionControl)();
	(this->info.*PointerActionControl)();
	(this->rules_title.*PointerActionControl)();
	(this->cursor.*PointerActionControl)();
	(this->music_on.*PointerActionControl)();
	(this->music_off.*PointerActionControl)();

	for (auto& iterator : this->rules)
		((*iterator).*PointerActionControl)();

	for (auto& iterator : this->options)
		((*iterator).*PointerActionControl)();

	this->RuleStarsUpdate();
	this->MusicOptionUpdate(add_controls);
	this->DifficultyLevelStars(add_controls);
}

void MainMenu::CursorPosition(const int current_option_index)
{
	vector<Label*> all_options;

	for (auto& iterator : this->rules)
		all_options.push_back(iterator.get());

	for (auto& iterator : this->options)
		all_options.push_back(iterator.get());

	const Label& current_option = *all_options[current_option_index];

	const float x = this->rules_title.GetX() + (this->rules_title.GetW() / 2.0f);
	const float y = current_option.GetY() + (current_option.GetH() / 2.0f) + 7.0f;

	this->cursor.SetPosition(x,y,true);
}

void MainMenu::RuleStarsUpdate()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	for (size_t i = 0; i < this->rules.size(); i++)
	{
		PictureBox& star = *this->rules_stars[i];

		if ((game.IsRuleEnabled(i)) && (!this->GetPause()))
			star.AddControl();
		else
			star.RemoveControl();
	}
}

void MainMenu::MusicOptionUpdate(const bool use_labels)
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	if (use_labels)
	{
		if (game.GetMusicPlaying())
		{
			this->music_on.AddControl();
			this->music_off.RemoveControl();
		}
		else
		{
			this->music_off.AddControl();
			this->music_on.RemoveControl();
		}
	}
	else
	{
		this->music_on.RemoveControl();
		this->music_off.RemoveControl();
	}
}

void MainMenu::DifficultyLevelStars(const bool use_stars)
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	for (auto& iterator : this->difficulty_level_stars)
	{
		iterator->RemoveControl();
	}

	if (use_stars)
	{
		for (int i = 0; i < game.GetDifficultyLevel().GetCurrent() + 1; i++)
		{
			this->difficulty_level_stars[i]->AddControl();
		}
	}
}

void MainMenu::Pausing()
{
	GameState::Pausing();
	this->ControlsUpdate(false);
}

void MainMenu::Resuming()
{
	GameState::Resuming();
	this->ControlsUpdate(true);
	GameState::GetGame<GameTripleTriad>().SetCurrentPlayer(0);
}

void MainMenu::Update()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();
	const Video& video = game.GetVideo();
	const Input& input = game.GetInput();

	if (this->information_dialogue_box.IsRemoved())
	{
		bool play_cursor_move = false;

		const int quit_index = this->options_quantity.GetTotal() - 1;
		const int computer_vs_computer = quit_index - 1;
		const int play_vs_computer_index = computer_vs_computer - 1;
		const int play_vs_human_index = play_vs_computer_index - 1;
		const int information_index = play_vs_human_index - 1;
		const int difficulty_level_index = information_index - 1;
		const int music_index = difficulty_level_index - 1;

		const int current_option_index = this->options_quantity.GetCurrent();

		const Player& player = game.GetCurrentPlayer();

		if (input.IsKeyboardKeyPressedOnce(player.GetKeyboardKeyDown()) || (input.IsJoystickPOVDown()))
		{
			this->options_quantity.Next();
			play_cursor_move = true;
		}

		else if (input.IsKeyboardKeyPressedOnce(player.GetKeyboardKeyUp()) || (input.IsJoystickPOVUp()))
		{
			this->options_quantity.Previous();
			play_cursor_move = true;
		}

		else if (input.IsKeyboardKeyPressedOnce(player.GetKeyboardKeyConfirm()) || (input.IsJoystickButtonPressedOnce(player.GetJoystickButtonConfirm())))
		{
			play_cursor_move = true;

			if (current_option_index == music_index)
			{
				Audio& audio = game.GetAudio();

				if (game.GetMusicPlaying())
				{
					audio.DisableMusic();
				}
				else
				{
					audio.EnableMusic();
				}
				game.SetMusicPlaying(!game.GetMusicPlaying());

				this->MusicOptionUpdate(true);
			}
			else if (current_option_index == difficulty_level_index)
			{
				game.GetDifficultyLevel().Next();
				this->DifficultyLevelStars(true);
				play_cursor_move = true;
			}
			else if (current_option_index == information_index)
			{
				this->information_dialogue_box.AddControl();
			}
			else if (current_option_index == play_vs_human_index)
			{
				game.NewMatchGame(true,true);
				GameState::AddGameState(make_unique<MatchGame>(),GameStateAction::PauseCurrentGameState);
			}

			else if (current_option_index == play_vs_computer_index)
			{
				game.NewMatchGame(true,false);
				GameState::AddGameState(make_unique<MatchGame>(),GameStateAction::PauseCurrentGameState);
			}

			else if (current_option_index == computer_vs_computer)
			{
				game.NewMatchGame(false,false);
				GameState::AddGameState(make_unique<MatchGame>(),GameStateAction::PauseCurrentGameState);
			}

			else if (current_option_index == quit_index)
			{
				game.GetApplication().Quit();
				play_cursor_move = false;
			}

			else
			{
				if (game.IsRuleEnabled(current_option_index))
					game.DisableRule(current_option_index);
				else
					game.EnableRule(current_option_index);
			}
		}

		else if (input.IsKeyboardKeyPressedOnce(player.GetKeyboardKeyCancel()) || (input.IsJoystickButtonPressedOnce(player.GetJoystickButtonCancel())))
		{
			game.GetAudio().PlaySoundFromBuffer(static_cast<int>(FileID::SoundCursorCancel));
			this->options_quantity.SetCurrent(quit_index);
		}

		else if (input.IsKeyboardKeyPressedOnce(KeyboardKey::Esc))
			game.GetApplication().Quit();

		if (current_option_index == difficulty_level_index)
		{
			if (input.IsKeyboardKeyPressedOnce(player.GetKeyboardKeyLeft()) || input.IsJoystickPOVLeft())
			{
				game.GetDifficultyLevel().Previous();
				this->DifficultyLevelStars(true);
				play_cursor_move = true;
			}
			else if (input.IsKeyboardKeyPressedOnce(player.GetKeyboardKeyRight()) || input.IsJoystickPOVRight())
			{
				game.GetDifficultyLevel().Next();
				this->DifficultyLevelStars(true);
				play_cursor_move = true;
			}
		}

		if (play_cursor_move)
			game.GetAudio().PlaySoundFromBuffer(static_cast<int>(FileID::SoundCursorMove));

		this->CursorPosition(current_option_index);
		this->RuleStarsUpdate();
	}
	else
	{
		if (!this->information_dialogue_box.IsControlFocused())
			this->information_dialogue_box.GainFocus(true);
	}

	this->information_dialogue_box.SetPosition(video.GetVirtualWidth() / 2.0f,video.GetVirtualHeight() / 2.0f,true);
}

void MainMenu::Show()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	this->background.Show(game.GetVideo());
}
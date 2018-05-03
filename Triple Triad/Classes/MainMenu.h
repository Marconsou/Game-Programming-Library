#ifndef MAINMENU_H
#define MAINMENU_H

#include "DialogueBox.h"
#include "PictureBox.h"
#include "MatchGame.h"

namespace TT
{
	class MainMenu : public GPL::GameState
	{
	public:
		MainMenu();
	private:
		GPL::Quantity options_quantity;
		GPL::Sprite background;
		GPL::Window window;
		GPL::Label about;
		GPL::Label controls_info;
		GPL::Label info;
		GPL::Label rules_title;
		GPL::Label music_on;
		GPL::Label music_off;
		GPL::PictureBox squaresoft_logo;
		GPL::PictureBox cursor;
		GPL::DialogueBox information_dialogue_box;
		std::vector<std::unique_ptr<GPL::Label>> rules;
		std::vector<std::unique_ptr<GPL::Label>> options;
		std::vector<std::unique_ptr<GPL::PictureBox>> rules_stars;
		std::vector<std::unique_ptr<GPL::PictureBox>> difficulty_level_stars;
		MainMenu(const MainMenu&) = delete;
		MainMenu& operator=(const MainMenu&) = delete;
		void ControlsUpdate(const bool add_controls);
		void CursorPosition(const int current_option_index);
		void RuleStarsUpdate();
		void MusicOptionUpdate(const bool use_labels);
		void DifficultyLevelStars(const bool use_stars);
		void Pausing() override;
		void Resuming() override;
		void Update() override;
		void Show() override;
	};
}

#endif
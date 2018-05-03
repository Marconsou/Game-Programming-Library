#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include "Interval.h"
#include "Audio.h"
#include "Card.h"
#include "Main.h"

namespace TT
{
	class Player
	{
	public:
		using Cards = std::array<Card,5>;
		Player();
		GPL::KeyboardKey GetKeyboardKeyLeft() const;
		GPL::KeyboardKey GetKeyboardKeyRight() const;
		GPL::KeyboardKey GetKeyboardKeyUp() const;
		GPL::KeyboardKey GetKeyboardKeyDown() const;
		GPL::KeyboardKey GetKeyboardKeyConfirm() const;
		GPL::KeyboardKey GetKeyboardKeyCancel() const;
		GPL::JoystickButton GetJoystickButtonConfirm() const;
		GPL::JoystickButton GetJoystickButtonCancel() const;
		const GPL::Point2D<float>& GetPosition() const;
		Card& GetCard(const size_t index);
		Cards& GetCards();
		const Cards& GetCards() const;
		bool IsHumanPlayer() const;
		bool IsHiddenCards() const;
		void Initialize(const bool flip_cards,const bool hidden_cards,bool is_human_player);
		int CalculateScore(const std::vector<Card*>& current_game_cards) const;
		int CardsOnHand() const;
		void KeyboardKeyActions(const GPL::KeyboardKey left,const GPL::KeyboardKey right,const GPL::KeyboardKey up,const GPL::KeyboardKey down,const GPL::KeyboardKey confirm,const GPL::KeyboardKey cancel);
		void JoystickButtonActions(const GPL::JoystickButton confirm,const GPL::JoystickButton cancel);
		void AddCard(const CardStats& card_stats);
		void PrepareToPlaceCards(const GPL::Timer& timer,const float initial_x,const float initial_y);
		bool PlaceCards(GPL::Audio& audio,const GPL::Timer& timer);
		void PrepareToFlipCards(const GPL::Timer& timer);
		bool FlipCards(const GPL::Timer& timer);
		void Update(const GPL::Video& video);
		void MatchGameStatedUpdate(const GPL::Timer& timer,const Player& player_opponent,const std::vector<Card*>& current_game_cards);
		void Show(GPL::Video& video);
		void ShowCardsOnHand(GPL::Video& video);
		void ShowCardsPlacedOnBoard(GPL::Video& video);
		void ShowCardsCapturing(GPL::Video& video);
	private:
		struct CardAnimation
		{
			bool start_placing_card{};
			bool card_placed{};
			bool start_flipping_card{};
			bool card_flipped{};

			float placing_card_limit{};
			float placing_card_accel{};
			GPL::Interval start_placing_card_timer;
			GPL::Interval placing_card_accel_timer;
			GPL::Interval start_flipping_card_timer;
			GPL::Interval flipping_card_accel_timer;
		};

		size_t add_card_index{};
		bool human_player{};
		bool prepare_to_place_cards{};
		bool placing_cards{};
		bool prepare_to_flip_cards{};
		bool flipping_cards{};
		bool hidden_cards{};
		bool raising_from_hand{};
		const Card* raising_from_hand_card{};
		std::vector<Card* const> cards_moving_down;
		std::vector<float> cards_moving_down_y;
		GPL::Interval adjust_card_timer{0.015f};
		GPL::Interval capturing_card_timer{0.015f};
		GPL::KeyboardKey kk_left;
		GPL::KeyboardKey kk_right;
		GPL::KeyboardKey kk_up;
		GPL::KeyboardKey kk_down;
		GPL::KeyboardKey kk_confirm;
		GPL::KeyboardKey kk_cancel;
		GPL::JoystickButton jb_confirm;
		GPL::JoystickButton jb_cancel;
		GPL::Point2D<float> position;
		Cards cards;
		std::array<CardAnimation,5> cards_animation;
		Player(const Player&) = delete;
		Player& operator=(const Player&) = delete;
		void MovingCardsDown(const GPL::Timer& timer);
		void CheckCaptureCards(const GPL::Timer& timer,const Player& player_opponent,const std::vector<Card*>& current_game_cards);
	};
}

#endif
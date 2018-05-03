#ifndef MATCHGAME_H
#define MATCHGAME_H

#include "Label.h"
#include "GameState.h"
#include "GameTripleTriad.h"
#include "Minimax.h"

namespace TT
{
	class MatchGame : public GPL::GameState
	{
	public:
		MatchGame();
		~MatchGame();
	private:
		bool show_player_turn_indicator{};
		bool prepare_spinning_indicator{true};
		bool spinning_indicator{};
		bool start_match_game{};
		bool selecting_card_from_hand{};
		bool selecting_place_on_the_board{};
		bool placing_card_on_the_board{};
		bool raising_card{};
		bool wait_for_cards_being_captured{};
		bool match_ended{};
		float rotate_accel_indicator{};
		float raising_card_y_accel{};
		Card* selecting_card{};
		Card* placing_card{};
		GPL::Quantity cursor_selecting_card_quantity{0,5};
		GPL::Quantity cursor_placing_card_quantity{static_cast<int>(BoardSlotLayout::Center),static_cast<int>(BoardSlotLayout::Max)};
		GPL::Interval start_spinning_indicator_timer{0.015f};
		GPL::Interval finish_spinning_indicator_timer{1.000f};
		GPL::Interval indicator_movement_timer;
		GPL::Interval raising_card_timer{0.020f};
		GPL::Model player_turn_indicator{GPL::PrimitiveType::TriangleList,4,4,12};
		GPL::Sprite cursor_selecting_card;
		GPL::Sprite cursor_placing_card;
		GPL::Text player_1_score;
		GPL::Text player_2_score;
		GPL::Text match_result;
		GPL::Label card_name;
		GPL::Label info;
		GPL::Window window;
		MatchGame(const MatchGame&) = delete;
		MatchGame& operator=(const MatchGame&) = delete;
		void PrepareSpinningIndicator();
		void StartSpinningIndicator();
		void RandomPlayerTurn();
		void FinishSpinningIndicator();
		void IndicatorMovement();
		void IndicatorRotationUpdate();
		void ResetIndicatorRotation();
		void PlayerSelectsCard();
		bool MoveCursorSelectingCard(const bool next);
		void MoveCursorSelectingCardToFirstOnHand();
		bool IsSelectingCardOnHand() const;
		void SelectingCardUpdate();
		void ConfirmPlaceCardOnBoard();
		void PlayerPlacesCardOnBoard();
		void StartMatchGameUpdate();
		void RaisingCard();
		void RaisedCardOffScreen();
		void CardPlacedOnBoard();
		void PassPlayerTurn();
		void PlayerScoreUpdate();
		void CardName();
		void MatchEnded();
		void Update() override;
		void Show() override;
	};
}

#endif
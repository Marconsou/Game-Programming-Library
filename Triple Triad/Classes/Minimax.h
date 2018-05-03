#ifndef MINIMAX_H
#define MINIMAX_H

#include "Player.h"
#include "Board.h"

namespace TT
{
	class Minimax
	{
	public:
		enum class Neighbor
		{
			Left,
			Right,
			Top,
			Bottom,
		};

		struct Card;
		struct CapturedCard
		{
			Card* target_card{};
			const Player* target_card_player{};
		};

		struct Card
		{
			TT::Card* source_card{};
			int left{};
			int top{};
			int right{};
			int bottom{};
			bool played_on_board{};
			const Player* captured_player{};
			std::list<CapturedCard> captured_cards;
		};

		struct GameState
		{
			const Player* player_min{};
			const Player* player_max{};
			std::vector<Card*> player_min_cards;
			std::vector<Card*> player_max_cards;
			std::array<Card*,9> board_cards;
			std::array<Card,5 + 5> current_game_cards;
			Card* ConvertCurrentCard(TT::Card* current_card);
			void RestoreCapturedCards(Card& card);
			Minimax::Card GameState::_CopyCard(TT::Card& card);
			void CopyCards(std::vector<TT::Card*>& current_game_cards);
			void SetBoardCards(const Board& board);
			void SetPlayerCards();
			bool IsBoardFull() const;
			int CalculateScore(const Player* player) const;
			const Player* CheckForWinnerCondition() const;
			bool IsPlayerMinWinner(const Player* player) const;
			bool IsPlayerMaxWinner(const Player* player) const;
			int ScoreBetweenPlayerMaxAndPlayerMin() const;
			void GetNeighborCards(Card*& left_card,Card*& right_card,Card*& top_card,Card*& bottom_card,const int board_card_index);
			void GameState::GetNeighborWalls(bool& left_wall,bool& right_wall,bool& top_wall,bool& bottom_wall,const int board_card_index);
			void CheckForBasicRule(Card& placed_card,const int board_card_index);
			void CheckNeighborCardValue(Card& placed_card,Card& target_card,const Neighbor neighbor);
			int CheckForGoodMoves(const Player* player);
		};

		static void ComputerMove(TT::Card* current_card,std::vector<TT::Card*>& current_game_cards,const Board& board,Player& player_min,Player& player_max,const Card*& best_card,int& best_position,int& score,const int depth);
	private:
		static GameState game_state;
		Minimax() = delete;
		Minimax(const Minimax&) = delete;
		Minimax& operator=(const Minimax&) = delete;
		static int Value(GameState& game_state,const bool maximize_player,const int depth);
	};
}

#endif
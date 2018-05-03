#include "Minimax.h"

using namespace std;
using namespace TT;

Minimax::GameState Minimax::game_state;

Minimax::Card* Minimax::GameState::ConvertCurrentCard(TT::Card* current_card)
{
	for (auto& iterator : this->current_game_cards)
	{
		if (iterator.source_card == current_card)
		{
			return &iterator;
		}
	}
	return nullptr;
}

void Minimax::GameState::RestoreCapturedCards(Card& card)
{
	for (auto& iterator : card.captured_cards)
	{
		iterator.target_card->captured_player = iterator.target_card_player;
	}
	card.captured_cards.clear();
}

Minimax::Card Minimax::GameState::_CopyCard(TT::Card& card)
{
	Card new_card;

	const CardStats& card_stats = card.GetCardStats();

	new_card.source_card = &card;
	new_card.left = card_stats.GetLeft();
	new_card.top = card_stats.GetTop();
	new_card.right = card_stats.GetRight();
	new_card.bottom = card_stats.GetBottom();
	new_card.played_on_board = (card.GetCardState() == CardState::PlacedOnBoard);
	new_card.captured_player = &card.GetCapturedPlayer();
	return new_card;
}

void Minimax::GameState::CopyCards(vector<TT::Card*>& current_game_cards)
{
	for (size_t i = 0; i < current_game_cards.size(); i++)
	{
		TT::Card& iterator = *current_game_cards[i];

		this->current_game_cards[i] = _CopyCard(iterator);
	}
}

void Minimax::GameState::SetBoardCards(const Board& board)
{
	for (size_t i = 0; i < static_cast<int>(BoardSlotLayout::Max); i++)
	{
		const TT::Card* board_card_iterator = &board.GetBoardSlotCard(i);

		this->board_cards[i] = nullptr;

		if (board_card_iterator)
		{
			for (auto& current_game_card_iterator : this->current_game_cards)
			{
				if (current_game_card_iterator.source_card == board_card_iterator)
				{
					this->board_cards[i] = &current_game_card_iterator;
				}
			}
		}
	}
}

void Minimax::GameState::SetPlayerCards()
{
	this->player_min_cards.clear();
	this->player_max_cards.clear();
	for (auto& iterator : this->current_game_cards)
	{
		if (iterator.source_card->GetCardState() == CardState::OnHand)
		{
			if (iterator.captured_player == this->player_min)
			{
				this->player_min_cards.push_back(&iterator);
			}
			else if (iterator.captured_player == this->player_max)
			{
				this->player_max_cards.push_back(&iterator);
			}
		}
	}
}

bool Minimax::GameState::IsBoardFull() const
{
	size_t counter = 0;
	for (auto& iterator : this->board_cards)
	{
		if (iterator)
			counter++;
	}
	return (counter == this->board_cards.size());
}

int Minimax::GameState::CalculateScore(const Player* player) const
{
	int score = 0;
	for (auto& iterator : this->current_game_cards)
	{
		if (iterator.captured_player == player)
			score++;
	}
	return score;
}

const Player* Minimax::GameState::CheckForWinnerCondition() const
{
	if (this->IsBoardFull())
	{
		const int player_min_score = this->CalculateScore(this->player_min);
		const int player_max_score = this->CalculateScore(this->player_max);

		if (player_min_score > player_max_score)
		{
			return this->player_min;
		}
		else if (player_min_score < player_max_score)
		{
			return this->player_max;
		}
	}
	return nullptr;
}

bool Minimax::GameState::IsPlayerMinWinner(const Player* player) const
{
	return (this->player_min == player);
}

bool Minimax::GameState::IsPlayerMaxWinner(const Player* player) const
{
	return (this->player_max == player);
}

int Minimax::GameState::ScoreBetweenPlayerMaxAndPlayerMin() const
{
	const int player_min_score = this->CalculateScore(this->player_min);
	const int player_max_score = this->CalculateScore(this->player_max);

	return (player_max_score - player_min_score);
}

void Minimax::GameState::GetNeighborCards(Card*& left_card,Card*& right_card,Card*& top_card,Card*& bottom_card,const int board_card_index)
{
	const int mod_value = board_card_index % 3;

	//Add left
	if (mod_value != 0)
		left_card = this->board_cards[board_card_index - 1];

	//Add right
	if (mod_value != 2)
		right_card = this->board_cards[board_card_index + 1];

	//Add top
	if (board_card_index - 2 > 0)
		top_card = this->board_cards[board_card_index - 3];

	//Add bottom
	if (board_card_index - 5 <= 0)
		bottom_card = this->board_cards[board_card_index + 3];
}

void Minimax::GameState::GetNeighborWalls(bool& left_wall,bool& right_wall,bool& top_wall,bool& bottom_wall,const int board_card_index)
{
	left_wall = false;
	right_wall = false;
	top_wall = false;
	bottom_wall = false;

	if (board_card_index == 0)
	{
		left_wall = top_wall = true;
	}
	else if(board_card_index == 1)
	{
		top_wall = true;
	}
	else if (board_card_index == 2)
	{
		right_wall = top_wall = true;
	}
	else if (board_card_index == 3)
	{
		left_wall = true;
	}
	else if (board_card_index == 4)
	{
		
	}
	else if (board_card_index == 5)
	{
		right_wall = true;
	}
	else if (board_card_index == 6)
	{
		left_wall = bottom_wall = true;
	}
	else if (board_card_index == 7)
	{
		bottom_wall = true;
	}
	else if (board_card_index == 8)
	{
		right_wall = bottom_wall = true;
	}
}

void Minimax::GameState::CheckForBasicRule(Card& placed_card,const int board_card_index)
{
	Card* left_card{};
	Card* right_card{};
	Card* top_card{};
	Card* bottom_card{};

	this->GetNeighborCards(left_card,right_card,top_card,bottom_card,board_card_index);

	if (left_card)
	{
		this->CheckNeighborCardValue(placed_card,*left_card,Neighbor::Left);
	}

	if (right_card)
	{
		this->CheckNeighborCardValue(placed_card,*right_card,Neighbor::Right);
	}

	if (top_card)
	{
		this->CheckNeighborCardValue(placed_card,*top_card,Neighbor::Top);
	}

	if (bottom_card)
	{
		this->CheckNeighborCardValue(placed_card,*bottom_card,Neighbor::Bottom);
	}
}

void Minimax::GameState::CheckNeighborCardValue(Card& placed_card,Card& target_card,const Neighbor neighbor)
{
	if (placed_card.captured_player != target_card.captured_player)
	{
		int value{};
		int opposite_value{};

		if (neighbor == Neighbor::Left)
		{
			value = placed_card.left;
			opposite_value = target_card.right;
		}
		else if (neighbor == Neighbor::Right)
		{
			value = placed_card.right;
			opposite_value = target_card.left;
		}
		else if (neighbor == Neighbor::Top)
		{
			value = placed_card.top;
			opposite_value = target_card.bottom;
		}
		else if (neighbor == Neighbor::Bottom)
		{
			value = placed_card.bottom;
			opposite_value = target_card.top;
		}

		if (value > opposite_value)
		{
			CapturedCard capture_card;
			capture_card.target_card = &target_card;
			capture_card.target_card_player = target_card.captured_player;

			placed_card.captured_cards.push_back(capture_card);

			target_card.captured_player = placed_card.captured_player;
		}
	}
}

int Minimax::GameState::CheckForGoodMoves(const Player* player)
{
	Card* left_card{};
	Card* right_card{};
	Card* top_card{};
	Card* bottom_card{};

	int score = 0;

	for (size_t i = 0; i < this->board_cards.size(); i++)
	{
		auto& iterator = this->board_cards[i];

		if (iterator)
		{
			if (iterator->captured_player == player)
			{
				bool left_wall{};
				bool right_wall{};
				bool top_wall{};
				bool bottom_wall{};

				this->GetNeighborCards(left_card,right_card,top_card,bottom_card,i);
				this->GetNeighborWalls(left_wall,right_wall,top_wall,bottom_wall,i);

				const bool is_left_side_protected = (left_card) || (left_wall);
				const bool is_right_side_protected = (right_card) || (right_wall);
				const bool is_top_side_protected = (top_card) || (top_wall);
				const bool is_bottom_side_protected = (bottom_card) || (bottom_wall);

				const int captured_cards_score = 100;

				if (!iterator->captured_cards.empty())
				{
					int total_score = 0;
					for (auto& captured_card_iterator : iterator->captured_cards)
					{
						total_score += captured_card_iterator.target_card->left;
						total_score += captured_card_iterator.target_card->right;
						total_score += captured_card_iterator.target_card->top;
						total_score += captured_card_iterator.target_card->bottom;
					}
					score += (total_score * 1);
				}

				if (is_left_side_protected)
				{
					if (!is_right_side_protected)
						score += iterator->right;
				}

				if (is_right_side_protected)
				{
					if (!is_left_side_protected)
						score += iterator->left;
				}

				if (is_top_side_protected)
				{
					if (!is_bottom_side_protected)
						score += iterator->bottom;
				}

				if (is_bottom_side_protected)
				{
					if (!is_top_side_protected)
						score += iterator->top;
				}
			}
		}
	}
	return score;
}

int Minimax::Value(GameState& game_state,const bool maximize_player,const int depth)
{
	const Player* player_winner = Minimax::game_state.CheckForWinnerCondition();

	if ((depth == 0) || (player_winner != nullptr) || (game_state.IsBoardFull()))
	{
		const int winner_bonus_score = 1000;

		int score = Minimax::game_state.ScoreBetweenPlayerMaxAndPlayerMin() * winner_bonus_score;

		if (Minimax::game_state.IsPlayerMaxWinner(player_winner))
		{
			return score;
		}
		else if (Minimax::game_state.IsPlayerMinWinner(player_winner))
		{
			return score;
		}

		if (maximize_player)
		{
			return game_state.CheckForGoodMoves(game_state.player_max);
		}
		else
		{
			return -game_state.CheckForGoodMoves(game_state.player_min);
		}
	}

	std::vector<Card*>& current_player_cards = maximize_player ? Minimax::game_state.player_max_cards : Minimax::game_state.player_min_cards;

	if (maximize_player)
	{
		int score = INT_MIN;
		for (auto& player_card_iterator : current_player_cards)
		{
			if (!player_card_iterator->played_on_board)
			{
				for (size_t i = 0; i < Minimax::game_state.board_cards.size(); i++)
				{
					auto& board_card_iterator = Minimax::game_state.board_cards[i];

					if (!board_card_iterator)
					{
						board_card_iterator = player_card_iterator;
						board_card_iterator->played_on_board = true;
						Minimax::game_state.CheckForBasicRule(*board_card_iterator,i);

						int temp_score = Minimax::Value(Minimax::game_state,false,depth - 1);

						Minimax::game_state.RestoreCapturedCards(*board_card_iterator);
						board_card_iterator->played_on_board = false;
						board_card_iterator = nullptr;

						if (temp_score > score)
						{
							score = temp_score;
						}
					}
				}
			}
		}
		return score;
	}
	else
	{
		int score = INT_MAX;
		for (auto& player_card_iterator : current_player_cards)
		{
			if (!player_card_iterator->played_on_board)
			{
				for (size_t i = 0; i < Minimax::game_state.board_cards.size(); i++)
				{
					auto& board_card_iterator = Minimax::game_state.board_cards[i];

					if (!board_card_iterator)
					{
						board_card_iterator = player_card_iterator;
						board_card_iterator->played_on_board = true;
						Minimax::game_state.CheckForBasicRule(*board_card_iterator,i);

						int temp_score = Minimax::Value(Minimax::game_state,true,depth - 1);

						Minimax::game_state.RestoreCapturedCards(*board_card_iterator);
						board_card_iterator->played_on_board = false;
						board_card_iterator = nullptr;

						if (temp_score < score)
						{
							score = temp_score;
						}
					}
				}
			}
		}
		return score;
	}
}

void Minimax::ComputerMove(TT::Card* current_card,vector<TT::Card*>& current_game_cards,const Board& board,Player& player_min,Player& player_max,const Card*& best_card,int& best_position,int& score,const int depth)
{
	Minimax::game_state.player_min = &player_min;
	Minimax::game_state.player_max = &player_max;
	Minimax::game_state.CopyCards(current_game_cards);
	Minimax::game_state.SetPlayerCards();
	Minimax::game_state.SetBoardCards(board);

	Card* converted_current_card = Minimax::game_state.ConvertCurrentCard(current_card);

	auto& player_card_iterator = converted_current_card;

	if (!player_card_iterator->played_on_board)
	{
		for (size_t i = 0; i < Minimax::game_state.board_cards.size(); i++)
		{
			auto& board_card_iterator = Minimax::game_state.board_cards[i];

			if (!board_card_iterator)
			{
				board_card_iterator = player_card_iterator;
				board_card_iterator->played_on_board = true;
				Minimax::game_state.CheckForBasicRule(*board_card_iterator,i);

				int temp_score = Minimax::Value(Minimax::game_state,false,depth);

				Minimax::game_state.RestoreCapturedCards(*board_card_iterator);
				board_card_iterator->played_on_board = false;
				board_card_iterator = nullptr;

				if (temp_score > score)
				{
					score = temp_score;

					best_position = i;
					best_card = player_card_iterator;
				}
			}
		}
	}
}
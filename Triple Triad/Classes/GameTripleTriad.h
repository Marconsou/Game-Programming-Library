#ifndef GAMETRIPLETRIAD_H
#define GAMETRIPLETRIAD_H

#include "Quantity.h"
#include "Window.h"
#include "Game.h"
#include "Rule.h"
#include "RenderTargetCard.h"

namespace TT
{
	class GameTripleTriad : public GPL::Game
	{
	public:
		GameTripleTriad(std::unique_ptr<GPL::Application>&& application);
		void SetMusicPlaying(const bool music_playing);
		bool GetMusicPlaying() const;
		GPL::Quantity& GetDifficultyLevel();
		Player& GetPlayer1();
		const Player& GetPlayer1() const;
		Player& GetPlayer2();
		const Player& GetPlayer2() const;
		Player& GetCurrentPlayer();
		Player& GetOpponentPlayer();
		void SetCurrentPlayer(const int player_number);
		Board& GetBoard();
		std::vector<Card*>& GetCurrentGameCards();
		bool IsPlayer1Turn() const;
		bool IsPlayer2Turn() const;
		void PassPlayerTurn();
		int CalculateScorePlayer1() const;
		int CalculateScorePlayer2() const;
		bool AnyCardIsBeingCaptured() const;
		void EnableRule(const int index);
		void DisableRule(const int index);
		bool IsRuleEnabled(const int index);
		void NewMatchGame(const bool player_1_is_human_player,const bool player_2_is_human_player);
		void DoneMatchGame();
		bool PrepareForMatchGameUpdate();
		void MatchGameStatedUpdate();
		void Show(const bool show_elementals);
		void CreateGame() override;
	private:
		bool music_playing{true};
		GPL::Quantity difficulty_level{2,4};
		Player player_1;
		Player player_2;
		Player* current_player{&this->player_1};
		Board board;
		const GPL::Texture* built_cards_texture{};
		std::vector<bool> rules;
		std::vector<std::unique_ptr<CardStats>> cards_stats;
		std::vector<std::unique_ptr<RenderTargetCard>> render_target_cards;
		std::vector<Card*> current_game_cards;
		GameTripleTriad(const GameTripleTriad&) = delete;
		GameTripleTriad& operator=(const GameTripleTriad&) = delete;
		void LoadResources();
		void LoadCards();
		void AddCards();
		void BuildCards();
	};
}

#endif
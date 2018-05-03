#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Game.h"

namespace GPL
{
	enum class GameStateAction
	{
		None,
		PauseCurrentGameState,
		HideCurrentGameState,
		DeleteCurrentGameState,
	};

	class GameState
	{
	public:
		GPL_DLL GameState() = default;
		GPL_DLL virtual ~GameState() = 0 {};
		GPL_DLL static void SetGame(Game& game);
		GPL_DLL static void SetGameTopInterface(std::unique_ptr<GameState>&& game_top_interface);
		GPL_DLL static GameState* AddGameState(std::unique_ptr<GameState>&& game_state,const GameStateAction game_state_action);
		GPL_DLL static int Main();
	protected:
		template<class Type> static Type& GetGame()
		{
			return static_cast<Type&>(*GameState::game);
		};

		GPL_DLL bool GetPause() const;
		GPL_DLL GameState& GetSubGameState(const size_t index);
		GPL_DLL GameState* AddSubGameState(std::unique_ptr<GameState>&& sub_game_state);
		GPL_DLL void HideSubGameState(const size_t index);
		GPL_DLL void ShowSubGameState(const size_t index);
		GPL_DLL void RemoveSubGameStates();
		GPL_DLL virtual void Pausing();
		GPL_DLL virtual void Resuming();
		GPL_DLL virtual void Hiding();
		GPL_DLL virtual void Showing();
		virtual void Update() = 0;
		virtual void Show() = 0;
	private:
		bool pause{};
		bool hide{};
		std::vector<std::unique_ptr<GameState>> sub_game_states;
		GameState(const GameState&) = delete;
		GameState& operator=(const GameState&) = delete;
		GPL_DLL static Game* game;
		static bool iterator_erased;
		static std::list<std::unique_ptr<GameState>>::iterator iterator;
		static std::unique_ptr<GameState> game_top_interface;
		static std::list<std::unique_ptr<GameState>> game_states;
		static void Pausing(std::unique_ptr<GameState>& game_state);
		static void Resuming(std::unique_ptr<GameState>& game_state);
		static void Hiding(std::unique_ptr<GameState>& game_state);
		static void Showing(std::unique_ptr<GameState>& game_state);
		static void Update(std::unique_ptr<GameState>& game_state);
		static void Show(std::unique_ptr<GameState>& game_state);
		static bool IsValidIterator();
		static void UpdateAllGameStates();
		static void ShowAllGameStates();
	};
}

#endif
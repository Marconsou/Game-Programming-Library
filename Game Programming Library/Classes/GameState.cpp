#include "GameState.h"

using namespace std;
using namespace GPL;

Game* GameState::game{};
bool GameState::iterator_erased{};
list<unique_ptr<GameState>>::iterator GameState::iterator;
unique_ptr<GameState> GameState::game_top_interface;
list<unique_ptr<GameState>> GameState::game_states;

bool GameState::GetPause() const
{
	return this->pause;
}

GameState& GameState::GetSubGameState(const size_t index)
{
	return *this->sub_game_states[index];
}

void GameState::Pausing()
{
	this->pause = true;
}

void GameState::Resuming()
{
	this->pause = false;
}

void GameState::Hiding()
{
	this->hide = true;
}

void GameState::Showing()
{
	this->hide = false;
}

void GameState::SetGame(Game& game)
{
	GameState::game = &game;
}

void GameState::SetGameTopInterface(unique_ptr<GameState>&& game_top_interface)
{
	GameState::game_top_interface = move(game_top_interface);
}

GameState* GameState::AddSubGameState(unique_ptr<GameState>&& sub_game_state)
{
	this->sub_game_states.push_back(move(sub_game_state));
	return this->sub_game_states.back().get();
}

void GameState::HideSubGameState(const size_t index)
{
	this->sub_game_states[index]->Hiding();
}

void GameState::ShowSubGameState(const size_t index)
{
	this->sub_game_states[index]->Showing();
}

void GameState::RemoveSubGameStates()
{
	this->sub_game_states.clear();
}

GameState* GameState::AddGameState(unique_ptr<GameState>&& game_state,const GameStateAction game_state_action)
{
	const bool adding_game_state = (game_state.get() != nullptr);

	//Deletar o último Game State
	if (game_state_action == GameStateAction::DeleteCurrentGameState)
	{
		//Equivalente ao pop_back só que com a vantagem de receber o iterator correto ao remover o último Game State
		GameState::iterator = GameState::game_states.erase(--GameState::game_states.end());
		GameState::iterator_erased = true;

		bool additional_action_enabled = ((!GameState::game_states.empty()) && (!adding_game_state));

		//Se o último agora estiver pausado e não for adicionar nenhum Game State (logo a frente) então ele estará no topo e deve resumir
		if ((additional_action_enabled) && (GameState::game_states.back()->pause))
			GameState::Resuming(game_states.back());

		//Se o último agora estiver escondido e não for adicionar nenhum Game State (logo a frente) então ele estará no topo e deve mostrar
		if ((additional_action_enabled) && (GameState::game_states.back()->hide))
			GameState::Showing(game_states.back());
	}

	//Pausar o último Game State
	else if (game_state_action == GameStateAction::PauseCurrentGameState)
		GameState::Pausing(game_states.back());

	//Esconder o último Game State
	else if (game_state_action == GameStateAction::HideCurrentGameState)
		GameState::Hiding(game_states.back());

	//Adicionar Game State
	if (adding_game_state)
	{
		GameState::game_states.push_back(move(game_state));
		return GameState::game_states.back().get();
	}

	return nullptr;
}

void GameState::Pausing(unique_ptr<GameState>& game_state)
{
	game_state->Pausing();
	for (auto& iterator : game_state->sub_game_states)
		GameState::Pausing(iterator);
}

void GameState::Resuming(unique_ptr<GameState>& game_state)
{
	game_state->Resuming();
	for (auto& iterator : game_state->sub_game_states)
		GameState::Resuming(iterator);
}

void GameState::Hiding(unique_ptr<GameState>& game_state)
{
	game_state->Hiding();
	for (auto& iterator : game_state->sub_game_states)
		GameState::Hiding(iterator);
}

void GameState::Showing(unique_ptr<GameState>& game_state)
{
	game_state->Showing();
	for (auto& iterator : game_state->sub_game_states)
		GameState::Showing(iterator);
}

void GameState::Update(unique_ptr<GameState>& game_state)
{
	//Lógica do Game State se não estiver pausado ou escondido
	if ((!game_state->pause) && (!game_state->hide))
		game_state->Update();

	//Verificar pois no Update acima existe a chance deste Game State ser removido
	if (GameState::IsValidIterator())
	{
		for (auto& iterator : game_state->sub_game_states)
			GameState::Update(iterator);
	}
}

void GameState::Show(unique_ptr<GameState>& game_state)
{
	//Mostrar o Game State se não estiver escondido
	if (!game_state->hide)
		game_state->Show();

	for (auto& iterator : game_state->sub_game_states)
		GameState::Show(iterator);
}

bool GameState::IsValidIterator()
{
	return (GameState::iterator != GameState::game_states.end());
}

void GameState::UpdateAllGameStates()
{
	//Executar todos os Game States
	for (GameState::iterator = GameState::game_states.begin(); iterator != GameState::game_states.end(); /* iterator++ */)
	{
		//Update
		if (GameState::IsValidIterator())
			GameState::Update(*GameState::iterator);

		//Se não removeu nenhum Game State passar para o próximo e resetar o valor do controle de remoção
		if (!GameState::iterator_erased)
			GameState::iterator++;
		GameState::iterator_erased = false;
	}

	//Game State específico sobre o topo de todas
	if (GameState::game_top_interface.get())
		GameState::Update(GameState::game_top_interface);
}

void GameState::ShowAllGameStates()
{
	//Executar todos os Game States
	for (auto& iterator : GameState::game_states)
		GameState::Show(iterator);

	//Game State específico sobre o topo de todas
	if (GameState::game_top_interface.get())
		GameState::Show(GameState::game_top_interface);
}

int GameState::Main()
{
	//Enquanto a aplicação estiver rodando e tiver algum Game State para processar
	while ((GameState::game->GetApplication().IsRunning()) && (!GameState::game_states.empty()))
	{
		//Se a aplicação já tiver processado as mensagens
		if (GameState::game->GetApplication().ProcessMessages())
		{
			//Se a aplicação estiver ativada
			if (GameState::game->GetApplication().IsActivated())
			{
				//Input
				GameState::game->GetInput().ProcessInput();
				Control::ProcessEvents(GameState::game->GetInput(),GameState::game->GetTimer());

				//Audio
				GameState::game->GetAudio().ProcessAudio();

				//Game States
				GameState::UpdateAllGameStates();
				GameState::ShowAllGameStates();

				//Video
				GameState::game->GetVideo().Render();
			}
		}
	}

	//Limpar todos os Game States para destruir recursos de Video
	GameState::game_top_interface.reset();
	GameState::game_states.clear();

	//Finalizar
	return EXIT_SUCCESS;
}
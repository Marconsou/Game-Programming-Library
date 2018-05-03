#include "GameTopInterface.h"

using namespace GPL;
using namespace TT;

void GameTopInterface::Update()
{

}

void GameTopInterface::Show()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	Control::ShowControls(game.GetInput(),game.GetVideo(),game.GetTimer());
}
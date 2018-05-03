#include "VideoDirect3D9.h"
#include "AudioXAudio.h"
#include "MainMenu.h"
#include "GameTopInterface.h"

using namespace std;
using namespace GPL;
using namespace TT;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	GameTripleTriad game(make_unique<ApplicationWin32>(true));
	game.RegisterVideoEngine<VideoDirect3D9>(VideoEngine::Direct3D9);
	game.RegisterAudioEngine<AudioXAudio>(AudioEngine::XAudio);
	game.CreateGame();
	GameState::SetGame(game);
	GameState::AddGameState(make_unique<MainMenu>(),GameStateAction::None);
	GameState::SetGameTopInterface(make_unique<GameTopInterface>());
	return GameState::Main();
}
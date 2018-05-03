#include "VideoDirect3D9.h"
#include "AudioXAudio.h"
#include "AudioOpenAL.h"
#include "GameTopInterface.h"
#include "MainMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	GameRPG game(make_unique<ApplicationWin32>());
	game.RegisterVideoEngine<VideoDirect3D9>(VideoEngine::Direct3D9);
	game.RegisterAudioEngine<AudioXAudio>(AudioEngine::XAudio);
	game.RegisterAudioEngine<AudioOpenAL>(AudioEngine::OpenAL);
	game.CreateGame();
	GameState::SetGame(game);
	GameState::AddGameState(make_unique<MainMenu>(),GameStateAction::None);
	GameState::SetGameTopInterface(make_unique<GameTopInterface>());
	return GameState::Main();
}
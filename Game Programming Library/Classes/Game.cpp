#include "Game.h"

using namespace std;
using namespace GPL;

Game::Game(unique_ptr<Application>&& application) :
application(move(application)),
timer(make_unique<Timer>()),
screen_effect(make_unique<ScreenEffect>())
{
}

Application& Game::GetApplication()
{
	return *this->application;
}

Input& Game::GetInput()
{
	return *this->input;
}

const Input& Game::GetInput() const
{
	return *this->input;
}

Video& Game::GetVideo()
{
	return *this->video;
}

const Video& Game::GetVideo() const
{
	return *this->video;
}

Audio& Game::GetAudio()
{
	return *this->audio;
}

const Audio& Game::GetAudio() const
{
	return *this->audio;
}

Timer& Game::GetTimer()
{
	return *this->timer;
}

const Timer& Game::GetTimer() const
{
	return *this->timer;
}

ScreenEffect& Game::GetScreenEffect()
{
	return *this->screen_effect;
}

const ScreenEffect& Game::GetScreenEffect() const
{
	return *this->screen_effect;
}

void Game::OnApplicationActivating(const Application& application)
{
	this->timer->Pause(timer_last_pause_state);
	this->audio->ResumeAudio();
}

void Game::OnApplicationInactivating(const Application& application)
{
	this->timer_last_pause_state = this->timer->GetPause();
	this->timer->Pause(true);
	this->audio->PauseAudio();
}

void Game::Initialize(const string& title,const VideoMode& video_mode,const AudioEngine audio_engine,const int icon_id)
{
	//Application
	this->application->CreateApplication(this->input,title,video_mode.GetWidth(),video_mode.GetHeight(),video_mode.GetWindowed(),icon_id);
	this->application->AddEventOnActivating(&Game::OnApplicationActivating,*this);
	this->application->AddEventOnInactivating(&Game::OnApplicationInactivating,*this);

	//Video
	this->factory_video_engine.CreateObject(this->video,VideoEngine::Direct3D9);
	this->video->CreateVideo(*this->application,video_mode);

	//Audio
	this->ChangeAudioEngine(audio_engine);
}

void Game::ChangeAudioEngine(const AudioEngine audio_engine)
{
	unique_ptr<Audio> new_audio;
	this->factory_audio_engine.CreateObject(new_audio,audio_engine);
	this->audio->ChangeAudioEngine(new_audio);
	this->audio = move(new_audio);
}
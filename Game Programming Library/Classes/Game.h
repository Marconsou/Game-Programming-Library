#ifndef GAME_H
#define GAME_H

#include "Factory.h"
#include "Control.h"
#include "Audio.h"
#include "ScreenEffect.h"

namespace GPL
{
	enum class VideoEngine
	{
		Direct3D9,
	};

	enum class AudioEngine
	{
		XAudio,
		OpenAL,
	};

	class Game
	{
	public:
		GPL_DLL Game(std::unique_ptr<Application>&& application);
		GPL_DLL virtual ~Game() = 0 {};
		GPL_DLL Application& GetApplication();
		GPL_DLL const Application& GetApplication() const;
		GPL_DLL Input& GetInput();
		GPL_DLL const Input& GetInput() const;
		GPL_DLL Video& GetVideo();
		GPL_DLL const Video& GetVideo() const;
		GPL_DLL Audio& GetAudio();
		GPL_DLL const Audio& GetAudio() const;
		GPL_DLL Timer& GetTimer();
		GPL_DLL const Timer& GetTimer() const;
		GPL_DLL ScreenEffect& GetScreenEffect();
		GPL_DLL const ScreenEffect& GetScreenEffect() const;
		GPL_DLL void ChangeAudioEngine(const AudioEngine audio_engine);

		template<class Type>
		void RegisterVideoEngine(const VideoEngine video_engine)
		{
			this->factory_video_engine.RegisterObject<Type>(video_engine);
		}

		template<class Type>
		void RegisterAudioEngine(const AudioEngine audio_engine)
		{
			this->factory_audio_engine.RegisterObject<Type>(audio_engine);
		}

		GPL_DLL virtual void CreateGame() = 0;
	protected:
		GPL_DLL void Initialize(const std::string& title,const VideoMode& video_mode,const AudioEngine audio_engine,const int icon_id = 0);
	private:
		bool timer_last_pause_state{};
		std::unique_ptr<Application> application;
		std::unique_ptr<Input> input;
		std::unique_ptr<Video> video;
		std::unique_ptr<Audio> audio;
		std::unique_ptr<Timer> timer;
		std::unique_ptr<ScreenEffect> screen_effect;
		Factory<VideoEngine,Video> factory_video_engine;
		Factory<AudioEngine,Audio> factory_audio_engine;
		void OnApplicationActivating(const Application& application);
		void OnApplicationInactivating(const Application& application);
	};
}

#endif
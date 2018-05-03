#ifndef AUDIOOPENAL_H
#define AUDIOOPENAL_H

#include "Audio.h"
#include "OpenAL.h"
#include "SoundOpenALOGG.h"
#include "MusicOpenALOGG.h"

namespace GPL
{
	class AudioOpenAL : public Audio
	{
	public:
		GPL_DLL AudioOpenAL(const bool enable_music = true,const bool enable_sound = true);
		GPL_DLL ~AudioOpenAL();
		GPL_DLL std::string GetDeviceDisplayName() const override;
		GPL_DLL void PlaySoundFromBuffer(const std::string& sound_id,const float frequency_ratio) override;
		GPL_DLL void PlaySoundFromBuffer(const int sound_id,const float frequency_ratio) override;
		void ResumeAudio() override;
		void PauseAudio() override;
	private:
		OpenAL openal;
		const SoundOpenAL& FindSound(const std::string& sound_id);
		void PlaySource(const SoundOpenAL& sound_openal,const float frequency_ratio);
		void CreateAudioEngine() override;
		void DestroyAudioEngine() override;
		void LoadMusicOGG(const std::string& music_id,std::unique_ptr<char[]>& memory_buffer,const size_t size) override;
		void LoadSoundOGG(const std::string& sound_id,std::unique_ptr<char[]>& memory_buffer,const size_t size) override;
	};
}

#endif
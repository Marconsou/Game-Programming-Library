#ifndef AUDIOXAUDIO_H
#define AUDIOXAUDIO_H

#include "Audio.h"
#include "XAudio.h"
#include "SoundXAudioOGG.h"
#include "MusicXAudioOGG.h"

namespace GPL
{
	class AudioXAudio : public Audio
	{
	public:
		GPL_DLL AudioXAudio(const bool enable_music = true,const bool enable_sound = true);
		GPL_DLL ~AudioXAudio();
		GPL_DLL std::string GetDeviceDisplayName() const override;
		GPL_DLL void PlaySoundFromBuffer(const std::string& sound_id,const float frequency_ratio) override;
		GPL_DLL void PlaySoundFromBuffer(const int sound_id,const float frequency_ratio) override;
		void ResumeAudio() override;
		void PauseAudio() override;
	private:
		XAudio xaudio;
		const Sound& GetSound(const std::string& sound_id);
		const Sound& GetSound(const int sound_id);
		const SoundXAudio& FindSound(const std::string& sound_id);
		void PlaySourceVoice(const SoundXAudio& sound_xaudio,const float frequency_ratio);
		void AddSourceVoices(const WAVEFORMATEX& wave_format);
		void CreateAudioEngine() override;
		void DestroyAudioEngine() override;
		void LoadMusicOGG(const std::string& music_id,std::unique_ptr<char[]>& memory_buffer,const size_t size) override;
		void LoadSoundOGG(const std::string& sound_id,std::unique_ptr<char[]>& memory_buffer,const size_t size) override;
	};
}

#endif
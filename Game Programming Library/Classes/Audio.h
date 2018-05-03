#ifndef AUDIO_H
#define AUDIO_H

#include <algorithm>
#include "ResourceManager.h"
#include "Convert.h"
#include "Source.h"
#include "Music.h"
#include "Log.h"
#include "ResourceFile.h"

namespace GPL
{
	class Audio
	{
	public:
		GPL_DLL Audio(const bool enable_music = true,const bool enable_sound = true);
		GPL_DLL virtual ~Audio() = 0 {};
		GPL_DLL void SetMusicVolume(const float music_volume);
		GPL_DLL float GetMusicVolume() const;
		GPL_DLL void SetSoundVolume(const float sound_volume);
		GPL_DLL float GetSoundVolume() const;
		GPL_DLL void SetMusicFrequencyRatio(const float music_frequency_ratio);
		GPL_DLL void EnableMusic();
		GPL_DLL void DisableMusic();
		GPL_DLL bool MusicIsEnabled() const;
		GPL_DLL void EnableSound();
		GPL_DLL void DisableSound();
		GPL_DLL bool SoundIsEnabled() const;
		GPL_DLL void StartFadeInMusic();
		GPL_DLL void StartFadeOutMusic();
		GPL_DLL void ChangeAudioEngine(std::unique_ptr<Audio>& new_audio);
		GPL_DLL void AddToMusicPlaylist(const std::string& file_name,const double restart_position = 0,const double finish_position = 0);
		GPL_DLL void AddToMusicPlaylist(const int music_id,const double restart_position = 0,const double finish_position = 0);
		GPL_DLL void PlayMusicFromPlaylist(const std::string& music_id,const bool restore_previous_position = true);
		GPL_DLL void PlayMusicFromPlaylist(const int music_id,const bool restore_previous_position = true);
		GPL_DLL void LoadSound(const std::string& file_name);
		GPL_DLL void LoadSound(const int sound_id);
		GPL_DLL void ProcessAudio();
		GPL_DLL virtual std::string GetDeviceDisplayName() const = 0;
		GPL_DLL virtual void PlaySoundFromBuffer(const std::string& sound_id,const float frequency_ratio = 1.0f) = 0;
		GPL_DLL virtual void PlaySoundFromBuffer(const int sound_id,const float frequency_ratio = 1.0f) = 0;
		virtual void ResumeAudio() = 0;
		virtual void PauseAudio() = 0;
	protected:
		double GetMusicRestartPosition(const std::string& music_id) const;
		double GetMusicFinishPosition(const std::string& music_id) const;
		std::unique_ptr<Music>& GetCurrentMusic();
		ResourceManager<std::unique_ptr<Sound>>& GetSounds();
		std::vector<std::unique_ptr<Source>>& GetSoundSources();
		void DestroyResources();
	private:
		enum class AudioFormat
		{
			Unknown,
			OGG,
		};

		struct MusicTrack
		{
			std::string id;
			double restart_position{};
			double finish_position{};
			double current_position{};
			MusicTrack() = default;
			MusicTrack(const MusicTrack&) = delete;
			MusicTrack& operator=(const MusicTrack&) = delete;
		};

		float music_volume{1.0f};
		float music_volume_max{1.0f};
		float sound_volume{1.0f};
		bool enable_music{};
		bool enable_sound{};
		bool fading_in_music{};
		bool fading_out_music{};
		bool music_volume_swap{};
		bool last_music_is_from_file{};
		bool last_music_restore_previous_position{};
		std::string last_music_id_played;
		std::unique_ptr<Music> current_music;
		std::unique_ptr<Music> temporary_music;
		ResourceManager<std::unique_ptr<MusicTrack>> music_playlist;
		ResourceManager<std::unique_ptr<Sound>> sounds;
		std::vector<std::unique_ptr<Source>> sound_sources;
		Audio(const Audio&) = delete;
		Audio& operator=(const Audio&) = delete;
		float GetAudioFadeVolume() const;
		void SetMusicCurrentPosition(const std::string& music_id,const double current_position);
		double GetMusicCurrentPosition(const std::string& music_id) const;
		void AddToMusicPlaylistBase(const bool resource_from_file,const std::string& file_name,const int music_id,const double restart_position,const double finish_position);
		void PlayMusicFromPlaylistBase(const std::string& file_name,const int music_id,const bool restore_previous_position);
		void LoadSoundBase(const std::string& file_name,const int sound_id);
		AudioFormat DetectFileType(const std::string& file_name) const;
		AudioFormat DetectFileType(const std::unique_ptr<char[]>& memory_buffer) const;
		void CheckMusicFadeEvent();
		void SwapMusic(const std::string& music_id);
		void RestoreMusicCurrentPosition(const std::string& music_id);
		void PlayingMusic(std::unique_ptr<Music>& music,const bool using_current_music);
		virtual void CreateAudioEngine() = 0;
		virtual void DestroyAudioEngine() = 0;
		virtual void LoadMusicOGG(const std::string& music_id,std::unique_ptr<char[]>& memory_buffer,const size_t size = 0) = 0;
		virtual void LoadSoundOGG(const std::string& sound_id,std::unique_ptr<char[]>& memory_buffer,const size_t size = 0) = 0;
	};
}

#endif
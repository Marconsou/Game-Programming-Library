#ifndef MUSICXAUDIOOGG_H
#define MUSICXAUDIOOGG_H

#include "Music.h"
#include "OGGFile.h"
#include "BufferXAudio.h"
#include "SourceVoiceXAudio.h"

namespace GPL
{
	class MusicXAudioOGG : public Music
	{
	public:
		GPL_DLL MusicXAudioOGG(const double restart_position = 0,const double finish_position = 0);
		GPL_DLL BufferXAudio& GetBufferXAudio();
		GPL_DLL void CreateSourceVoice(IXAudio2* xaudio,const WAVEFORMATEX& wave_format);
		GPL_DLL void SetVolume(const float volume) override;
		GPL_DLL float GetVolume() const override;
		GPL_DLL void SetCurrentPosition(const double current_position) override;
		GPL_DLL double GetCurrentPosition() override;
		GPL_DLL void LoadMusic(const std::string& file_name) override;
		GPL_DLL void LoadMusic(std::unique_ptr<char[]>& memory_buffer,const size_t size) override;
		GPL_DLL void Playing() override;
		GPL_DLL void Stop() const override;
	private:
		OGGFile ogg_file;
		BufferXAudio buffer_xaudio;
		SourceVoiceXAudio source_voice_xaudio;
		void LoadAudioData(const OGGFile& ogg_file);
	};
}

#endif
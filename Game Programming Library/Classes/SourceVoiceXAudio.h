#ifndef SOURCEVOICEXAUDIO_H
#define SOURCEVOICEXAUDIO_H

#include <XAudio2.h>
#include "Source.h"
#include "Log.h"

namespace GPL
{
	class SourceVoiceXAudio : public Source
	{
	public:
		GPL_DLL SourceVoiceXAudio() = default;
		GPL_DLL ~SourceVoiceXAudio();
		GPL_DLL float GetVolume() const;
		GPL_DLL void CreateSourceVoice(IXAudio2* xaudio,const WAVEFORMATEX& wave_format);
		GPL_DLL void Start(const XAUDIO2_BUFFER& xaudio_buffer,const float frequency_ratio) const;
		GPL_DLL bool CheckSourceVoiceFormat(const WAVEFORMATEX& wave_format) const;
		GPL_DLL int HasBuffersQueued() const;
		GPL_DLL void DeleteSourceVoice();
		GPL_DLL void SetVolume(const float volume) override;
		GPL_DLL void Stop() const override;
	private:
		IXAudio2SourceVoice* xaudio_source_voice{};
		WORD bits{};
		WORD channels{};
		DWORD rate{};
	};
}

#endif
#ifndef BUFFERXAUDIO_H
#define BUFFERXAUDIO_H

#include <XAudio2.h>
#include "BuildDLL.h"

namespace GPL
{
	class BufferXAudio
	{
	public:
		BufferXAudio() = default;
		GPL_DLL WAVEFORMATEX& GetWaveFormat();
		GPL_DLL const WAVEFORMATEX& GetWaveFormat() const;
		GPL_DLL XAUDIO2_BUFFER& GetXAudioBuffer();
		GPL_DLL const XAUDIO2_BUFFER& GetXAudioBuffer() const;
	private:
		WAVEFORMATEX wave_format;
		XAUDIO2_BUFFER xaudio_buffer;
		BufferXAudio(const BufferXAudio&) = delete;
		BufferXAudio& operator=(const BufferXAudio&) = delete;
	};
}

#endif
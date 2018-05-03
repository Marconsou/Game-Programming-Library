#include "BufferXAudio.h"

using namespace GPL;

WAVEFORMATEX& BufferXAudio::GetWaveFormat()
{
	return this->wave_format;
}

const WAVEFORMATEX& BufferXAudio::GetWaveFormat() const
{
	return this->wave_format;
}

XAUDIO2_BUFFER& BufferXAudio::GetXAudioBuffer()
{
	return this->xaudio_buffer;
}

const XAUDIO2_BUFFER& BufferXAudio::GetXAudioBuffer() const
{
	return this->xaudio_buffer;
}
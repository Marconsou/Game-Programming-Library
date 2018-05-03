#include "SoundXAudio.h"

using namespace GPL;

BufferXAudio& SoundXAudio::GetBufferXAudio()
{
	return this->buffer_xaudio;
}

const BufferXAudio& SoundXAudio::GetBufferXAudio() const
{
	return this->buffer_xaudio;
}
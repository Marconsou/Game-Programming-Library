#ifndef SOUNDXAUDIO_H
#define SOUNDXAUDIO_H

#include "Sound.h"
#include "BufferXAudio.h"

namespace GPL
{
	class SoundXAudio : public Sound
	{
	public:
		GPL_DLL virtual ~SoundXAudio() = 0 {};
		GPL_DLL BufferXAudio& GetBufferXAudio();
		GPL_DLL const BufferXAudio& GetBufferXAudio() const;
	private:
		BufferXAudio buffer_xaudio;
	};
}

#endif
#ifndef SOUNDOPENAL_H
#define SOUNDOPENAL_H

#include "Sound.h"
#include "BufferOpenAL.h"

namespace GPL
{
	class SoundOpenAL : public Sound
	{
	public:
		GPL_DLL virtual ~SoundOpenAL() = 0 {};
		GPL_DLL ALuint GetBuffer() const;
	protected:
		void CreateBuffer(const int channels,const ALsizei size,const ALsizei rate);
	private:
		BufferOpenAL buffer_openal;
	};
}

#endif
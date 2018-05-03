#ifndef BUFFEROPENAL_H
#define BUFFEROPENAL_H

#include <vector>
#include <al.h>
#include "Log.h"

namespace GPL
{
	class BufferOpenAL
	{
	public:
		GPL_DLL BufferOpenAL() = default;
		GPL_DLL ~BufferOpenAL();
		GPL_DLL std::vector<ALuint>& GetBuffer();
		GPL_DLL const std::vector<ALuint>& GetBuffer() const;
		GPL_DLL void CreateBuffer(const int channels,const int buffer_total);
		GPL_DLL void CreateBuffer(char* audio_data,const int channels,const ALsizei size,const ALsizei rate);
		GPL_DLL void BufferData(char* audio_data,const int buffer_index,const ALsizei size,const ALsizei rate);
	private:
		ALenum format{};
		std::vector<ALuint> buffer;
		BufferOpenAL(const BufferOpenAL&) = delete;
		BufferOpenAL& operator=(const BufferOpenAL&) = delete;
		void DeleteBuffer();
	};
}

#endif
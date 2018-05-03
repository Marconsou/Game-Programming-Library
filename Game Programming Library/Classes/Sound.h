#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <memory>
#include "BuildDLL.h"

namespace GPL
{
	class Sound
	{
	public:
		GPL_DLL Sound() = default;
		GPL_DLL virtual ~Sound() = 0 {};
		GPL_DLL std::unique_ptr<char[]>& GetAudioData();
		GPL_DLL virtual void LoadSound(const std::string& file_name) = 0;
		GPL_DLL virtual void LoadSound(std::unique_ptr<char[]>& memory_buffer,const size_t size) = 0;
	private:
		std::unique_ptr<char[]> audio_data;
		Sound(const Sound&) = delete;
		Sound& operator=(const Sound&) = delete;
	};
}

#endif
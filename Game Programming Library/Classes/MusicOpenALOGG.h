#ifndef MUSICOPENALOGG_H
#define MUSICOPENALOGG_H

#include "Music.h"
#include "OGGFile.h"
#include "BufferOpenAL.h"
#include "SourceOpenAL.h"

namespace GPL
{
	class MusicOpenALOGG : public Music
	{
	public:
		GPL_DLL MusicOpenALOGG(const double restart_position = 0,const double finish_position = 0);
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
		BufferOpenAL buffer_openal;
		SourceOpenAL source_openal;
		void LoadAudioData(OGGFile& ogg_file);
		bool Decode(const int buffer_index);
	};
}

#endif
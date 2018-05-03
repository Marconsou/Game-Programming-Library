#ifndef SOUNDOPENALOGG_H
#define SOUNDOPENALOGG_H

#include "SoundOpenAL.h"
#include "OGGFile.h"

namespace GPL
{
	class SoundOpenALOGG : public SoundOpenAL
	{
	public:
		GPL_DLL void LoadSound(const std::string& file_name) override;
		GPL_DLL void LoadSound(std::unique_ptr<char[]>& memory_buffer,const size_t size) override;
	private:
		void LoadAudioData(OGGFile& ogg_file);
	};
}

#endif
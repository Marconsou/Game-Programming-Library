#ifndef OGGFILE_H
#define OGGFILE_H

#include <memory>
#include <vorbis/vorbisfile.h>
#include "Log.h"

namespace GPL
{
	class OGGFile
	{
	public:
		GPL_DLL OGGFile();
		GPL_DLL explicit OGGFile(const std::string& file_name);
		GPL_DLL OGGFile(std::unique_ptr<char[]>& memory_buffer,const size_t size);
		GPL_DLL ~OGGFile();
		GPL_DLL int GetChannels() const;
		GPL_DLL long GetRate() const;
		GPL_DLL void SetCurrentPosition(const double current_position);
		GPL_DLL double GetCurrentPosition();
		GPL_DLL void Open(const std::string& file_name);
		GPL_DLL void Open(std::unique_ptr<char[]>& memory_buffer,const size_t size);
		GPL_DLL size_t ReadAllData(std::unique_ptr<char[]>& audio_buffer);
		GPL_DLL size_t ReadChunkData(char* audio_buffer,const size_t audio_buffer_size,const bool rewind);
		GPL_DLL void CheckForReplay(const double restart_position,const double finish_position);
		GPL_DLL void Close();
	private:
		struct OGGFileCallback
		{
			char* current_pointer{};
			size_t file_size{};
			std::unique_ptr<char[]> file_pointer;
			OGGFileCallback() = default;
			OGGFileCallback(const OGGFileCallback&) = delete;
			OGGFileCallback& operator=(const OGGFileCallback&) = delete;
		};

		OggVorbis_File ogg_vorbis_file;
		OGGFileCallback ogg_file_callback;
		OGGFile(const OGGFile&) = delete;
		OGGFile& operator=(const OGGFile&) = delete;
		size_t GetAudioBufferSize();
		static size_t ReadCallback(void* ptr,size_t size,size_t nmemb,void* datasource);
		static int SeekCallback(void* datasource,ogg_int64_t offset,int whence);
		static int CloseCallback(void* datasource);
		static long TellCallback(void* datasource);
	};
}

#endif
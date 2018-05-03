#ifndef MUSIC_H
#define MUSIC_H

#include <vector>
#include <memory>
#include "BuildDLL.h"

namespace GPL
{
	class Music
	{
	public:
		GPL_DLL Music(const double restart_position = 0,const double finish_position = 0,const int buffer_total = 3,const int buffer_size = 4096 * 4);
		GPL_DLL virtual ~Music() = 0 {};
		GPL_DLL void SetFrequencyRatio(const float frequency_ratio);
		GPL_DLL float GetFrequencyRatio() const;
		GPL_DLL double GetRestartPosition() const;
		GPL_DLL double GetFinishPosition() const;
		GPL_DLL int GetBufferTotal() const;
		GPL_DLL int GetBufferSize() const;
		GPL_DLL char* GetCurrentBuffer();
		GPL_DLL void NextBuffer();
		GPL_DLL virtual void SetVolume(const float volume) = 0;
		GPL_DLL virtual float GetVolume() const = 0;
		GPL_DLL virtual void SetCurrentPosition(const double current_position) = 0;
		GPL_DLL virtual double GetCurrentPosition() = 0;
		GPL_DLL virtual void LoadMusic(const std::string& file_name) = 0;
		GPL_DLL virtual void LoadMusic(std::unique_ptr<char[]>& memory_buffer,const size_t size) = 0;
		GPL_DLL virtual void Playing() = 0;
		GPL_DLL virtual void Stop() const = 0;
	private:
		float frequency_ratio{1.0f};
		const double restart_position{};
		const double finish_position{};
		int current_buffer_index{};
		const int buffer_total{};
		const int buffer_size{};
		std::vector<char> buffers;
		Music(const Music&) = delete;
		Music& operator=(const Music&) = delete;
	};
}

#endif
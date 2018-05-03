#ifndef SOURCE_H
#define SOURCE_H

#include "Sound.h"

namespace GPL
{
	class Source
	{
	public:
		GPL_DLL Source() = default;
		GPL_DLL virtual ~Source() = 0 {};
		GPL_DLL void SetLastSoundPlayed(const Sound& last_sound_played);
		GPL_DLL const Sound& GetLastSoundPlayed() const;
		GPL_DLL virtual void SetVolume(const float volume) = 0;
		GPL_DLL virtual void Stop() const = 0;
	private:
		const Sound* last_sound_played{};
		Source(const Source&) = delete;
		Source& operator=(const Source&) = delete;
	};
}

#endif
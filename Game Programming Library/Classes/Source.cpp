#include "Source.h"

using namespace GPL;

void Source::SetLastSoundPlayed(const Sound& last_sound_played)
{
	this->last_sound_played = &last_sound_played;
}

const Sound& Source::GetLastSoundPlayed() const
{
	return *this->last_sound_played;
}
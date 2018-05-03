#include "Sound.h"

using namespace std;
using namespace GPL;

unique_ptr<char[]>& Sound::GetAudioData()
{
	return this->audio_data;
}
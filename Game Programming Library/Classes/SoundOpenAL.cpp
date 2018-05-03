#include "SoundOpenAL.h"

using namespace GPL;

ALuint SoundOpenAL::GetBuffer() const
{
	return this->buffer_openal.GetBuffer()[0];
}

void SoundOpenAL::CreateBuffer(const int channels,const ALsizei size,const ALsizei rate)
{
	this->buffer_openal.CreateBuffer(&this->GetAudioData()[0],channels,size,rate);
}
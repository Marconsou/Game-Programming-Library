#include "SourceOpenAL.h"

using namespace std;
using namespace GPL;

SourceOpenAL::~SourceOpenAL()
{
	this->DeleteSource();
}

void SourceOpenAL::SetVolume(const float volume)
{
	alSourcef(this->source,AL_GAIN,min(max(0.0f,volume),1.0f));
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alSourcef");
}

float SourceOpenAL::GetVolume() const
{
	ALfloat volume;
	alGetSourcef(this->source,AL_GAIN,&volume);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alGetSourcef");
	return volume;
}

void SourceOpenAL::SetFrequencyRatio(const ALfloat frequency_ratio)
{
	alSourcef(this->source,AL_PITCH,frequency_ratio);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alSourcef");
}

void SourceOpenAL::CreateSource()
{
	//Deletar Source
	this->DeleteSource();

	//Gerar Source
	alGenSources(1,&this->source);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alGenSources");
}

void SourceOpenAL::Play(const ALuint buffer) const
{
	//Utilizar um Buffer para tocar o audio
	alSourcei(this->source,AL_BUFFER,buffer);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alSourcei");

	//Iniciar
	this->Play();
}

void SourceOpenAL::Play() const
{
	alSourcePlay(this->source);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alSourcePlay");
}

void SourceOpenAL::Pause() const
{
	alSourcePause(this->source);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alSourcePause");
}

void SourceOpenAL::Stop() const
{
	//Parar de tocar o Source
	alSourceStop(this->source);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alSourceStop");

	//Limpar os Buffer pendente deste Source
	alSourcei(this->source,AL_BUFFER,0);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alSourcei");
}

void SourceOpenAL::QueueBuffers(const ALsizei total,const ALuint* buffers) const
{
	alSourceQueueBuffers(this->source,total,buffers);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alSourceQueueBuffers");
}

void SourceOpenAL::UnqueueBuffers(const ALsizei total,ALuint* buffers) const
{
	alSourceUnqueueBuffers(this->source,total,buffers);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alSourceUnqueueBuffers");
}

int SourceOpenAL::HasBuffersProcessed() const
{
	ALint processed;
	alGetSourcei(this->source,AL_BUFFERS_PROCESSED,&processed);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alGetSourcei");
	return processed;
}

int SourceOpenAL::HasBuffersQueued() const
{
	ALint queued;
	alGetSourcei(this->source,AL_BUFFERS_QUEUED,&queued);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alGetSourcei");
	return queued;
}

ALint SourceOpenAL::SourceState() const
{
	ALint state;
	alGetSourcei(this->source,AL_SOURCE_STATE,&state);
	if (alGetError() != AL_NO_ERROR)
		Log::Error(__FUNCTION__,"alGetSourcei");
	return state;
}

bool SourceOpenAL::IsInitial() const
{
	return (this->SourceState() == AL_INITIAL);
}

bool SourceOpenAL::IsPlaying() const
{
	return (this->SourceState() == AL_PLAYING);
}

bool SourceOpenAL::IsPaused() const
{
	return (this->SourceState() == AL_PAUSED);
}

bool SourceOpenAL::IsStopped() const
{
	return (this->SourceState() == AL_STOPPED);
}

void SourceOpenAL::DeleteSource()
{
	if (this->source != 0)
	{
		alDeleteSources(1,&this->source);
		if (alGetError() != AL_NO_ERROR)
			Log::Error(__FUNCTION__,"alDeleteSources");

		this->source = 0;
	}
}
#ifndef SOURCEOPENAL_H
#define SOURCEOPENAL_H

#include <algorithm>
#include <al.h>
#include "Source.h"
#include "Log.h"

namespace GPL
{
	class SourceOpenAL : public Source
	{
	public:
		GPL_DLL ~SourceOpenAL();
		GPL_DLL float GetVolume() const;
		GPL_DLL void SetFrequencyRatio(const ALfloat frequency_ratio);
		GPL_DLL void CreateSource();
		GPL_DLL void Play(const ALuint buffer) const;
		GPL_DLL void Play() const;
		GPL_DLL void Pause() const;
		GPL_DLL void QueueBuffers(const ALsizei total,const ALuint* buffers) const;
		GPL_DLL void UnqueueBuffers(const ALsizei total,ALuint* buffers) const;
		GPL_DLL int HasBuffersProcessed() const;
		GPL_DLL int HasBuffersQueued() const;
		GPL_DLL bool IsInitial() const;
		GPL_DLL bool IsPlaying() const;
		GPL_DLL bool IsPaused() const;
		GPL_DLL bool IsStopped() const;
		GPL_DLL void SetVolume(const float volume) override;
		GPL_DLL void Stop() const override;
	private:
		ALuint source{};
		ALint SourceState() const;
		void DeleteSource();
	};
}

#endif
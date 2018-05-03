#ifndef XAUDIO_H
#define XAUDIO_H

#include <XAudio2.h>
#include <atlbase.h>
#include "Log.h"

namespace GPL
{
	class XAudio
	{
	public:
		XAudio() = default;
		GPL_DLL ~XAudio();
		GPL_DLL IXAudio2* GetXAudio() const;
		GPL_DLL std::string XAudio::GetDeviceDisplayName() const;
		GPL_DLL void CreateXAudio();
		GPL_DLL void DestroyXAudio();
		GPL_DLL void ResumeAudio() const;
		GPL_DLL void PauseAudio() const;
	private:
		CComPtr<IXAudio2> xaudio;
		IXAudio2MasteringVoice* xaudio_master_voice{};
		XAudio(const XAudio&) = delete;
		XAudio& operator=(const XAudio&) = delete;
	};
}

#endif
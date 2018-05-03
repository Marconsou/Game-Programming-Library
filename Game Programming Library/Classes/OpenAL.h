#ifndef OPENAL_H
#define OPENAL_H

#include <alc.h>
#include "Log.h"

namespace GPL
{
	class OpenAL
	{
	public:
		GPL_DLL OpenAL() = default;
		GPL_DLL ~OpenAL();
		GPL_DLL std::string GetDeviceDisplayName() const;
		GPL_DLL void CreateOpenAL();
		GPL_DLL void DestroyOpenAL();
	private:
		ALCdevice* openal_device{};
		ALCcontext* openal_context{};
		OpenAL(const OpenAL&) = delete;
		OpenAL& operator=(const OpenAL&) = delete;
	};
}

#endif
#ifndef VIDEOMODE_H
#define VIDEOMODE_H

#include "BuildDLL.h"

namespace GPL
{
	enum class BitsPerPixel
	{
		ColorDepth32Bits = 32,
		ColorDepth16Bits = 16,
	};

	class VideoMode
	{
	public:
		VideoMode() = default;
		GPL_DLL VideoMode(const int width,const int height,const BitsPerPixel bpp,const bool windowed,const bool vsync,const int full_screen_refresh_rate = 60);
		GPL_DLL bool operator==(const VideoMode& video_mode) const;
		GPL_DLL bool operator!=(const VideoMode& video_mode) const;
		GPL_DLL int GetWidth() const;
		GPL_DLL int GetHeight() const;
		GPL_DLL int GetFullScreenRefreshRate() const;
		GPL_DLL BitsPerPixel GetBPP() const;
		GPL_DLL bool GetWindowed() const;
		GPL_DLL bool GetVSync() const;
	private:
		int width{};
		int height{};
		int full_screen_refresh_rate{};
		BitsPerPixel bpp{BitsPerPixel::ColorDepth32Bits};
		bool windowed{true};
		bool vsync{true};
		VideoMode(const VideoMode&) = delete;
	};
}

#endif
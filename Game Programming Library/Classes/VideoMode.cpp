#include "VideoMode.h"

using namespace GPL;

VideoMode::VideoMode(const int width,const int height,const BitsPerPixel bpp,const bool windowed,const bool vsync,const int full_screen_refresh_rate) :
width(width),
height(height),
full_screen_refresh_rate(full_screen_refresh_rate),
bpp(bpp),
windowed(windowed),
vsync(vsync)
{

}

bool VideoMode::operator==(const VideoMode& video_mode) const
{
	return ((this->width == video_mode.width) &&
			(this->height == video_mode.height) &&
			(this->full_screen_refresh_rate == video_mode.full_screen_refresh_rate) &&
			(this->bpp == video_mode.bpp) &&
			(this->windowed == video_mode.windowed) &&
			(this->vsync == video_mode.vsync));
}

bool VideoMode::operator!=(const VideoMode& video_mode) const
{
	return !this->operator==(video_mode);
}

int VideoMode::GetWidth() const
{
	return this->width;
}

int VideoMode::GetHeight() const
{
	return this->height;
}

int VideoMode::GetFullScreenRefreshRate() const
{
	return this->full_screen_refresh_rate;
}

BitsPerPixel VideoMode::GetBPP() const
{
	return this->bpp;
}

bool VideoMode::GetWindowed() const
{
	return this->windowed;
}

bool VideoMode::GetVSync() const
{
	return this->vsync;
}
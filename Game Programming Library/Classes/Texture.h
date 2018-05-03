#ifndef TEXTURE_H
#define TEXTURE_H

#include <FreeImage.h>
#include "Color.h"
#include "Log.h"
#include "ResourceFile.h"

namespace GPL
{
	class Texture
	{
	public:
		GPL_DLL Texture() = default;
		GPL_DLL virtual ~Texture() = 0 {};
		GPL_DLL int GetWidth() const;
		GPL_DLL int GetHeight() const;
		GPL_DLL static int GetTextureSizeMax();
		GPL_DLL static int NextPowerOfTwo(int value);
	protected:
		void SetSize(const int width,const int height,const bool check_power_of_two);
		void LoadFromFreeImage(std::unique_ptr<BYTE[]>& texture_pixels,int& texture_width,int& texture_height,const std::string& file_name,const int texture_id,const Color& color_key);
	private:
		int width{};
		int height{};
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		void ColorKey(std::unique_ptr<BYTE[]>& texture_pixels,const int texture_width,const int texture_height,const Color& color_key);
	};
}

#endif
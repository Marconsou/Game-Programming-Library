#ifndef FONTDIRECT3D9_H
#define FONTDIRECT3D9_H

#include "TextureDirect3D9.h"
#include "Font.h"

namespace GPL
{
	class FontDirect3D9 : public Font
	{
	public:
		GPL_DLL void LoadFont(const CComPtr<IDirect3DDevice9>& direct3d_device,const std::string& file_name,const int size,const FT_ULong first_character,const FT_ULong last_character,const float outline);
		GPL_DLL void LoadFont(const CComPtr<IDirect3DDevice9>& direct3d_device,const int font_id,const int size,const FT_ULong first_character,const FT_ULong last_character,const float outline);
	};
}

#endif
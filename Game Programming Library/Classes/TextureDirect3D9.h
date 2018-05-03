#ifndef TEXTUREDIRECT3D9_H
#define TEXTUREDIRECT3D9_H

#include <d3d9.h>
#include <atlbase.h>
#include "Texture.h"

namespace GPL
{
	class TextureDirect3D9 : public Texture
	{
	public:
		GPL_DLL const CComPtr<IDirect3DTexture9>& GetDirect3DTexture() const;
		GPL_DLL void CreateTexture(const CComPtr<IDirect3DDevice9>& direct3d_device,const UINT width,const UINT height,const UINT levels,const DWORD usage,const D3DFORMAT format,const D3DPOOL pool,const bool check_power_of_two);
		GPL_DLL void CreateTexture(const CComPtr<IDirect3DDevice9>& direct3d_device,const int width,const int height,const std::unique_ptr<BYTE[]>& texture_pixels,const int bytes_per_pixel,const D3DFORMAT format);
		GPL_DLL void LoadTexture(const CComPtr<IDirect3DDevice9>& direct3d_device,const std::string& file_name,const Color& color_key);
		GPL_DLL void LoadTexture(const CComPtr<IDirect3DDevice9>& direct3d_device,const int texture_id,const Color& color_key);
		GPL_DLL void ActivateTexture(const CComPtr<IDirect3DDevice9>& direct3d_device) const;
		static void DeactivateTexture(const CComPtr<IDirect3DDevice9>& direct3d_device);
		GPL_DLL void DeleteTexture();
	private:
		CComPtr<IDirect3DTexture9> direct3d_texture;
		static const TextureDirect3D9* last_texture;
	};
}

#endif
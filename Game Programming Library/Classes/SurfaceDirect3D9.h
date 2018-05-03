#ifndef SURFACEDIRECT3D9_H
#define SURFACEDIRECT3D9_H

#include <d3d9.h>
#include <atlbase.h>
#include "Log.h"

namespace GPL
{
	class SurfaceDirect3D9
	{
	public:
		SurfaceDirect3D9() = default;
		GPL_DLL void ActivateRenderTarget(const CComPtr<IDirect3DDevice9>& direct3d_device) const;
		GPL_DLL void RenderTargetFromBackBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device);
		GPL_DLL void SurfaceFromTexture(const CComPtr<IDirect3DTexture9>& direct3d_texture);
		GPL_DLL void DeleteSurface();
	private:
		CComPtr<IDirect3DSurface9> direct3d_surface;
		SurfaceDirect3D9(const SurfaceDirect3D9&) = delete;
		SurfaceDirect3D9& operator=(const SurfaceDirect3D9&) = delete;
	};
}

#endif
#ifndef RENDERTARGETDIRECT3D9_H
#define RENDERTARGETDIRECT3D9_H

#include "TextureDirect3D9.h"
#include "RenderTarget.h"
#include "SurfaceDirect3D9.h"

namespace GPL
{
	class RenderTargetDirect3D9 : public RenderTarget
	{
	public:
		GPL_DLL void ActivateRenderTarget(const CComPtr<IDirect3DDevice9>& direct3d_device) const;
		GPL_DLL void RenderTargetFromBackBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device,const int width,const int height,const Color& clear_color);
		GPL_DLL void CreateTextureRenderTarget(const CComPtr<IDirect3DDevice9>& direct3d_device,const int width,const int height,const Color& clear_color);
		void Clear() override;
	private:
		SurfaceDirect3D9 surface;
	};
}

#endif
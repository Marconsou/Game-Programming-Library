#include "SurfaceDirect3D9.h"

using namespace GPL;

void SurfaceDirect3D9::ActivateRenderTarget(const CComPtr<IDirect3DDevice9>& direct3d_device) const
{
	if (FAILED(direct3d_device->SetRenderTarget(0,this->direct3d_surface)))
		Log::Error(__FUNCTION__,"SetRenderTarget");
}

void SurfaceDirect3D9::RenderTargetFromBackBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device)
{
	this->DeleteSurface();

	if (FAILED(direct3d_device->GetRenderTarget(0,&this->direct3d_surface)))
		Log::Error(__FUNCTION__,"GetRenderTarget");
}

void SurfaceDirect3D9::SurfaceFromTexture(const CComPtr<IDirect3DTexture9>& direct3d_texture)
{
	this->DeleteSurface();

	if (FAILED(direct3d_texture->GetSurfaceLevel(0,&this->direct3d_surface)))
		Log::Error(__FUNCTION__,"GetSurfaceLevel");
}

void SurfaceDirect3D9::DeleteSurface()
{
	this->direct3d_surface.Release();
}
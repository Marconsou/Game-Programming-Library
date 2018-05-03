#include "RenderTargetDirect3D9.h"

using namespace std;
using namespace GPL;

void RenderTargetDirect3D9::ActivateRenderTarget(const CComPtr<IDirect3DDevice9>& direct3d_device) const
{
	this->surface.ActivateRenderTarget(direct3d_device);
}

void RenderTargetDirect3D9::RenderTargetFromBackBuffer(const CComPtr<IDirect3DDevice9>& direct3d_device,const int width,const int height,const Color& clear_color)
{
	this->surface.RenderTargetFromBackBuffer(direct3d_device);
	this->SetRenderTarget(width,height,clear_color);
}

void RenderTargetDirect3D9::CreateTextureRenderTarget(const CComPtr<IDirect3DDevice9>& direct3d_device,const int width,const int height,const Color& clear_color)
{
	//Se a textura não estiver alocada
	if (!this->GetPointerTexture().get())
		this->GetPointerTexture() = make_unique<TextureDirect3D9>();

	//Para que outros objetos não perca a referência para esta textura então não desalocá-la mas sim remover a textura
	else
		static_cast<TextureDirect3D9&>(*this->GetPointerTexture().get()).DeleteTexture();

	//Criando a textura para Render Target
	static_cast<TextureDirect3D9&>(*this->GetPointerTexture().get()).CreateTexture(direct3d_device,width,height,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,false);

	//Criando a Surface da Textura
	this->surface.SurfaceFromTexture(static_cast<const TextureDirect3D9&>(this->GetTexture()).GetDirect3DTexture());
	this->SetRenderTarget(width,height,clear_color);
}

void RenderTargetDirect3D9::Clear()
{
	//Se estiver usando textura então removê-la
	if (this->GetPointerTexture().get())
		static_cast<TextureDirect3D9&>(*this->GetPointerTexture().get()).DeleteTexture();

	//Remover Surface
	this->surface.DeleteSurface();
}
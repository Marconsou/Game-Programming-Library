#include "TextureDirect3D9.h"

using namespace std;
using namespace GPL;

const TextureDirect3D9* TextureDirect3D9::last_texture{};

const CComPtr<IDirect3DTexture9>& TextureDirect3D9::GetDirect3DTexture() const
{
	return this->direct3d_texture;
}

void TextureDirect3D9::CreateTexture(const CComPtr<IDirect3DDevice9>& direct3d_device,const UINT width,const UINT height,const UINT levels,const DWORD usage,const D3DFORMAT format,const D3DPOOL pool,const bool check_power_of_two)
{
	//Deletando a textura se necessário
	this->DeleteTexture();

	//Atualizando e verificando o tamanho da textura
	this->SetSize(width,height,check_power_of_two);

	//Criando a textura
	if (FAILED(direct3d_device->CreateTexture(width,height,levels,usage,format,pool,&this->direct3d_texture,nullptr)))
		Log::Error(__FUNCTION__,"CreateTexture");
}

void TextureDirect3D9::CreateTexture(const CComPtr<IDirect3DDevice9>& direct3d_device,const int width,const int height,const unique_ptr<BYTE[]>& texture_pixels,const int bytes_per_pixel,const D3DFORMAT format)
{
	//Criando a textura
	this->CreateTexture(direct3d_device,width,height,1,0,format,D3DPOOL_MANAGED,true);

	//Lock
	D3DLOCKED_RECT data;
	if (FAILED(this->direct3d_texture->LockRect(0,&data,nullptr,0)))
		Log::Error(__FUNCTION__,"LockRect");

	//Copiando os dados do buffer para a textura
	memcpy(data.pBits,texture_pixels.get(),this->GetWidth() * this->GetHeight() * bytes_per_pixel);

	//Unlock
	if (FAILED(this->direct3d_texture->UnlockRect(0)))
		Log::Error(__FUNCTION__,"UnlockRect");
}

void TextureDirect3D9::LoadTexture(const CComPtr<IDirect3DDevice9>& direct3d_device,const string& file_name,const Color& color_key)
{
	//Carregando a imagem para o Buffer
	int texture_width;
	int texture_height;
	unique_ptr<BYTE[]> texture_pixels;
	this->LoadFromFreeImage(texture_pixels,texture_width,texture_height,file_name,-1,color_key);

	//Criando a textura com tamanho e os pixels já calculados e preenchidos
	this->CreateTexture(direct3d_device,texture_width,texture_height,texture_pixels,4,D3DFMT_A8R8G8B8);
}

void TextureDirect3D9::LoadTexture(const CComPtr<IDirect3DDevice9>& direct3d_device,const int texture_id,const Color& color_key)
{
	//Carregando a imagem para o Buffer
	int texture_width;
	int texture_height;
	unique_ptr<BYTE[]> texture_pixels;
	this->LoadFromFreeImage(texture_pixels,texture_width,texture_height,"",texture_id,color_key);

	//Criando a textura com tamanho e os pixels já calculados e preenchidos
	this->CreateTexture(direct3d_device,texture_width,texture_height,texture_pixels,4,D3DFMT_A8R8G8B8);
}

void TextureDirect3D9::ActivateTexture(const CComPtr<IDirect3DDevice9>& direct3d_device) const
{
	if (TextureDirect3D9::last_texture != this)
	{
		TextureDirect3D9::last_texture = this;
		if (FAILED(direct3d_device->SetTexture(0,this->direct3d_texture)))
			Log::Error(__FUNCTION__,"SetTexture");
	}
}

void TextureDirect3D9::DeactivateTexture(const CComPtr<IDirect3DDevice9>& direct3d_device)
{
	TextureDirect3D9::last_texture = nullptr;
	if (FAILED(direct3d_device->SetTexture(0,nullptr)))
		Log::Error(__FUNCTION__,"SetTexture");
}

void TextureDirect3D9::DeleteTexture()
{
	this->direct3d_texture.Release();
}
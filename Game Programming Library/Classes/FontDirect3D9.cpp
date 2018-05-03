#include "FontDirect3D9.h"

using namespace std;
using namespace GPL;

void FontDirect3D9::LoadFont(const CComPtr<IDirect3DDevice9>& direct3d_device,const string& file_name,const int size,const FT_ULong first_character,const FT_ULong last_character,const float outline)
{
	int texture_width;
	int texture_height;
	unique_ptr<BYTE[]> texture_pixels;

	//Carregando a fonte para o Buffer
	this->LoadFontFreeType(texture_pixels,texture_width,texture_height,file_name,-1,size,first_character,last_character,outline);

	//Criando a textura com tamanho e os pixels já calculados e preenchidos
	static_cast<TextureDirect3D9*>(this->GetPointerTexture())->CreateTexture(direct3d_device,texture_width,texture_height,texture_pixels,2,D3DFMT_A8L8);
}

void FontDirect3D9::LoadFont(const CComPtr<IDirect3DDevice9>& direct3d_device,const int font_id,const int size,const FT_ULong first_character,const FT_ULong last_character,const float outline)
{
	int texture_width;
	int texture_height;
	unique_ptr<BYTE[]> texture_pixels;

	//Carregando a fonte para o Buffer
	this->LoadFontFreeType(texture_pixels,texture_width,texture_height,"",font_id,size,first_character,last_character,outline);

	//Criando a textura com tamanho e os pixels já calculados e preenchidos
	static_cast<TextureDirect3D9*>(this->GetPointerTexture())->CreateTexture(direct3d_device,texture_width,texture_height,texture_pixels,2,D3DFMT_A8L8);
}
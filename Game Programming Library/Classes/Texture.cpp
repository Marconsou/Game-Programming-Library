#include "Texture.h"

using namespace std;
using namespace GPL;

int Texture::GetWidth() const
{
	return this->width;
}

int Texture::GetHeight() const
{
	return this->height;
}

void Texture::SetSize(const int width,const int height,const bool check_power_of_two)
{
	//Largura e altura da textura
	this->width = width;
	this->height = height;

	//Verificando o limite do tamanho da textura
	if ((this->width > Texture::GetTextureSizeMax()) || (this->height > Texture::GetTextureSizeMax()))
		Log::Warning("Large texture size!");

	//Verificando se está em potência de 2
	if (check_power_of_two)
	{
		if ((this->width != Texture::NextPowerOfTwo(this->width)) || (this->height != Texture::NextPowerOfTwo(this->height)))
			Log::Warning("Non power of two!");
	}
}

void Texture::ColorKey(unique_ptr<BYTE[]>& texture_pixels,const int texture_width,const int texture_height,const Color& color_key)
{
	//Alterando a cor do Pixel para a nova textura
	const int bytes_per_pixel = 4;
	for (int x = 0; x < texture_width; x++)
	{
		for (int y = 0; y < texture_height; y++)
		{
			const int index = ((y * texture_width) + x) * bytes_per_pixel;

			const int r = texture_pixels[index];
			const int g = texture_pixels[index + 1];
			const int b = texture_pixels[index + 2];

			//Alpha Pixel transparente
			if ((r == color_key.GetRed() * 255.0f) && (g == color_key.GetGreen() * 255.0f) && (b == color_key.GetBlue() * 255.0f))
				texture_pixels[index + 3] = 0;
		}
	}
}

void Texture::LoadFromFreeImage(unique_ptr<BYTE[]>& texture_pixels,int& texture_width,int& texture_height,const string& file_name,const int texture_id,const Color& color_key)
{
	//Objetos da FreeImage
	FIBITMAP* fi_bitmap = nullptr;

	//Carregando a fonte
	if (!file_name.empty())
	{
		//Identificando o formato e carregando a imagem de um arquivo
		fi_bitmap = FreeImage_Load(FreeImage_GetFileType(file_name.c_str()),file_name.c_str());
		if (!fi_bitmap)
			Log::Error(__FUNCTION__,"FreeImage_Load",file_name);
	}
	else
	{
		//Extraindo o arquivo da fonte para ler da memória
		unique_ptr<char[]> memory_buffer;
		const size_t size = ResourceFile::Read(texture_id,memory_buffer);
		if (!size)
			Log::Error(__FUNCTION__,"Read");

		//Abrindo o buffer na memória
		FIMEMORY* fi_memory = FreeImage_OpenMemory(reinterpret_cast<BYTE*>(memory_buffer.get()),size);
		if (!fi_memory)
			Log::Error(__FUNCTION__,"FreeImage_OpenMemory");

		//Identificando o formato e carregando a imagem na memória
		fi_bitmap = FreeImage_LoadFromMemory(FreeImage_GetFileTypeFromMemory(fi_memory),fi_memory);
		if (!fi_bitmap)
			Log::Error(__FUNCTION__,"FreeImage_LoadFromMemory");

		//Limpando
		FreeImage_CloseMemory(fi_memory);
	}

	//Profundidade das cores (Bits Per Pixels) e mantendo a imagem em 32-bits
	if (FreeImage_GetBPP(fi_bitmap) != 32)
	{
		//Convertendo imagem para 32-bits
		FIBITMAP* converted_fi_bitmap = FreeImage_ConvertTo32Bits(fi_bitmap);
		if (!converted_fi_bitmap)
			Log::Error(__FUNCTION__,"FreeImage_ConvertTo32Bits");

		//Limpando a imagem antiga
		FreeImage_Unload(fi_bitmap);

		//Recebendo a imagem nova
		fi_bitmap = converted_fi_bitmap;
	}

	//Atualizando o tamanho da textura
	texture_width = FreeImage_GetWidth(fi_bitmap);
	texture_height = FreeImage_GetHeight(fi_bitmap);

	//Pegando os Pixels da imagem
	const int bytes_per_pixel = 4;
	const size_t size = texture_width * texture_height * bytes_per_pixel;
	texture_pixels = make_unique<BYTE[]>(size);

	for (int x = 0; x < texture_width; x++)
	{
		for (int y = 0; y < texture_height; y++)
		{
			const int index = ((y * texture_width) + x) * bytes_per_pixel;
			const int inverted_index = (((texture_height - y - 1) * texture_width) + x) * bytes_per_pixel;

			texture_pixels[index] = FreeImage_GetBits(fi_bitmap)[inverted_index];
			texture_pixels[index + 1] = FreeImage_GetBits(fi_bitmap)[inverted_index + 1];
			texture_pixels[index + 2] = FreeImage_GetBits(fi_bitmap)[inverted_index + 2];
			texture_pixels[index + 3] = FreeImage_GetBits(fi_bitmap)[inverted_index + 3];
		}
	}

	//Aplicando Color Key se necessário
	if (color_key != Color::Null)
		this->ColorKey(texture_pixels,texture_width,texture_height,color_key);

	//Removendo a imagem
	FreeImage_Unload(fi_bitmap);
}

int Texture::GetTextureSizeMax()
{
	return 1024;
}

int Texture::NextPowerOfTwo(int value)
{
	value--;
	value |= value >> 1;
	value |= value >> 2;
	value |= value >> 4;
	value |= value >> 8;
	value |= value >> 16;
	return ++value;
}
#include "Font.h"

using namespace std;
using namespace GPL;

const int Font::pixel_space{3};
const int Font::texture_width_max{Texture::GetTextureSizeMax() / 1};
const size_t Font::bytes_per_pixel{sizeof(Font::PixelL8A8)};

float Font::Character::GetWidth() const
{
	return (this->xmax - this->xmin + 1);
}

float Font::Character::GetHeight() const
{
	return (this->ymax - this->ymin + 1);
}

void Font::Character::SetBBox(const Span& span)
{
	this->xmin = static_cast<float>(span.x);
	this->xmax = static_cast<float>(span.y);
	this->ymin = static_cast<float>(span.x);
	this->ymax = static_cast<float>(span.y);
}

void Font::Character::Include(const Vector2D& vector_2d)
{
	this->xmin = min(this->xmin,vector_2d.x);
	this->ymin = min(this->ymin,vector_2d.y);
	this->xmax = max(this->xmax,vector_2d.x);
	this->ymax = max(this->ymax,vector_2d.y);
}

void Font::SetTexture(Texture& texture)
{
	this->pointer_texture = &texture;
}

const Texture& Font::GetTexture() const
{
	return *this->pointer_texture;
}

Texture* Font::GetPointerTexture()
{
	return this->pointer_texture;
}

FT_ULong Font::CharacterIndex(const FT_ULong index) const
{
	return (index - this->first_character);
}

float Font::GetMaxAdvanceWidth() const
{
	return this->max_advance_width;
}

float Font::GetMaxBearing() const
{
	return this->max_bearing;
}

float Font::GetLineHeight() const
{
	return this->line_height;
}

float Font::GetCharacterLeft(const FT_ULong index) const
{
	return this->characters[this->CharacterIndex(index)]->left;
}

float Font::GetCharacterTop(const FT_ULong index) const
{
	return this->characters[this->CharacterIndex(index)]->top;
}

float Font::GetCharacterTexturePositionX(const FT_ULong index) const
{
	return this->characters[this->CharacterIndex(index)]->texture_position_x;
}

float Font::GetCharacterTexturePositionY(const FT_ULong index) const
{
	return this->characters[this->CharacterIndex(index)]->texture_position_y;
}

float Font::GetCharacterWidth(const FT_ULong index) const
{
	return this->characters[this->CharacterIndex(index)]->GetWidth();
}

float Font::GetCharacterHeight(const FT_ULong index) const
{
	return this->characters[this->CharacterIndex(index)]->GetHeight();
}

float Font::GetCharacterAdvanceWidth(const FT_ULong index) const
{
	return this->characters[this->CharacterIndex(index)]->advance_width;
}

void Font::ExtractPixels(int& texture_width,int& texture_height,const string& file_name,const int font_id,const int size,const float outline)
{
	FT_Library library{};
	FT_Face face{};

	if (FT_Init_FreeType(&library))
		Log::Error(__FUNCTION__,"FT_Init_FreeType");

	unique_ptr<char[]> memory_buffer;
	if (!file_name.empty())
	{
		if (FT_New_Face(library,file_name.c_str(),0,&face))
			Log::Error(__FUNCTION__,"FT_New_Face",file_name);
	}
	else
	{
		const size_t size = ResourceFile::Read(font_id,memory_buffer);
		if (!size)
			Log::Error(__FUNCTION__,"Read");

		if (FT_New_Memory_Face(library,reinterpret_cast<FT_Byte*>(memory_buffer.get()),size,0,&face))
			Log::Error(__FUNCTION__,"FT_New_Memory_Face");
	}

	if (FT_Select_Charmap(face,FT_ENCODING_UNICODE))
		Log::Error(__FUNCTION__,"FT_Select_Charmap","FT_ENCODING_UNICODE");

	if (FT_Set_Char_Size(face,size << 6,size << 6,90,90))
		Log::Error(__FUNCTION__,"FT_Set_Char_Size");

	int width{};
	int height{};
	int max_line_height{};
	int increment_y{};
	bool max_width_reached{};

	for (FT_ULong i = this->first_character; i <= this->last_character; i++)
	{
		unique_ptr<Character> character = make_unique<Character>();

		if (FT_Load_Char(face,i,FT_LOAD_NO_BITMAP))
			Log::Error(__FUNCTION__,"FT_Load_Char","FT_LOAD_NO_BITMAP");

		character->left = static_cast<float>(face->glyph->metrics.horiBearingX >> 6);
		character->top = static_cast<float>(face->glyph->metrics.horiBearingY >> 6);
		character->advance_width = static_cast<float>(face->glyph->advance.x >> 6) + (outline * 1.0f);

		this->max_advance_width = max(this->max_advance_width,character->advance_width);
		this->max_bearing = max(this->max_bearing,character->top);
		this->min_hang = min(this->min_hang,static_cast<float>(character->top - (face->glyph->metrics.height >> 6)));

		//Need an outline for this to work
		if (face->glyph->format == FT_GLYPH_FORMAT_OUTLINE)
		{
			//Render the basic glyph to a span list
			vector<Span> spans;
			this->RenderSpans(library,face->glyph->outline,spans);

			//Next we need the spans for the outline
			vector<Span> outline_spans;

			//Set up a stroker
			FT_Stroker stroker;
			if (FT_Stroker_New(library,&stroker))
				Log::Error(__FUNCTION__,"FT_Stroker_New");

			FT_Stroker_Set(stroker,static_cast<FT_Fixed>(outline * 64),FT_STROKER_LINECAP_ROUND,FT_STROKER_LINEJOIN_ROUND,0);

			FT_Glyph glyph;
			if (FT_Get_Glyph(face->glyph,&glyph))
				Log::Error(__FUNCTION__,"FT_Get_Glyph");

			if (FT_Glyph_StrokeBorder(&glyph,stroker,0,1))
				Log::Error(__FUNCTION__,"FT_Glyph_StrokeBorder");

			//Again, this needs to be an outline to work
			if (glyph->format == FT_GLYPH_FORMAT_OUTLINE)
			{
				//Render the outline spans to the span list
				this->RenderSpans(library,reinterpret_cast<FT_OutlineGlyph&>(glyph)->outline,outline_spans);
			}

			//Clean up afterwards
			FT_Stroker_Done(stroker);
			FT_Done_Glyph(glyph);

			//Now we need to put it all together
			if (!spans.empty())
				this->CopySpansPixels(*character,spans,outline_spans,i);
		}
		else
			Log::Error(__FUNCTION__,"FT_GLYPH_FORMAT_OUTLINE");

		this->CalculateTextureSize(*character,i,width,height,max_line_height,increment_y,max_width_reached);

		characters.push_back(move(character));
	}

	if (FT_Done_Face(face))
		Log::Error(__FUNCTION__,"FT_Done_Face");

	if (FT_Done_FreeType(library))
		Log::Error(__FUNCTION__,"FT_Done_FreeType");

	//Atualizando a altura da linha
	this->line_height = (this->max_bearing - this->min_hang) + (outline * 2.0f);

	//Garantia de pelo menos uma linha
	height += increment_y;

	//Largura máxima alcançada
	if (max_width_reached)
		width = Font::texture_width_max;

	//Tamanho final da textura
	texture_width = Texture::NextPowerOfTwo(width);
	texture_height = Texture::NextPowerOfTwo(height);

	//Verificar a relação da altura com a largura máxima da textura
	if (texture_height >= Font::texture_width_max)
		Log::Warning("Large font (texture) size!");
}

void Font::RenderSpans(const FT_Library& library,FT_Outline& outline,vector<Span>& spans) const
{
	//Set up the raster parameters and render the outline
	FT_Raster_Params params{};
	params.flags = FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
	params.gray_spans = Font::RasterCallback;
	params.user = &spans;

	if (FT_Outline_Render(library,&outline,&params))
		Log::Error(__FUNCTION__,"FT_Outline_Render");
}

void Font::RasterCallback(const int y,const int count,const FT_Span* const spans,void* const user)
{
	//Each time the renderer calls us back we just push another span entry on our list
	vector<Span>* pointer_spans = reinterpret_cast<vector<Span>*>(user);
	for (int i = 0; i < count; ++i)
	{
		const FT_Span& iterator = spans[i];

		pointer_spans->push_back(Span(iterator.x,y,iterator.len,iterator.coverage));
	}
}

void Font::CalculateTextureSize(const Character& character,const FT_ULong i,int& width,int& height,int& max_line_height,int& increment_y,bool& max_width_reached) const
{
	const bool is_character_space = Font::IsCharacterSpace(i);

	//Maior altura da linha
	max_line_height = max(max_line_height,static_cast<int>(character.GetHeight()));

	//Distância entre os caracteres
	const int increment_x = static_cast<int>(character.GetWidth()) + Font::pixel_space;
	increment_y = max_line_height + Font::pixel_space;

	//Ainda está nesta linha
	if (increment_x + width < Font::texture_width_max)
	{
		//Não considerar espaço para não incrementar o espaço entre os pixels
		if (!is_character_space)
			width += increment_x;
	}

	//Hora de pular de linha
	else
	{
		//Não considerar espaço para não incrementar o espaço entre os pixels
		if (!is_character_space)
			width = increment_x;

		//Adicionando a altura desta linha antes de ir para a próxima
		height += increment_y;

		//Maior altura da linha anterior não deve-se entrar em consideração, então resetar valor
		max_line_height = 0;

		//Próxima linha
		max_width_reached = true;
	}
}

void Font::CopySpansPixels(Character& character,const vector<Span>& spans,const vector<Span>& outline_spans,const FT_ULong i)
{
	//Preto para funcionar corretamente
	const FT_Byte outline_luminance = 0;

	//Figure out what the bounding rect is for both the span lists
	character.SetBBox(spans.front());

	for (const auto& iterator : spans)
	{
		character.Include(Vector2D(static_cast<float>(iterator.x),static_cast<float>(iterator.y)));
		character.Include(Vector2D(static_cast<float>(iterator.x + iterator.width - 1),static_cast<float>(iterator.y)));
	}

	for (const auto& iterator : outline_spans)
	{
		character.Include(Vector2D(static_cast<float>(iterator.x),static_cast<float>(iterator.y)));
		character.Include(Vector2D(static_cast<float>(iterator.x + iterator.width - 1),static_cast<float>(iterator.y)));
	}

	if (!Font::IsCharacterSpace(i))
	{
		//Get some metrics of our image
		int width = static_cast<int>(character.GetWidth());
		int height = static_cast<int>(character.GetHeight());

		//Allocate data for our image
		unique_ptr<PixelL8A8[]> pixels = make_unique<PixelL8A8[]>(width * height);

		//Loop over the outline spans and just draw them into the image
		for (const auto& iterator : outline_spans)
		{
			for (int w = 0; w < iterator.width; ++w)
			{
				const int x = static_cast<int>(iterator.x - character.xmin + w);
				const int y = static_cast<int>(height - 1 - (iterator.y - character.ymin));

				const int index = (width * y) + x;

				PixelL8A8& pixel = pixels[index];

				pixel.l = outline_luminance;
				pixel.a = iterator.coverage;
			}
		}

		//Then loop over the regular glyph spans and blend them into the image
		for (const auto& iterator : spans)
		{
			for (int w = 0; w < iterator.width; ++w)
			{
				const int x = static_cast<int>(iterator.x - character.xmin + w);
				const int y = static_cast<int>(height - 1 - (iterator.y - character.ymin));

				const int index = (width * y) + x;

				PixelL8A8& pixel = pixels[index];

				FT_Byte& dst_l = pixel.l;
				FT_Byte& dst_a = pixel.a;

				FT_Byte src_l = 255;
				FT_Byte src_a = iterator.coverage;

				dst_l = static_cast<FT_Byte>(dst_l + ((src_l - dst_l) * src_a) / 255.0f);
				dst_a = min(255,dst_a + src_a);
			}
		}
		character.pixels = move(pixels);
	}
}

void Font::CopyTexturePixels(unique_ptr<BYTE[]>& texture_pixels,const int texture_width,const int& texture_height)
{
	int texture_position_x{};
	int texture_position_y{};
	int max_line_height{};

	for (FT_ULong i = this->first_character; i <= this->last_character; i++)
	{
		Character& character = *characters[this->CharacterIndex(i)];

		const bool is_character_space = Font::IsCharacterSpace(i);

		const int width = static_cast<int>(character.GetWidth());
		const int height = static_cast<int>(character.GetHeight());

		const int increment_x = width + Font::pixel_space;
		const int increment_y = max_line_height + Font::pixel_space;

		//Se passou da largura máxima
		if (texture_position_x + increment_x >= Font::texture_width_max)
		{
			//Verificar se não é espaço e resetar a posição para o ínicio
			if (!is_character_space)
				texture_position_x = 0;

			//Adicionar a altura do maior caractere desta linha
			texture_position_y += increment_y;

			//Resetando o valor da maior altura
			max_line_height = 0;
		}

		//Maior altura da linha
		max_line_height = max(max_line_height,height);

		character.texture_position_x = static_cast<float>(texture_position_x);
		character.texture_position_y = static_cast<float>(texture_position_y);

		//Verificar se não é espaço
		if ((!is_character_space) && (character.pixels))
		{
			//Posição relativa à textura final
			int global_texture_index_x = texture_position_x;
			int global_texture_index_y = texture_position_y;
			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					//Copiar os pixels da imagem do caractere para a textura
					const int texture_index = ((texture_width * global_texture_index_y) + global_texture_index_x) * Font::bytes_per_pixel;
					const int pixel_index = (width * y) + x;

					const PixelL8A8& pixel = character.pixels[pixel_index];

					texture_pixels[texture_index] = pixel.l;
					texture_pixels[texture_index + 1] = pixel.a;

					global_texture_index_y++;
				}
				global_texture_index_x++;
				global_texture_index_y = texture_position_y;
			}
			texture_position_x += increment_x;
		}

		//Limpar os pixels
		character.pixels.reset();
	}
}

void Font::LoadFontFreeType(unique_ptr<BYTE[]>& texture_pixels,int& texture_width,int& texture_height,const string& file_name,const int font_id,const int size,const FT_ULong first_character,const FT_ULong last_character,const float outline)
{
	//http://www.freetype.org/freetype2/docs/tutorial/example2.cpp
	//http://lazyfoo.net/tutorials/OpenGL/23_freetype_fonts/index.php

	//Armazenar o primeiro caractere para acessar facilmente o índice correspondente
	this->first_character = first_character;
	this->last_character = last_character;

	this->characters.reserve(this->last_character - this->first_character + 1);

	this->ExtractPixels(texture_width,texture_height,file_name,font_id,size,outline);

	texture_pixels = make_unique<BYTE[]>(texture_width * texture_height * Font::bytes_per_pixel);

	this->CopyTexturePixels(texture_pixels,texture_width,texture_height);
}

bool Font::IsCharacterSpace(const FT_ULong character)
{
	return (character == ' ');
}
#ifndef FONT_H
#define FONT_H

#include <algorithm>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H
#include "Texture.h"

namespace GPL
{
	class Font
	{
	public:
		GPL_DLL Font() = default;
		GPL_DLL virtual ~Font() = 0 {};
		GPL_DLL void SetTexture(Texture& texture);
		GPL_DLL const Texture& GetTexture() const;
		GPL_DLL float GetMaxAdvanceWidth() const;
		GPL_DLL float GetMaxBearing() const;
		GPL_DLL float GetLineHeight() const;
		GPL_DLL float GetCharacterLeft(const FT_ULong index) const;
		GPL_DLL float GetCharacterTop(const FT_ULong index) const;
		GPL_DLL float GetCharacterTexturePositionX(const FT_ULong index) const;
		GPL_DLL float GetCharacterTexturePositionY(const FT_ULong index) const;
		GPL_DLL float GetCharacterWidth(const FT_ULong index) const;
		GPL_DLL float GetCharacterHeight(const FT_ULong index) const;
		GPL_DLL float GetCharacterAdvanceWidth(const FT_ULong index) const;
		GPL_DLL static bool IsCharacterSpace(const FT_ULong character);
	protected:
		Texture* GetPointerTexture();
		void LoadFontFreeType(std::unique_ptr<BYTE[]>& texture_pixels,int& texture_width,int& texture_height,const std::string& file_name,const int font_id,const int size,const FT_ULong first_character,const FT_ULong last_character,const float outline);
	private:
		struct PixelL8A8
		{
			FT_Byte l{};
			FT_Byte a{};
			PixelL8A8() = default;
			PixelL8A8(const PixelL8A8&) = delete;
			PixelL8A8& operator=(const PixelL8A8&) = delete;
		};

		struct Vector2D
		{
			float x{};
			float y{};
			Vector2D(const float x,const float y) :
				x(x),
				y(y) {}
			Vector2D() = default;
			Vector2D(const Vector2D&) = delete;
			Vector2D& operator=(const Vector2D&) = delete;
		};

		struct Span
		{
			int x{};
			int y{};
			int width{};
			int coverage{};
			Span(const int x,const int y,const int width,const int coverage) :
				x(x),
				y(y),
				width(width),
				coverage(coverage) {}
		};

		struct Character
		{
			float left{};
			float top{};
			float texture_position_x{};
			float texture_position_y{};
			float xmin{};
			float xmax{};
			float ymin{};
			float ymax{};
			float advance_width{};
			std::unique_ptr<PixelL8A8[]> pixels;
			Character() = default;
			Character(const Character&) = delete;
			Character& operator=(const Character&) = delete;
			float GetWidth() const;
			float GetHeight() const;
			void SetBBox(const Span& span);
			void Include(const Vector2D& vector_2d);
		};

		Texture* pointer_texture{};
		FT_ULong first_character{};
		FT_ULong last_character{};
		float max_advance_width{};
		float max_bearing{};
		float min_hang{};
		float line_height{};
		std::vector<std::unique_ptr<Character>> characters;
		static const int pixel_space;
		static const int texture_width_max;
		static const size_t bytes_per_pixel;
		Font(const Font&) = delete;
		Font& operator=(const Font&) = delete;
		FT_ULong CharacterIndex(const FT_ULong index) const;
		void ExtractPixels(int& texture_width,int& texture_height,const std::string& file_name,const int font_id,const int size,const float outline);
		void RenderSpans(const FT_Library& library,FT_Outline& outline,std::vector<Span>& spans) const;
		void CalculateTextureSize(const Character& character,const FT_ULong i,int& width,int& height,int& max_line_height,int& increment_y,bool& max_width_reached) const;
		void CopySpansPixels(Character& character,const std::vector<Span>& spans,const std::vector<Span>& outline_spans,const FT_ULong i);
		void CopyTexturePixels(std::unique_ptr<BYTE[]>& texture_pixels,const int texture_width,const int& texture_height);
		static void RasterCallback(const int y,const int count,const FT_Span* const spans,void* const user);
	};
}

#endif
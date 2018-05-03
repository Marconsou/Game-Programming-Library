#ifndef TEXT_H
#define TEXT_H

#include "Video.h"

namespace GPL
{
	class Text
	{
	public:
		GPL_DLL Text();
		GPL_DLL Text(const Font& font,const std::string& string_text,const Color& color = Color::White);
		GPL_DLL const Font& GetFont() const;
		GPL_DLL void SetRenderTarget(const RenderTarget& render_target);
		GPL_DLL const RenderTarget& GetRenderTarget() const;
		GPL_DLL void SetView(const View& view);
		GPL_DLL const View& GetView() const;
		GPL_DLL void SetPixelateGridSize(const float pixelate_grid_size);
		GPL_DLL void SetInvertColor(const bool invert_color);
		GPL_DLL void SetGrayScale(const bool gray_scale);
		GPL_DLL void SetTransformX(const float transform_x);
		GPL_DLL float GetTransformX() const;
		GPL_DLL void SetTransformY(const float transform_y);
		GPL_DLL float GetTransformY() const;
		GPL_DLL void SetScaleX(const float scale_x);
		GPL_DLL float GetScaleX() const;
		GPL_DLL void SetScaleY(const float scale_y);
		GPL_DLL float GetScaleY() const;
		GPL_DLL void SetRotate(const float rotate);
		GPL_DLL float GetRotate() const;
		GPL_DLL void SetX(const float x);
		GPL_DLL float GetX() const;
		GPL_DLL void SetY(const float y);
		GPL_DLL float GetY() const;
		GPL_DLL void SetPosition(const float x,const float y,const bool centralize = false);
		GPL_DLL float GetW() const;
		GPL_DLL float GetH() const;
		GPL_DLL void SetAlpha(const float alpha);
		GPL_DLL void SetAlpha(const int index,const float alpha);
		GPL_DLL float GetAlpha(const int index = 0) const;
		GPL_DLL void SetColorLeft(const Color& color_left);
		GPL_DLL void SetColorTop(const Color& color_top);
		GPL_DLL void SetColorRight(const Color& color_right);
		GPL_DLL void SetColorBottom(const Color& color_bottom);
		GPL_DLL void SetColor(const Color& color);
		GPL_DLL void SetColor(const int index,const Color& color);
		GPL_DLL const Color& GetColor(const int index = 0) const;
		GPL_DLL void SetString(const std::string& string_text);
		GPL_DLL const std::string& GetString() const;
		GPL_DLL size_t GetValidCharacterTotal() const;
		GPL_DLL void SetText(const Font& font,const std::string& string_text,const Color& color = Color::White);
		GPL_DLL void AddText(const std::string& string_text,const Color& color);
		GPL_DLL void Show(Video& video,const int show_text_index_max = -1);
		GPL_DLL void Clear();
		GPL_DLL static Point2D<float> TextSize(const Font& font,const std::string& string_text);
	private:
		Model model;
		const Font* font{};
		size_t valid_character_total{};
		bool data_update{true};
		std::string string_text;
		Point2D<float> size;
		static const size_t vertex_rect_total;
		Text(const Text&) = delete;
		Text& operator=(const Text&) = delete;
		void SetColorBySide(const Color& color,const size_t first_index,const size_t second_index);
		void DataUpdate();
		void CharacterDataUpdate(const int index,const float x,const float y,const float w,const float h,const float texture_position_x,const float texture_position_y);

		template<typename Type>
		void CheckForDataUpdate(const Type& value_old,const Type& value_new)
		{
			if (value_old != value_new)
				this->data_update = true;
		}
	};
}

#endif
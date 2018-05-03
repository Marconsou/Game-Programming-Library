#ifndef SPRITE_H
#define SPRITE_H

#include "Video.h"

namespace GPL
{
	class Sprite
	{
	public:
		GPL_DLL Sprite() = default;
		GPL_DLL void SetTexture(const Texture& texture);
		GPL_DLL const Texture& GetTexture() const;
		GPL_DLL void SetRenderTarget(const RenderTarget& render_target);
		GPL_DLL const RenderTarget& GetRenderTarget() const;
		GPL_DLL void SetView(const View& view);
		GPL_DLL const View& GetView() const;
		GPL_DLL void SetPixelateGridSize(const float pixelate_grid_size);
		GPL_DLL void SetInvertColor(const bool invert_color);
		GPL_DLL void SetGrayScale(const bool gray_scale);
		GPL_DLL void SetTurnHorizontal(const bool turn_horizontal);
		GPL_DLL void SetTurnVertical(const bool turn_vertical);
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
		GPL_DLL void SetW(const float w);
		GPL_DLL float GetW() const;
		GPL_DLL void SetH(const float h);
		GPL_DLL float GetH() const;
		GPL_DLL void SetSize(const float w,const float h);
		GPL_DLL void SetColor(const Color& color);
		GPL_DLL void SetColor(const Color& color_left_top,const Color& color_right_top,const Color& color_left_bottom,const Color& color_right_bottom);
		GPL_DLL const Color& GetColor(const int index = 0) const;
		GPL_DLL void SetTexturePosition(const float texture_position_x,const float texture_position_y);
		GPL_DLL const Point2D<float>& GetTexturePosition() const;
		GPL_DLL void SetLeftTopVertexPosition(const float x,const float y);
		GPL_DLL const Point2D<float>& GetLeftTopVertexPosition() const;
		GPL_DLL void SetRightTopVertexPosition(const float x,const float y);
		GPL_DLL const Point2D<float>& GetRightTopVertexPosition() const;
		GPL_DLL void SetLeftBottomVertexPosition(const float x,const float y);
		GPL_DLL const Point2D<float>& GetLeftBottomVertexPosition() const;
		GPL_DLL void SetRightBottomVertexPosition(const float x,const float y);
		GPL_DLL const Point2D<float>& GetRightBottomVertexPosition() const;
		GPL_DLL void Show(Video& video);
	private:
		Model model{PrimitiveType::TriangleStrip,2,4,0};
		Point2D<float> size;
		Point2D<float> texture_position;
		Point2D<float> left_top_vertex;
		Point2D<float> right_top_vertex;
		Point2D<float> left_bottom_vertex;
		Point2D<float> right_bottom_vertex;
		bool data_update{true};
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;
		void DataUpdate();
		void VertexPositionUpdate(Point2D<float>& vertex_position,const float x,const float y);

		template<typename Type>
		void CheckForDataUpdate(const Type& value_old,const Type& value_new)
		{
			if (value_old != value_new)
				this->data_update = true;
		}
	};
}

#endif
#include "Sprite.h"

using namespace GPL;

void Sprite::SetTexture(const Texture& texture)
{
	this->CheckForDataUpdate(&this->GetTexture(),&texture);
	this->model.SetTexture(texture);
}

const Texture& Sprite::GetTexture() const
{
	return this->model.GetTexture();
}

void Sprite::SetRenderTarget(const RenderTarget& render_target)
{
	this->model.SetRenderTarget(render_target);
}

const RenderTarget& Sprite::GetRenderTarget() const
{
	return this->model.GetRenderTarget();
}

void Sprite::SetView(const View& view)
{
	this->model.SetView(view);
}

const View& Sprite::GetView() const
{
	return this->model.GetView();
}

void Sprite::SetPixelateGridSize(const float pixelate_grid_size)
{
	this->model.SetPixelateGridSize(pixelate_grid_size);
}

void Sprite::SetInvertColor(const bool invert_color)
{
	this->model.SetInvertColor(invert_color);
}

void Sprite::SetGrayScale(const bool gray_scale)
{
	this->model.SetGrayScale(gray_scale);
}

void Sprite::SetTurnHorizontal(const bool turn_horizontal)
{
	if (turn_horizontal)
		this->model.GetTextureCoordinateInverted().SetX((this->GetW() + (this->model.GetVertexTextureCoordinate(0).GetX() * 2)) / this->model.GetTexture().GetWidth());
	else
		this->model.GetTextureCoordinateInverted().SetX(0.0f);
}

void Sprite::SetTurnVertical(const bool turn_vertical)
{
	if (turn_vertical)
		this->model.GetTextureCoordinateInverted().SetY((this->GetH() + (this->model.GetVertexTextureCoordinate(0).GetY() * 2)) / this->model.GetTexture().GetHeight());
	else
		this->model.GetTextureCoordinateInverted().SetY(0.0f);
}

void Sprite::SetTransformX(const float transform_x)
{
	this->model.GetTransform().SetX(transform_x);
}

float Sprite::GetTransformX() const
{
	return this->model.GetTransform().GetX();
}

void Sprite::SetTransformY(const float transform_y)
{
	this->model.GetTransform().SetY(transform_y);
}

float Sprite::GetTransformY() const
{
	return this->model.GetTransform().GetY();
}

void Sprite::SetScaleX(const float scale_x)
{
	this->model.GetScale().SetX(scale_x);
}

float Sprite::GetScaleX() const
{
	return this->model.GetScale().GetX();
}

void Sprite::SetScaleY(const float scale_y)
{
	this->model.GetScale().SetY(scale_y);
}

float Sprite::GetScaleY() const
{
	return this->model.GetScale().GetY();
}

void Sprite::SetRotate(const float rotate)
{
	this->model.GetRotate().SetZ(rotate);
}

float Sprite::GetRotate() const
{
	return this->model.GetRotate().GetZ();
}

void Sprite::SetX(const float x)
{
	this->model.GetTranslate().SetX(ceil(x));
}

float Sprite::GetX() const
{
	return this->model.GetTranslate().GetX();
}

void Sprite::SetY(const float y)
{
	this->model.GetTranslate().SetY(ceil(y));
}

float Sprite::GetY() const
{
	return this->model.GetTranslate().GetY();
}

void Sprite::SetPosition(const float x,const float y,const bool centralize)
{
	const float center_x = (centralize) ? (this->GetW() / 2.0f) : 0.0f;
	const float center_y = (centralize) ? (this->GetH() / 2.0f) : 0.0f;

	this->SetX(x - center_x);
	this->SetY(y - center_y);
}

void Sprite::SetW(const float w)
{
	this->CheckForDataUpdate(this->GetW(),w);
	this->size.SetX(w);
}

float Sprite::GetW() const
{
	return this->size.GetX();
}

void Sprite::SetH(const float h)
{
	this->CheckForDataUpdate(this->GetH(),h);
	this->size.SetY(h);
}

float Sprite::GetH() const
{
	return this->size.GetY();
}

void Sprite::SetSize(const float w,const float h)
{
	this->SetW(w);
	this->SetH(h);
}

void Sprite::SetColor(const Color& color)
{
	for (size_t i = 0; i < this->model.GetVertexTotal(); i++)
		this->model.SetVertexColor(i,color);
}

void Sprite::SetColor(const Color& color_left_top,const Color& color_right_top,const Color& color_left_bottom,const Color& color_right_bottom)
{
	this->model.SetVertexColor(0,color_left_top);
	this->model.SetVertexColor(1,color_right_top);
	this->model.SetVertexColor(2,color_left_bottom);
	this->model.SetVertexColor(3,color_right_bottom);
}

const Color& Sprite::GetColor(const int index) const
{
	return this->model.GetVertexColor(index);
}

void Sprite::SetTexturePosition(const float texture_position_x,const float texture_position_y)
{
	this->CheckForDataUpdate(this->texture_position.GetX(),texture_position_x);
	this->texture_position.SetX(texture_position_x);

	this->CheckForDataUpdate(this->texture_position.GetY(),texture_position_y);
	this->texture_position.SetY(texture_position_y);
}

const Point2D<float>& Sprite::GetTexturePosition() const
{
	return this->texture_position;
}

void Sprite::SetLeftTopVertexPosition(const float x,const float y)
{
	this->VertexPositionUpdate(this->left_top_vertex,x,y);
}

const Point2D<float>& Sprite::GetLeftTopVertexPosition() const
{
	return this->left_top_vertex;
}

void Sprite::SetRightTopVertexPosition(const float x,const float y)
{
	this->VertexPositionUpdate(this->right_top_vertex,x,y);
}

const Point2D<float>& Sprite::GetRightTopVertexPosition() const
{
	return this->right_top_vertex;
}

void Sprite::SetLeftBottomVertexPosition(const float x,const float y)
{
	this->VertexPositionUpdate(this->left_bottom_vertex,x,y);
}

const Point2D<float>& Sprite::GetLeftBottomVertexPosition() const
{
	return this->left_bottom_vertex;
}

void Sprite::SetRightBottomVertexPosition(const float x,const float y)
{
	this->VertexPositionUpdate(this->right_bottom_vertex,x,y);
}

const Point2D<float>& Sprite::GetRightBottomVertexPosition() const
{
	return this->right_bottom_vertex;
}

void Sprite::VertexPositionUpdate(Point2D<float>& vertex_position,const float x,const float y)
{
	this->CheckForDataUpdate(vertex_position.GetX(),x);
	this->CheckForDataUpdate(vertex_position.GetY(),y);

	vertex_position.SetX(x);
	vertex_position.SetY(y);
}

void Sprite::DataUpdate()
{
	if (this->data_update)
	{
		// (x1,y1) 0----1 (x2,y1)
		//		   |   /|
		//		   |  / |
		//		   | /  |
		// (x1,y2) 2----3 (x2,y2)

		this->model.SetVertexPosition(0,this->left_top_vertex.GetX(),this->left_top_vertex.GetY());
		this->model.SetVertexPosition(1,this->right_top_vertex.GetX() + this->GetW(),this->right_top_vertex.GetY());
		this->model.SetVertexPosition(2,this->left_bottom_vertex.GetX(),this->left_bottom_vertex.GetY() + this->GetH());
		this->model.SetVertexPosition(3,this->right_bottom_vertex.GetX() + this->GetW(),this->right_bottom_vertex.GetY() + this->GetH());

		if (&this->GetTexture())
		{
			const float u = this->texture_position.GetX() / this->model.GetTexture().GetWidth();
			const float v = this->texture_position.GetY() / this->model.GetTexture().GetHeight();

			const float uw = this->GetW() / this->model.GetTexture().GetWidth();
			const float vh = this->GetH() / this->model.GetTexture().GetHeight();

			const float x_1 = u;
			const float y_1 = v;

			const float x_2 = x_1 + uw;
			const float y_2 = y_1 + vh;

			this->model.SetVertexTextureCoordinate(0,x_1,y_1);
			this->model.SetVertexTextureCoordinate(1,x_2,y_1);
			this->model.SetVertexTextureCoordinate(2,x_1,y_2);
			this->model.SetVertexTextureCoordinate(3,x_2,y_2);
		}

		this->data_update = false;
	}
}

void Sprite::Show(Video& video)
{
	this->DataUpdate();
	video.Draw(this->model);
}
#include "TrackBar.h"

using namespace std;
using namespace GPL;

TrackBar::TrackBar() :
	value(0),
	old_value(0),
	value_max(0),
	orientation{},
	mouse_click_on_bar(false),
	mouse_click_on_cursor(false),
	bar(PrimitiveType::TriangleStrip,2,4),
	cursor(PrimitiveType::TriangleStrip,2,4)
{
	this->AddEventOnKeyDown(&TrackBar::OnKeyDown,*this);
	this->AddEventOnMouseDown(&TrackBar::OnMouseDown,*this);
	this->AddEventOnMouseUp(&TrackBar::OnMouseUp,*this);
}

void TrackBar::SetValue(const int value)
{
	this->CheckForDataUpdate(this->value,value);
	this->old_value = this->value;
	this->value = max(min(value,this->value_max),0);
}

int TrackBar::GetValue() const
{
	return this->value;
}

void TrackBar::SetTrackBar(const int value_max,const float bar_length,const float bar_thickness,const float cursor_thickness,const float cursor_length,const Color& bar_color,const Color& cursor_color,const TrackBarOrientation orientation)
{
	//Valor mínimo e máximo
	this->value_max = value_max;

	//Orientação da direção do TrackBar
	this->orientation = orientation;

	//Horizontal
	if (this->orientation == TrackBarOrientation::Horizontal)
	{
		this->bar_rect.SetSize(bar_length,bar_thickness);
		this->cursor_rect.SetSize(cursor_thickness,cursor_length);
		this->GetRect().SetSize(bar_length,cursor_length);
	}

	//Vertical
	else if (this->orientation == TrackBarOrientation::Vertical)
	{
		this->bar_rect.SetSize(bar_thickness,bar_length);
		this->cursor_rect.SetSize(cursor_length,cursor_thickness);
		this->GetRect().SetSize(cursor_length,bar_length);
	}

	//Bar Color
	for (size_t i = 0; i < this->bar.GetVertexTotal(); i++)
		this->bar.SetVertexColor(i,bar_color);

	//Cursor Color
	for (size_t i = 0; i < this->cursor.GetVertexTotal(); i++)
		this->cursor.SetVertexColor(i,cursor_color);
}

void TrackBar::DataUpdate(const Input& input)
{
	//Se clicou na barra ou no cursor
	if ((this->mouse_click_on_bar) || (this->mouse_click_on_cursor))
	{
		//Horizontal
		if (this->orientation == TrackBarOrientation::Horizontal)
			this->SetValue(this->CalculateValueByPosition(static_cast<float>(input.GetMouseX()),this->GetX(),this->GetW(),this->cursor_rect.GetPosition().GetX(),this->cursor_rect.GetSize().GetX()));

		//Vertical
		else if (this->orientation == TrackBarOrientation::Vertical)
			this->SetValue(this->CalculateValueByPosition(static_cast<float>(input.GetMouseY()),this->GetY(),this->GetH(),this->cursor_rect.GetPosition().GetY(),this->cursor_rect.GetSize().GetY()));
	}

	if (this->GetDataUpdate())
	{
		//Horizontal
		if (this->orientation == TrackBarOrientation::Horizontal)
		{
			float position = this->value * ((this->GetW() - (this->cursor_rect.GetSize().GetX())) / this->value_max);

			//Posição X normal para o começo
			const float cursor_x = this->GetX() + position;

			this->cursor_rect.SetPosition(cursor_x,this->GetY());
			this->bar_rect.SetPosition(this->GetX(),this->GetY() + (this->GetH() / 2.0f) - (this->bar_rect.GetSize().GetY() / 2.0f));
		}

		//Vertical
		else if (this->orientation == TrackBarOrientation::Vertical)
		{
			float position = this->value * ((this->GetH() - (this->cursor_rect.GetSize().GetY())) / (this->value_max));

			//Posição Y invertida para o final
			const float cursor_y = this->GetY() + this->GetH() - this->cursor_rect.GetSize().GetY() - position;

			this->cursor_rect.SetPosition(this->GetX(),cursor_y);
			this->bar_rect.SetPosition(this->GetX() + (this->GetW() / 2.0f) - (this->bar_rect.GetSize().GetX() / 2.0f),this->GetY());
		}

		//Atualizar as dimensões dos objetos
		TrackBar::RectUpdate(this->bar_rect,this->bar);
		TrackBar::RectUpdate(this->cursor_rect,this->cursor);

		this->SetDataUpdate(false);
	}
}

int TrackBar::CalculateValueByPosition(const float mouse_position,const float track_bar_position,const float track_bar_size,const float cursor_position,const float cursor_size) const
{
	//Posição relativa na barra
	const float relative_position = mouse_position - track_bar_position;

	//Tamanho por onde o cursor percorre a barra
	const float virtual_track_size = track_bar_size - cursor_size;

	//Tamanho em que cada valor ocupa na barra
	const float bar_value_size = virtual_track_size / this->value_max;

	//Metade do tamanho do cursor
	const float cursor_half_size = (cursor_size / 2.0f);

	float final_position = 0.0f;
	float align_center = 0.0f;

	//Horizontal
	if (this->orientation == TrackBarOrientation::Horizontal)
	{
		final_position = relative_position;
		align_center = ((mouse_position < cursor_position + cursor_half_size) ? bar_value_size : 0.0f);
	}

	//Vertical
	else if (this->orientation == TrackBarOrientation::Vertical)
	{
		final_position = track_bar_size - relative_position;
		align_center = ((mouse_position > cursor_position + cursor_half_size) ? bar_value_size : 0.0f);
	}

	return static_cast<int>(((final_position - cursor_half_size + align_center) / virtual_track_size) * this->value_max);
}

void TrackBar::CheckForSpecificEvents()
{
	if (this->value != this->old_value)
	{
		this->on_value_changed(*this);
		this->old_value = this->value;
	}
}

bool TrackBar::Show(const Input& input,Video& video,const Timer& timer)
{
	//Atualizar dados
	this->DataUpdate(input);

	//Mostrar a barra
	video.Draw(this->bar);

	//Mostrar o cursor
	video.Draw(this->cursor);

	return false;
}

void TrackBar::Reset()
{
	this->mouse_click_on_bar = false;
	this->mouse_click_on_cursor = false;
}

void TrackBar::OnEnabledChanged(const Control& control)
{
	const bool change = !this->GetEnabled();

	this->bar.SetGrayScale(change);
	this->cursor.SetGrayScale(change);

	if (change)
		this->Reset();
}

void TrackBar::OnKeyDown(const Control& control,const KeyboardKey keyboard_key)
{
	if ((keyboard_key == KeyboardKey::Right) || (keyboard_key == KeyboardKey::Up))
		this->SetValue(this->value + 1);

	else if ((keyboard_key == KeyboardKey::Left) || (keyboard_key == KeyboardKey::Down))
		this->SetValue(this->value - 1);
}

void TrackBar::OnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	this->mouse_click_on_bar = this->bar_rect.PointInRect(mouse_x,mouse_y);
	this->mouse_click_on_cursor = this->cursor_rect.PointInRect(mouse_x,mouse_y);
}

void TrackBar::OnMouseUp(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	this->Reset();
}

void TrackBar::RectUpdate(const Rect<float>& rect,Model& model)
{
	const float x_1 = rect.GetPosition().GetX();
	const float y_1 = rect.GetPosition().GetY();

	const float x_2 = x_1 + rect.GetSize().GetX();
	const float y_2 = y_1 + rect.GetSize().GetY();

	//Vertex Position
	model.SetVertexPosition(0,x_1,y_1);
	model.SetVertexPosition(1,x_2,y_1);
	model.SetVertexPosition(2,x_1,y_2);
	model.SetVertexPosition(3,x_2,y_2);
}
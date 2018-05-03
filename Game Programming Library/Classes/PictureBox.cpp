#include "PictureBox.h"

using namespace std;
using namespace GPL;

void PictureBox::SetPosition(const float x,const float y,const bool centralize)
{
	Control::SetPosition(x,y,centralize);
	this->sprite.SetPosition(x,y,centralize);
	this->animation_frame.SetPosition(x,y,centralize);
}

void PictureBox::SetSprite(const Texture& texture,const float w,const float h,const float texture_position_x,const float texture_position_y,const Color& color)
{
	this->sprite.SetTexture(texture);
	this->sprite.SetSize(w,h);
	this->sprite.SetTexturePosition(texture_position_x,texture_position_y);
	this->sprite.SetColor(color);
	this->GetRect().SetSize(this->sprite.GetW(),this->sprite.GetH());
}

void PictureBox::SetAnimationFrame(const Timer& timer,const Texture& texture,const float frame_width,const float frame_height,const int frame_quantity,const float interval,const int pixel_gap)
{
	this->animation_frame.SetAnimationFrame(timer,texture,frame_width,frame_height,frame_quantity,interval,pixel_gap);
	this->animation_frame.Play(timer);
	this->GetRect().SetSize(this->animation_frame.GetW(),this->animation_frame.GetH());
}

void PictureBox::SetToolTip(const Font& font,const float edge_distance,const Color& background_color)
{
	this->tooltip.SetToolTip(font,edge_distance,background_color);
}

void PictureBox::NewToolTipTextLine(const string& string_text,const Color& color,const ToolTipTextAlign text_align)
{
	this->tooltip.NewTextLine(string_text,color,text_align);
}

void PictureBox::AddToolTipTextLine(const string& string_text,const Color& color)
{
	this->tooltip.AddTextLine(string_text,color);
}

void PictureBox::ShowAdditionalContent(const Input& input,Video& video,const Timer& timer)
{
	//Mostrar no lado oposto do Label em relação a tela Y
	const float distance_y = 3.0f;
	const float tooltip_y = (this->GetY() > video.GetVirtualHeight() / 2.0f) ? (this->GetY() - (this->tooltip.GetH() / 2.0f) - distance_y) :
		(this->GetY() + this->GetH() + (this->tooltip.GetH() / 2.0f) + distance_y);

	this->tooltip.SetPosition(this->GetX() + (this->GetW() / 2.0f),tooltip_y,true);
	this->tooltip.ShowToolTip(video);
}

bool PictureBox::Show(const Input& input,Video& video,const Timer& timer)
{
	this->sprite.Show(video);
	this->animation_frame.Show(video,timer,true);

	return this->GetMouseHover();
}

void PictureBox::OnEnabledChanged(const Control& control)
{
	const bool change = !this->GetEnabled();

	this->sprite.SetGrayScale(change);
	this->animation_frame.SetGrayScale(change);
}
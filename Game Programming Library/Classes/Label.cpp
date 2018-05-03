#include "Label.h"

using namespace std;
using namespace GPL;

void Label::SetPosition(const float x,const float y,const bool centralize)
{
	Control::SetPosition(x,y,centralize);
	this->text.SetPosition(x,y,centralize);
}

void Label::SetTextString(const string& string_text)
{
	this->text.SetString(string_text);
	this->GetRect().SetSize(this->text.GetW(),this->text.GetH());
}

const string& Label::GetTextString() const
{
	return this->text.GetString();
}

void Label::SetText(const Font& font,const string& string_text,const Color& color)
{
	this->text.SetText(font,string_text,color);
	this->GetRect().SetSize(this->text.GetW(),this->text.GetH());
}

void Label::SetTextColor(const Color& color)
{
	this->text.SetColor(color);
}

const Color& Label::GetTextColor() const
{
	return this->text.GetColor();
}

void Label::SetToolTip(const Font& font,const float edge_distance,const Color& background_color)
{
	this->tooltip.SetToolTip(font,edge_distance,background_color);
}

void Label::AddText(const string& string_text,const Color& color)
{
	this->text.AddText(string_text,color);
	this->GetRect().SetSize(this->text.GetW(),this->text.GetH());
}

void Label::ClearText()
{
	this->text.Clear();
}

void Label::NewToolTipTextLine(const string& string_text,const Color& color,const ToolTipTextAlign text_align)
{
	this->tooltip.NewTextLine(string_text,color,text_align);
}

void Label::AddToolTipTextLine(const string& string_text,const Color& color)
{
	this->tooltip.AddTextLine(string_text,color);
}

void Label::ShowAdditionalContent(const Input& input,Video& video,const Timer& timer)
{
	//Mostrar no lado oposto do Label em relação a tela Y
	const float distance_y = 3.0f;
	const float tooltip_y = (this->GetY() > video.GetVirtualHeight() / 2.0f) ? (this->GetY() - (this->tooltip.GetH() / 2.0f) - distance_y) :
		(this->GetY() + this->GetH() + (this->tooltip.GetH() / 2.0f) + distance_y);

	this->tooltip.SetPosition(this->GetX() + (this->GetW() / 2.0f),tooltip_y,true);
	this->tooltip.ShowToolTip(video);
}

bool Label::Show(const Input& input,Video& video,const Timer& timer)
{
	//Mostrar texto
	this->text.Show(video);

	return this->GetMouseHover();
}

void Label::OnEnabledChanged(const Control& control)
{
	const bool change = !this->GetEnabled();

	this->text.SetGrayScale(change);
}
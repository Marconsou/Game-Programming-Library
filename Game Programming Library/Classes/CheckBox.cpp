#include "CheckBox.h"

using namespace std;
using namespace GPL;

const float CheckBox::text_space(5.0f);

CheckBox::CheckBox() :
	checked(false),
	old_checked(false)
{
	this->AddEventOnMouseDown(&CheckBox::OnMouseDown,*this);
}

void CheckBox::SetChecked(const bool checked)
{
	this->CheckForDataUpdate(this->checked,checked);
	this->old_checked = this->checked;
	this->checked = checked;
}

bool CheckBox::GetChecked() const
{
	return this->checked;
}

void CheckBox::SetCheckBox(const Font& font,const string& string_text,const Color& text_color,const Texture& texture,const float background_w,const float background_h,const float background_texture_coordinate_x,const float background_texture_coordinate_y,const float check_w,const float check_h,const float check_texture_coordinate_x,const float check_texture_coordinate_y)
{
	//Text
	this->text.SetText(font,string_text,text_color);

	//Tamanho
	this->GetRect().SetSize(background_w + CheckBox::text_space + this->text.GetW(),max(background_h,this->text.GetH()));

	//Background
	this->background.SetTexture(texture);
	this->background.SetSize(background_w,background_h);
	this->background.SetTexturePosition(background_texture_coordinate_x,background_texture_coordinate_y);

	//Check
	this->check.SetTexture(texture);
	this->check.SetSize(check_w,check_h);
	this->check.SetTexturePosition(check_texture_coordinate_x,check_texture_coordinate_y);
}

void CheckBox::DataUpdate()
{
	if (this->GetDataUpdate())
	{
		//Se o texto é maior que o diametro do rádio
		const bool text_larger_than_box = (this->text.GetH() > this->background.GetH());

		float text_y;
		float background_y;
		if (!text_larger_than_box)
		{
			background_y = this->GetY();
			text_y = this->GetY() + (this->background.GetH()) - (this->text.GetH());
		}
		else
		{
			background_y = this->GetY() + (this->text.GetH() / 2.0f) - (this->background.GetH() / 2.0f);
			text_y = this->GetY();
		}

		this->background.SetPosition(this->GetX(),background_y);
		this->text.SetPosition(this->GetX() + this->background.GetW() + CheckBox::text_space,text_y);
		this->check.SetPosition(this->background.GetX() + (this->background.GetW() / 2.0f),this->background.GetY() + (this->background.GetH() / 2.0f),true);

		this->SetDataUpdate(false);
	}
}

void CheckBox::CheckForSpecificEvents()
{
	if (this->checked != this->old_checked)
	{
		this->on_checked_changed(*this);
		this->old_checked = this->checked;
	}
}

bool CheckBox::Show(const Input& input,Video& video,const Timer& timer)
{
	//Atualizar dados
	this->DataUpdate();

	//Background
	this->background.Show(video);

	//Check
	if (this->checked)
		this->check.Show(video);

	//Text
	this->text.Show(video);

	return false;
}

void CheckBox::OnEnabledChanged(const Control& control)
{
	const bool change = !this->GetEnabled();

	this->text.SetGrayScale(change);
	this->background.SetGrayScale(change);
	this->check.SetGrayScale(change);
}

void CheckBox::OnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	this->SetChecked(!this->checked);
}
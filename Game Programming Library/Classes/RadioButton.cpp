#include "RadioButton.h"

using namespace std;
using namespace GPL;

const float RadioButton::text_space(5.0f);
RadioButton::RadioGroup RadioButton::radio_groups;

RadioButton::RadioButton() :
	checked(false),
	old_checked(false)
{
	this->AddEventOnMouseDown(&RadioButton::OnMouseDown,*this);
	this->AddEventOnCheckedChanged(&RadioButton::OnCheckedChanged,*this);
}

RadioButton::~RadioButton()
{
	for (RadioGroup::const_iterator iterator = RadioButton::radio_groups.begin(); iterator != RadioButton::radio_groups.end(); iterator++)
	{
		if (this == &iterator->second)
		{
			RadioButton::radio_groups.erase(iterator);
			break;
		}
	}
}

void RadioButton::SetChecked(const bool checked)
{
	this->CheckForDataUpdate(this->checked,checked);
	this->old_checked = this->checked;
	this->checked = checked;
}

bool RadioButton::GetChecked() const
{
	return this->checked;
}

void RadioButton::SetRadioButton(const Font& font,const string& string_text,const Color& text_color,const Texture& texture,const float w,const float h,const float texture_position_x,const float texture_position_y,const string& radio_group_name)
{
	//Verificar se já se encontra na lista do Radio Group
	bool skip = false;
	for (RadioGroup::const_iterator iterator = RadioButton::radio_groups.begin(); iterator != RadioButton::radio_groups.end(); iterator++)
	{
		if (this == &iterator->second)
		{
			skip = true;
			break;
		}
	}

	//Adicionando para o Radio Groups se necessário
	if (!skip)
		RadioButton::radio_groups.insert(pair<const string,RadioButton&>(radio_group_name,*this));

	//Text
	this->text.SetText(font,string_text,text_color);

	//Tamanho
	this->GetRect().SetSize(w + RadioButton::text_space + this->text.GetW(),max(h,this->text.GetH()));

	//Background
	this->background.SetTexture(texture);
	this->background.SetSize(w,h);
	this->background.SetTexturePosition(texture_position_x,texture_position_y);

	//Check
	this->check.SetTexture(texture);
	this->check.SetSize(w,h);
	this->check.SetTexturePosition(texture_position_x + w,texture_position_y);
}

void RadioButton::DataUpdate()
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
		this->text.SetPosition(this->GetX() + this->background.GetW() + RadioButton::text_space,text_y);
		this->check.SetPosition(this->background.GetX(),this->background.GetY());

		this->SetDataUpdate(false);
	}
}

void RadioButton::CheckForSpecificEvents()
{
	if (this->checked != this->old_checked)
	{
		this->on_checked_changed(*this);
		this->old_checked = this->checked;
	}
}

bool RadioButton::Show(const Input& input,Video& video,const Timer& timer)
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

void RadioButton::OnEnabledChanged(const Control& control)
{
	const bool change = !this->GetEnabled();

	this->text.SetGrayScale(change);
	this->background.SetGrayScale(change);
	this->check.SetGrayScale(change);
}

void RadioButton::OnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	//Nâo pode desmarcar ele mesmo diretamente
	if (!this->checked)
		this->SetChecked(!this->checked);
}

void RadioButton::OnCheckedChanged(const Control& control)
{
	//Se ele estiver marcado, desmarcar todos os outros do mesmo grupo
	if (this->checked)
	{
		//Buscar pelo nome do grupo
		string radio_group_name;
		for (RadioGroup::const_iterator iterator = RadioButton::radio_groups.begin(); iterator != RadioButton::radio_groups.end(); iterator++)
		{
			if (this == &iterator->second)
				radio_group_name = iterator->first;
		}

		//Desmarcar todos os outros do mesmo grupo
		for (RadioGroup::const_iterator iterator = RadioButton::radio_groups.begin(); iterator != RadioButton::radio_groups.end(); iterator++)
		{
			if ((this != &iterator->second) && (iterator->first == radio_group_name))
				iterator->second.checked = false;
		}
	}
}
#include "Bar.h"

using namespace std;
using namespace GPL;

Bar::Bar() :
	show_background_bar(true),
	percentage(0),
	background_percentage(0),
	bar_width_initial(0.0f),
	background_bar_change_timer(0.020f)
{
	this->AddEventOnEnabledChanged(&Bar::OnEnabledChanged,*this);
}

void Bar::SetBarBase(Sprite& bar,const Texture& texture,const Color& color,const Rect<float>& texture_rect)
{
	bar.SetTexture(texture);
	bar.SetColor(color);
	bar.SetTexturePosition(texture_rect.GetPosition().GetX(),texture_rect.GetPosition().GetY());
	bar.SetSize(texture_rect.GetSize().GetX(),texture_rect.GetSize().GetY());
}

void Bar::SetBar(const Texture& texture,const Color& background_color,const Color& background_bar_color,const Color& foreground_bar_color,const Rect<float>& background_texture_rect,const Rect<float>& bar_texture_rect,const Point2D<float>& bar_position_relative)
{
	this->SetBarBase(this->background,texture,background_color,background_texture_rect);
	this->SetBarBase(this->background_bar,texture,background_bar_color,bar_texture_rect);
	this->SetBarBase(this->foreground_bar,texture,foreground_bar_color,bar_texture_rect);
	this->bar_position_relative = bar_position_relative;
	this->bar_width_initial = bar_texture_rect.GetSize().GetX();
	this->GetRect().SetSize(this->background.GetW(),this->background.GetH());
}

void Bar::SetShowBackgroundBar(const bool show_background_bar)
{
	this->show_background_bar = show_background_bar;
}

void Bar::SetPercentage(const int value_base,const int value_max)
{
	this->percentage = static_cast<int>(max(min((static_cast<float>(value_base) / static_cast<float>(value_max)) * 100.0f,100.0f),0.0f));
}

int Bar::GetPercentage() const
{
	return this->percentage;
}

int Bar::GetBackgroundPercentage() const
{
	return this->background_percentage;
}

void Bar::Update(const Input& input,const Timer& timer)
{
	//Barra do fundo será modificada com base na barra da frente a cada tempo
	if (this->background_bar_change_timer.Action(timer))
	{
		//Reduzir gradualmente
		if (this->background_percentage > this->percentage)
		{
			this->background_percentage -= 1;
			this->background_percentage = max(this->background_percentage,0);
		}

		//Resetar valor para a porcentagem atual
		else if (this->background_percentage < this->percentage)
			this->background_percentage = this->percentage;
	}

	//Atualizando a posição
	this->background.SetPosition(this->GetX(),this->GetY());
	this->foreground_bar.SetPosition(this->background.GetX() + this->bar_position_relative.GetX(),this->background.GetY() + this->bar_position_relative.GetY());
	this->background_bar.SetPosition(this->foreground_bar.GetX(),this->foreground_bar.GetY());

	//Atualizando o tamanho da barra do fundo com base na porcentagem
	this->background_bar.SetW((this->background_percentage / 100.0f) * this->bar_width_initial);

	//Atualizando o tamanho da barra da frente com base na porcentagem
	this->foreground_bar.SetW((this->percentage / 100.0f) * this->bar_width_initial);
}

bool Bar::Show(const Input& input,Video& video,const Timer& timer)
{
	//Mostrar o fundo da barra
	this->background.Show(video);

	//Mostrar a barra do fundo
	if (this->show_background_bar)
		this->background_bar.Show(video);

	//Mostrar a barra da frente
	this->foreground_bar.Show(video);

	return false;
}

void Bar::OnEnabledChanged(const Control& control)
{
	const bool change = !this->GetEnabled();

	this->background.SetGrayScale(change);
	this->background_bar.SetGrayScale(change);
	this->foreground_bar.SetGrayScale(change);
}
#include "ScreenEffect.h"

using namespace std;
using namespace GPL;

void ScreenEffect::StartFadeInScreen(const ScreenEffectFadeMode screen_fade_mode)
{
	this->screen_fade_mode = screen_fade_mode;
	this->fading_in_screen = true;
	this->fading_out_screen = false;
}

void ScreenEffect::StartFadeOutScreen(const ScreenEffectFadeMode screen_fade_mode)
{
	this->screen_fade_mode = screen_fade_mode;
	this->fading_out_screen = true;
	this->fading_in_screen = false;
}

bool ScreenEffect::FadeInEnd() const
{
	return (this->alpha == 0.0f);
}

bool ScreenEffect::FadeOutEnd() const
{
	return (this->alpha == 1.0f);
}

void ScreenEffect::Show(Video& video,const Timer& timer)
{
	//Fade In
	if (this->fading_in_screen)
	{
		//Fim
		if (this->FadeInEnd())
		{
			this->alpha = 0.0f;
			this->fading_in_screen = false;
		}
	}

	//Fade Out
	else if (this->fading_out_screen)
	{
		//Fim
		if (this->FadeOutEnd())
		{
			this->alpha = 1.0f;
			this->fading_out_screen = false;
		}
	}

	//Atualizando o valor de de Alpha
	static Interval screen_fade_timer(0.025f,timer);
	if (screen_fade_timer.Action(timer))
	{
		const float alpha_change =
			(this->screen_fade_mode == ScreenEffectFadeMode::Slow) ? 0.015f :
			(this->screen_fade_mode == ScreenEffectFadeMode::Normal) ? 0.054f :
			(this->screen_fade_mode == ScreenEffectFadeMode::Fast) ? 0.094f : 0.0f;

		if (this->fading_in_screen)
			this->alpha -= alpha_change;

		else if (this->fading_out_screen)
			this->alpha += alpha_change;

		this->alpha = min(max(this->alpha,0.0f),1.0f);
	}

	if (this->alpha > 0.0f)
	{
		//Altualizando transparência da tela
		static Color color(Color::Black);
		color.SetAlpha(this->alpha);

		//Renderizar tela
		const float width = static_cast<float>(video.GetVirtualWidth());
		const float height = static_cast<float>(video.GetVirtualHeight());

		for (size_t i = 0; i < screen.GetVertexTotal(); i++)
			screen.SetVertexColor(i,color);

		this->screen.SetVertexPosition(0,0.0f,0.0f);
		this->screen.SetVertexPosition(1,width,0.0f);
		this->screen.SetVertexPosition(2,0.0f,height);
		this->screen.SetVertexPosition(3,width,height);

		video.Draw(this->screen);
	}
}
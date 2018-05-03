#include "TextDynamicZoom.h"

using namespace std;
using namespace GPL;

void TextDynamicZoom::SetPosition(const float x,const float y,const bool centralize)
{
	TextDynamic::SetPosition(x,y,centralize);
	this->text_dynamic.SetPosition(this->GetRect().GetPosition().GetX(),this->GetRect().GetPosition().GetY() - this->change_y);
}

void TextDynamicZoom::SetTextDynamic(const Font& font,const string& string_text,const Color& color)
{
	//Resetando os valores do texto dinâmico
	this->Clear();

	//Texto
	this->text_dynamic.SetText(font,string_text,color);
	this->GetRect().SetSize(this->text_dynamic.GetW(),this->text_dynamic.GetH());
	this->text_dynamic.SetTransformX(this->GetRect().GetSize().GetX() / 2.0f);
	this->text_dynamic.SetTransformY(this->GetRect().GetSize().GetY() / 2.0f);
}

bool TextDynamicZoom::Play(const bool force_replay)
{
	return TextDynamic::Play(force_replay);
}

bool TextDynamicZoom::Show(Video& video,const Timer& timer)
{
	//Mostrar o Text Dynamic
	if (this->GetPlaying())
	{
		//Posição inicial
		const float x = this->GetRect().GetPosition().GetX();
		const float y = this->GetRect().GetPosition().GetY();

		//Tamanho do texto dinâmico
		float scale = this->text_dynamic.GetScaleX();
		if (this->scale_timer.Action(timer))
		{
			//Incrementar ou diminuir o tamanho
			const float change_scale = (!this->revert_scale) ? 0.15f : -0.15f;
			scale = max(min(this->text_dynamic.GetScaleX() + change_scale,2.0f),1.0f);

			//Revertendo o tamanho
			if (scale == 2.0f)
				this->revert_scale = true;
		}

		//Atualizar escala do texto dinâmico
		this->text_dynamic.SetScaleX(scale);
		this->text_dynamic.SetScaleY(scale);

		//Temporizador para mudar Alpha e a posição Y
		if (this->interval.Action(timer))
		{
			//Atualizando a cor com Alpha
			this->text_dynamic.SetAlpha(this->text_dynamic.GetAlpha() - 0.025f);

			//Atualizando o valor de Y
			this->change_y += 2.0f;
			this->text_dynamic.SetY(this->GetRect().GetPosition().GetY() - this->change_y);

			//Texto totalmente transparente
			if (this->text_dynamic.GetAlpha() <= 0.0f)
				this->SetPlaying(false);
		}

		//Mostrando o texto
		if (this->GetPlaying())
			this->text_dynamic.Show(video);
	}
	return this->GetPlaying();
}

void TextDynamicZoom::Clear()
{
	this->SetPlaying(false);

	//Alpha
	this->text_dynamic.SetAlpha(1.0f);

	//Scale
	this->text_dynamic.SetScaleX(1.0f);
	this->text_dynamic.SetScaleY(1.0f);

	this->revert_scale = false;
	this->change_y = 0.0f;
}
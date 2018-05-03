#include "AnimationFrame.h"

using namespace std;
using namespace GPL;

void AnimationFrame::SetTexture(const Texture& texture)
{
	this->sprite.SetTexture(texture);
}

void AnimationFrame::SetX(const float x)
{
	this->sprite.SetX(x);
}

float AnimationFrame::GetX() const
{
	return this->sprite.GetX();
}

void AnimationFrame::SetY(const float y)
{
	this->sprite.SetY(y);
}

float AnimationFrame::GetY() const
{
	return this->sprite.GetY();
}

void AnimationFrame::SetPosition(const float x,const float y,const bool centralize)
{
	this->sprite.SetPosition(x,y,centralize);
}

float AnimationFrame::GetW() const
{
	return this->sprite.GetW();
}

float AnimationFrame::GetH() const
{
	return this->sprite.GetH();
}

void AnimationFrame::SetPause(const bool pause)
{
	this->pause = pause;
}

void AnimationFrame::SetGrayScale(const bool gray_scale)
{
	this->sprite.SetGrayScale(gray_scale);
}

void AnimationFrame::SetColor(const Color& color)
{
	this->sprite.SetColor(color);
}

int AnimationFrame::GetCurrentFrame() const
{
	return this->frame_quantity.GetCurrent();
}

void AnimationFrame::TimerIntervalUpdate(const Timer& timer,const float interval)
{
	this->animation_timer.SetInterval(interval);
	this->animation_timer.Synchronize(timer);
}

void AnimationFrame::SetAnimationFrame(const Timer& timer,const Texture& texture,const float frame_width,const float frame_height,const int frame_quantity,const float interval,const int pixel_gap)
{
	//Tipo de estrutura e intervalo dos Pixels
	this->pixel_gap = pixel_gap;

	//Tamanho de cada Frame
	this->sprite.SetTexture(texture);
	this->sprite.SetSize(frame_width,frame_height);

	//Quantidade de Frames
	this->frame_quantity.SetTotal(frame_quantity);

	//Intervalo de cada Frame
	this->TimerIntervalUpdate(timer,interval);
	for (int i = 0; i < this->frame_quantity.GetTotal(); i++)
		this->interval.push_back(interval);
}

void AnimationFrame::EditInterval(const Timer& timer,const float interval)
{
	for (size_t i = 0; i < this->interval.size(); i++)
		this->EditInterval(timer,i,interval);
}

void AnimationFrame::EditInterval(const Timer& timer,const int index,const float interval)
{
	this->interval[index] = interval;
	if (this->frame_quantity.GetCurrent() == index)
		this->TimerIntervalUpdate(timer,interval);
}

bool AnimationFrame::IsPlaying() const
{
	return this->playing;
}

bool AnimationFrame::IsAtTheBeginning() const
{
	return this->frame_quantity.IsAtTheBeginning();
}

bool AnimationFrame::IsAtTheEnd() const
{
	return this->frame_quantity.IsAtTheEnd();
}

void AnimationFrame::Play(const Timer& timer,const bool forward,const bool force_replay)
{
	if ((!this->playing) || (force_replay))
	{
		this->playing = true;
		this->forward = forward;

		//Tocar para frente, começando pelo ínicio
		if (this->forward)
		{
			this->frame_quantity.Begin();
			this->TimerIntervalUpdate(timer,this->interval[0]);
		}

		//Tocar para trás, começando pelo final
		else
		{
			this->frame_quantity.End();
			this->TimerIntervalUpdate(timer,this->interval[this->frame_quantity.GetTotal() - 1]);
		}
	}
}

void AnimationFrame::Show(Video& video,const Timer& timer,const bool replay)
{
	//Mostrar o Sprite
	if (this->playing)
	{
		//Mudar para o próximo frame se não estiver pausado
		if ((!this->pause) && (this->animation_timer.Action(timer)))
		{
			const bool playing_forward = (this->forward) && (!this->frame_quantity.IsAtTheEnd());
			const bool playing_backward = (!this->forward) && (!this->frame_quantity.IsAtTheBeginning());

			//Animação não acabou e ainda está tocando
			if ((playing_forward) || (playing_backward))
			{
				//Passando para o próximo ou anterior dependendo do modo
				if (this->forward)
					this->frame_quantity.Next();
				else
					this->frame_quantity.Previous();

				//Atualizando o valor do intervalo
				this->TimerIntervalUpdate(timer,this->interval[this->frame_quantity.GetCurrent()]);
			}
			else
			{
				if (replay)
					this->Play(timer,this->forward);
				else
					this->playing = false;
			}
		}

		//Calculando a posição da textura
		const float total_width = this->GetW() + this->pixel_gap;
		const int frame_quantity_x = this->sprite.GetTexture().GetWidth() / static_cast<int>(total_width);
		const float texture_position_x = total_width * (this->frame_quantity.GetCurrent() % frame_quantity_x);
		const float texture_position_y = total_width * (this->frame_quantity.GetCurrent() / frame_quantity_x);

		//Atualizando a posição na textura
		this->sprite.SetTexturePosition(texture_position_x,texture_position_y);

		//Mostra a animação
		this->sprite.Show(video);
	}
}
#include "TextDynamic.h"

using namespace std;
using namespace GPL;

void TextDynamic::SetPlaying(const bool playing)
{
	this->playing = playing;
}

bool TextDynamic::GetPlaying() const
{
	return this->playing;
}

Rect<float>& TextDynamic::GetRect()
{
	return this->rect;
}

float TextDynamic::GetX() const
{
	return this->rect.GetPosition().GetX();
}

float TextDynamic::GetY() const
{
	return this->rect.GetPosition().GetY();
}

void TextDynamic::SetPosition(const float x,const float y,const bool centralize)
{
	this->rect.SetPosition(x,y,centralize);
}

float TextDynamic::GetW() const
{
	return this->rect.GetSize().GetX();
}

float TextDynamic::GetH() const
{
	return this->rect.GetSize().GetY();
}

bool TextDynamic::Play(const bool force_replay)
{
	if ((!this->playing) || (force_replay))
	{
		//Resetando os valores do texto dinâmico
		this->Clear();

		//Habilitando o texto dinâmico para ser mostrado
		this->playing = true;
		return true;
	}
	return false;
}
#include "AnimatedMapObject.h"

using namespace GPL;
using namespace RPG;

AnimatedMapObject::AnimatedMapObject() :
	MapObject(0.0f,0.0f,0.0f,0.0f,false,true)
{

}

void AnimatedMapObject::SetAnimatedMapObject(const Timer& timer,const Texture& texture,const float frame_width,const float frame_height,const int frame_quantity,const float interval,const int pixel_gap)
{
	//Tamanho e área de interação (mesmo não tendo algum tipo de interação)
	this->SetW(frame_width);
	this->SetH(frame_height);
	this->GetInteractionArea().SetSize(frame_width,frame_height);

	//Aniamtion Frame
	this->animation_frame.SetAnimationFrame(timer,texture,frame_width,frame_height,frame_quantity,interval,pixel_gap);
	this->animation_frame.Play(timer);
}

void AnimatedMapObject::SetPause(const bool pause)
{
	this->animation_frame.SetPause(pause);
}

void AnimatedMapObject::SetGrayScale(const bool gray_scale)
{
	this->animation_frame.SetGrayScale(gray_scale);
}

void AnimatedMapObject::UpdateMovement(const Timer& timer)
{
	//Área de interação do objeto centralizado
	this->GetInteractionArea().SetPosition(this->GetActionPositionX(),this->GetActionPositionY(),true);
}

void AnimatedMapObject::Update(const Timer& timer)
{
	//Atualizando as posições do objeto baseado na câmera
	this->animation_frame.SetPosition(this->GetX() - this->GetCameraX(),this->GetY() - this->GetCameraY());
}

void AnimatedMapObject::Show(Video& video,const Timer& timer)
{
	this->animation_frame.Show(video,timer,true);
}
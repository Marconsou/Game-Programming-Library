#include "StaticMapObject.h"

using namespace GPL;
using namespace RPG;

StaticMapObject::StaticMapObject() :
	MapObject(0.0f,0.0f,0.0f,0.0f,false,true)
{

}

void StaticMapObject::SetStaticMapObject(const Texture& texture,const float w,const float h,const float texture_position_x,const float texture_position_y)
{
	//Tamanho e área de interação (mesmo não tendo algum tipo de interação)
	this->SetW(w);
	this->SetH(h);
	this->GetInteractionArea().SetSize(w,h);

	//Sprite
	this->sprite.SetTexture(texture);
	this->sprite.SetSize(w,h);
	this->sprite.SetTexturePosition(texture_position_x,texture_position_y);
}

void StaticMapObject::SetGrayScale(const bool gray_scale)
{
	this->sprite.SetGrayScale(gray_scale);
}

void StaticMapObject::UpdateMovement(const Timer& timer)
{
	//Área de interação do objeto centralizado
	this->GetInteractionArea().SetPosition(this->GetActionPositionX(),this->GetActionPositionY(),true);
}

void StaticMapObject::Update(const Timer& timer)
{
	//Atualizando as posições do objeto baseado na câmera
	this->sprite.SetPosition(this->GetX() - this->GetCameraX(),this->GetY() - this->GetCameraY());
}

void StaticMapObject::Show(Video& video,const Timer& timer)
{
	this->sprite.Show(video);
}
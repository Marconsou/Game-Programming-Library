#include "StaticMapObject.h"

using namespace GPL;
using namespace RPG;

StaticMapObject::StaticMapObject() :
	MapObject(0.0f,0.0f,0.0f,0.0f,false,true)
{

}

void StaticMapObject::SetStaticMapObject(const Texture& texture,const float w,const float h,const float texture_position_x,const float texture_position_y)
{
	//Tamanho e �rea de intera��o (mesmo n�o tendo algum tipo de intera��o)
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
	//�rea de intera��o do objeto centralizado
	this->GetInteractionArea().SetPosition(this->GetActionPositionX(),this->GetActionPositionY(),true);
}

void StaticMapObject::Update(const Timer& timer)
{
	//Atualizando as posi��es do objeto baseado na c�mera
	this->sprite.SetPosition(this->GetX() - this->GetCameraX(),this->GetY() - this->GetCameraY());
}

void StaticMapObject::Show(Video& video,const Timer& timer)
{
	this->sprite.Show(video);
}
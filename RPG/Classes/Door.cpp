#include "Door.h"

using namespace std;
using namespace GPL;
using namespace RPG;

Door::Door(const LanguageTextID new_map_text_id,const DoorType door_type) :
	Gateway(new_map_text_id),
	door_type(door_type),
	last_open_index(0),
	entered(false),
	open_index(0,4,false),
	timer(0.050f)
{
	this->AddEventOnEnterInteractionArea(&Door::EnteringDoorEvent,*this);
	this->AddEventOnLeaveInteractionArea(&Door::LeavingDoorEvent,*this);
}

void Door::SetDoor(const Texture& texture,const float w,const float h)
{
	this->SetGateway(w,h);
	this->door_sprite.SetTexture(texture);
	this->door_sprite.SetSize(w,h);
}

void Door::SetGrayScale(const bool gray_scale)
{
	this->door_sprite.SetGrayScale(gray_scale);
}

void Door::UpdateMovement(const Timer& timer)
{
	Gateway::UpdateMovement(timer);
}

void Door::Update(const Timer& timer)
{
	Gateway::Update(timer);

	//Atualizando as posições do objeto baseado na câmera
	this->door_sprite.SetPosition(this->GetX() - this->GetCameraX(),this->GetY() - this->GetCameraY());

	//Fazer a porta abrir
	this->last_open_index = this->open_index.GetCurrent();
	if (this->timer.Action(timer))
	{
		if (this->entered)
			this->open_index.Next();
		else
			this->open_index.Previous();
	}

	//Atualizando a textura
	this->door_sprite.SetTexturePosition(this->door_type * this->GetW(),this->open_index.GetCurrent() * this->GetH());
}

void Door::Show(Video& video,const Timer& timer)
{
	Gateway::Show(video,timer);

	//Mostrar a porta
	this->door_sprite.Show(video);
}

void Door::CheckForSpecificEvents()
{
	//Se houve alguma animação
	const int current_open_index = this->open_index.GetCurrent();
	if (this->last_open_index != current_open_index)
	{
		//Porta aberta
		if ((this->last_open_index == 2) && (current_open_index == 3))
			this->on_opened(*this,this->GetInteraction());
	}
}

void Door::EnteringDoorEvent(MapObject& map_object_base,MapObject& map_object_interacting)
{
	this->entered = true;
}

void Door::LeavingDoorEvent(MapObject& map_object_base,MapObject& map_object_interacting)
{
	this->entered = false;
}
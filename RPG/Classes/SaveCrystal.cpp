#include "SaveCrystal.h"

using namespace GPL;
using namespace RPG;

const Database* SaveCrystal::database(nullptr);

SaveCrystal::SaveCrystal() :
	MapObject(64.0f,128.0f,192.0f,192.0f),
	interaction(false)
{

}

void SaveCrystal::SetSaveCrystal(const Video& video,const Timer& timer)
{
	//Save Crystal
	this->save_crystal.SetAnimationFrame(timer,video.GetTexture(TextureSaveCrystalDeactivatedFileID),this->GetW(),this->GetH(),3,0.150f);
	this->save_crystal.Play(timer);

	//Save Crystal Touch
	this->save_crystal_touch.SetAnimationFrame(timer,video.GetTexture(TextureSaveCrystalTouchFileID),192.0f,192.0f,5,0.120f);
}

float SaveCrystal::GetActionPositionX() const
{
	return (this->GetX() + (this->GetW() / 2.0f));
}

float SaveCrystal::GetActionPositionY() const
{
	return (this->GetY() + (this->GetH() * 0.75f));
}

float SaveCrystal::GetMoveToPositionX(const MapObject& map_object) const
{
	return this->GetMoveToPositionBase(&MapObject::GetActionPositionX,map_object,64.0f);
}

float SaveCrystal::GetMoveToPositionY(const MapObject& map_object) const
{
	return this->GetMoveToPositionBase(&MapObject::GetActionPositionY,map_object,64.0f);
}

void SaveCrystal::SetPause(const bool pause)
{
	this->save_crystal.SetPause(pause);
}

void SaveCrystal::SetGrayScale(const bool gray_scale)
{
	this->save_crystal.SetGrayScale(gray_scale);
}

void SaveCrystal::UpdateMovement(const Timer& timer)
{
	//Área de interação do objeto centralizado
	this->GetInteractionArea().SetPosition(this->GetActionPositionX(),this->GetActionPositionY(),true);
}

void SaveCrystal::Update(const Timer& timer)
{
	//Atualizando as posições do objeto baseado na câmera
	const float x = this->GetX() - this->GetCameraX();
	const float y = this->GetY() - this->GetCameraY();
	this->save_crystal.SetPosition(x,y);
	this->save_crystal_touch.SetPosition(x + (this->GetW() / 2.0f),y + (this->GetH() / 2.0f),true);
}

void SaveCrystal::Show(Video& video,const Timer& timer)
{
	//Atualizando o texto de ação por cima do Save Crystal
	this->SetActionToolTipText(video.GetFont(FontQlassikBoldMediumFileID),SaveCrystal::database->GetLanguageText(SaveCrystalActionTextID),Color::Green,3.0f);

	//Se o Save Crystal for tocado/interagido
	const bool is_map_object_interacted = (MapObject::GetMapObjectInteracted() == this);
	if (!this->interaction)
	{
		if (is_map_object_interacted)
		{
			this->save_crystal.SetTexture(video.GetTexture(TextureSaveCrystalActivatedFileID));
			this->save_crystal_touch.Play(timer);
			this->interaction = true;
		}
	}
	else
	{
		if (!is_map_object_interacted)
		{
			this->save_crystal.SetTexture(video.GetTexture(TextureSaveCrystalDeactivatedFileID));
			this->interaction = false;
		}
	}
	
	//Mostrar o Save Crystal
	this->save_crystal.Show(video,timer,true);
	this->save_crystal_touch.Show(video,timer);
}

void SaveCrystal::SetDatabase(const Database& database)
{
	SaveCrystal::database = &database;
}
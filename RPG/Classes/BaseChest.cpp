#include "BaseChest.h"

using namespace std;
using namespace GPL;
using namespace RPG;

const Database* BaseChest::database(nullptr);

BaseChest::BaseChest(const ChestType chest_type) :
	MapObject(64.0f,64.0f,64.0f,64.0f),
	chest_type(chest_type),
	last_open_index(0),
	open_index(0,4,false),
	timer(0.075f)
{

}

void BaseChest::SetChest(const Video& video)
{
	this->chest_sprite.SetTexture(video.GetTexture(TextureChestFileID));
	this->chest_sprite.SetSize(this->GetW(),this->GetH());
}

float BaseChest::GetMoveToPositionY(const MapObject& map_object) const
{
	return this->GetActionPositionY() + this->GetInteractionArea().GetSize().GetY();
}

void BaseChest::SetGrayScale(const bool gray_scale)
{
	this->chest_sprite.SetGrayScale(gray_scale);
}

void BaseChest::UpdateMovement(const Timer& timer)
{
	//Área de interação do objeto centralizado
	this->GetInteractionArea().SetPosition(this->GetX(),this->GetY() + this->GetInteractionArea().GetSize().GetY());
}

void BaseChest::Update(const Timer& timer)
{
	//Atualizando as posições do objeto baseado na câmera
	this->chest_sprite.SetPosition(this->GetX() - this->GetCameraX(),this->GetY() - this->GetCameraY());

	//Fazer o baú abrir ou fechar
	this->last_open_index = this->open_index.GetCurrent();
	if (this->timer.Action(timer))
	{
		if (MapObject::GetMapObjectInteracted() == this)
			this->open_index.Next();
		else
			this->open_index.Previous();
	}

	//Atualizando a textura
	this->chest_sprite.SetTexturePosition(this->chest_type * this->GetW(),this->open_index.GetCurrent() * this->GetH());
}

void BaseChest::Show(Video& video,const Timer& timer)
{
	//Atualizando o texto de ação por cima do Chest
	this->SetActionToolTipText(video.GetFont(FontQlassikBoldMediumFileID),BaseChest::database->GetLanguageText(OpenTextID),Color::Green,3.0f,this->IsPrivateChest() ? ("(" + BaseChest::database->GetLanguageText(PrivateChestTextID) + ")") : "",Color::Green);

	//Mostrar o Chest
	this->chest_sprite.Show(video);
}

void BaseChest::CheckForSpecificEvents()
{
	//Se houve alguma animação
	const int current_open_index = this->open_index.GetCurrent();
	if (this->last_open_index != current_open_index)
	{
		//Abrindo o baú
		if ((this->last_open_index == 0) && (current_open_index == 1))
			this->on_opening(*this);

		//Baú aberto
		else if ((this->last_open_index == 2) && (current_open_index == 3))
			this->on_opened(*this);

		//Fechando o baú
		else if ((this->last_open_index == 3) && (current_open_index == 2))
			this->on_closing(*this);

		//Baú fechado
		else if ((this->last_open_index == 1) && (current_open_index == 0))
			this->on_closed(*this);
	}
}

void BaseChest::SetDatabase(const Database& database)
{
	BaseChest::database = &database;
}

const Database& BaseChest::GetDatabase()
{
	return *BaseChest::database;
}
#include "Gateway.h"

using namespace std;
using namespace GPL;
using namespace RPG;

const Database* Gateway::database(nullptr);

Gateway::Gateway(const LanguageTextID new_map_text_id) :
	new_map_text_id(new_map_text_id)
{

}

void Gateway::SetGateway(const float w,const float h)
{
	this->SetW(w);
	this->SetH(h);
	this->GetInteractionArea().SetSize(w,h);
}

void Gateway::UpdateMovement(const Timer& timer)
{
	//Área de interação do objeto centralizado
	this->GetInteractionArea().SetPosition(this->GetActionPositionX(),this->GetActionPositionY(),true);
}

void Gateway::Update(const Timer& timer)
{
	
}

void Gateway::Show(Video& video,const Timer& timer)
{
	//Atualizando o texto de ação por cima do Gateway para o próximo mapa
	this->SetActionToolTipText(video.GetFont(FontQlassikBoldMediumFileID),Gateway::database->GetLanguageText(GatewayActionTextID),Color::White,3.0f,Gateway::database->GetLanguageText(new_map_text_id),Color::Yellow);
}

void Gateway::SetDatabase(const Database& database)
{
	Gateway::database = &database;
}
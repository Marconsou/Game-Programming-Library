#include "NPC.h"

using namespace std;
using namespace GPL;
using namespace RPG;

const Database* NPC::database(nullptr);

NPC::NPC() :
	dialogue(0)
{

}

void NPC::SetDialogue(const int dialogue)
{
	this->dialogue = dialogue;
}

int NPC::GetDialogue() const
{
	return this->dialogue;
}

void NPC::SetInteractionArea(const float w,const float h)
{
	this->GetInteractionArea().SetSize(w,h);
}

float NPC::GetMoveToPositionX(const MapObject& map_object) const
{
	//Manter o valor múltiplo de 64
	const float half = (this->GetInteractionArea().GetSize().GetX() / 2.0f);
	const float value = ((static_cast<int>(half) % 64) == 0) ? half : half - 32.0f;
	return this->GetMoveToPositionBase(&MapObject::GetActionPositionX,map_object,value);
}

float NPC::GetMoveToPositionY(const MapObject& map_object) const
{
	//Manter o valor múltiplo de 64
	const float half = (this->GetInteractionArea().GetSize().GetY() / 2.0f);
	const float value = ((static_cast<int>(half) % 64) == 0) ? half : half - 32.0f;
	return this->GetMoveToPositionBase(&MapObject::GetActionPositionY,map_object,value);
}

void NPC::NextDialogue()
{
	this->dialogue++;
}

void NPC::Show(Video& video,const Timer& timer)
{
	//Mostrando o NPC
	Character::Show(video,timer);

	//Atualizando o texto de ação por cima do NPC
	this->SetActionToolTipText(video.GetFont(FontQlassikBoldMediumFileID),NPC::database->GetLanguageText(NPCActionTextID),Color::Green,3.0f);
}

void NPC::SetDatabase(const Database& database)
{
	NPC::database = &database;
}
#ifndef NPC_H
#define NPC_H

#include "Character.h"
#include "Database.h"

namespace RPG
{
	class NPC : public Character
	{
	private:
		//Diálogo atual da conversa
		int dialogue;

		//Referência do Database para o texto de ação em cima do NPC
		static const Database* database;

		//Pegar Move To Position X
		virtual float GetMoveToPositionX(const MapObject& map_object) const;

		//Pegar Move To Position Y
		virtual float GetMoveToPositionY(const MapObject& map_object) const;

		//Mostrar o objeto
		virtual void Show(GPL::Video& video,const GPL::Timer& timer);
	public:
		//Construtor
		NPC();

		//Alterar Dialogue
		void SetDialogue(const int dialogue);

		//Pegar Dialogue
		int GetDialogue() const;

		//Alterar Interaction Area
		void SetInteractionArea(const float w,const float h);

		//Avançar para o próximo Dialogue
		void NextDialogue();

		//Alterar Database
		static void SetDatabase(const Database& database);
	};
}

#endif
#ifndef SAVECRYSTAL_H
#define SAVECRYSTAL_H

#include "AnimationFrame.h"
#include "MapObject.h"
#include "Database.h"

namespace RPG
{
	class SaveCrystal : public GPL::MapObject
	{
	private:
		//Interação foi feita com o Save Crystal
		bool interaction;

		//Save Crystal
		GPL::AnimationFrame save_crystal;

		//Animação do Save Crystal ao interagir
		GPL::AnimationFrame save_crystal_touch;

		//Referência do Database para o texto de ação em cima do Save Crystal
		static const Database* database;

		//Pegar Action Position X
		virtual float GetActionPositionX() const;

		//Pegar Action Position Y
		virtual float GetActionPositionY() const;

		//Pegar Move To Position X
		virtual float GetMoveToPositionX(const MapObject& map_object) const;

		//Pegar Move To Position Y
		virtual float GetMoveToPositionY(const MapObject& map_object) const;

		//Alterar Pause
		virtual void SetPause(const bool pause);

		//Alterar Gray Scale
		virtual void SetGrayScale(const bool gray_scale);

		//Atualizar dados de relacionados aos movimentos
		virtual void UpdateMovement(const GPL::Timer& timer);

		//Atualizar dados do objeto
		virtual void Update(const GPL::Timer& timer);

		//Mostrar o objeto
		virtual void Show(GPL::Video& video,const GPL::Timer& timer);
	public:
		//Construtor
		SaveCrystal();

		//Alterar Save Crystal
		void SetSaveCrystal(const GPL::Video& video,const GPL::Timer& timer);

		//Alterar Database
		static void SetDatabase(const Database& database);
	};
}

#endif
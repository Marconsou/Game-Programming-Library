#ifndef DOOR_H
#define DOOR_H

#include "Quantity.h"
#include "Interval.h"
#include "Sprite.h"
#include "Gateway.h"

namespace RPG
{
	//Tipo da porta
	enum DoorType
	{
		//Wood
		DoorSingleWoodDarkWindowed = 0,
		DoorSingleWoodLightWindowed,
		DoorSingleWoodDark,
		DoorSingleWoodLight,
	};

	class Door : public Gateway
	{
	private:
		using Event = GPL::Signal<void,MapObject&,MapObject&>;

		//Tipo da porta
		const DoorType door_type;

		//�ltimo �ndice da abertura da porta
		int last_open_index;

		//Personagem entrou na regi�o da porta
		bool entered;

		//Porta
		GPL::Sprite door_sprite;

		//�ndice de cada abertura do ba�
		GPL::Quantity open_index;

		//Temporizador da anima��o do ba�
		GPL::Interval timer;

		//Evento da porta aberta
		Event on_opened;

		//Evento ao entrar na regi�o da porta
		void EnteringDoorEvent(GPL::MapObject& map_object_base,GPL::MapObject& map_object_interacting);

		//Evento ao sair da regi�o da porta
		void LeavingDoorEvent(GPL::MapObject& map_object_base,GPL::MapObject& map_object_interacting);

		//Alterar Gray Scale
		virtual void SetGrayScale(const bool gray_scale);

		//Atualizar dados de relacionados aos movimentos
		virtual void UpdateMovement(const GPL::Timer& timer);

		//Atualizar dados do objeto
		virtual void Update(const GPL::Timer& timer);

		//Mostrar o objeto
		virtual void Show(GPL::Video& video,const GPL::Timer& timer);

		//Verificar por eventos espec�ficos do objeto do mapa
		virtual void CheckForSpecificEvents();
	public:
		//Construtor
		Door(const LanguageTextID new_map_text_id,const DoorType door_type);

		//Alterar Door
		void SetDoor(const GPL::Texture& texture,const float w,const float h);

		template<class Event,class Object> void AddEventOnOpened(const Event& event,Object& object) { this->on_opened.Add(event,object,std::placeholders::_1,std::placeholders::_2); }
	};
}

#endif
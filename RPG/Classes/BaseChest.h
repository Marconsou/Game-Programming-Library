#ifndef BASECHEST_H
#define BASECHEST_H

#include "Quantity.h"
#include "Interval.h"
#include "Sprite.h"
#include "MapObject.h"
#include "Database.h"

namespace RPG
{
	//Tipo do baú
	enum ChestType
	{
		ChestSmall = 0,
		ChestNormal,
		ChestRed,
		ChestBlue,
	};

	class BaseChest : public GPL::MapObject
	{
	private:
		using Event = GPL::Signal<void,MapObject&>;


		//Tipo do baú
		const ChestType chest_type;

		//Último índice da abertura do baú
		int last_open_index;

		//Baú
		GPL::Sprite chest_sprite;

		//Índice de cada abertura do baú
		GPL::Quantity open_index;

		//Temporizador da animação do baú
		GPL::Interval timer;

		//Evento do baú se abrindo
		Event on_opening;

		//Evento do baú aberto
		Event on_opened;

		//Evento do baú se fechando
		Event on_closing;

		//Evento do baú fechado
		Event on_closed;

		//Referência do Database para o texto de ação em cima do Chest
		static const Database* database;

		//Pegar Move To Position Y
		virtual float GetMoveToPositionY(const MapObject& map_object) const;

		//Alterar Gray Scale
		virtual void SetGrayScale(const bool gray_scale);

		//Atualizar dados de relacionados aos movimentos
		virtual void UpdateMovement(const GPL::Timer& timer);

		//Atualizar dados do objeto
		virtual void Update(const GPL::Timer& timer);

		//Mostrar o objeto
		virtual void Show(GPL::Video& video,const GPL::Timer& timer);

		//Verificar por eventos específicos do objeto do mapa
		virtual void CheckForSpecificEvents();
	protected:
		//Pegar Database
		static const Database& GetDatabase();
	public:
		//Construtor
		BaseChest(const ChestType chest_type);

		//Alterar Chest
		void SetChest(const GPL::Video& video);

		template<class Event,class Object> void AddEventOnOpening(const Event& event,Object& object) { this->on_opening.Add(event,object,std::placeholders::_1); }
		template<class Event,class Object> void AddEventOnOpened(const Event& event,Object& object) { this->on_opened.Add(event,object,std::placeholders::_1); }
		template<class Event,class Object> void AddEventOnClosing(const Event& event,Object& object) { this->on_closing.Add(event,object,std::placeholders::_1); }
		template<class Event,class Object> void AddEventOnClosed(const Event& event,Object& object) { this->on_closed.Add(event,object,std::placeholders::_1); }

		//Pegar Items
		virtual std::vector<std::unique_ptr<Item>>& GetItems() = 0;

		//Pegar Menu Text
		virtual const std::string& GetMenuText() const = 0;

		//Verificar se é o baú privado
		virtual bool IsPrivateChest() const = 0;

		//Alterar Database
		static void SetDatabase(const Database& database);
	};
}

#endif
#ifndef MAPAREA01_H
#define MAPAREA01_H

#include "Map.h"
#include "NPC.h"
#include "AnimatedMapObject.h"
#include "SaveCrystal.h"
#include "Chest.h"
#include "PrivateChest.h"
#include "Door.h"
#include "StaticMapObject.h"

namespace RPG
{
	class MapArea01 : public Map
	{
	private:

		Shop item_shop;


		void TalkWithNPC0Event(GPL::MapObject& map_object_base,GPL::MapObject& map_object_interacting);


		void NPC0Dialogue0Option0Event(const GPL::Control& control,const int option_selected_index);


		void GatewayEvent(GPL::MapObject& map_object_base,GPL::MapObject& map_object_interacting);


		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();

		//Mostrar todo o conteúdo
		virtual void Show();

		//Carregar o arquivo contendo as informações do mapa
		virtual void LoadingMapFile();

		//Carregar os dados depois de carregar o arquivo
		virtual void LoadingMapData();

		//Carregar o restante dos conteúdos do mapa
		virtual void LoadingMapContents();

		//Salvar os dados do mapa antes de removê-lo
		virtual void SaveMapDataState();
	public:
		//Construtor
		MapArea01(const float hero_position_x,const float hero_position_y,const bool hero_teleporting,const HeroMapChangeDirection hero_entering_map_direction);
	};
}

#endif
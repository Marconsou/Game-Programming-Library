#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "MapArea00.h"
#include "MapArea01.h"

namespace RPG
{
	class MapManager : public GPL::GameState
	{
	private:
		//Mapa que está sendo carregado
		Map* loading_map;

		//ID da última música tocada
		FileID last_music_id;

		//Carregando arquivo com os dados do mapa
		bool load_map_file;

		//Carregando os dados do mapa
		bool load_map_data;

		//Mapa carregado
		bool map_loaded;

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();

		//Mostrar todo o conteúdo
		virtual void Show() {};
	public:
		//Construtor
		MapManager();

		//Criar mapa com base no ID
		bool CreateMap(const MapID map_id_to_load,const float hero_position_x,const float hero_position_y);
	};
}

#endif
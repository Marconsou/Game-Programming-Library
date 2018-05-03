#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "MapArea00.h"
#include "MapArea01.h"

namespace RPG
{
	class MapManager : public GPL::GameState
	{
	private:
		//Mapa que est� sendo carregado
		Map* loading_map;

		//ID da �ltima m�sica tocada
		FileID last_music_id;

		//Carregando arquivo com os dados do mapa
		bool load_map_file;

		//Carregando os dados do mapa
		bool load_map_data;

		//Mapa carregado
		bool map_loaded;

		//Atualizar dados e a l�gica de todo o conte�do
		virtual void Update();

		//Mostrar todo o conte�do
		virtual void Show() {};
	public:
		//Construtor
		MapManager();

		//Criar mapa com base no ID
		bool CreateMap(const MapID map_id_to_load,const float hero_position_x,const float hero_position_y);
	};
}

#endif
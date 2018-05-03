#ifndef MAPTILEBASE_H
#define MAPTILEBASE_H

#include "Format.h"
#include "TileSet.h"
#include "MapObject.h"
#include "GameState.h"

namespace GPL
{
	class MapTileBase : public GameState
	{
	private:
		struct SharedTile
		{
			bool walkable{true};
			SharedTile() = default;
			SharedTile& operator=(const SharedTile&) = delete;
		};

		//Dimens�o dos Tile Sets e quantidade de total de Tiles
		Point2D<int> tile_total;

		//Posi��o da c�mera dentro do mapa
		Point2D<float> camera;

		//Objetos do mapa
		std::vector<std::shared_ptr<MapObject>> map_objects;

		//Todos os Tile Sets do fundo renderizados em sequ�ncia
		std::vector<std::unique_ptr<TileSet>> background_tile_sets;

		//Todos os Tile Sets da frente renderizados em sequ�ncia
		std::vector<std::unique_ptr<TileSet>> foreground_tile_sets;

		//Tiles com dados compartilhados
		std::vector<std::vector<SharedTile>> shared_tiles;

		//IDs das texturas dos Tile Sets
		std::vector<int> texture_tile_sets_id;

		//Dados do mapa com texto ao ler de uma fonte
		std::vector<std::string> map_data_values;

		//Carregar Tile Set dos dados j� carregados
		void LoadTileSetFromData(std::vector<std::unique_ptr<TileSet>>& tile_sets,const std::vector<int>& texture_tile_sets_id,const std::vector<std::string>& values,size_t& value_index,const int tile_set_index);

		//Carregar Tiles com dados compartilhados dos dados j� carregados
		void LoadSharedTilesFromData(const std::vector<std::string>& values,size_t& value_index);
	protected:
		//Pegar Tile Total
		GPL_DLL const Point2D<int>& GetTileTotal() const;

		//Pegar Camera
		GPL_DLL const Point2D<float>& GetCamera() const;

		//Pegar Map Objects
		GPL_DLL std::vector<std::shared_ptr<MapObject>>& GetMapObjects();

		//Pegar Shared Tiles
		GPL_DLL bool GetSharedTileWalkable(const size_t x,const size_t y) const;

		//Pegar Texture Tile Sets ID
		GPL_DLL const std::vector<int>& GetTextureTileSetsID() const;

		//Alterar Pause
		GPL_DLL void SetPause(const bool pause);

		//Alterar Gray Scale
		GPL_DLL void SetGrayScale(const bool gray_scale);

		//Adicionar ID da textura do Tile Set
		GPL_DLL void AddTextureTileSetID(const int texture_tile_set_id);

		//Centralizar c�mera em um objeto do mapa
		GPL_DLL void CenterCamera(const Video& video,const MapObject& map_object);

		//Carregar mapa
		GPL_DLL void LoadMapFile(const int map_id);

		//Carregar dados do mapa depois de ter carregado de uma fonte
		GPL_DLL void LoadMapData(const std::vector<int>& texture_background_tile_sets_id,const std::vector<int>& texture_foreground_tile_sets_id);

		//Adicionar o objeto do mapa
		template<class Type> void AddMapObject(std::shared_ptr<Type>& map_object)
		{
			//Adicionar objeto do mapa para receber eventos e adicionar tamb�m no pr�prio mapa
			map_object.get()->AddMapObject();
			if (find(this->map_objects.begin(),this->map_objects.end(),map_object) == this->map_objects.end())
				this->map_objects.push_back(map_object);

			//C�mera do mapa
			map_object.get()->SetCamera(this->camera);
		}

		//Pausar todo o conte�do
		GPL_DLL void Pausing() override;

		//Resumir todo o conte�do pausado
		GPL_DLL void Resuming() override;

		//Atualizar dados e a l�gica de todo o conte�do
		GPL_DLL void Update() override;

		//Mostrar todo o conte�do
		GPL_DLL void Show() override;
	public:
		//Construtor
		GPL_DLL MapTileBase();

		//Destrutor
		GPL_DLL virtual ~MapTileBase() = 0;
	};
}

#endif
#include "MapTileBase.h"

using namespace std;
using namespace GPL;

MapTileBase::MapTileBase()
{

}

MapTileBase::~MapTileBase()
{
	Video& video = GameState::GetGame<Game>().GetVideo();

	//Removendo as texturas carregas por este mapa
	for (size_t i = 0; i < this->texture_tile_sets_id.size(); i++)
		video.UnloadTexture(this->texture_tile_sets_id[i]);
}

const Point2D<int>& MapTileBase::GetTileTotal() const
{
	return this->tile_total;
}

const Point2D<float>& MapTileBase::GetCamera() const
{
	return this->camera;
}

vector<shared_ptr<MapObject>>& MapTileBase::GetMapObjects()
{
	return this->map_objects;
}

bool MapTileBase::GetSharedTileWalkable(const size_t x,const size_t y) const
{
	return this->shared_tiles[x][y].walkable;
}

const vector<int>& MapTileBase::GetTextureTileSetsID() const
{
	return this->texture_tile_sets_id;
}

void MapTileBase::SetPause(const bool pause)
{
	//Map Objects
	for (size_t i = 0; i < this->map_objects.size(); i++)
		this->map_objects[i]->SetPause(pause);
}

void MapTileBase::SetGrayScale(const bool gray_scale)
{
	//Background Tile Sets
	for (size_t i = 0; i < this->background_tile_sets.size(); i++)
		this->background_tile_sets[i]->SetGrayScale(gray_scale);

	//Map Objects
	for (size_t i = 0; i < this->map_objects.size(); i++)
		this->map_objects[i]->SetGrayScale(gray_scale);

	//Foreground Tile Sets
	for (size_t i = 0; i < this->foreground_tile_sets.size(); i++)
		this->foreground_tile_sets[i]->SetGrayScale(gray_scale);
}

void MapTileBase::AddTextureTileSetID(const int texture_tile_set_id)
{
	this->texture_tile_sets_id.push_back(texture_tile_set_id);
}

void MapTileBase::Pausing()
{
	GameState::Pausing();
	this->SetPause(true);
	this->SetGrayScale(true);
}

void MapTileBase::Resuming()
{
	GameState::Resuming();
	this->SetPause(false);
	this->SetGrayScale(false);
}

void MapTileBase::Update()
{
	const Timer& timer = GameState::GetGame<Game>().GetTimer();

	//Atualizar os dados dos objetos do mapa
	for (size_t i = 0; i < this->map_objects.size(); i++)
		this->map_objects[i]->Update(timer);

	//Atualizar Background Tile Sets
	for (size_t i = 0; i < this->background_tile_sets.size(); i++)
		this->background_tile_sets[i]->Update(timer,this->camera);

	//Atualizar Foreground Tile Sets
	for (size_t i = 0; i < this->foreground_tile_sets.size(); i++)
		this->foreground_tile_sets[i]->Update(timer,this->camera);
}

void MapTileBase::Show()
{
	Video& video = GameState::GetGame<Game>().GetVideo();
	const Timer& timer = GameState::GetGame<Game>().GetTimer();

	//Mostrar Background Tile Sets
	for (size_t i = 0; i < this->background_tile_sets.size(); i++)
		this->background_tile_sets[i]->Show(video);

	//Mostrar todos os objetos do mapa já ordenados
	MapObject::ShowMapObjectsSorted(video,timer);

	//Mostrar Foreground Tile Sets
	for (size_t i = 0; i < this->foreground_tile_sets.size(); i++)
		this->foreground_tile_sets[i]->Show(video);
}

void MapTileBase::CenterCamera(const Video& video,const MapObject& map_object)
{
	//Dimensão do mapa
	const float map_width = this->tile_total.GetX() * TileSet::GetTileSize();
	const float map_height = this->tile_total.GetY() * TileSet::GetTileSize();

	//Aplicando a câmera
	this->camera.SetX(map_object.GetX() + (map_object.GetW() / 2.0f) - (video.GetVirtualWidth() / 2.0f));
	this->camera.SetY(map_object.GetY() + (map_object.GetH() / 2.0f) - (video.GetVirtualHeight() / 2.0f));

	//Limitando a câmera
	this->camera.SetX(max(min(this->camera.GetX(),map_width - video.GetVirtualWidth()),0.0f));
	this->camera.SetY(max(min(this->camera.GetY(),map_height - video.GetVirtualHeight()),0.0f));
}

void MapTileBase::LoadMapFile(const int map_id)
{
	unique_ptr<char[]> memory_buffer;
	const size_t size = ResourceFile::Read(map_id,memory_buffer);
	if (!size)
		Log::Error(__FUNCTION__,"Read","ID: " + Convert::NumberToString(map_id));

	//Extrair os valores já formatados
	Format::Split(this->map_data_values,memory_buffer.get());
}

void MapTileBase::LoadMapData(const vector<int>& texture_background_tile_sets_id,const vector<int>& texture_foreground_tile_sets_id)
{
	//Total pela largura
	size_t value_index = 0;
	this->tile_total.SetX(Convert::StringToNumber(this->map_data_values[value_index]));
	value_index++;

	//Total pela altura
	this->tile_total.SetY(Convert::StringToNumber(this->map_data_values[value_index]));
	value_index++;

	//Total de Background Tile Sets
	const size_t background_tile_sets_total = Convert::StringToNumber(this->map_data_values[value_index]);
	value_index++;

	//Total de Foreground Tile Sets
	const size_t foreground_tile_sets_total = Convert::StringToNumber(this->map_data_values[value_index]);
	value_index++;

	//Quantidade de Background Tile Sets
	this->background_tile_sets.resize(background_tile_sets_total);

	//Carregar Background Tile Sets
	for (size_t i = 0; i < this->background_tile_sets.size(); i++)
		this->LoadTileSetFromData(this->background_tile_sets,texture_background_tile_sets_id,this->map_data_values,value_index,i);

	//Quantidade de Foreground Tile Sets
	this->foreground_tile_sets.resize(foreground_tile_sets_total);

	//Carregar Foreground Tile Sets
	for (size_t i = 0; i < this->foreground_tile_sets.size(); i++)
		this->LoadTileSetFromData(this->foreground_tile_sets,texture_foreground_tile_sets_id,this->map_data_values,value_index,i);

	//Carregar dados dos Tiles passáveis
	this->LoadSharedTilesFromData(this->map_data_values,value_index);

	//Limpar dados
	this->map_data_values.clear();
}

void MapTileBase::LoadTileSetFromData(vector<unique_ptr<TileSet>>& tile_sets,const vector<int>& texture_tile_sets_id,const vector<string>& values,size_t& value_index,const int tile_set_index)
{
	//Quantidade de Tile Set dinâmico deste Tile Set
	const int dynamic_tile_set_quantity = Convert::StringToNumber(values[value_index]);
	value_index++;

	//Criando o Tile Set
	tile_sets[tile_set_index] = make_unique<TileSet>(GameState::GetGame<Game>().GetVideo(),this->tile_total,texture_tile_sets_id[tile_set_index],dynamic_tile_set_quantity);
	TileSet& current_tile_set = *tile_sets[tile_set_index].get();

	//Índice máximo para acessar os valores para o Tile Set
	size_t current_tile_set_total_index = (this->tile_total.GetX() * this->tile_total.GetY()) + value_index;

	//Índices para acessar os Tiles ID deste Tile Set
	int x = 0;
	int y = 0;

	for (size_t i = value_index; i < current_tile_set_total_index; i++)
	{
		current_tile_set.SetTileID(x,y,Convert::StringToNumber(values[value_index]));
		value_index++;
		x++;

		//Pular para próxima linha
		if (x == this->tile_total.GetX())
		{
			x = 0;
			y++;
		}
	}

	//Construir o Tile Set de uma vez após obter os dados necessários
	current_tile_set.Build();
}

void MapTileBase::LoadSharedTilesFromData(const vector<string>& values,size_t& value_index)
{
	//Carregar Tiles com dados compartilhados
	this->shared_tiles.resize(tile_total.GetX(),vector<SharedTile>(tile_total.GetY()));

	//Índice máximo para acessar os valores para os Tiles passáveis
	size_t current_tile_set_total_index = (this->tile_total.GetX() * this->tile_total.GetY()) + value_index;

	//Índices para acessar os dados de Tile passáveis
	int x = 0;
	int y = 0;

	for (size_t i = value_index; i < current_tile_set_total_index; i++)
	{
		this->shared_tiles[x][y].walkable = ((Convert::StringToNumber(values[value_index])) != 0 ? true : false);
		value_index++;
		x++;

		//Pular para próxima linha
		if (x == this->tile_total.GetX())
		{
			x = 0;
			y++;
		}
	}
}
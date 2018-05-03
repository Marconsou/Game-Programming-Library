#include "MapManager.h"

using namespace std;
using namespace GPL;
using namespace RPG;

MapManager::MapManager() :
	loading_map(nullptr),
	last_music_id(static_cast<FileID>(-1)),
	load_map_file(false),
	load_map_data(false),
	map_loaded(false)
{
	TileSet::SetTileSize(64.0f);
}

bool MapManager::CreateMap(const MapID map_id_to_load,const float hero_position_x,const float hero_position_y)
{
	if (map_id_to_load != NoMapToLoad)
	{
		const GameStateAction game_state_action = this->loading_map ? GameStateAction::DeleteCurrentGameState : GameStateAction::None;
		const HeroMapChangeDirection hero_entering_map_direction = this->loading_map ? this->loading_map->GetHeroEnteringMapDirection() : DirectionRetain;
		const bool hero_teleporting = this->loading_map ?  this->loading_map->GetHeroTeleporting() : false;
		unique_ptr<Map> new_map;

		//Se for deletar o mapa atual então salvar os dados
		if (game_state_action == GameStateAction::DeleteCurrentGameState)
			this->loading_map->SaveMapDataState();

		//MapArea00ID
		if (map_id_to_load == MapArea00ID)
			new_map = make_unique<MapArea00>(hero_position_x,hero_position_y,hero_teleporting,hero_entering_map_direction);

		//MapArea01ID
		else if (map_id_to_load == MapArea01ID)
			new_map = make_unique<MapArea01>(hero_position_x,hero_position_y,hero_teleporting,hero_entering_map_direction);

		//Adicionar mapa no Game States
		this->loading_map = new_map.get();
		GameState::AddGameState(move(new_map),game_state_action);
		this->map_loaded = false;
		return true;
	}
	return false;
}

void MapManager::Update()
{
	//Começar a carregar algo somente com a tela toda escura
	if (GameState::GetGame<GameRPG>().GetScreenEffect().FadeOutEnd())
	{
		//Criar mapa com base no ID
		if (!this->CreateMap(this->loading_map->GetNewMapID(),this->loading_map->GetHeroPositionX(),this->loading_map->GetHeroPositionY()))
		{
			//Se não tiver carregado o mapa todo
			if (!this->map_loaded)
			{
				//Se for diferente significa que deve mudar a música
				if (this->last_music_id != this->loading_map->GetMusicID())
				{
					GameState::GetGame<GameRPG>().GetAudio().PlayMusicFromPlaylist(this->loading_map->GetMusicID(),false);
					this->last_music_id = this->loading_map->GetMusicID();
				}

				//Carregar texturas uma por loop
				if (!this->loading_map->LoadingTextures())
				{
					//Carregar o arquivo com os dados do mapa
					if (!this->load_map_file)
					{
						this->loading_map->LoadingMapFile();
						this->load_map_file = true;
					}
					else
					{
						//Carregar dados do mapa
						if (!this->load_map_data)
						{
							this->loading_map->LoadingMapData();
							this->load_map_data = true;
						}
						else
						{
							//Carregar o restante dos conteúdos do mapa
							this->loading_map->LoadingMapContents();
							this->loading_map->MapLoaded();
							this->load_map_file = false;
							this->load_map_data = false;
							this->map_loaded = true;
						}
					}
				}
			}
		}
	}
}
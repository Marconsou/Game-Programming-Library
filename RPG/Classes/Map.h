#ifndef MAP_H
#define MAP_H

#include "MapTileBase.h"
#include "TeleportMenu.h"
#include "MapMenu.h"
#include "ChestMenu.h"
#include "ShopMenu.h"

namespace RPG
{
	//Direção do herói na mudança de mapa
	enum HeroMapChangeDirection
	{
		DirectionRetain = 0,
		DirectionLeft,
		DirectionRight,
		DirectionUp,
		DirectionDown,
	};

	class Map : public GPL::MapTileBase
	{
	private:
		//ID do texto no nome do mapa
		const LanguageTextID map_name_text_id;

		//ID da música que será tocada durante o mapa
		const FileID music_id;

		//ID do mapa atual
		const MapID current_map_id;

		//ID do novo mapa para ser carregado
		MapID new_map_id;

		//Direção para onde o herói quando entrar no mapa
		HeroMapChangeDirection hero_entering_map_direction;

		//Direção para onde o herói dever ir enquanto estiver deixando o mapa
		HeroMapChangeDirection hero_leaving_map_direction;

		//Herói está andando continuamente sem interagir com nenhum objeto do mapa
		bool hero_walking_click;

		//Herói está se teleportando para outro mapa
		bool hero_teleporting;

		//Último valor armazenado se o herói foi teleportado para verificar no próximo loop se foi modificado
		bool last_hero_teleporting;

		//Mapa todo carregado
		bool map_loaded;

		//Mudando de mapa
		bool changing_map;

		//Map Menu adicionado
		bool map_menu_added;

		//Nova posição X do herói no mapa
		float hero_position_x;

		//Nova posição Y do herói no mapa
		float hero_position_y;

		//Opção selecionada pelo Teleport Menu
		int teleport_selected_area;

		//Quantidade de texturas carregadas
		size_t textures_loaded;

		//Dialogue Box para uso geral inclusive para iniciar uma conversa ao interagir com outros personagens
		GPL::DialogueBox generic_dialogue_box;

		//Atualizar o Pathfind dos personagens com base no mapa
		std::vector<std::shared_ptr<Character>> characters_pathfind_update;

		//Verificar se precisa pular qualquer interação com o Mouse
		bool SkipMouseInteraction() const;

		//Quando deixar o mapa fazer o movimento automático do herói para alguma direção se for necessário
		void LeavingMapAutomaticMovement() const;

		//Fazer o controle do herói como movimentos e ações
		void HeroControl();

		//Adicionar herói já com a posição e direção carregada
		void AddHero();

		//Adicionar o Map Menu dinamicamente de acordo com alguma condição
		void AddMapMenuDynamically();

		//Teleporte do herói
		void HeroTeleportation();

		//Verificar para qual área o herói será teleportado
		bool TeleportAreaSelection();

		//Atualizar as interações dos objetos do mapa
		void MapObjectsInteractionUpdate();

		//Atualizar dados do Pathfind de cada personagem do mapa
		void CharactersPathfindUpdate();

		//Finalizar qualquer interação
		void EndInteraction(const bool hero_unlock_movement);

		//Evento geral das opções do Dialogue Box para On Click
		void GeneralOptionOnClick(const GPL::Control& control);

		//Evento para opção Back
		void BackOptionOnClick(const GPL::Control& control);

		//Evento para inciar uma interação entre os objetos do mapa
		void BeginInteractingObjectsEvent(GPL::MapObject& map_object_base,GPL::MapObject& map_object_interacting);

		//Evento de interação usando Dialogue Box ao fechá-lo
		void DialogueBoxEndInteractingObjectsEvent(const GPL::Control& control);

		//Evento para inciar uma interação com o Save Crystal
		void SaveCrystalInteractionEvent(GPL::MapObject& map_object_base,GPL::MapObject& map_object_interacting);

		//Evento ao escolher a opção de salvar
		void SaveOptionSelectedEvent(const GPL::Control& control,const int option_selected_index);

		//Evento ao escolher a opção de teleportar
		void TeleportOptionSelectedEvent(const GPL::Control& control,const int option_selected_index);

		//Evento abrindo um baú
		void ChestOpeningEvent(GPL::MapObject& map_object);

		//Evento ao abrir um baú
		void ChestOpenedEvent(GPL::MapObject& map_object);

		//Evento ao fechar um baú
		void ChestClosedEvent(GPL::MapObject& map_object);

		//Evento ao entrar em um Gateway
		void EnteringGatewayEvent(GPL::MapObject& map_object_base,GPL::MapObject& map_object_interacting);

		//Evento ao entrar em um Door
		void EnteringDoorEvent(GPL::MapObject& map_object_base,GPL::MapObject& map_object_interacting);

		//Evento quando fechar o Chest Menu
		void CloseChestMenuEvent(const Menu& menu);

		//Evento quando fechar o Shop Menu
		void CloseShopMenuEvent(const Menu& menu);

		//Evento quando fechar o Teleport Menu
		void CloseTeleportMenuEvent(const Menu& menu);

		//Evento ao fechar algum Menu
		void CloseMenuEvent(const Menu& menu);

		//Evento ao mostrar o herói e então mostrar a animação se teleportando
		void HeroTeleportingAnimationOnShow(GPL::MapObject& map_object);

		//Atualizar posição de um personagem
		template<class Type> void CharacterPosition(std::shared_ptr<Type>& character,const float x,const float y,const bool add_action_position_y,const bool tile_size_relative_value)
		{
			//Position
			const float position_x = (tile_size_relative_value) ? (x * TileSet::GetTileSize()) : x;
			const float position_y = (tile_size_relative_value) ? (y * TileSet::GetTileSize()) : y;
			const float action_position_distance_y = (character->GetY() + character->GetH()) - character->GetActionPositionY();
			character->SetPosition(position_x,position_y + ((add_action_position_y) ? action_position_distance_y : 0.0f));

			const int index_x = static_cast<int>(character->GetActionPositionX() / TileSet::GetTileSize());
			const int index_y = static_cast<int>(character->GetActionPositionY() / TileSet::GetTileSize());

			//Node Initial
			character->SetPathfindNodeInitial(index_x,index_y);

			//Node Final
			character->SetPathfindNodeFinal(index_x,index_y);
		}

		//Carregar dados do NPC
		template<class Type> void LoadNPC(std::shared_ptr<Type>& npc,const float x,const float y,const bool tile_size_relative_value)
		{
			MapDataState::MapState& map_state = GameState::GetGame<GameRPG>().GetHero().GetMapDataState().GetMapStates()[this->current_map_id];

			//Se for a primeira vez visitando o mapa
			if (map_state.GetFirstTimeVisiting())
			{
				//Adicionando um NPC para ter os dados salvos depois
				map_state.AddNPCState();

				//Atualizar para posição original
				this->CharacterPosition(npc,x,y,true,tile_size_relative_value);
			}
			else
			{
				//Carregar os dados salvos do NPC
				MapDataState::NPCState& npc_state = map_state.GetNPCState();

				//Atualizar posição posteriormente que foi salvada
				this->CharacterPosition(npc,npc_state.GetX(),npc_state.GetY(),false,false);

				//Alterando dados básicos do NPC
				npc->SetDialogue(npc_state.GetDialogue());
			}
		}

		//Carregar itens do baú
		template<class Type> void LoadChest(Type& chest,const std::vector<ItemID>& items)
		{
			MapDataState::MapState& map_state = GameState::GetGame<GameRPG>().GetHero().GetMapDataState().GetMapStates()[this->current_map_id];

			//Se for a primeira vez carregando o mapa, baús serão carregados como novos mesmo em jogos iguais (Random)
			if (map_state.GetFirstTimeLoading())
			{
				//Adicionando um baú para ter os dados salvos depois
				map_state.AddChestState(items.size());

				//Adicionando os itens
				chest.AddItems(items);
			}
			else
				chest.AddItems(map_state.GetChestState().GetItems());
		}
	protected:
		//Alterar Title Dialogue Box
		void SetTitleDialogueBox(const LanguageTextID text_id,const GPL::Color& color = GPL::Color::Green,const float width = 300.0f);

		//Adicionar texto para o Dialogue Box
		void AddTextDialogueBox(const LanguageTextID text_id,const GPL::Color& color = GPL::Color::White);

		//Adicionar opção para o Dialogue Box
		void AddOptionDialogueBox(const LanguageTextID text_id,const GPL::Color& color = GPL::Color::Gold,const GPL::KeyboardKey keyboard_key_shotcut = {},const bool add_general_on_click_event = true);

		//Atualizar os dados do Dialogue Box
		void DialogueBoxUpdate();

		//Se o objeto do mapa é o herói
		bool IsHeroCharacter(const GPL::MapObject& map_object_interacting);

		//Se o mapa já está carregado
		bool IsMapLoaded() const;

		//Mostrar Shop Menu
		void ShowShopMenu(Shop& shop);

		//Mudar o mapa
		void ChangeMap(const MapID new_map_id,const float hero_position_x,const float hero_position_y,const HeroMapChangeDirection hero_leaving_map_direction = DirectionRetain,const HeroMapChangeDirection hero_entering_map_direction = DirectionRetain);

		//Adicionar evento On Click para uma opção
		template<class Type> void AddOptionEventOnClick(const int index,void (Type::*Event)(const GPL::Control&),Type& type) { this->generic_dialogue_box.AddOptionEventOnClick(index,Event,type); }

		//Adicionar evento On Option Selected para uma opção
		template<class Type> void AddOptionEventOnOptionSelected(const int index,void (Type::*Event)(const GPL::Control&,const int),Type& type) { this->generic_dialogue_box.AddOptionEventOnOptionSelected(index,Event,type); }

		//Adicionar personagem para o mapa
		template<class Type> void AddCharacter(std::shared_ptr<Type>& character,const float x,const float y,const bool tile_size_relative_value = true)
		{
			//Adicionar no mapa este personagem
			this->AddMapObject(character);

			//Lista usada para atualizar o Pathfind dos personagens pelo próprio mapa
			this->characters_pathfind_update.push_back(character);

			//Node Map
			character->CreatePathfindGridNodeMap(this->GetTileTotal().GetX(),this->GetTileTotal().GetY(),TileSet::GetTileSize());

			//Position
			this->CharacterPosition(character,x,y,true,tile_size_relative_value);
		}

		//Criar NPC
		template<class Type,class MapType> void CreateNPC(void (MapType::*OnInteraction)(GPL::MapObject&,GPL::MapObject&),MapType& type,const FileID texture_id,const float x,const float y,const float interaction_area_w = 3.0f,const float interaction_area_h = 3.0f,const bool tile_size_relative_value = true)
		{
			GameRPG& game = GameState::GetGame<GameRPG>();

			//Database para o texto de ação em cima do NPC
			Type::SetDatabase(game.GetDatabase());

			//Criar NPC
			std::shared_ptr<Type> npc = std::make_shared<Type>();

			//Adicionar personagem
			this->AddCharacter(npc,x,y,tile_size_relative_value);

			//Interaction Area
			npc->SetInteractionArea((tile_size_relative_value) ? (interaction_area_w * TileSet::GetTileSize()) : interaction_area_w,(tile_size_relative_value) ? (interaction_area_h * TileSet::GetTileSize()) : interaction_area_h);

			//Eventos
			npc->AddEventOnInteraction(&Map::BeginInteractingObjectsEvent,*this);
			npc->AddEventOnInteraction(OnInteraction,type);

			//Texture
			npc->SetCharacterTexture(game.GetVideo().GetTexture(texture_id));
			npc->SetCharacterShadowTexture(game.GetVideo().GetTexture(TextureCharacterShadowFileID));

			//Carregar dados do NPC
			this->LoadNPC(npc,x,y,tile_size_relative_value);
		}

		//Criar Animated Map Object
		template<class Type> void CreateAnimatedMapObject(const FileID texture_id,const float x,const float y,const float frame_width,const float frame_height,const int frame_quantity,const float interval,const int pixel_gap = 0,const bool tile_size_relative_value = true)
		{
			GameRPG& game = GameState::GetGame<GameRPG>();

			//Criar Animated Map Object
			std::shared_ptr<Type> animated_map_object = std::make_shared<Type>();

			//Alterar principais propriedades
			const float position_x = (tile_size_relative_value) ? (x * TileSet::GetTileSize()) : x;
			const float position_y = (tile_size_relative_value) ? (y * TileSet::GetTileSize()) : y;
			const float width = (tile_size_relative_value) ? (frame_width * TileSet::GetTileSize()) : frame_width;
			const float height = (tile_size_relative_value) ? (frame_height * TileSet::GetTileSize()) : frame_height;
			animated_map_object->SetAnimatedMapObject(game.GetTimer(),game.GetVideo().GetTexture(texture_id),width,height,frame_quantity,interval,pixel_gap);
			animated_map_object->SetPosition(position_x,position_y);

			//Adicionar Animated Map Object no mapa
			this->AddMapObject(animated_map_object);
		}

		//Criar Save Crystal
		template<class Type> void CreateSaveCrystal(const float x,const float y,const bool tile_size_relative_value = true)
		{
			GameRPG& game = GameState::GetGame<GameRPG>();

			//Database para o texto de ação em cima do Save Crystal
			Type::SetDatabase(game.GetDatabase());

			//Criar Save Crystal
			std::shared_ptr<Type> save_crystal = std::make_shared<Type>();

			//Alterar principais propriedades
			const float position_x = (tile_size_relative_value) ? (x * TileSet::GetTileSize()) : x;
			const float position_y = (tile_size_relative_value) ? (y * TileSet::GetTileSize()) : y;
			save_crystal->SetSaveCrystal(game.GetVideo(),game.GetTimer());
			save_crystal->SetPosition(position_x,position_y);

			//Eventos
			save_crystal->AddEventOnInteraction(&Map::BeginInteractingObjectsEvent,*this);
			save_crystal->AddEventOnInteraction(&Map::SaveCrystalInteractionEvent,*this);

			//Tendo o Save Point, deve ter teleporte para este mapa então colocar como desativado inicialmente
			MapDataState::MapState& map_state = GameState::GetGame<GameRPG>().GetHero().GetMapDataState().GetMapStates()[this->current_map_id];
			if (map_state.GetTeleportState() == NoTeleport)
				map_state.SetTeleportState(TeleportDeactivated);

			//Adicionar Save Crystal no mapa
			this->AddMapObject(save_crystal);
		}

		//Criar Chest
		template<class Type> Type& CreateChest(const ChestType chest_type,const float x,const float y,const bool tile_size_relative_value = true)
		{
			GameRPG& game = GameState::GetGame<GameRPG>();

			//Database para o texto de ação em cima do Chest
			Type::SetDatabase(game.GetDatabase());

			//Criar Chest
			std::shared_ptr<Type> chest = std::make_shared<Type>(chest_type);

			//Alterar principais propriedades
			const float position_x = (tile_size_relative_value) ? (x * TileSet::GetTileSize()) : x;
			const float position_y = (tile_size_relative_value) ? (y * TileSet::GetTileSize()) : y;
			chest->SetChest(game.GetVideo());
			chest->SetPosition(position_x,position_y);

			//Eventos
			chest->AddEventOnInteraction(&Map::BeginInteractingObjectsEvent,*this);
			chest->AddEventOnOpening(&Map::ChestOpeningEvent,*this);
			chest->AddEventOnOpened(&Map::ChestOpenedEvent,*this);
			chest->AddEventOnClosed(&Map::ChestClosedEvent,*this);

			//Adicionar Chest no mapa
			this->AddMapObject(chest);
			return *chest.get();
		}

		//Criar Chest
		template<class Type> void CreateChest(const ChestType chest_type,const std::vector<ItemID>& items,const float x,const float y,const bool tile_size_relative_value = true)
		{
			this->LoadChest(this->CreateChest<Type>(chest_type,x,y,tile_size_relative_value),items);
		}

		//Criar Private Chest
		template<class Type> void CreatePrivateChest(const float x,const float y,const bool tile_size_relative_value = true)
		{
			//Criar Chest dados básicos
			Type& private_chest = this->CreateChest<Type>(ChestBlue,x,y,tile_size_relative_value);

			//Atualizando o Private Chest do herói para o baú
			private_chest.SetItems(GameState::GetGame<GameRPG>().GetHero().GetPrivateChest());
		}

		//Criar Gateway
		template<class Type,class MapType> void CreateGateway(void (MapType::*OnEnterInteractionArea)(GPL::MapObject&,GPL::MapObject&),MapType& type,const LanguageTextID new_map_text_id,const float x,const float y,const float w,const float h,const bool tile_size_relative_value = true)
		{
			GameRPG& game = GameState::GetGame<GameRPG>();

			//Database para o texto de ação em cima do Gateway
			Type::SetDatabase(game.GetDatabase());

			//Criar Gateway
			std::shared_ptr<Type> gateway = std::make_shared<Type>(new_map_text_id);

			//Alterar principais propriedades
			const float position_x = (tile_size_relative_value) ? (x * TileSet::GetTileSize()) : x;
			const float position_y = (tile_size_relative_value) ? (y * TileSet::GetTileSize()) : y;
			const float width = (tile_size_relative_value) ? (w * TileSet::GetTileSize()) : w;
			const float height = (tile_size_relative_value) ? (h * TileSet::GetTileSize()) : h;
			gateway->SetGateway(width,height);
			gateway->SetPosition(position_x,position_y);

			//Eventos
			gateway->AddEventOnEnterInteractionArea(&Map::EnteringGatewayEvent,*this);
			gateway->AddEventOnEnterInteractionArea(OnEnterInteractionArea,type);

			//Adicionar Gateway no mapa
			this->AddMapObject(gateway);
		}

		//Criar Door
		template<class Type,typename DoorType,class MapType> void CreateDoor(void (MapType::*OnOpened)(GPL::MapObject&,GPL::MapObject&),MapType& type,const LanguageTextID new_map_text_id,const DoorType door_type,const float x,const float y,const float w,const float h,const bool tile_size_relative_value = true)
		{
			GameRPG& game = GameState::GetGame<GameRPG>();

			//Database para o texto de ação em cima do Door
			Type::SetDatabase(game.GetDatabase());

			//Criar Door
			std::shared_ptr<Type> door = std::make_shared<Type>(new_map_text_id,door_type);

			//Alterar principais propriedades
			const float position_x = (tile_size_relative_value) ? (x * TileSet::GetTileSize()) : x;
			const float position_y = (tile_size_relative_value) ? (y * TileSet::GetTileSize()) : y;
			const float width = (tile_size_relative_value) ? (w * TileSet::GetTileSize()) : w;
			const float height = (tile_size_relative_value) ? (h * TileSet::GetTileSize()) : h;
			door->SetDoor(game.GetVideo().GetTexture(TextureDoor0FileID),width,height);
			door->SetPosition(position_x,position_y);

			//Eventos
			door->AddEventOnEnterInteractionArea(&Map::EnteringDoorEvent,*this);
			door->AddEventOnOpened(OnOpened,type);

			//Adicionar Door no mapa
			this->AddMapObject(door);
		}

		//Criar Static Map Object
		template<class Type> void CreateStaticMapObject(const FileID texture_id,const float x,const float y,const float w,const float h,const float texture_position_x,const float texture_position_y,const bool tile_size_relative_value = true)
		{
			GameRPG& game = GameState::GetGame<GameRPG>();

			//Criar Static Map Object
			std::shared_ptr<Type> static_map_object = std::make_shared<Type>();

			//Alterar principais propriedades
			const float position_x = (tile_size_relative_value) ? (x * TileSet::GetTileSize()) : x;
			const float position_y = (tile_size_relative_value) ? (y * TileSet::GetTileSize()) : y;
			const float width = (tile_size_relative_value) ? (w * TileSet::GetTileSize()) : w;
			const float height = (tile_size_relative_value) ? (h * TileSet::GetTileSize()) : h;
			const float converted_texture_position_x = (tile_size_relative_value) ? (texture_position_x * TileSet::GetTileSize()) : texture_position_x;
			const float converted_texture_position_y = (tile_size_relative_value) ? (texture_position_y * TileSet::GetTileSize()) : texture_position_y;
			static_map_object->SetStaticMapObject(game.GetVideo().GetTexture(texture_id),width,height,converted_texture_position_x,converted_texture_position_y);
			static_map_object->SetPosition(position_x,position_y);

			//Adicionar Static Map Object no mapa
			this->AddMapObject(static_map_object);
		}

		//Salvar dados dos objetos do mapa
		template<class NPCType,class ChestType> void SaveAllMapDataState(const std::vector<const NPCType*>& npcs = std::vector<const NPCType*>(),std::vector<ChestType*>& chests = std::vector<ChestType*>())
		{
			MapDataState::MapState& map_state = GameState::GetGame<GameRPG>().GetHero().GetMapDataState().GetMapStates()[this->current_map_id];

			//NPCs
			for (size_t i = 0; i < npcs.size(); i++)
			{
				//Automaticamente já vai pegar o próximo
				MapDataState::NPCState& npc_state = map_state.GetNPCState();

				const NPCType& iterator = *npcs[i];

				npc_state.SetDialogue(iterator.GetDialogue());
				npc_state.SetX(iterator.GetX());
				npc_state.SetY(iterator.GetY());
			}

			//Chests
			for (size_t i = 0; i < chests.size(); i++)
			{
				//Automaticamente já vai pegar o próximo
				MapDataState::ChestState& chest_state = map_state.GetChestState();

				ChestType& iterator = *chests[i];

				chest_state.SetItems(iterator.GetItems());
			}
		}

		//Pausar todo o conteúdo
		void Pausing() override;

		//Resumir todo o conteúdo pausado
		void Resuming() override;

		//Atualizar dados e a lógica de todo o conteúdo
		void Update() override;

		//Mostrar todo o conteúdo
		void Show() override;
	public:
		//Construtor
		Map(const LanguageTextID map_name_text_id,const FileID music_id,const MapID current_map_id,const float hero_position_x,const float hero_position_y,const bool hero_teleporting,const HeroMapChangeDirection hero_entering_map_direction = DirectionRetain);

		//Destrutor
		virtual ~Map();

		//Pegar Music ID
		FileID GetMusicID() const;

		//Pegar New Map ID
		MapID GetNewMapID() const;

		//Pegar Hero Entering Map Direction
		HeroMapChangeDirection GetHeroEnteringMapDirection() const;

		//Pegar Hero Teleporting
		bool GetHeroTeleporting() const;

		//Pegar Hero Position X
		float GetHeroPositionX() const;

		//Pegar Hero Position Y
		float GetHeroPositionY() const;

		//Mapa carregado e as finalizações do mapa
		void MapLoaded();

		//Carregando as texturas do mapa
		bool LoadingTextures();

		//Carregar o arquivo contendo as informações do mapa
		virtual void LoadingMapFile() = 0;

		//Carregar os dados depois de carregar o arquivo
		virtual void LoadingMapData() = 0;

		//Carregar o restante dos conteúdos do mapa
		virtual void LoadingMapContents() = 0;

		//Salvar os dados do mapa antes de removê-lo
		virtual void SaveMapDataState() = 0;
	};
}

#endif
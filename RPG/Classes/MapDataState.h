#ifndef MAPDATASTATE_H
#define MAPDATASTATE_H

#include <vector>
#include <memory>
#include "Item.h"

namespace RPG
{
	//ID dos mapas
	enum MapID
	{
		NoMapToLoad = -1,
		MapArea00ID,
		MapArea01ID,
		MapMax,
	};

	//Estado de teleporte para o mapa
	enum TeleportState
	{
		NoTeleport = 0,
		TeleportDeactivated,
		TeleportActivated,
	};

	class MapDataState
	{
	public:
		//Estrutura para dados de NPC
		struct NPCState
		{
		private:
			//Diálogo atual da conversa do NPC
			int dialogue;

			//Posição X caso o NPC se move no mapa
			float x;

			//Posição Y caso o NPC se move no mapa
			float y;
		public:
			//Construtor
			NPCState();

			//Alterar Dialogue
			void SetDialogue(const int dialogue);

			//Pegar Dialogue
			int GetDialogue() const;

			//Alterar X
			void SetX(const float x);

			//Pegar X
			float GetX() const;

			//Alterar Y
			void SetY(const float y);

			//Pegar Y
			float GetY() const;
		};

		//Estrutura para dados de baú
		struct ChestState
		{
		private:
			//Itens do baú
			std::vector<std::unique_ptr<Item>> items;
		public:
			//Construtor
			ChestState(const size_t items_size = 0);

			//Alterar Items
			void SetItems(const std::vector<std::unique_ptr<Item>>& items);

			//Pegar Items
			std::vector<std::unique_ptr<Item>>& GetItems();
		};

		//Estrutura para os dados do mapa
		struct MapState
		{
		private:
			//Mapa visitado pelo menos uma vez desde sempre, uma vez visitado sempre visitado
			bool visited;

			//PRimeira vez visitando o mapa
			bool first_time_visiting;

			//Mapa carregado durante o jogo atual
			bool loaded;

			//Primeira vez carregando o mapa durante o jogo
			bool first_time_loading;

			//Índice para acessar os dados de um NPC
			int npc_index;

			//Índice para acessar os dados de um baú
			int chest_index;

			//Estado de teleporte do mapa
			TeleportState teleport_state;

			//Dados dos NPCs
			std::vector<NPCState> npc_states;

			//Dados dos báus
			std::vector<std::unique_ptr<ChestState>> chest_states;
		public:
			//Construtor
			MapState();

			//Pegar Visited
			bool GetVisited() const;

			//Pegar First Time Visiting
			bool GetFirstTimeVisiting() const;

			//Pegar First Time Loading
			bool GetFirstTimeLoading() const;

			//Alterar Teleport State
			void SetTeleportState(const TeleportState teleport_state);

			//Pegar Teleport State
			TeleportState GetTeleportState() const;

			//Pegar NPC State
			NPCState& GetNPCState();

			//Pegar Chest State
			ChestState& GetChestState();

			//Adicionar NPC State
			void AddNPCState();

			//Adicionar Chest State
			void AddChestState(const size_t items_size);

			//Mapa visitado e carregado pelo menos uma vez durante o jogo
			void VisitingMap();

			//Resetar os valores de índices para acessar os principais objetos
			void ResetIndices();
		};
	private:
		//Dados de cada mapa
		std::vector<MapState> map_states;
	public:
		//Construtor
		MapDataState();

		//Pegar Map States
		std::vector<MapState>& GetMapStates();
	};
}

#endif
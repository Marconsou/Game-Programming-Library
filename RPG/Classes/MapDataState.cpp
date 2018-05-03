#include "MapDataState.h"

using namespace std;
using namespace RPG;

MapDataState::NPCState::NPCState() :
	dialogue(0),
	x(0.0f),
	y(0.0f) 
{

}

void MapDataState::NPCState::SetDialogue(const int dialogue)
{
	this->dialogue = dialogue;
}

int MapDataState::NPCState::GetDialogue() const
{
	return this->dialogue;
}

void MapDataState::NPCState::SetX(const float x)
{
	this->x = x;
}

float MapDataState::NPCState::GetX() const
{
	return this->x;
}

void MapDataState::NPCState::SetY(const float y)
{
	this->y = y;
}

float MapDataState::NPCState::GetY() const
{
	return this->y;
}

MapDataState::ChestState::ChestState(const size_t items_size) :
	items(items_size)
{
	for (size_t i = 0; i < this->items.size(); i++)
		this->items[i] = make_unique<Item>();
}

void MapDataState::ChestState::SetItems(const vector<unique_ptr<Item>>& items)
{
	//Copiando os itens
	for (size_t i = 0; i < items.size(); i++)
		this->items[i]->Copy(*items[i].get());
}

vector<unique_ptr<Item>>& MapDataState::ChestState::GetItems()
{
	return this->items;
}

MapDataState::MapState::MapState() :
	visited(false),
	first_time_visiting(false),
	loaded(false),
	first_time_loading(false),
	npc_index(0),
	chest_index(0),
	teleport_state(NoTeleport)
{

}

bool MapDataState::MapState::GetVisited() const
{
	return this->visited;
}

bool MapDataState::MapState::GetFirstTimeVisiting() const
{
	return this->first_time_visiting;
}

bool MapDataState::MapState::GetFirstTimeLoading() const
{
	return this->first_time_loading;
}

void MapDataState::MapState::SetTeleportState(const TeleportState teleport_state)
{
	this->teleport_state = teleport_state;
}

TeleportState MapDataState::MapState::GetTeleportState() const
{
	return this->teleport_state;
}

MapDataState::NPCState& MapDataState::MapState::GetNPCState()
{
	NPCState& npc_state = this->npc_states[this->npc_index];
	this->npc_index++;
	return npc_state;
}

MapDataState::ChestState& MapDataState::MapState::GetChestState()
{
	ChestState& chest_state = *this->chest_states[this->chest_index];
	this->chest_index++;
	return chest_state;
}

void MapDataState::MapState::AddNPCState()
{
	this->npc_states.push_back(NPCState());
}

void MapDataState::MapState::AddChestState(const size_t items_size)
{
	this->chest_states.push_back(make_unique<ChestState>(items_size));
}

void MapDataState::MapState::VisitingMap()
{
	this->first_time_visiting = !this->visited;
	this->visited = true;
	this->first_time_loading = !this->loaded;
	this->loaded = true;
	this->ResetIndices();
}

void MapDataState::MapState::ResetIndices()
{
	this->npc_index = 0;
	this->chest_index = 0;
}

MapDataState::MapDataState() :
	map_states(MapMax)
{

}

vector<MapDataState::MapState>& MapDataState::GetMapStates()
{
	return this->map_states;
}
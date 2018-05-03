#include "MapArea01.h"

using namespace std;
using namespace GPL;
using namespace RPG;

MapArea01::MapArea01(const float hero_position_x,const float hero_position_y,const bool hero_teleporting,const HeroMapChangeDirection hero_entering_map_direction) :
	Map(MapArea01TextID,MusicMusic01FileID,MapArea01ID,hero_position_x,hero_position_y,hero_teleporting,hero_entering_map_direction),
	item_shop(ItemShopTextID)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	this->AddTextureTileSetID(TextureBackground01FileID);
	this->AddTextureTileSetID(TextureForeground00FileID);
	this->AddTextureTileSetID(TextureCivilian01FileID);
}

void MapArea01::LoadingMapFile()
{
	this->LoadMapFile(MapArea01FileID);
}

void MapArea01::LoadingMapData()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	vector<int> texture_background_tile_sets_id;
	texture_background_tile_sets_id.push_back(this->GetTextureTileSetsID()[0]);
	texture_background_tile_sets_id.push_back(this->GetTextureTileSetsID()[1]);

	vector<int> texture_foreground_tile_sets_id;
	texture_foreground_tile_sets_id.push_back(this->GetTextureTileSetsID()[1]);
	this->LoadMapData(texture_background_tile_sets_id,texture_foreground_tile_sets_id);
}

void MapArea01::LoadingMapContents()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Save Crystal
	this->CreateSaveCrystal<SaveCrystal>(7,6);

	//NPC
	this->CreateNPC<NPC>(&MapArea01::TalkWithNPC0Event,*this,TextureCivilian01FileID,9,4,1,4);

	//Item Shop
	for (int i = PhysicalRecoveryLevel1; i < PhysicalRecoveryLevel1 + 10; i++)
		this->item_shop.AddItem(game.GetDatabase().GetItems(static_cast<ItemID>(i)));
	this->item_shop.AddItem(game.GetDatabase().GetItems(ShortSword));
	this->item_shop.AddItem(game.GetDatabase().GetItems(BroadSword));
	this->item_shop.AddItem(game.GetDatabase().GetItems(LongSword));
	this->item_shop.AddItem(game.GetDatabase().GetItems(Cloth));

	//Gateway
	this->CreateGateway<Gateway>(&MapArea01::GatewayEvent,*this,MapArea00TextID,9,9,1,1);

	//Static Map Object
	this->CreateStaticMapObject<StaticMapObject>(TextureForeground00FileID,8,5,3,2,10,0);
}

void MapArea01::Update()
{
	if (this->IsMapLoaded())
	{
		Map::Update();
	}
}

void MapArea01::Show()
{
	if (this->IsMapLoaded())
	{
		GameRPG& game = GameState::GetGame<GameRPG>();

		Map::Show();

		
		//NPC& object = static_cast<NPC&>(*this->GetMapObjects()[2].get());
		//Gateway& object = static_cast<Gateway&>(*this->GetMapObjects()[7].get());
		//Chest& object = static_cast<Chest&>(*this->GetMapObjects()[4].get());
		/*
		static Sprite s;
		s.SetPosition(object.GetInteractionArea().GetPosition().GetX() - this->GetCamera().GetX(),object.GetInteractionArea().GetPosition().GetY() - this->GetCamera().GetY());
		s.SetSize(object.GetInteractionArea().GetSize().GetX(),object.GetInteractionArea().GetSize().GetY());
		s.Show(game.GetVideo());
		*/
	}
}

void MapArea01::SaveMapDataState()
{
	//NPCs
	std::vector<const NPC*> npcs;
	npcs.push_back(static_cast<NPC*>(this->GetMapObjects()[1].get()));

	//Salvar dados
	this->SaveAllMapDataState<NPC,Chest>(npcs);
}

void MapArea01::TalkWithNPC0Event(MapObject& map_object_base,MapObject& map_object_interacting)
{
	this->SetTitleDialogueBox(MapArea01NPC0NameTextID);
	this->AddTextDialogueBox(MapArea01NPC0Dialogue0Text0TextID);
	this->AddOptionDialogueBox(MapArea01NPC0Dialogue0Option0TextID);
	this->AddOptionDialogueBox(MapArea01NPC0Dialogue0Option1TextID);

	this->AddOptionEventOnOptionSelected(0,&MapArea01::NPC0Dialogue0Option0Event,*this);

	this->DialogueBoxUpdate();
}

void MapArea01::NPC0Dialogue0Option0Event(const Control& control,const int option_selected_index)
{
	this->ShowShopMenu(this->item_shop);
}

void MapArea01::GatewayEvent(MapObject& map_object_base,MapObject& map_object_interacting)
{
	if (this->IsHeroCharacter(map_object_interacting))
		this->ChangeMap(MapArea00ID,5,8);
}
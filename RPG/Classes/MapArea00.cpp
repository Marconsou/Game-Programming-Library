#include "MapArea00.h"

using namespace std;
using namespace GPL;
using namespace RPG;

Sprite s1,s2,sp;
View v;
float vx = 1.0f;
float vy = 1.0f;

MapArea00::MapArea00(const float hero_position_x,const float hero_position_y,const bool hero_teleporting,const HeroMapChangeDirection hero_entering_map_direction) :
	Map(MapArea00TextID,MusicMusic00FileID,MapArea00ID,hero_position_x,hero_position_y,hero_teleporting,hero_entering_map_direction)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	this->AddTextureTileSetID(TextureBackground00FileID);
	this->AddTextureTileSetID(TextureBackground01FileID);
	this->AddTextureTileSetID(TextureBackground02FileID);
	this->AddTextureTileSetID(TextureBackground03FileID);
	this->AddTextureTileSetID(TextureBackground04FileID);
	this->AddTextureTileSetID(TextureBackground05FileID);
	this->AddTextureTileSetID(TextureForeground00FileID);
	this->AddTextureTileSetID(TextureDoor0FileID);
	this->AddTextureTileSetID(TextureFountain0FileID);
	this->AddTextureTileSetID(TextureCivilian00FileID);
	this->AddTextureTileSetID(TextureCivilian01FileID);

	static bool a = false;

	if (!a)
	{
		/*v.GetViewport().SetSize(vx,vy);
		s1.SetView(v);
		sp.SetView(v);*/

		

		game.GetVideo().CreateRenderTarget(128,128);
		game.GetVideo().RemoveRenderTarget(0);
		game.GetVideo().CreateRenderTarget(64,64);
		a = true;
	}

	s1.SetTexture(game.GetVideo().GetTexture(TextureCommonFileID));
	//s1.SetPosition(0.0f,0.0f);
	s1.SetSize(32.0f,32.0f);
	s1.SetTexturePosition(0.0f,66.0f);
	s1.SetScaleX(800.0f / 64.0f);
	s1.SetScaleY(600.0f / 64.0f);
	s1.SetRenderTarget(game.GetVideo().GetLastRenderTarget());

	s2.SetTexture(game.GetVideo().GetTexture(TextureCommonFileID));
	s2.SetPosition(800.0f / 64.0f * 32.0f,600.0f / 64.0f * 32.0f);
	s2.SetSize(32.0f,32.0f);
	s2.SetTexturePosition(0.0f,99.0f);

	s2.SetScaleX(800.0f / 64.0f);
	s2.SetScaleY(600.0f / 64.0f);

	s2.SetRenderTarget(s1.GetRenderTarget());

	sp.SetTexture(game.GetVideo().GetLastRenderTarget().GetTexture());
	sp.SetSize((float)s1.GetRenderTarget().GetWidth(),(float)s1.GetRenderTarget().GetHeight());

	//sp.SetScaleX(800.0f / 1024.0f);
	//sp.SetScaleY(600.0f / 1024.0f);
}

void MapArea00::LoadingMapFile()
{
	this->LoadMapFile(MapArea00FileID);
}

void MapArea00::LoadingMapData()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	vector<int> texture_background_tile_sets_id;
	texture_background_tile_sets_id.push_back(this->GetTextureTileSetsID()[2]);
	texture_background_tile_sets_id.push_back(this->GetTextureTileSetsID()[6]);

	vector<int> texture_foreground_tile_sets_id;
	texture_foreground_tile_sets_id.push_back(this->GetTextureTileSetsID()[6]);
	this->LoadMapData(texture_background_tile_sets_id,texture_foreground_tile_sets_id);
}

void MapArea00::LoadingMapContents()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Save Crystal
	this->CreateSaveCrystal<SaveCrystal>(10,6);

	//NPC
	this->CreateNPC<NPC>(&MapArea00::TalkWithNPC0Event,*this,TextureCivilian00FileID,7,9);

	//Animated Map Object
	this->CreateAnimatedMapObject<AnimatedMapObject>(TextureFountain0FileID,10,8,3,3,4,0.125f);

	//Private Chest
	this->CreatePrivateChest<PrivateChest>(12,2);

	//Chest
	std::vector<ItemID> chest_items;
	chest_items.push_back(ShortSword);
	chest_items.push_back(PhysicalRecoveryLevel1);
	chest_items.push_back(BroadSword);
	this->CreateChest<Chest>(ChestSmall,chest_items,9,2);

	//Gateway
	this->CreateGateway<Gateway>(&MapArea00::GatewayEvent,*this,MapArea00TextID,0,11,1,3);

	//Door
	this->CreateDoor<Door>(&MapArea00::DoorEvent,*this,MapArea01TextID,DoorSingleWoodDarkWindowed,5,7,1,2);

	//Static Map Object
	this->CreateStaticMapObject<StaticMapObject>(TextureForeground00FileID,5,6,1,1,10,4);
}

void MapArea00::Update()
{
	if (this->IsMapLoaded())
	{
		GameRPG& game = GameState::GetGame<GameRPG>();


		Map::Update();

		NPC& npc = static_cast<NPC&>(*this->GetMapObjects()[1].get());
		static bool change = false;
		static Interval ti(3.0f);
		if (ti.Action(game.GetTimer()))
		{
			npc.SetPathfindNodeFinal(1,1);

			change = !change;
			if (change)
				npc.SetPathfindNodeFinal(11,3);
			else
				npc.SetPathfindNodeFinal(5,11);

			npc.FindPath();
		}
		
		/*vx = game.GetInput().GetMouseX() / 800.0f;
		vy = game.GetInput().GetMouseY() / 600.0f;*/


		//sp.SetPixelateGridSize(static_cast<float>(game.GetInput().GetMouseX()) / static_cast<float>(sp.GetTexture().GetWidth()));

		//game.GetApplication().SetTitle(Convert::NumberToString(vx) + "x" + Convert::NumberToString(vy));

		//v.GetViewport().SetSize(vx,vy);
	}
}

void MapArea00::Show()
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

		//sp.SetSize(game.GetInput().GetMouseX(),game.GetInput().GetMouseY());


		s1.Show(game.GetVideo());
		s2.Show(game.GetVideo());

		sp.Show(game.GetVideo());

		//sp.SetPixelateGridSize((float)game.GetInput().GetMouseX());
	}
}

void MapArea00::SaveMapDataState()
{
	//NPCs
	std::vector<const NPC*> npcs;
	npcs.push_back(static_cast<NPC*>(this->GetMapObjects()[1].get()));

	//Chests
	std::vector<Chest*> chests;
	chests.push_back(static_cast<Chest*>(this->GetMapObjects()[4].get()));

	//Salvar dados
	this->SaveAllMapDataState(npcs,chests);
}

void MapArea00::TalkWithNPC0Event(MapObject& map_object_base,MapObject& map_object_interacting)
{
	const NPC& npc = static_cast<NPC&>(map_object_base);

	this->SetTitleDialogueBox(MapArea00NPC0NameTextID);

	if (npc.GetDialogue() == 0)
	{
		this->AddTextDialogueBox(MapArea00NPC0Dialogue0Text0TextID);
		this->AddTextDialogueBox(MainQuestName0TextID,Color::Green);
		this->AddTextDialogueBox(MapArea00NPC0Dialogue0Text2TextID);

		this->AddOptionDialogueBox(MapArea00NPC0Dialogue0Option0TextID);
		this->AddOptionDialogueBox(MapArea00NPC0Dialogue0Option1TextID);

		this->AddOptionEventOnOptionSelected(0,&MapArea00::NPC0Dialogue0Option0Event,*this);
	}
	else if (npc.GetDialogue() == 1)
	{
		this->AddTextDialogueBox(MapArea00NPC0Dialogue0Text1TextID);
		this->AddTextDialogueBox(MainQuestName0TextID,Color::Green);
		this->AddTextDialogueBox(MapArea00NPC0Dialogue0Text2TextID);

		this->AddOptionDialogueBox(MapArea00NPC0Dialogue0Option0TextID);
		this->AddOptionDialogueBox(MapArea00NPC0Dialogue0Option1TextID);

		this->AddOptionEventOnOptionSelected(0,&MapArea00::NPC0Dialogue1Option0Event,*this);
	}

	this->DialogueBoxUpdate();
}

void MapArea00::NPC0Dialogue0Option0Event(const Control& control,const int option_selected_index)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	game.GetHero().GetMainQuests()[MainQuest0].SetQuestState(QuestStateStarted);
	game.GetAudio().PlaySoundFromBuffer(SoundQuestStartedFileID);
	game.NewMessageLogText(game.GetDatabase().GetLanguageText(QuestStartedTextID));
	game.AddMessageLogText(game.GetDatabase().GetLanguageText(MainQuestName0TextID),Color::Yellow);

	static_cast<NPC&>(*this->GetMapObjects()[1].get()).NextDialogue();
}

void MapArea00::NPC0Dialogue1Option0Event(const Control& control,const int option_selected_index)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	if (!game.GetHero().GetMainQuests()[MainQuest0].IsCompleted())
	{
		game.GetHero().GetMainQuests()[MainQuest0].SetQuestState(QuestStateCompleted);
		game.GetAudio().PlaySoundFromBuffer(SoundQuestCompletedFileID);
		game.NewMessageLogText(game.GetDatabase().GetLanguageText(QuestCompletedTextID));
		game.AddMessageLogText(game.GetDatabase().GetLanguageText(MainQuestName0TextID),Color::Yellow);
	}
}

void MapArea00::GatewayEvent(MapObject& map_object_base,MapObject& map_object_interacting)
{
	if (this->IsHeroCharacter(map_object_interacting))
		this->ChangeMap(MapArea00ID,1,1,DirectionLeft,DirectionDown);
}

void MapArea00::DoorEvent(MapObject& map_object_base,MapObject& map_object_interacting)
{
	if (this->IsHeroCharacter(map_object_interacting))
		this->ChangeMap(MapArea01ID,9,7,DirectionRetain,DirectionUp);
}
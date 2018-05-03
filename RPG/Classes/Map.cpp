#include "Map.h"

using namespace std;
using namespace GPL;
using namespace RPG;

Map::Map(const LanguageTextID map_name_text_id,const FileID music_id,const MapID current_map_id,const float hero_position_x,const float hero_position_y,const bool hero_teleporting,const HeroMapChangeDirection hero_entering_map_direction) :
	map_name_text_id(map_name_text_id),
	music_id(music_id),
	current_map_id(current_map_id),
	new_map_id(NoMapToLoad),
	hero_entering_map_direction(hero_entering_map_direction),
	hero_leaving_map_direction(DirectionRetain),
	hero_walking_click(false),
	hero_teleporting(hero_teleporting),
	last_hero_teleporting(false),
	map_loaded(false),
	changing_map(false),
	map_menu_added(false),
	hero_position_x(hero_position_x),
	hero_position_y(hero_position_y),
	teleport_selected_area(-1),
	textures_loaded(0)
{
	GameState::GetGame<GameRPG>().GetHero().GetMapDataState().GetMapStates()[this->current_map_id].VisitingMap();
	this->generic_dialogue_box.AddEventOnRemove(&Map::DialogueBoxEndInteractingObjectsEvent,*this);
}

Map::~Map()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//No Pause Menu quando sai do jogo o herói é deletado e depois o Mapa é deletado então deve verificar aqui
	if (game.HeroCreated())
		game.GetHero().GetCharacter()->RemoveAllEventsOnShow();
}

FileID Map::GetMusicID() const
{
	return this->music_id;
}

MapID Map::GetNewMapID() const
{
	return this->new_map_id;
}

HeroMapChangeDirection Map::GetHeroEnteringMapDirection() const
{
	return this->hero_entering_map_direction;
}

bool Map::GetHeroTeleporting() const
{
	return this->hero_teleporting;
}

float Map::GetHeroPositionX() const
{
	return this->hero_position_x;
}

float Map::GetHeroPositionY() const
{
	return this->hero_position_y;
}

void Map::SetTitleDialogueBox(const LanguageTextID text_id,const Color& color,const float width)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	const float space = 10.0f;
	this->generic_dialogue_box.SetDialogueBox(game.GetVideo().GetFont(FontQlassikBoldMediumFileID),3,width,space,space,game.GetTextSpeedInterval(),game.GetDatabase().GetLanguageText(text_id),color);
}

void Map::AddTextDialogueBox(const LanguageTextID text_id,const Color& color)
{
	this->generic_dialogue_box.AddText(GameState::GetGame<GameRPG>().GetDatabase().GetLanguageText(text_id),color);
}

void Map::AddOptionDialogueBox(const LanguageTextID text_id,const Color& color,const KeyboardKey keyboard_key_shotcut,const bool add_general_on_click_event)
{
	const int index = this->generic_dialogue_box.GetOptionsTotal();

	//Option Text
	this->generic_dialogue_box.AddOption(GameState::GetGame<GameRPG>().GetDatabase().GetLanguageText(text_id),color,10.0f);

	//Event
	if (add_general_on_click_event)
		this->generic_dialogue_box.AddOptionEventOnClick(index,&Map::GeneralOptionOnClick,*this);

	//Tecla de atalho quando precisar
	if (!Input::IsKeyboardKeyUnknown(keyboard_key_shotcut))
		this->generic_dialogue_box.AddOptionKeyShortcut(index,keyboard_key_shotcut);
}

void Map::DialogueBoxUpdate()
{
	//Adicionar e atualizar Dialogue Box
	this->generic_dialogue_box.AddControl();
	GameState::GetGame<GameRPG>().SetDialogueBox(this->generic_dialogue_box);
}

bool Map::SkipMouseInteraction() const
{
	return (((MapObject::GetMapObjectInteracted()) || (Control::AnyControlMouseHovered()) || GameState::GetGame<GameRPG>().GetHero().GetCharacter()->IsMovementLocked()) || (this->changing_map) || (this->hero_teleporting));
}

void Map::Pausing()
{
	MapTileBase::Pausing();
	GameState::GetGame<GameRPG>().SetShowMessageLog(false);
}

void Map::Resuming()
{
	MapTileBase::Resuming();
	GameState::GetGame<GameRPG>().SetShowMessageLog(true);
}

void Map::Update()
{
	//Só se já carregou o mapa completamente pelo Map Manager
	if (this->map_loaded)
	{
		GameRPG& game = GameState::GetGame<GameRPG>();

		//Quando deixar o mapa fazer o movimento automático do herói para alguma direção se for necessário
		this->LeavingMapAutomaticMovement();

		//Processar e verificar por eventos dos objetos do mapa
		MapObject::ProcessEvents(game.GetInput(),game.GetTimer(),this->SkipMouseInteraction());

		//Fazer o controle do herói como movimentos e ações
		this->HeroControl();

		//Atualizar a câmera sobre o mapa e centralizando no herói
		this->CenterCamera(game.GetVideo(),*game.GetHero().GetCharacter().get());

		//Atualizar os Tile Sets e os objetos do mapa
		MapTileBase::Update();

		//Estado do movimento do herói
		game.GetHero().HeroMovementStatsUpdate();

		//Adicionar o Map Menu dinamicamente de acordo com alguma condição
		this->AddMapMenuDynamically();

		//Teleporte do herói
		this->HeroTeleportation();

		//Atualizando a posição do Generic Dialogue Box com base na posição do herói e fazer com que não fique por cima dele
		const float value = (game.GetVideo().GetVirtualHeight() / 4.0f);
		const float position = (game.GetHero().GetCharacter()->GetActionPositionY() - this->GetCamera().GetY() < (game.GetVideo().GetVirtualHeight() / 2.0f)) ? value : - value;
		this->generic_dialogue_box.SetPosition((game.GetVideo().GetVirtualWidth() / 2.0f),(game.GetVideo().GetVirtualHeight() / 2.0f) + position,true);

		//Mostrar Message Log quando possível
		game.SetShowMessageLog((!game.GetHero().GetCharacter()->IsMovementLocked()));
	}
}

void Map::Show()
{
	//Só se já carregou o mapa completamente pelo Map Manager
	if (this->map_loaded)
	{
		GameRPG& game = GameState::GetGame<GameRPG>();

		//Mostrar os Tile Sets e os objetos do mapa
		MapTileBase::Show();

		//Mostrar algum texto de ação de interação de algum objeto do mapa quando necessário
		if ((!this->hero_walking_click) && (!this->GetPause()) && (!this->changing_map) && (!this->hero_teleporting))
			MapObject::ShowMapObjectActionToolTip(game.GetVideo());
	}
}

void Map::LeavingMapAutomaticMovement() const
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Se estiver mudando de mapa pois está saindo
	if (this->changing_map)
	{
		//Desabilitar para não ter conflito com o movimento e câmera
		game.GetHero().GetCharacter()->DisablePathfind();

		//Left
		if (this->hero_leaving_map_direction == DirectionLeft)
			game.GetHero().GetCharacter()->MoveLeft();

		//Right
		else if (this->hero_leaving_map_direction == DirectionRight)
			game.GetHero().GetCharacter()->MoveRight();

		//Up
		else if (this->hero_leaving_map_direction == DirectionUp)
			game.GetHero().GetCharacter()->MoveUp();

		//Down
		else if (this->hero_leaving_map_direction == DirectionDown)
			game.GetHero().GetCharacter()->MoveDown();
	}

	//Mapa rodando normalmente então manter o habilitado
	else
		game.GetHero().GetCharacter()->EnablePathfind();
}

void Map::HeroControl()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Se o herói não estiver travado para se mover e interagir ou alguma interação já estiver ocorrendo
	Character& character = *game.GetHero().GetCharacter().get();
	if (!this->SkipMouseInteraction())
	{
		//Se clicou com o Mouse 
		if (game.GetInput().IsMouseButtonPressed(MouseButton::Left))
		{
			//Se não tive foco em algum objeto do mapa
			if (!MapObject::GetMapObjectFocused())
			{
				//Fazer o personagem somente andar
				this->hero_walking_click = true;
			}
		}
		else
		{
			//Dar a chance para clicar em algum objeto do mapa
			this->hero_walking_click = false;
		}

		//Posição final para onde o herói vai se movimentar e se vai precisar atualizar o Pathfind
		int node_final_x = -1;
		int node_final_y = -1;

		//Fazer o personagem andar continuamente até a posição do Mouse enquano estiver segurando o botão do Mouse 
		if (this->hero_walking_click)
		{
			//Posição do Mouse convertida em índice no mapa
			node_final_x = static_cast<int>((game.GetInput().GetMouseX() + this->GetCamera().GetX()) / TileSet::GetTileSize());
			node_final_y = static_cast<int>((game.GetInput().GetMouseY() + this->GetCamera().GetY()) / TileSet::GetTileSize());
		}

		//Se tiver objeto com o foco, fazer o herói andar até ele
		if (MapObject::GetMapObjectFocused())
		{
			//Posição de ação do objeto do mapa com o foco convertida em índice no mapa
			const int move_to_index_x = static_cast<int>(MapObject::GetMapObjectFocused()->GetMoveToPositionX(character) / TileSet::GetTileSize());
			const int move_to_index_y = static_cast<int>(MapObject::GetMapObjectFocused()->GetMoveToPositionY(character) / TileSet::GetTileSize());

			//Posição de ação do herói convertida em índice no mapa
			const int character_index_x = static_cast<int>(character.GetActionPositionX() / TileSet::GetTileSize());
			const int character_index_y = static_cast<int>(character.GetActionPositionY() / TileSet::GetTileSize());

			//Se o herói ainda não estiver na posição para se mover do objeto do mapa então atualizar a posição para onde ele deve ir
			if ((character_index_x != move_to_index_x) || (character_index_y != move_to_index_y))
			{
				node_final_x = move_to_index_x;
				node_final_y = move_to_index_y;
			}
		}

		//Atualizar o Node final quando necessário
		if ((node_final_x != -1) && (node_final_y != -1))
		{
			//Para onde deve ir
			character.SetPathfindNodeFinal(node_final_x,node_final_y);

			//Atualizando a câmera do Pathfind para aumentar o desempenho para não verificar todo o mapa
			const int camera_index_x = static_cast<int>(this->GetCamera().GetX() / TileSet::GetTileSize());
			const int camera_index_y = static_cast<int>(this->GetCamera().GetY() / TileSet::GetTileSize());
			const int camera_index_w = camera_index_x + min(this->GetTileTotal().GetX(),static_cast<int>(game.GetVideo().GetVirtualWidth() / TileSet::GetTileSize()));
			const int camera_index_h = camera_index_y + min(this->GetTileTotal().GetY(),static_cast<int>(game.GetVideo().GetVirtualHeight() / TileSet::GetTileSize()));
			character.SetPathfindCameraIndex(camera_index_x,camera_index_y,camera_index_w,camera_index_h);

			//Encontrar o caminho
			character.FindPath();
		}
	}
}

void Map::AddHero()
{
	shared_ptr<Character>& character = GameState::GetGame<GameRPG>().GetHero().GetCharacter();

	//Character
	this->AddCharacter(character,this->hero_position_x,this->hero_position_y);

	//Deve ser adicionado toda vez para um novo mapa e o evento será removido no próprio destrutor do mapa, para evitar de ser chamado incorretamente com o mapa já destruído
	character->AddEventOnShow(&Map::HeroTeleportingAnimationOnShow,*this);

	//Left
	if (this->hero_entering_map_direction == DirectionLeft)
		character->TurnLeft();

	//Right
	else if (this->hero_entering_map_direction == DirectionRight)
		character->TurnRight();

	//Up
	else if (this->hero_entering_map_direction == DirectionUp)
		character->TurnUp();

	//Down
	else if (this->hero_entering_map_direction == DirectionDown)
		character->TurnDown();

	//Se o herói não estiver teleportando então habilita os movimentos
	if (!this->hero_teleporting)
		character->UnlockMovement();
}

void Map::AddMapMenuDynamically()
{
	//Adicionar o Map Menu assim que o herói ficar desbloqueado com os movimentos
	if (!GameState::GetGame<GameRPG>().GetHero().GetCharacter()->IsMovementLocked())
	{
		if (!this->map_menu_added)
		{
			this->AddSubGameState(make_unique<MapMenu>(this->map_name_text_id));
			this->map_menu_added = true;
		}
	}
	else
	{
		if (this->map_menu_added)
		{
			this->RemoveSubGameStates();
			this->map_menu_added = false;
		}
	}
}

void Map::HeroTeleportation()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Só começar quando a tela estiver toda clara
	if (game.GetScreenEffect().FadeInEnd())
	{
		Character& character = *game.GetHero().GetCharacter().get();
		AnimationFrame& teleporting_animation = game.GetAnimations()[HeroTeleporting];

		//Personagem fica invisível quando estiver no processo de teleporte
		character.SetShow(!this->hero_teleporting);

		//Se houve modificação no processo de teleporte do herói em relação ao último loop
		if (this->last_hero_teleporting != this->hero_teleporting)
		{
			teleporting_animation.Play(game.GetTimer(),teleporting_animation.IsAtTheBeginning());
			game.GetAudio().PlaySoundFromBuffer(SoundTeleportFileID);
		}

		//Teleportando
		if (this->hero_teleporting)
		{
			//Bloquando os movimentos do herói durante o teleporte
			character.LockMovement();

			//Animação do teleporte acabou
			if (!teleporting_animation.IsPlaying())
			{
				//Se não carregou nenhum mapa novo significa que o teleporte esta sendo feito durante a inicialização do mapa
				if (!this->TeleportAreaSelection())
				{
					character.UnlockMovement();
					this->hero_teleporting = false;
				}
			}
		}

		//Salvar último valor para o próximo loop
		this->last_hero_teleporting = this->hero_teleporting;
	}
}

bool Map::TeleportAreaSelection()
{
	//MapArea00ID
	if (this->teleport_selected_area == MapArea00ID)
		this->ChangeMap(MapArea00ID,8,8,DirectionRetain,DirectionDown);

	 //MapArea01ID
	else if (this->teleport_selected_area == MapArea01ID)
		this->ChangeMap(MapArea01ID,7,7,DirectionRetain,DirectionDown);

	return (this->teleport_selected_area != -1);
}

void Map::MapObjectsInteractionUpdate()
{
	Character& character = *GameState::GetGame<GameRPG>().GetHero().GetCharacter().get();

	//Atualizando todos os objetos para interagirem com o herói
	for (size_t i = 0; i < this->GetMapObjects().size(); i++)
		this->GetMapObjects()[i]->SetInteraction(character);
}

void Map::CharactersPathfindUpdate()
{
	for (int y = 0; y < this->GetTileTotal().GetY(); y++)
	{
		for (int x = 0; x < this->GetTileTotal().GetX(); x++)
		{
			for (size_t i = 0; i < this->characters_pathfind_update.size(); i++)
				this->characters_pathfind_update[i]->SetPathfindNodeWalkable(x,y,this->GetSharedTileWalkable(x,y));
		}
	}
	this->characters_pathfind_update.clear();
}

bool Map::IsHeroCharacter(const MapObject& map_object_interacting)
{
	return (&map_object_interacting == GameState::GetGame<GameRPG>().GetHero().GetCharacter().get());
}

bool Map::IsMapLoaded() const
{
	return this->map_loaded;
}

void Map::MapLoaded()
{
	//Adicionar herói já com a posição e direção carregada
	this->AddHero();

	//Atualizar as interações dos objetos do mapa
	this->MapObjectsInteractionUpdate();

	//Atualizar dados do Pathfind de cada personagem do mapa
	this->CharactersPathfindUpdate();

	//Clarear a tela
	GameState::GetGame<GameRPG>().GetScreenEffect().StartFadeInScreen(ScreenEffectFadeMode::Fast);

	//Mapa já todo carregado
	this->map_loaded = true;
}

bool Map::LoadingTextures()
{
	const bool loading = this->textures_loaded < this->GetTextureTileSetsID().size();

	//Se tiver texturas para carregar
	if (loading)
	{
		GameState::GetGame<GameRPG>().GetVideo().LoadTexture(this->GetTextureTileSetsID()[this->textures_loaded]);
		this->textures_loaded++;
	}
	return loading;
}

void Map::ShowShopMenu(Shop& shop)
{
	ShopMenu* menu = static_cast<ShopMenu*>(GameState::AddGameState(make_unique<ShopMenu>(shop),GameStateAction::PauseCurrentGameState));
	menu->AddEventOnClose(&Map::CloseShopMenuEvent,*this);
}

void Map::ChangeMap(const MapID new_map_id,const float hero_position_x,const float hero_position_y,const HeroMapChangeDirection hero_leaving_map_direction,const HeroMapChangeDirection hero_entering_map_direction)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	this->changing_map = (this->new_map_id != new_map_id);
	this->new_map_id = new_map_id;
	this->hero_position_x = hero_position_x;
	this->hero_position_y = hero_position_y;
	this->hero_entering_map_direction = hero_entering_map_direction;
	this->hero_leaving_map_direction = hero_leaving_map_direction;
	this->RemoveSubGameStates();

	//Escurecer a tela
	game.GetScreenEffect().StartFadeOutScreen(ScreenEffectFadeMode::Fast);

	//Resetar valores
	game.GetHero().GetMapDataState().GetMapStates()[this->current_map_id].ResetIndices();
}

void Map::EndInteraction(const bool hero_unlock_movement)
{
	if (MapObject::GetMapObjectInteracted())
		MapObject::GetMapObjectInteracted()->UnlockMovement();

	//Resetar valor pois a interação já acabou
	MapObject::ResetMapObjectInteracted();

	//Desbloquear os movimentos do herói
	if (hero_unlock_movement)
		GameState::GetGame<GameRPG>().GetHero().GetCharacter()->UnlockMovement();
}

void Map::GeneralOptionOnClick(const Control& control)
{
	GameState::GetGame<GameRPG>().GetAudio().PlaySoundFromBuffer(SoundClickFileID);
}

void Map::BackOptionOnClick(const Control& control)
{
	GameState::GetGame<GameRPG>().GetAudio().PlaySoundFromBuffer(SoundCancelFileID);
}

void Map::BeginInteractingObjectsEvent(MapObject& map_object_base,MapObject& map_object_interacting)
{
	//Virar os objetos do mapa entre sí
	map_object_base.TurnTo(map_object_interacting);

	//Travar os objetos do mapa
	map_object_base.LockMovement();
	map_object_interacting.LockMovement();
}

void Map::DialogueBoxEndInteractingObjectsEvent(const Control& control)
{
	this->EndInteraction(true);
}

void Map::SaveCrystalInteractionEvent(MapObject& map_object_base,MapObject& map_object_interacting)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	game.GetAudio().PlaySoundFromBuffer(SoundSaveCrystalFileID);

	this->SetTitleDialogueBox(SaveCrystalTextID,Color::Green,140.0f);
	this->AddOptionDialogueBox(SaveCrystalActionTextID,Color::Gold,KeyboardKey::S);
	this->AddOptionDialogueBox(TeleportTextID,Color::Gold,KeyboardKey::T);
	this->AddOptionDialogueBox(BackTextID,Color::Gold,KeyboardKey::Esc,false);

	this->AddOptionEventOnOptionSelected(0,&Map::SaveOptionSelectedEvent,*this);
	this->AddOptionEventOnOptionSelected(1,&Map::TeleportOptionSelectedEvent,*this);
	this->AddOptionEventOnClick(2,&Map::BackOptionOnClick,*this);

	this->DialogueBoxUpdate();

	//Se o teleporte estiver desativado
	MapDataState::MapState& map_state = game.GetHero().GetMapDataState().GetMapStates()[this->current_map_id];
	if (map_state.GetTeleportState() == TeleportDeactivated)
	{
		map_state.SetTeleportState(TeleportActivated);
		game.NewMessageLogText(game.GetDatabase().GetLanguageText(TeleportActivatedTextID),Color::White);
	}
}

void Map::SaveOptionSelectedEvent(const Control& control,const int option_selected_index)
{
	///
	GameState::GetGame<GameRPG>().NewMessageLogText("[Save] not implemented!",Color::Red);
	///
}

void Map::TeleportOptionSelectedEvent(const Control& control,const int option_selected_index)
{
	TeleportMenu* menu = static_cast<TeleportMenu*>(GameState::AddGameState(make_unique<TeleportMenu>(this->current_map_id),GameStateAction::None));
	menu->AddEventOnClose(&Map::CloseTeleportMenuEvent,*this);
}

void Map::ChestOpeningEvent(MapObject& map_object)
{
	GameState::GetGame<GameRPG>().GetAudio().PlaySoundFromBuffer(SoundChestOpeningFileID);
}

void Map::ChestOpenedEvent(MapObject& map_object)
{
	ChestMenu* menu = static_cast<ChestMenu*>(GameState::AddGameState(make_unique<ChestMenu>(static_cast<BaseChest&>(map_object)),GameStateAction::PauseCurrentGameState));
	menu->AddEventOnClose(&Map::CloseChestMenuEvent,*this);
}

void Map::ChestClosedEvent(MapObject& map_object)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	game.GetAudio().PlaySoundFromBuffer(SoundChestClosingFileID);
	game.GetHero().GetCharacter()->UnlockMovement();
}

void Map::EnteringGatewayEvent(MapObject& map_object_base,MapObject& map_object_interacting)
{
	GameState::GetGame<GameRPG>().GetHero().GetCharacter()->ClearPathfind();
}

void Map::EnteringDoorEvent(MapObject& map_object_base,MapObject& map_object_interacting)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	this->EnteringGatewayEvent(map_object_base,map_object_interacting);
	game.GetAudio().PlaySoundFromBuffer(SoundDoorOpeningFileID);
	game.GetHero().GetCharacter()->LockMovement();
}

void Map::CloseChestMenuEvent(const Menu& menu)
{
	//Deixar para desbloquear os movimentos do herói somente quando fechar completamente o baú
	this->EndInteraction(false);
}

void Map::CloseShopMenuEvent(const Menu& menu)
{
	this->CloseMenuEvent(menu);
	ItemButton::SetShopping(false);
	ItemButton::ClearAllItemButtons();
}

void Map::CloseTeleportMenuEvent(const Menu& menu)
{
	this->CloseMenuEvent(menu);
	this->teleport_selected_area = static_cast<const TeleportMenu&>(menu).GetSelectedArea();

	//Opção válida selecionada, então começar o processo de teleporte do herói
	if (this->teleport_selected_area != -1)
		this->hero_teleporting = true;
}

void Map::CloseMenuEvent(const Menu& menu)
{
	this->EndInteraction(true);
}

void Map::HeroTeleportingAnimationOnShow(MapObject& map_object)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Se estiver teleportando e a tela toda clara
	if ((this->hero_teleporting) && (game.GetScreenEffect().FadeInEnd()))
	{
		const Character& character = static_cast<Character&>(map_object);

		game.GetAnimations()[HeroTeleporting].SetPosition(character.GetX() + (character.GetW() / 2.0f) - this->GetCamera().GetX(),character.GetY() + (character.GetH() / 2.0f) - this->GetCamera().GetY(),true);
		game.GetAnimations()[HeroTeleporting].Show(game.GetVideo(),game.GetTimer());
	}
}
#include "TeleportMenu.h"

using namespace GPL;
using namespace RPG;

TeleportMenu::TeleportMenu(const MapID current_map_id) :
	Menu(1),
	current_map_id(current_map_id),
	selected_area(-1)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Como o mapa não vai ficar pausado, então travar o movimento aqui do herói
	game.GetHero().GetCharacter()->LockMovement();

	//Dialogue Box
	const float space = 10.0f;
	DialogueBox& dialogue_box = this->CreateControl<DialogueBox>();
	game.SetDialogueBox(dialogue_box);
	dialogue_box.SetDialogueBox(this->GetDefaultFontMedium(),1,100.0f,space,space,game.GetTextSpeedInterval(),game.GetDatabase().GetLanguageText(DestinationTextID),Color::Green);
	dialogue_box.SetPosition(game.GetVideo().GetVirtualWidth() / 2.0f,game.GetVideo().GetVirtualHeight() / 2.0f,true);

	//Teleportes que estão ativados
	int index = 0;
	for (int i = 0; i < MapMax; i++)
	{
		if ((game.GetHero().GetMapDataState().GetMapStates()[i].GetTeleportState() == TeleportActivated) && (i != this->current_map_id))
		{
			dialogue_box.AddOption(game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(MapArea00TextID + i)),Color::White,space);
			dialogue_box.AddOptionEventOnClick(index,&Menu::GeneralOnClick,static_cast<Menu&>(*this));
			dialogue_box.AddOptionEventOnOptionSelected(index,&TeleportMenu::MapAreaOnOptionSelected,*this);
			index++;
		}
	}

	index = dialogue_box.GetOptionsTotal();
	dialogue_box.AddOption(game.GetDatabase().GetLanguageText(BackTextID),Color::Gold);
	dialogue_box.AddOptionKeyShortcut(index,KeyboardKey::Esc);
	dialogue_box.AddOptionEventOnClick(index,&TeleportMenu::BackOnClick,*this);
	dialogue_box.AddOptionEventOnOptionSelected(index,&TeleportMenu::BackOnOptionSelected,*this);
	dialogue_box.AddControl();
}

int TeleportMenu::GetSelectedArea() const
{
	return this->selected_area;
}

void TeleportMenu::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Dialogue Box
	this->GetControl<DialogueBox>(0).SetPosition(game.GetVideo().GetVirtualWidth() / 2.0f,game.GetVideo().GetVirtualHeight() / 2.0f,true);
}

void TeleportMenu::Close()
{
	GameState::AddGameState(nullptr,GameStateAction::DeleteCurrentGameState);
}

void TeleportMenu::BackOnClick(const Control& control)
{
	GameState::GetGame<GameRPG>().GetAudio().PlaySoundFromBuffer(SoundCancelFileID);
}

void TeleportMenu::MapAreaOnOptionSelected(const Control& control,const int option_selected_index)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	int teleport_counter = 0;
	for (int i = 0; i < MapMax; i++)
	{
		//Mapa tem teleporte e não é o próprio mapa atual
		if ((game.GetHero().GetMapDataState().GetMapStates()[i].GetTeleportState() == TeleportActivated) && (i != this->current_map_id))
			teleport_counter++;

		//Contador passou do índice da opção selecionada então pegar o valor do mapa que será carregado
		if (teleport_counter > option_selected_index)
		{
			this->selected_area = i;
			break;
		}
	}

	this->Close();
}

void TeleportMenu::BackOnOptionSelected(const Control& control,const int option_selected_index)
{
	this->Close();
}
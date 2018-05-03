#include "GameTopInterface.h"

using namespace std;
using namespace GPL;
using namespace RPG;

GameTopInterface::GameTopInterface()
{
	this->cursor.SetTexture(GameState::GetGame<GameRPG>().GetVideo().GetTexture(TextureCommonFileID));
	this->cursor.SetSize(31.0f,31.0f);
}

void GameTopInterface::ShowRecentAchievementUnlocked()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	static Sprite background;
	static bool show_achievement_unlocked = false;
	static Text text;
	static Interval timer(5.0f);
	static ColorChanger color_changer(Color(1.0f,0.0f,0.0f,0.75f),Color(0.5f,0.0f,0.0f,0.75f),0.020f,0.5f);

	//Preparando para mostrar a conquista desbloqueada
	if (!game.GetRecentAchievementUnlocked().empty())
	{
		const float border_size = 5.0f;

		background.SetColor(Color::Red);

		show_achievement_unlocked = true;
		text.SetText(this->GetDefaultFontMedium(),game.GetDatabase().GetLanguageText(AchievementUnlockedTextID) + " ",Color::Gold);
		text.AddText(game.GetRecentAchievementUnlocked(),Color::White);
		text.SetPosition(game.GetVideo().GetVirtualWidth() / 2.0f,(game.GetVideo().GetVirtualHeight() / 2.0f) - 100.0f,true);
		background.SetSize(text.GetW() + (border_size * 2.0f),text.GetH() + (border_size * 2.0f));
		background.SetPosition(text.GetX() - border_size,text.GetY() - border_size);
		game.SetRecentAchievementUnlocked("");
		game.GetAudio().PlaySoundFromBuffer(SoundAchievementUnlockedFileID);
		timer.Synchronize(game.GetTimer());
	}

	//Mostrando a mensagem que a conquista foi desbloqueada
	if (show_achievement_unlocked)
	{
		//Sair do jogo no meio da mensagem
		show_achievement_unlocked = game.HeroCreated();
		if (game.HeroCreated())
		{
			background.SetColor(color_changer.RunColorChanger(game.GetTimer()));
			background.Show(game.GetVideo());
			text.Show(game.GetVideo());
		}
		
		//Acabou o tempo da mensagem
		if (timer.Action(game.GetTimer()))
			show_achievement_unlocked = false;
	}
}

void GameTopInterface::ShowCursor()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	if ((game.HeroCreated()) && (!game.GetHero().GetPickedItem().IsEmpty()))
	{
		Sprite& picked_item_icon = game.GetHero().GetPickedItemIcon();

		picked_item_icon.Show(game.GetVideo());

		//Se os requerimentos para usar o item não foram atingidos
		if (game.GetHero().PickedItemRequirementNotMet())
			game.GetHero().GetPickedItemIcon().SetColor(Color::Red);
		else
			game.GetHero().GetPickedItemIcon().SetColor(Color::White);
	}
	else
		this->cursor.Show(game.GetVideo());
}

void GameTopInterface::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Posição do cursor
	const float mouse_x = static_cast<float>(game.GetInput().GetMouseX());
	const float mouse_y = static_cast<float>(game.GetInput().GetMouseY());

	//Cursor
	this->cursor.SetPosition(mouse_x - 2.0f,mouse_y);

	//Item Icon
	if ((game.HeroCreated()) && (!game.GetHero().GetPickedItem().IsEmpty()))
		game.GetHero().GetPickedItemIcon().SetPosition(mouse_x,mouse_y,true);
}

void GameTopInterface::Show()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Message Log
	game.ShowMessageLog();

	//Controls
	Control::ShowControls(game.GetInput(),game.GetVideo(),game.GetTimer());

	//Achievement Unlocked
	this->ShowRecentAchievementUnlocked();

	//Text Dynamics
	game.ShowTextDynamic();

	//Cursor in game
	this->ShowCursor();

	//Screen Effect
	game.GetScreenEffect().Show(game.GetVideo(),game.GetTimer());
}
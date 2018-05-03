#include "InformationMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

Interval InformationMenu::colon_timer_interval(0.5f);

InformationMenu::InformationMenu(const bool& change_window_position) :
	Menu(InformationMenuControlMax),
	change_window_position(change_window_position),
	window_speed_y(0.0f)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Information Window
	Window& information_window = this->CreateControl<Window>();
	game.SetWindow(information_window,4,1);
	information_window.SetPosition(50.0f,game.GetVideo().GetVirtualHeight() + information_window.GetH());
	information_window.AddControl();

	//Gold Picture Box
	PictureBox& gold_picture_box = this->CreateControl<PictureBox>();
	gold_picture_box.SetAnimationFrame(game.GetTimer(),game.GetVideo().GetTexture(TextureGoldFileID),16.0f,16.0f,4,0.085f);
	gold_picture_box.AddControl();

	//Timer Picture Box
	PictureBox& timer_picture_box = this->CreateControl<PictureBox>();
	timer_picture_box.SetSprite(game.GetVideo().GetTexture(TextureCommonFileID),16.0f,16.0f,33.0f,50.0f);
	timer_picture_box.AddControl();

	//Gold Label
	Label& gold_label = this->CreateControl<Label>();
	gold_label.SetText(this->GetDefaultFontMedium(),"");
	gold_label.AddControl();

	//Timer Label
	Label& timer_label = CreateControl<Label>();
	timer_label.SetText(this->GetDefaultFontMedium(),"");
	timer_label.AddControl();

	//Atualizar as posições dos controles
	this->PositionUpdate();

	InformationMenu::colon_timer_interval.Synchronize(game.GetHero().GetPlayTime());
}

void InformationMenu::Update()
{
	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void InformationMenu::PositionUpdate()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	PictureBox& gold_picture_box = this->GetControl<PictureBox>(GoldPictureBox);
	PictureBox& timer_picture_box = this->GetControl<PictureBox>(TimerPictureBox);

	//Movimentar a janela
	if (this->change_window_position)
	{
		Window& information_window = this->GetControl<Window>(InformationWindow);

		const float value_max = 491.0f;
		if (information_window.GetY() != value_max)
		{
			this->window_speed_y += 1.0f;
			information_window.SetPosition(50.0f,max(information_window.GetY() - this->window_speed_y,value_max));

			//Picture Box
			gold_picture_box.SetPosition(information_window.GetX() + 10.0f,information_window.GetY() + 10.0f);
			timer_picture_box.SetPosition(gold_picture_box.GetX(),gold_picture_box.GetY() + gold_picture_box.GetH() + 10.0f);
		}
	}

	//Time
	const int seconds = static_cast<int>(game.GetHero().GetPlayTime().CurrentTime());
	const int hours = (seconds / 3600);
	const int minutes = seconds / 60;
	const int minutes_left = minutes % 60;
	const int seconds_left = seconds % 60;

	static const Color* color = &Color::White;

	//Mudança de cor
	if (InformationMenu::colon_timer_interval.Action(game.GetHero().GetPlayTime()))
	{
		if (color == &Color::White)
			color = &Color::Gray;
		else
			color = &Color::White;
	}

	//Gold Label
	Label& gold_label = this->GetControl<Label>(GoldLabel);
	gold_label.SetTextString(Convert::NumberToString(game.GetHero().GetStats().GetGold()));
	gold_label.SetPosition(gold_picture_box.GetX() + gold_picture_box.GetW() + (gold_label.GetW() / 2.0f) + 5.0f,gold_picture_box.GetY() + (gold_picture_box.GetH() / 2.0f),true);

	//Timer Label
	Label& timer_label = this->GetControl<Label>(TimerLabel);
	timer_label.ClearText();
	timer_label.AddText((hours < 100 ? + (hours < 10 ? + "00" : "0") : "") + Convert::NumberToString(hours),Color::White);
	timer_label.AddText(":",*color);
	timer_label.AddText((minutes_left < 10 ? + "0" : "") + Convert::NumberToString(minutes_left),Color::White);
	timer_label.AddText(":",*color);
	timer_label.AddText((seconds_left < 10 ? + "0" : "") + Convert::NumberToString(seconds_left),Color::White);
	timer_label.SetPosition(timer_picture_box.GetX() + timer_picture_box.GetW() + (timer_label.GetW() / 2.0f) + 5.0f,timer_picture_box.GetY() + (timer_picture_box.GetH() / 2.0f),true);
}
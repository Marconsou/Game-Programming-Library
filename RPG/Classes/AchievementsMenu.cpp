#include "AchievementsMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

AchievementsMenu::AchievementsMenu(const float x,const float y) :
	Menu(GameState::GetGame<GameRPG>().GetHero().GetAchievements().size() + AchievementsMenuControlMax)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Achievement Label
	Label& achievement_label = this->CreateControl<Label>();

	achievement_label.SetText(this->GetDefaultFontSmall(),game.GetDatabase().GetLanguageText(AchievementsTextID),Color::Green);
	achievement_label.SetPosition(x,y);
	achievement_label.AddControl();

	//Achievement Dialogue Box
	DialogueBox& achievement_dialogue_box = this->CreateControl<DialogueBox>();
	game.SetDialogueBox(achievement_dialogue_box);

	//Achievement Percentage Label
	size_t achievements_unlocked = 0;
	const size_t achievements_total = game.GetHero().GetAchievements().size();
	for (size_t	i = 0; i < game.GetHero().GetAchievements().size(); i++)
	{
		if (game.GetHero().GetAchievements()[i].GetUnlocked())
			achievements_unlocked++;
	}
	Label& achievement_percentage_label = this->CreateControl<Label>();
	const int percentage = static_cast<int>(achievements_unlocked / achievements_total) * 100;
	const float percentage_color = min(max(percentage / 100.0f,0.25f),1.0f);
	const Color color(Color::Gold.GetRed() * percentage_color ,Color::Gold.GetGreen() * percentage_color,Color::Gold.GetBlue() * percentage_color);
	achievement_percentage_label.SetText(game.GetVideo().GetFont(FontPerspectiveSansBlackItalicFileID),Convert::NumberToString(percentage) + "%",color);
	achievement_percentage_label.SetPosition(x + achievement_label.GetW() + 10.0f,y + (achievement_label.GetH() / 2.0f) - (achievement_percentage_label.GetH() / 2.0f) - 2.0f);
	achievement_percentage_label.AddControl();

	//Achievement Labels
	const size_t achievement_start_index = AchievementsMenuControlMax;
	for (size_t i = achievement_start_index; i < this->GetControlTotal(); i++)
	{
		Button& iterator = this->CreateControl<Button>();

		const int achievement_index = i - achievement_start_index;

		iterator.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
		iterator.SetButton(this->GetDefaultFontSmall(),game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(SkillfulTextID + achievement_index)),Color::Gray);
		iterator.NewToolTipTextLine(game.GetDatabase().GetLanguageText(AchievementsClickTextID),Color::White);
		iterator.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
		iterator.AddEventOnClick(&AchievementsMenu::GeneralOnClick,*this);
		iterator.SetPosition(x,y + ((i - 1) * achievement_label.GetH()) + 1.0f);
		iterator.AddControl();
	}
}

void AchievementsMenu::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	Hero& hero = game.GetHero();

	//Centralizar no meio da tela
	this->GetControl<DialogueBox>(AchievementDialogueBox).SetPosition(game.GetVideo().GetVirtualWidth() / 2.0f,game.GetVideo().GetVirtualHeight() / 2.0f,true);

	//Achievement Labels
	const size_t achievement_start_index = AchievementsMenuControlMax;
	for (size_t i = achievement_start_index; i < this->GetControlTotal(); i++)
	{
		Button& iterator = this->GetControl<Button>(i);

		const int achievement_index = i - achievement_start_index;

		if (hero.GetAchievements()[achievement_index].GetUnlocked())
			iterator.SetColor(Color::White);
	}
}

void AchievementsMenu::GeneralOnClick(const Control& control)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Buscar o índice correto da conquista
	size_t index;
	for (size_t i = 0; i < this->GetControlTotal(); i++)
	{
		if (&control == &this->GetControl<Control>(i))
		{
			index = i - AchievementsMenuControlMax;
			break;
		}
	}

	//Nome e descrição da conquista
	const string achievement_name(game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(SkillfulTextID + index)));
	const string achievement_description(game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(SkillfulDescriptionTextID + index)));

	//Separa os textos corretamente
	vector<string> strings;
	vector<Color> colors;
	Menu::ExtractInformation(achievement_description,game.GetHero().GetAchievements()[index].GetValues(),strings,colors);

	//Dialogue Box com os textos da conquista
	const float tab_space = 10.0f;
	DialogueBox& achievement_dialogue_box = this->GetControl<DialogueBox>(AchievementDialogueBox);
	achievement_dialogue_box.SetDialogueBox(this->GetDefaultFontMedium(),3,max(Text::TextSize(this->GetDefaultFontMedium(),achievement_name).GetX(),200.0f),tab_space,tab_space,game.GetTextSpeedInterval(),achievement_name,Color::Gold);

	//Adicionando os textos e cores dos textos corretamente
	for (size_t i = 0; i < strings.size(); i++)
		achievement_dialogue_box.AddText(strings[i],colors[i]);
	achievement_dialogue_box.AddControl();
}
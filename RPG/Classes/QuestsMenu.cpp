#include "QuestsMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

QuestsMenu::QuestsMenu(const float x,const float y,const float space_w) :
	Menu(GameState::GetGame<GameRPG>().GetHero().GetMainQuests().size() + GameState::GetGame<GameRPG>().GetHero().GetOptionalQuests().size() + QuestsMenuControlMax)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Quest Label
	Label& quest_label = this->CreateControl<Label>();

	quest_label.SetText(this->GetDefaultFontSmall(),game.GetDatabase().GetLanguageText(QuestsTextID),Color::Green);
	quest_label.SetPosition(x,y);
	quest_label.AddControl();

	//Quest Dialogue Box
	DialogueBox& quest_dialogue_box = this->CreateControl<DialogueBox>();
	game.SetDialogueBox(quest_dialogue_box);

	//Quests Buttons
	const size_t quest_start_index = QuestsMenuControlMax;
	this->AddQuestButtons(game.GetHero().GetMainQuests(),quest_start_index,0,MainQuestName0TextID,MainQuestsClickTextID,x,y);
	this->AddQuestButtons(game.GetHero().GetOptionalQuests(),quest_start_index + game.GetHero().GetMainQuests().size(),game.GetHero().GetMainQuests().size(),OptionalQuestName0TextID,OptionalQuestsClickTextID,x + space_w,y);
}

void QuestsMenu::AddQuestButtons(const vector<Quest>& quests,const size_t quest_start_index,const size_t quest_discount_index,const LanguageTextID quest_name_text_id,const LanguageTextID quest_click_text_id,const float x,const float y)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	const Label& quest_label = this->GetControl<Label>(0);

	//Quests Buttons
	const size_t quests_total = quests.size();
	for (size_t i = quest_start_index; i < quest_start_index + quests_total; i++)
	{
		const int quest_index = i - quest_start_index;

		const Quest& quest = quests[quest_index];

		Button& button = this->CreateControl<Button>();

		button.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
		button.SetButton(this->GetDefaultFontSmall(),game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(quest_name_text_id + quest_index)),quest.IsStarted() ? Color::Gray : Color::White);
		button.NewToolTipTextLine(game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(quest_click_text_id + quest_index)),Color::White);
		button.AddEventOnClick(&Menu::GeneralOnClick,static_cast<Menu&>(*this));
		button.AddEventOnClick(&QuestsMenu::GeneralOnClick,*this);
		button.SetPosition(x,y + ((i - quest_discount_index) * quest_label.GetH()) + 1.0f);

		//Não mostrar se a Quest ainda não foi habilitada
		if (!quest.IsUnknown())
			button.AddControl();
	}
}

void QuestsMenu::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Centralizar no meio da tela
	this->GetControl<DialogueBox>(QuestDialogueBox).SetPosition(game.GetVideo().GetVirtualWidth() / 2.0f,game.GetVideo().GetVirtualHeight() / 2.0f,true);
}

void QuestsMenu::GeneralOnClick(const Control& control)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Buscar o índice correto da Quest
	size_t index;
	for (size_t i = 0; i < this->GetControlTotal(); i++)
	{
		if (&control == &this->GetControl<Control>(i))
		{
			index = i - QuestsMenuControlMax;
			break;
		}
	}

	const size_t main_quests_total = game.GetHero().GetMainQuests().size();

	//Verificar se vai utilizar Main Quests ou Optional Quests
	const bool using_main_quests = (index < main_quests_total);
	Quest& quest = using_main_quests ? game.GetHero().GetMainQuests()[index] : game.GetHero().GetOptionalQuests()[index - main_quests_total];
	const LanguageTextID quest_name_text_id = (using_main_quests) ? MainQuestName0TextID : static_cast<LanguageTextID>(OptionalQuestName0TextID - main_quests_total + 1);
	const LanguageTextID quest_description_text_id = (using_main_quests) ? MainQuestDescription0TextID : static_cast<LanguageTextID>(OptionalQuestDescription0TextID - main_quests_total + 1);

	//Nome e descrição da Quest
	const string quest_name(game.GetDatabase().GetLanguageText(quest_name_text_id));
	const string quest_description(game.GetDatabase().GetLanguageText(quest_description_text_id));

	//Separa os textos corretamente
	vector<string> strings;
	vector<Color> colors;

	//Quest Started
	if (quest.IsStarted())
		Menu::ExtractInformation(quest_description,quest.GetValues(),strings,colors);

	//Quest Completed
	else if (quest.IsCompleted())
	{
		strings.push_back(game.GetDatabase().GetLanguageText(QuestCompletedDescriptionTextID));
		colors.push_back(Color::White);
	}

	//Dialogue Box com os textos da Quest
	const float tab_space = 10.0f;
	DialogueBox& quest_dialogue_box = this->GetControl<DialogueBox>(QuestDialogueBox);
	quest_dialogue_box.SetDialogueBox(this->GetDefaultFontMedium(),3,max(Text::TextSize(this->GetDefaultFontMedium(),quest_name).GetX(),200.0f),tab_space,tab_space,game.GetTextSpeedInterval(),quest_name,Color::Gold);

	//Adicionando os textos e cores dos textos corretamente
	for (size_t i = 0; i < strings.size(); i++)
		quest_dialogue_box.AddText(strings[i],colors[i]);
	quest_dialogue_box.AddControl();
}
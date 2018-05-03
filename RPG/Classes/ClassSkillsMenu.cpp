#include "ClassSkillsMenu.h"

using namespace std;
using namespace GPL;
using namespace RPG;

ClassSkillsMenu::ClassSkillsMenu(const vector<vector<SkillLevel>>& class_skills,const Texture& button_texture) :
	Menu(GameState::GetGame<GameRPG>().GetHero().GetSkills().size() * 2),
	class_skills(class_skills)
{
	Hero& hero =  GameState::GetGame<GameRPG>().GetHero();

	for (size_t i = 0; i < this->GetControlTotal() / 2; i++)
	{
		//Skill Level Labels
		Label& label = this->CreateControl<Label>();

		label.AddControl();

		//Skill Buttons
		SkillButton& skill_button = this->CreateControl<SkillButton>();

		skill_button.SetSkill(*hero.GetSkills()[i].get(),button_texture,i);
		skill_button.AddEventOnClick(&ClassSkillsMenu::AddSkillLevelOnClick,*this);
		skill_button.AddControl();
	}
}

void ClassSkillsMenu::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	static ColorChanger color_changer(Color::Green,Color(0.0f,0.5f,0.0f),0.050f,0.5f);

	for (size_t i = 0; i < this->GetControlTotal() / 2; i++)
	{
		//Skill Level Labels
		Label& label = this->GetControl<Label>(i);

		//Skill Buttons
		size_t index_added = i + 1;
		SkillButton& skill_button = this->GetControl<SkillButton>(index_added);

		//Skill
		const Skill& skill = skill_button.GetSkill();

		label.SetText(this->GetDefaultFontSmall(),skill.SkillLearned() ? game.GetDatabase().GetLanguageText(LvTextID) + " " + Convert::NumberToString(skill.GetLevel()) : game.GetDatabase().GetLanguageText(NewSkillTextID),skill.SkillLearned() ? Color::Gold : color_changer.RunColorChanger(game.GetTimer()));
		label.SetPosition(skill_button.GetX() + (skill_button.GetW() / 2.0f),skill_button.GetY() + skill_button.GetH() + (label.GetH() / 2.0f),true);
	}
}

void ClassSkillsMenu::CheckForAchievementSkillful(const Skill& skill)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	if (skill.SkillIsLevelMax())
	{
		Achievement& achievement = game.GetHero().GetAchievements()[Skillful];
		if (!achievement.GetUnlocked())
		{
			achievement.SetUnlocked(true);
			game.SetRecentAchievementUnlocked(game.GetDatabase().GetLanguageText(SkillfulTextID));
		}
	}
}

void ClassSkillsMenu::BaseToolTipUpdate(const LanguageTextID language_text_id)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Atualizar dados básicos dos ToolTips
	for (size_t i = 0; i < this->GetControlTotal() / 2; i++)
	{
		size_t index_added = i + 1;
		SkillButton& iterator = this->GetControl<SkillButton>(index_added);

		iterator.ClearToolTip();
		iterator.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());

		if (!iterator.GetSkill().SkillLearned())
		{
			iterator.NewToolTipTextLine(game.GetDatabase().GetLanguageText(LearnTextID),Color::Green);
			iterator.AddToolTipTextLine(" " + game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(language_text_id + i)),Color::Gold);
		}
		else
		{
			iterator.NewToolTipTextLine(game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(language_text_id + i)) + " " + game.GetDatabase().GetLanguageText(LevelTextID),Color::Gold);
			iterator.AddToolTipTextLine(" " + Convert::NumberToString(iterator.GetSkill().GetLevel()),Color::White);
		}

		if (iterator.GetSkill().GetRequiredLevel() > 1)
		{
			const bool requirement_met = !game.GetHero().SkillRequirementNotMet(iterator.GetSkill());

			iterator.NewToolTipTextLine(game.GetDatabase().GetLanguageText(RequiredLevelTextID),requirement_met ? Color::Yellow : Color::Red);
			iterator.AddToolTipTextLine(" " + Convert::NumberToString(iterator.GetSkill().GetRequiredLevel()),requirement_met ? Color::White : Color::Red);
		}

		iterator.NewToolTipTextLine(game.GetDatabase().GetLanguageText(TypeTextID),Color::Yellow);
		iterator.AddToolTipTextLine(" " + game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(NaturalTextID + iterator.GetSkill().GetClassType())),Color::White);
	}
}

void ClassSkillsMenu::AddSkillLevelOnClick(Control& control)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	Hero& hero = game.GetHero();

	Skill& skill = static_cast<SkillButton&>(control).GetSkill();

	//Se a habilidade já não estiver no nível máximo, tiver pontos de habilidade para gastar e tiver nível do herói para usar a habilidade
	if ((!skill.SkillIsLevelMax()) && (hero.GetSP() && (!hero.SkillRequirementNotMet(skill))))
	{
		const LanguageTextID language_text_id = skill.SkillLearned() ? SkillLevelUpTextID : SkillLearnedTextID;
		const Color& color = skill.SkillLearned() ? Color::Green : Color::Gold;

		game.AddTextDynamic<TextDynamicZoom>(game.GetDatabase().GetLanguageText(language_text_id),color,control.GetX() + (control.GetW() / 2.0f),control.GetY() + (control.GetH() / 2.0f));

		//Encontrando o índice do nível da habilidade
		int skill_index = 0;
		for (size_t i = 0; i < this->GetControlTotal() / 2; i++)
		{
			size_t index_added = i + 1;
			SkillButton& iterator = this->GetControl<SkillButton>(index_added);

			if (&control == &iterator)
				skill_index = i;
		}

		skill.LevelUp(this->class_skills[skill_index]);
		hero.SpendSP();
		this->SkillButtonToolTipUpdate();
		this->CheckForAchievementSkillful(skill);
		game.GetAudio().PlaySoundFromBuffer(SoundSkillLevelUpFileID);
	}
	else
		game.GetAudio().PlaySoundFromBuffer(SoundErrorFileID);
}
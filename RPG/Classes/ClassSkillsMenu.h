#ifndef CLASSSKILLSMENU_H
#define CLASSSKILLSMENU_H

#include "ColorChanger.h"
#include "TextDynamicZoom.h"
#include "Label.h"
#include "SkillButton.h"
#include "Menu.h"

namespace RPG
{
	class ClassSkillsMenu : public Menu
	{
	private:
		//Refer�ncia das habilidades de acordo com a classe
		const std::vector<std::vector<SkillLevel>>& class_skills;

		//Verificar o Achievement Skillful
		void CheckForAchievementSkillful(const Skill& skill);

		//Evento do bot�o para aumentar o n�vel da habilidade
		void AddSkillLevelOnClick(GPL::Control& control);

		//Atualizar o ToolTip dos bot�es das habilidades
		virtual void SkillButtonToolTipUpdate() = 0;
	protected:
		//Atualizar os dados b�sicos dos ToolTips dos bot�es das habilidades
		void BaseToolTipUpdate(const LanguageTextID language_text_id);

		//Atualizar dados e a l�gica de todo o conte�do
		virtual void Update();
	public:
		//Construtor
		ClassSkillsMenu(const std::vector<std::vector<SkillLevel>>& class_skills,const GPL::Texture& button_texture);
	};
}

#endif
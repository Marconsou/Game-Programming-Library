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
		//Referência das habilidades de acordo com a classe
		const std::vector<std::vector<SkillLevel>>& class_skills;

		//Verificar o Achievement Skillful
		void CheckForAchievementSkillful(const Skill& skill);

		//Evento do botão para aumentar o nível da habilidade
		void AddSkillLevelOnClick(GPL::Control& control);

		//Atualizar o ToolTip dos botões das habilidades
		virtual void SkillButtonToolTipUpdate() = 0;
	protected:
		//Atualizar os dados básicos dos ToolTips dos botões das habilidades
		void BaseToolTipUpdate(const LanguageTextID language_text_id);

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		ClassSkillsMenu(const std::vector<std::vector<SkillLevel>>& class_skills,const GPL::Texture& button_texture);
	};
}

#endif
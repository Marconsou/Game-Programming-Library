#ifndef QUESTSMENU_H
#define QUESTSMENU_H

#include "Label.h"
#include "Menu.h"

namespace RPG
{
	class QuestsMenu : public Menu
	{
	private:
		//IDs dos controles do Quests Menu
		enum QuestsMenuControlID
		{
			QuestLabel = 0,
			QuestDialogueBox,
			QuestsMenuControlMax,
		};

		//Adicionar os botões das Quests
		void AddQuestButtons(const std::vector<Quest>& quests,const size_t quest_start_index,const size_t quest_discount_index,const LanguageTextID quest_name_text_id,const LanguageTextID quest_click_text_id,const float x,const float y);

		//Evento geral para On Click
		void GeneralOnClick(const GPL::Control& control);

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		QuestsMenu(const float x,const float y,const float space_w);
	};
}

#endif
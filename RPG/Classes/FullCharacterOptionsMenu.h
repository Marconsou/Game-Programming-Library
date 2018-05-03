#ifndef FULLCHARACTEROPTIONSMENU_H
#define FULLCHARACTEROPTIONSMENU_H

#include "SimpleCharacterOptionsMenu.h"
#include "CharacterInventoryMenu.h"
#include "SkillsMenu.h"
#include "QuestsMenu.h"
#include "AchievementsMenu.h"

namespace RPG
{
	class FullCharacterOptionsMenu : public SimpleCharacterOptionsMenu
	{
	private:
		//Sub Menu do Full Character Options Menu selecionado
		enum FullCharacterOptionsMenuSelection
		{
			NoSelection = 0,
			InventorySelection,
			SkillsSelection,
			QuestsSelection,
			AchievementsSelection,
		};

		//IDs dos controles do Full Character Options Menu
		enum FullCharacterOptionsMenuControlID
		{
			InventoryButton = SimpleCharacterOptionsMenuControlMax,
			SkillsButton,
			QuestsButton,
			AchievementsButton,
			APToSpendPictureBox,
			SPToSpendPictureBox,
			FullCharacterOptionsMenuControlMax,
		};

		//Tamanho da janela principal de conte�do
		const float contents_window_width;

		//Adicionar AP to Spend automaticamente
		bool ap_to_spend_picture_box_control_added;

		//Adicionar SP to Spend automaticamente
		bool sp_to_spend_picture_box_control_added;

		//�ltimo Sub Menu selecionado
		FullCharacterOptionsMenuSelection last_sub_menu_selected;

		//Atualizar as posi��es dos controles
		void PositionUpdate();

		//Atualizar o �cone indicando que tem pontos para gastar
		void SpendIconPictureBoxUpdate(const int value,bool& control_added,GPL::PictureBox& picture_box);

		//Selecionar Sub Menu
		void SelectSubMenu(FullCharacterOptionsMenuSelection sub_menu_selection);

		//Evento do bot�o Inventory
		void InventoryOnClick(const GPL::Control& control);

		//Evento do bot�o Skills
		void SkillsOnClick(const GPL::Control& control);

		//Evento do bot�o Quests
		void QuestsOnClick(const GPL::Control& control);

		//Evento do bot�o Achievements
		void AchievementsOnClick(const GPL::Control& control);

		//Atualizar dados e a l�gica de todo o conte�do
		virtual void Update();
	public:
		//Construtor
		FullCharacterOptionsMenu(const GPL::Point2D<float>& position,const bool& change_window_position,const float contents_window_width);
	};
}

#endif
#ifndef EXTERNALITEMSMENU_H
#define EXTERNALITEMSMENU_H

#include "Label.h"
#include "ItemButton.h"
#include "Menu.h"

namespace RPG
{
	class ExternalItemsMenu : public Menu
	{
	private:
		//Refer�ncia da posi��o do Menu
		const GPL::Point2D<float>& position;

		//Se pode colocar Quest item nos items do Menu
		const bool can_put_quest_item;

		//Refer�ncia de uam estrutura de items qualquer
		std::vector<std::unique_ptr<Item>>& items;

		//Atualizar as posi��es dos controles
		void PositionUpdate();

		//Evento para interagir com os items
		void ItemOnMouseClick(GPL::Control& control,const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Atualizar dados e a l�gica de todo o conte�do
		virtual void Update();
	public:
		//Construtor
		ExternalItemsMenu(const GPL::Point2D<float>& position,std::vector<std::unique_ptr<Item>>& items,const std::string& menu_text,const bool can_put_quest_item,const bool is_shop_item);
	};
}

#endif
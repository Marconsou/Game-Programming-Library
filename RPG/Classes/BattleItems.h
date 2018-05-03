#ifndef BATTLEITEMS_H
#define BATTLEITEMS_H

#include "Label.h"
#include "ItemButton.h"
#include "Menu.h"

namespace RPG
{
	class BattleItems : public Menu
	{
	private:
		//Referência da posição do Menu
		const GPL::Point2D<float>& position;

		//Atualizar as posições dos controles
		void PositionUpdate();

		//Evento para equipar um item de batalha ou usar
		void BattleItemsOnMouseClick(GPL::Control& control,const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		BattleItems(const GPL::Point2D<float>& position,const bool opening_from_shop_menu);
	};
}

#endif
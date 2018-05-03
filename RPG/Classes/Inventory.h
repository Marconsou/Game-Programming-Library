#ifndef INVENTORY_H
#define INVENTORY_H

#include "Label.h"
#include "PictureBox.h"
#include "ItemButton.h"
#include "Menu.h"

namespace RPG
{
	class Inventory : public Menu
	{
	private:
		//IDs de alguns controles adicionais diferentes dos Item Buttons do Inventory
		enum InventoryControlID
		{
			SilhouettePictureBox = 0,
			DiscardItemButton,
			InventoryLabel,
			InventoryControlAdded,
		};

		//Referência da posição do Menu
		const GPL::Point2D<float>& position;

		//Atualizar as posições dos controles
		void PositionUpdate();

		//Evento para interagir com o item
		void ItemOnMouseClick(GPL::Control& control,const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento para equipar Weapon ou Shield
		void EquipHandOnMouseClick(GPL::Control& control,const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento para equipar Helm
		void EquipHelmOnMouseClick(GPL::Control& control,const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento para equipar Armor
		void EquipArmorOnMouseClick(GPL::Control& control,const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento para equipar Gloves
		void EquipGlovesOnMouseClick(GPL::Control& control,const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento para equipar Boots
		void EquipBootsOnMouseClick(GPL::Control& control,const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento para equipar Accessory
		void EquipAccessoryOnMouseClick(GPL::Control& control,const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento para descarta item pelo Discard
		void DiscardOnMouseClick(const GPL::Control& control,const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		Inventory(const GPL::Point2D<float>& position,const bool opening_from_shop_menu);
	};
}

#endif
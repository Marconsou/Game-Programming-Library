#include "Inventory.h"

using namespace std;
using namespace GPL;
using namespace RPG;

Inventory::Inventory(const Point2D<float>& position,const bool opening_from_shop_menu) :
	Menu(GameState::GetGame<GameRPG>().GetHero().GetInventory().size() + GameState::GetGame<GameRPG>().GetHero().GetEquipments().size() + InventoryControlAdded),
	position(position)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Inventory
	const size_t inventory_size = game.GetHero().GetInventory().size();
	for (size_t i = 0; i < inventory_size; i++)
		this->CreateControl<ItemButton>();

	//Equipments
	const size_t equipments_size = game.GetHero().GetEquipments().size();
	for (size_t i = inventory_size; i < inventory_size + equipments_size; i++)
	{
		ItemButton& iterator = this->CreateControl<ItemButton>();

		iterator.SetDefaultEmptyIcon(static_cast<ItemIcon>(ItemIconEmpty + i + 1 - inventory_size));
		iterator.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
	}

	//Silhouette Animation Frame
	PictureBox& silhouette_picture_box = this->CreateControl<PictureBox>();
	silhouette_picture_box.AddControl();

	//Right Hand
	ItemButton& right_hand = this->GetControl<ItemButton>(inventory_size + EquipmentSlotRightHand);
	right_hand.SetItemButton(*game.GetHero().GetEquipments()[EquipmentSlotRightHand]);
	right_hand.GetItem().SetDescription(game.GetDatabase().GetLanguageText(EquipHandTextID));
	right_hand.AddEventOnMouseClick(&Inventory::EquipHandOnMouseClick,*this);
	right_hand.AddControl();

	//Left Hand
	ItemButton& left_hand = this->GetControl<ItemButton>(inventory_size + EquipmentSlotLeftHand);
	left_hand.SetItemButton(*game.GetHero().GetEquipments()[EquipmentSlotLeftHand]);
	left_hand.GetItem().SetDescription(game.GetDatabase().GetLanguageText(EquipHandTextID));
	left_hand.AddEventOnMouseClick(&Inventory::EquipHandOnMouseClick,*this);
	left_hand.AddControl();

	//Helm
	ItemButton& helm = this->GetControl<ItemButton>(inventory_size + EquipmentSlotHelm);
	helm.SetItemButton(*game.GetHero().GetEquipments()[EquipmentSlotHelm]);
	helm.GetItem().SetDescription(game.GetDatabase().GetLanguageText(EquipHelmTextID));
	helm.AddEventOnMouseClick(&Inventory::EquipHelmOnMouseClick,*this);
	helm.AddControl();

	//Armor
	ItemButton& armor = this->GetControl<ItemButton>(inventory_size + EquipmentSlotArmor);
	armor.SetItemButton(*game.GetHero().GetEquipments()[EquipmentSlotArmor]);
	armor.GetItem().SetDescription(game.GetDatabase().GetLanguageText(EquipArmorTextID));
	armor.AddEventOnMouseClick(&Inventory::EquipArmorOnMouseClick,*this);
	armor.AddControl();

	//Gloves
	ItemButton& gloves = this->GetControl<ItemButton>(inventory_size + EquipmentSlotGloves);
	gloves.SetItemButton(*game.GetHero().GetEquipments()[EquipmentSlotGloves]);
	gloves.GetItem().SetDescription(game.GetDatabase().GetLanguageText(EquipGlovesTextID));
	gloves.AddEventOnMouseClick(&Inventory::EquipGlovesOnMouseClick,*this);
	gloves.AddControl();

	//Boots
	ItemButton& boots = this->GetControl<ItemButton>(inventory_size + EquipmentSlotBoots);
	boots.SetItemButton(*game.GetHero().GetEquipments()[EquipmentSlotBoots]);
	boots.GetItem().SetDescription(game.GetDatabase().GetLanguageText(EquipBootsTextID));
	boots.AddEventOnMouseClick(&Inventory::EquipBootsOnMouseClick,*this);
	boots.AddControl();

	//Right Accessory
	ItemButton& right_accessory = this->GetControl<ItemButton>(inventory_size + EquipmentSlotRightAccessory);
	right_accessory.SetItemButton(*game.GetHero().GetEquipments()[EquipmentSlotRightAccessory]);
	right_accessory.GetItem().SetDescription(game.GetDatabase().GetLanguageText(EquipAccessoryTextID));
	right_accessory.AddEventOnMouseClick(&Inventory::EquipAccessoryOnMouseClick,*this);
	right_accessory.AddControl();

	//Left Accessory
	ItemButton& left_accessory = this->GetControl<ItemButton>(inventory_size + EquipmentSlotLeftAccessory);
	left_accessory.SetItemButton(*game.GetHero().GetEquipments()[EquipmentSlotLeftAccessory]);
	left_accessory.GetItem().SetDescription(game.GetDatabase().GetLanguageText(EquipAccessoryTextID));
	left_accessory.AddEventOnMouseClick(&Inventory::EquipAccessoryOnMouseClick,*this);
	left_accessory.AddControl();

	//Inventory
	for (size_t i = 0; i < inventory_size; i++)
	{
		ItemButton& iterator = this->GetControl<ItemButton>(i);

		iterator.SetItemButton(*game.GetHero().GetInventory()[i],false,opening_from_shop_menu);
		iterator.AddEventOnMouseClick(&Inventory::ItemOnMouseClick,*this);
		iterator.AddControl();
	}

	//Discard Item Button
	ItemButton& discard_item_button = this->CreateControl<ItemButton>();
	discard_item_button.SetDefaultEmptyIcon(ItemIconDiscard);
	discard_item_button.SetItemButton(game.GetHero().GetDiscardItem());
	discard_item_button.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
	discard_item_button.GetItem().SetDescription(game.GetDatabase().GetLanguageText(DiscardItemTextID));
	discard_item_button.AddEventOnMouseClick(&Inventory::DiscardOnMouseClick,*this);
	discard_item_button.AddControl();

	//Silhouette Picture Box
	silhouette_picture_box.SetSprite(game.GetVideo().GetTexture(TextureCommonFileID),91.0f,189.0f,33.0f,67.0f);

	//Inventory Label
	Label& inventory_label = this->CreateControl<Label>();
	inventory_label.SetText(this->GetDefaultFontSmall(),game.GetDatabase().GetLanguageText(InventoryTextID) + ":",Color::Gold);
	inventory_label.AddControl();

	//Atualizar as posições dos controles
	this->PositionUpdate();
}

void Inventory::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Atualizar as posições dos controles
	this->PositionUpdate();

	//Atualizar a mão esquerda corretamente caso ter equipado uma arma de duas mãos (deve ser atualizado aqui para quando for trocar de Menus)
	const size_t inventory_size = game.GetHero().GetInventory().size();
	ItemButton& right_hand = this->GetControl<ItemButton>(inventory_size + EquipmentSlotRightHand);
	ItemButton& left_hand = this->GetControl<ItemButton>(inventory_size + EquipmentSlotLeftHand);
	if (right_hand.GetItem().IsTwoHandedWeapon())
		left_hand.SetItemButton(*game.GetHero().GetEquipments()[EquipmentSlotRightHand]);
	else
		left_hand.SetItemButton(*game.GetHero().GetEquipments()[EquipmentSlotLeftHand]);
}

void Inventory::PositionUpdate()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	const size_t inventory_size = game.GetHero().GetInventory().size();
	const size_t equipments_size = game.GetHero().GetEquipments().size();

	float x = this->position.GetX() + 398.0f;
	float y = this->position.GetY() + 65.0f;

	//Right Hand
	ItemButton& right_hand = this->GetControl<ItemButton>(inventory_size + EquipmentSlotRightHand);
	right_hand.SetPosition(x,y);

	//Left Hand
	x = right_hand.GetX() + 118.0f;
	ItemButton& left_hand = this->GetControl<ItemButton>(inventory_size + EquipmentSlotLeftHand);
	left_hand.SetPosition(x,y);

	//Helm
	x = ((left_hand.GetX() - right_hand.GetX()) / 2.0f) + right_hand.GetX() + (right_hand.GetW() / 2.0f);
	y -= 30.0f;
	ItemButton& helm = this->GetControl<ItemButton>(inventory_size + EquipmentSlotHelm);
	helm.SetPosition(x,y,true);

	//Armor
	y += 66.0f;
	ItemButton& armor = this->GetControl<ItemButton>(inventory_size + EquipmentSlotArmor);
	armor.SetPosition(x,y,true);

	//Gloves
	x = right_hand.GetX() + 18.0f;
	y = right_hand.GetY() + 90.0f;
	ItemButton& gloves = this->GetControl<ItemButton>(inventory_size + EquipmentSlotGloves);
	gloves.SetPosition(x,y);

	//Boots
	x = left_hand.GetX() - 18.0f;
	ItemButton& boots = this->GetControl<ItemButton>(inventory_size + EquipmentSlotBoots);
	boots.SetPosition(x,y);

	//Right Accessory
	x = right_hand.GetX() + 9.0f;
	y = armor.GetY() + 25.0f;
	ItemButton& right_accessory = this->GetControl<ItemButton>(inventory_size + EquipmentSlotRightAccessory);
	right_accessory.SetPosition(x,y);

	//Left Accessory
	x = left_hand.GetX() - 9.0f;
	ItemButton& left_accessory = this->GetControl<ItemButton>(inventory_size + EquipmentSlotLeftAccessory);
	left_accessory.SetPosition(x,y);

	//Inventory
	const float initial_x = right_hand.GetX() + -7.0f;
	const float initial_y = right_accessory.GetY() + right_accessory.GetH() + 120.0f;

	x = initial_x;
	y = initial_y;

	for (size_t i = 0; i < inventory_size; i++)
	{
		ItemButton& iterator = this->GetControl<ItemButton>(i);

		const int mod = i % 5;
		const float item_distance = (iterator.GetW() + 1.0f);

		x = initial_x + (mod * item_distance);
		if ((mod == 0) && (i != 0))
		{
			x = initial_x;
			y += item_distance;
		}

		iterator.SetPosition(x,y);
	}

	//Discard Item Button
	x = boots.GetX() + 25.0f;
	y = boots.GetY() + 55.0f;
	ItemButton& discard_item_button = this->GetControl<ItemButton>(this->GetControlTotal() - InventoryControlAdded + DiscardItemButton);
	discard_item_button.SetPosition(x + (discard_item_button.GetW() / 2.0f),y + (discard_item_button.GetH() / 2.0f),true);

	//Silhouette Picture Box
	PictureBox& silhouette_picture_box = this->GetControl<PictureBox>(this->GetControlTotal() - InventoryControlAdded + SilhouettePictureBox);
	silhouette_picture_box.SetPosition(armor.GetX() + (armor.GetW() / 2.0f),armor.GetY() + (armor.GetH() / 2.0f) + 5.0f,true);

	//Inventory Label
	Label& inventory_label = this->GetControl<Label>(this->GetControlTotal() - InventoryControlAdded + InventoryLabel);
	inventory_label.SetPosition(initial_x,initial_y - inventory_label.GetH());
}

void Inventory::ItemOnMouseClick(Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	static_cast<ItemButton&>(control).ItemOnMouseClick(mouse_button,mouse_x,mouse_y,true);
}

void Inventory::EquipHandOnMouseClick(Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	if (mouse_button == MouseButton::Left)
	{
		const size_t inventory_size = GameState::GetGame<GameRPG>().GetHero().GetInventory().size();

		static_cast<ItemButton&>(control).EquipHand(this->GetControl<ItemButton>(inventory_size + EquipmentSlotRightHand),this->GetControl<ItemButton>(inventory_size + EquipmentSlotLeftHand));
	}
}

void Inventory::EquipHelmOnMouseClick(Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	if (mouse_button == MouseButton::Left)
	{
		GameRPG& game = GameState::GetGame<GameRPG>();

		static_cast<ItemButton&>(control).EquipItem(game.GetDatabase().GetLanguageText(EquipHelmTextID),game.GetHero().GetPickedItem().IsHelm());
	}
}

void Inventory::EquipArmorOnMouseClick(Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	if (mouse_button == MouseButton::Left)
	{
		GameRPG& game = GameState::GetGame<GameRPG>();

		static_cast<ItemButton&>(control).EquipItem(game.GetDatabase().GetLanguageText(EquipArmorTextID),game.GetHero().GetPickedItem().IsArmor());
	}
}

void Inventory::EquipGlovesOnMouseClick(Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	if (mouse_button == MouseButton::Left)
	{
		GameRPG& game = GameState::GetGame<GameRPG>();

		static_cast<ItemButton&>(control).EquipItem(game.GetDatabase().GetLanguageText(EquipGlovesTextID),game.GetHero().GetPickedItem().IsGloves());
	}
}

void Inventory::EquipBootsOnMouseClick(Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	if (mouse_button == MouseButton::Left)
	{
		GameRPG& game = GameState::GetGame<GameRPG>();

		static_cast<ItemButton&>(control).EquipItem(game.GetDatabase().GetLanguageText(EquipBootsTextID),game.GetHero().GetPickedItem().IsBoots());
	}
}

void Inventory::EquipAccessoryOnMouseClick(Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	if (mouse_button == MouseButton::Left)
	{
		GameRPG& game = GameState::GetGame<GameRPG>();

		static_cast<ItemButton&>(control).EquipItem(game.GetDatabase().GetLanguageText(EquipAccessoryTextID),game.GetHero().GetPickedItem().IsAccessory());
	}
}

void Inventory::DiscardOnMouseClick(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	if (mouse_button == MouseButton::Left)
	{
		GameRPG& game = GameState::GetGame<GameRPG>();

		Item& picked_item = game.GetHero().GetPickedItem();

		//Se tiver pego um item e não for do tipo Quest Item então pode removê-lo
		if ((!picked_item.IsEmpty()) && (!picked_item.IsQuestItem()))
		{
			picked_item.Remove();
			game.GetAudio().PlaySoundFromBuffer(SoundDiscardItemFileID);
		}
		else if (picked_item.IsQuestItem())
			game.GetAudio().PlaySoundFromBuffer(SoundErrorFileID);
	}
}
#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H

#include "ColorChanger.h"
#include "TextDynamicZoom.h"
#include "GameRPG.h"

namespace RPG
{
	class ItemButton : public GPL::Button
	{
	private:
		using PointerGetBool = bool (Ability::*)() const;

		//Refer�ncia de um Item
		Item* item;

		//�cone padr�o caso o item for vazio
		ItemIcon default_empty_icon;

		//ID do item mudou ent�o fazer algumas atualiza��es de cores do �cone do item
		ItemID item_id_changed;

		//Se � um item de loja
		bool is_shop_item;

		//Mouse entrou na regi�o do bot�o do item
		bool mouse_entering;

		//Controle para mudar de cor
		bool color_changing;

		//Refer�ncia do objeto do jogo
		static GameRPG* game;

		//Fazendo compras em algum Shop
		static bool shopping;

		//Pointeiro de m�todo para todos os valores para habilidades
		static std::vector<PointerGetBool> pointers_get_bool;

		//Item Buttons que deve ser atualizados ao mesmo tempo
		static std::vector<ItemButton*> item_buttons_to_update;

		//Adicionar informa��o ao exibir o ToolTip do Item Button
		void AddInformation(const std::string& label,const int value,const bool plus = false,const bool percentage = false,const GPL::Color& label_color = GPL::Color::Yellow,const GPL::Color& value_color = GPL::Color::White);

		//Adicionar informa��o ao exibir o ToolTip do Item Button
		void AddInformation(const std::string& label,const std::string& value = "",const GPL::Color& label_color = GPL::Color::Yellow,const GPL::Color& value_color = GPL::Color::White);

		//Verificar se � o bot�o de algum equipamento
		bool IsEquipmentButton() const;

		//Atualizar �cone
		void UpdateIcon();

		//Atualizar dados
		void DataUpdate();

		//Comprar item do bot�o
		bool BuyItem();

		//Vender algum item
		bool SellItem(Item& item);

		//Trocar itens entre o item associado ao bot�o com o item pego pelo Mouse
		bool SwapPickedItem();

		//Evento com o Mouse entrando na regi�o do bot�o do item
		void ItemOnMouseEnter(const GPL::Control& control);

		//Evento com o Mouse saindo da regi�o do bot�o do item
		void ItemOnMouseLeave(const GPL::Control& control);

		//Usar item do tipo Usable
		void ConsumeUsableItem(const float x,const float y);

		//Atualizar dados do controle antes de mostr�-lo
		void Update(const GPL::Input& input,const GPL::Timer& timer) override;

		//Mostrar o controle
		bool Show(const GPL::Input& input,GPL::Video& video,const GPL::Timer& timer) override;

		//Atualizar todos os controles adicionados para serem atualizados
		static void UpdateAllItemButtons();
	public:
		//Construtor
		ItemButton();

		//Alterar Item Button
		void SetItemButton(Item& item,const bool is_shop_item = false,const bool add_item_button_to_update = false);

		//Pegar Item
		Item& GetItem();

		//Alterar Default Empty Icon
		void SetDefaultEmptyIcon(const ItemIcon default_empty_icon);

		//Evento ao clicar em um item
		void ItemOnMouseClick(const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y,const bool can_put_quest_item = false,const bool usable_only = false);

		//Equipar um item
		bool EquipItem(const std::string& empty_item_tooltip,const bool is_correct_slot);

		//Eequipar uma das m�os com algum equipamento
		bool EquipHand(ItemButton& right_hand,ItemButton& left_hand);

		//Alterar Game
		static void SetGame(GameRPG& game);

		//Alterar Shopping
		static void SetShopping(const bool shopping);

		//Limpar a lista de Item Buttons para serem atualizados
		static void ClearAllItemButtons();
	};
}

#endif
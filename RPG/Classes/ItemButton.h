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

		//Referência de um Item
		Item* item;

		//Ícone padrão caso o item for vazio
		ItemIcon default_empty_icon;

		//ID do item mudou então fazer algumas atualizações de cores do ícone do item
		ItemID item_id_changed;

		//Se é um item de loja
		bool is_shop_item;

		//Mouse entrou na região do botão do item
		bool mouse_entering;

		//Controle para mudar de cor
		bool color_changing;

		//Referência do objeto do jogo
		static GameRPG* game;

		//Fazendo compras em algum Shop
		static bool shopping;

		//Pointeiro de método para todos os valores para habilidades
		static std::vector<PointerGetBool> pointers_get_bool;

		//Item Buttons que deve ser atualizados ao mesmo tempo
		static std::vector<ItemButton*> item_buttons_to_update;

		//Adicionar informação ao exibir o ToolTip do Item Button
		void AddInformation(const std::string& label,const int value,const bool plus = false,const bool percentage = false,const GPL::Color& label_color = GPL::Color::Yellow,const GPL::Color& value_color = GPL::Color::White);

		//Adicionar informação ao exibir o ToolTip do Item Button
		void AddInformation(const std::string& label,const std::string& value = "",const GPL::Color& label_color = GPL::Color::Yellow,const GPL::Color& value_color = GPL::Color::White);

		//Verificar se é o botão de algum equipamento
		bool IsEquipmentButton() const;

		//Atualizar ícone
		void UpdateIcon();

		//Atualizar dados
		void DataUpdate();

		//Comprar item do botão
		bool BuyItem();

		//Vender algum item
		bool SellItem(Item& item);

		//Trocar itens entre o item associado ao botão com o item pego pelo Mouse
		bool SwapPickedItem();

		//Evento com o Mouse entrando na região do botão do item
		void ItemOnMouseEnter(const GPL::Control& control);

		//Evento com o Mouse saindo da região do botão do item
		void ItemOnMouseLeave(const GPL::Control& control);

		//Usar item do tipo Usable
		void ConsumeUsableItem(const float x,const float y);

		//Atualizar dados do controle antes de mostrá-lo
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

		//Eequipar uma das mãos com algum equipamento
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
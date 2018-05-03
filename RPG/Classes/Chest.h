#ifndef CHEST_H
#define CHEST_H

#include "BaseChest.h"

namespace RPG
{
	class Chest : public BaseChest
	{
	private:
		//Itens do baú
		std::vector<std::unique_ptr<Item>> items;

		//Pegar Menu Text
		virtual const std::string& GetMenuText() const;

		//Verificar se é o baú privado
		virtual bool IsPrivateChest() const;
	public:
		//Construtor
		Chest(const ChestType chest_type = ChestSmall);

		//Adicionar item
		void AddItem(const Item& item);

		//Adicionar item
		void AddItem(const ItemID item_id);

		//Adicionar itens
		void AddItems(const std::vector<std::unique_ptr<Item>>& items);

		//Adicionar itens
		void AddItems(const std::vector<ItemID>& items);

		//Pegar Items
		std::vector<std::unique_ptr<Item>>& GetItems() override;
	};
}

#endif
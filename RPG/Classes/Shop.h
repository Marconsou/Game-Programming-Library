#ifndef SHOP_H
#define SHOP_H

#include "Database.h"

namespace RPG
{
	class Shop
	{
	private:
		//ID do texto do nome do Shop
		const LanguageTextID text_id;

		//Itens para ser vendido
		std::vector<std::unique_ptr<Item>> items;
	public:
		//Construtor
		Shop(const LanguageTextID text_id);

		//Pegar Text ID
		LanguageTextID GetTextID() const;

		//Pegar Items
		std::vector<std::unique_ptr<Item>>& GetItems();

		//Adicionar item para venda
		void AddItem(const Item& item);
	};
}

#endif
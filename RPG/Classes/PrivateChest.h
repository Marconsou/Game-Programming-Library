#ifndef PRIVATECHEST_H
#define PRIVATECHEST_H

#include "BaseChest.h"

namespace RPG
{
	class PrivateChest : public BaseChest
	{
	private:
		//Referência dos items do baú privado do herói
		std::vector<std::unique_ptr<Item>>* items;

		//Pegar Items
		std::vector<std::unique_ptr<Item>>& GetItems() override;

		//Pegar Menu Text
		virtual const std::string& GetMenuText() const;

		//Verificar se é o baú privado
		virtual bool IsPrivateChest() const;
	public:
		//Construtor
		PrivateChest(const ChestType chest_type);

		//Alterar Items
		void SetItems(std::vector<std::unique_ptr<Item>>& items);
	};
}

#endif
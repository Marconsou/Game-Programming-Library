#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "StatsBasic.h"
#include "Elemental.h"
#include "StatusNegative.h"
#include "Ability.h"

namespace RPG
{
	//Ícones dos itens
	enum ItemIcon
	{
		ItemIconEmpty = -10,
		ItemIconRightHand,
		ItemIconLeftHand,
		ItemIconHelm,
		ItemIconArmor,
		ItemIconGloves,
		ItemIconBoots,
		ItemIconRightAccessory,
		ItemIconLeftAccessory,
		ItemIconDiscard,
		ItemIconValidItem,
	};

	//Classe dos itens
	enum ItemClass
	{
		ItemClassEmpty = 0,
		ItemClassUsable,
		ItemClassQuestItem,
		ItemClassDagger,
		ItemClassSword,
		ItemClassAxe,
		ItemClassMace,
		ItemClassStaff,
		ItemClassSpear,
		ItemClassBow,
		ItemClassShield,
		ItemClassHelm,
		ItemClassArmor,
		ItemClassGloves,
		ItemClassBoots,
		ItemClassAccessory,
	};

	//ID dos itens
	enum ItemID
	{
		NullItemID = -1,

		//Usables
		PhysicalRecoveryLevel1,
		PhysicalRecoveryLevel2,
		PhysicalRecoveryLevel3,
		PhysicalRecoveryLevel4,
		PhysicalRecoveryLevel5,
		MagicalRecoveryLevel1,
		MagicalRecoveryLevel2,
		MagicalRecoveryLevel3,
		MagicalRecoveryLevel4,
		MagicalRecoveryLevel5,

		//Quest Items
		Letter,

		//Swords
		ShortSword,
		BroadSword,
		LongSword,

		//Shields
		Buckler,

		//Helms
		Cap,

		//Armors
		Cloth,

		//Gloves
		LeatherGloves,

		//Boots
		LeatherBoots,

		//Accessories
		CommonRing,

		ItemMax,
	};

	class Item
	{
	private:
		//Referência da origem do item para sincronizar alguns dados de texto quando trocar de idioma
		const Item* source_item;

		//Nome
		std::string name;

		//Descrição
		std::string description;

		//Ícone
		ItemIcon icon;

		//Classe
		ItemClass class_type;

		//ID
		ItemID id;

		//Preço de venda
		int sell_price;

		//Chance de encontrar o item
		int find_chance;

		//Nível exigente
		int required_level;

		//Peso que será reduzido na velocidade
		int weight;

		//Quantidade de mãos para equipar se necessário
		int hands;

		//Atributos básicos
		StatsBasic stats;

		//Dano elemental
		Elemental elemental_damage;

		//Resistência elemental
		Elemental elemental_resist;

		//Absorção elemental
		Elemental elemental_absorb;

		//Mudança de estado para ataque
		StatusNegative status_attack;

		//Mudança de estado para defesa
		StatusNegative status_defense;

		//Recuperação de estado
		StatusNegative status_negative_recovery;

		//Habilidades gerais
		Ability ability;

		Item(const Item&) = delete;
		Item& operator=(const Item&) = default;
	public:
		//Construtor
		Item(const ItemIcon icon = ItemIconEmpty);

		//Alterar Name
		void SetName(const std::string& name);

		//Pegar Name
		const std::string& GetName() const;

		//Alterar Description
		void SetDescription(const std::string& description);

		//Pegar Description
		const std::string& GetDescription() const;

		//Alterar Icon
		void SetIcon(const ItemIcon icon);

		//Pegar Icon
		ItemIcon GetIcon() const;

		//Alterar Class Type
		void SetClassType(const ItemClass class_type);

		//Pegar Class Type
		ItemClass GetClassType() const;

		//Alterar ID
		void SetID(const ItemID id);

		//Pegar ID
		ItemID GetID() const;

		//Alterar Sell Price
		void SetSellPrice(const int sell_price);

		//Pegar Sell Price
		int GetSellPrice() const;

		//Pegar Buy Price
		int GetBuyPrice() const;

		//Alterar Find Chance
		void SetFindChance(const int find_chance);

		//Pegar Find Chance
		int GetFindChance() const;

		//Alterar Required Level
		void SetRequiredLevel(const int required_level);

		//Pegar Required Level
		int GetRequiredLevel() const;

		//Alterar Weight
		void SetWeight(const int weight);

		//Pegar Weight
		int GetWeight() const;

		//Alterar Hands
		void SetHands(const int hands);

		//Pegar Hands
		int GetHands() const;

		//Pegar Stats
		StatsBasic& GetStats();

		//Pegar Elemental Damage
		Elemental& GetElementalDamage();

		//Pegar Elemental Resist
		Elemental& GetElementalResist();

		//Pegar Elemental Absorb
		Elemental& GetElementalAbsorb();

		//Pegar Status Attack
		StatusNegative& GetStatusAttack();

		//Pegar Status Defense
		StatusNegative& GetStatusDefense();

		//Pegar Status Negative Recovery
		StatusNegative& GetStatusNegativeRecovery();

		//Pegar Ability
		Ability& GetAbility();

		//Trocar o item copiando seus dados
		void Swap(Item& item);

		//Receber o item e remover o outro
		void Receive(Item& item);

		//Copiar o item e salvar a origem do item
		void Copy(const Item& item);

		//Remover item e colocar como vazio
		void Remove();

		//Verificar se o item esta vazio
		bool IsEmpty() const;

		//Verificar se o item é do tipo Usable
		bool IsUsable() const;

		//Verificar se o item é do tipo Quest Item
		bool IsQuestItem() const;

		//Verificar se o item é um equipamento
		bool IsEquipment() const;

		//Verificar se o item é do tipo Dagger
		bool IsDagger() const;

		//Verificar se o item é do tipo Sword
		bool IsSword() const;

		//Verificar se o item é do tipo Axe
		bool IsAxe() const;

		//Verificar se o item é do tipo Mace
		bool IsMace() const;

		//Verificar se o item é do tipo Staff
		bool IsStaff() const;

		//Verificar se o item é do tipo Spear
		bool IsSpear() const;

		//Verificar se o item é do tipo Bow
		bool IsBow() const;

		//Verificar se o item é uma arma
		bool IsWeapon() const;

		//Verificar se o item é do tipo Shield
		bool IsShield() const;

		//Verificar se o item é do tipo Helm
		bool IsHelm() const;

		//Verificar se o item é do tipo Armor
		bool IsArmor() const;

		//Verificar se o item é do tipo Gloves
		bool IsGloves() const;

		//Verificar se o item é do tipo Boots
		bool IsBoots() const;

		//Verificar se o item é do tipo Accessory
		bool IsAccessory() const;

		//Se é uma arma de uma mão
		bool IsOneHandedWeapon() const;

		//Se é uma arma de duas mãos
		bool IsTwoHandedWeapon() const;

		//Se é uma arma de combate corpo a corpo
		bool IsMeleeWeapon() const;

		//Se é uma arma de longo alcance
		bool IsMissileWeapon() const;

		//Verificar as exigências para usar ou equipar o item
		bool CheckRequirement(const int level) const;
	};
}

#endif
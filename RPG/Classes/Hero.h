#ifndef HERO_H
#define HERO_H

#include "Achievement.h"
#include "Quest.h"
#include "Stats.h"
#include "Skill.h"
#include "MapDataState.h"
#include "Character.h"

namespace RPG
{
	//Espa�o para os equipamentos
	enum EquipmentSlot
	{
		EquipmentSlotRightHand = 0,
		EquipmentSlotLeftHand,
		EquipmentSlotHelm,
		EquipmentSlotArmor,
		EquipmentSlotGloves,
		EquipmentSlotBoots,
		EquipmentSlotRightAccessory,
		EquipmentSlotLeftAccessory,
	};

	//Tipo de movimento do her�i
	enum HeroMovement
	{
		HeroMovementSpeedSlow = 0,
		HeroMovementSpeedNormal,
		HeroMovementSpeedFast,
	};

	//Classe do her�i
	enum HeroClass
	{
		HeroClassWarrior = 0,
		HeroClassMage,
	};

	class Hero
	{
	private:
		//Pode usar duas armas ao mesmo tempo
		const bool dual_weapon;

		//Pontos para aumentar os atributos
		int ap;

		//Pontos para aumentar as habilidades
		int sp;

		//For�a
		int strength;

		//Intelig�ncia
		int intelligence;

		//Agilidade
		int agility;

		//Experi�ncia atual
		int exp;

		//Experi�ncia para o pr�ximo n�vel
		int next_level;

		//Dano f�sico m�nimo secund�rio
		int physical_damage_min_secondary;

		//Dano f�sico m�ximo secund�rio
		int physical_damage_max_secondary;

		//Chance de acertar secund�rio
		int hit_secondary;

		//Chance de causar dano cr�tico secund�rio
		int critical_strike_secondary;

		//Chance de atacar mais uma vez secund�rio
		int quick_strike_secondary;

		//Valor em % do dano para roubar HP secund�rio
		int hp_steal_secondary;

		//Valor em % do dano para roubar MP secund�rio
		int mp_steal_secondary;

		//Bonus para HP Max por ponto em Strength
		const int strength_hp_max_up;

		//Bonus para MP Max por ponto em Intelligence
		const int intelligence_mp_max_up;

		//Bonus base para Hit
		const int base_hit;

		//Bonus para Hit com base em Agility
		const int agility_hit;

		//Bonus base para Evade
		const int base_evade;

		//Bonus para Evade com base em Agility
		const int agility_evade;

		//Speed com base em Agility
		const int agility_speed;

		//Bonus base para Critical Strike
		const int base_critical_strike;

		//Tipo de movimento
		HeroMovement movement;

		//Dano Elemental secund�rio
		Elemental elemental_damage_secondary;

		//Mudan�a de estado para ataque secund�rio
		StatusNegative status_attack_secondary;

		//Todos os atributos e estat�sticas
		Stats stats;

		//Habilidades gerais
		Ability ability;

		//�cone do item pego
		GPL::Sprite picked_item_icon;

		//Item pego pelo cursor do Mouse
		Item picked_item;

		//Descartar item
		Item discard_item;

		//Invent�rio
		std::vector<std::unique_ptr<Item>> inventory;

		//Equipamentos
		std::vector<std::unique_ptr<Item>> equipments;

		//Itens de batalha
		std::vector<std::unique_ptr<Item>> battle_items;

		//Itens do ba� privado
		std::vector<std::unique_ptr<Item>> private_chest;

		//Habilidades
		std::vector<std::unique_ptr<Skill>> skills;

		//Objetivos principais
		std::vector<Quest> main_quests;

		//Objetivos opcionais
		std::vector<Quest> optional_quests;

		//Conquistas
		std::vector<Achievement> achievements;

		//Dados de todos os mapas salvos
		MapDataState map_data_state;

		//Personagem
		std::shared_ptr<Character> character;

		//Tempo de jogo
		GPL::Timer play_time;

		//Calcular a experi�ncia com base no n�vel
		int CalculateExp(const int level) const;

		//Verificar se houve um aumento de n�vel e aument�-lo
		bool CheckAndLevelUp();

		//Verificar o valor dos equipamentos
		template<class Type> bool CheckEquipmentValue(Type& (Item::*PointerGetObject)(),bool (Type::*PointerGetBool)() const) const
		{
			for (size_t i = 0; i < this->equipments.size(); i++)
			{
				if (((this->equipments[i].get()->*PointerGetObject)().*PointerGetBool)())
					return true;
			}
			return false;
		}

		//Somar o valor dos equipamentos
		template<class Type> int AddEquipmentValue(Type& (Item::*PointerGetObject)(),int (Type::*PointerGetInt)() const,const bool using_percentage_max = false,const int base_value = 0) const
		{
			int total = base_value;
			for (size_t i = 0; i < this->equipments.size(); i++)
				total += ((this->equipments[i].get()->*PointerGetObject)().*PointerGetInt)();
			return (using_percentage_max) ? min(total,100) : total;
		}

		//Calcular os valores considerados de ataque
		template<class Type> void CalculateOffensiveStats(Type& (Item::*PointerGetObject)(),int (Type::*PointerGetInt)() const,int& value,int& value_secondary,const bool using_percentage_max = false,const int base_value = 0,const int shared_value = 0)
		{
			const int total = this->AddEquipmentValue(PointerGetObject,PointerGetInt,false,shared_value);
			const int right_hand_value = ((this->equipments[EquipmentSlotRightHand].get()->*PointerGetObject)().*PointerGetInt)();
			const int left_hand_value = ((this->equipments[EquipmentSlotLeftHand].get()->*PointerGetObject)().*PointerGetInt)();
			const int others_equipments_shared = (total - right_hand_value - left_hand_value) / 2;

			if (!this->TwoHandsAttack())
			{
				value = base_value + total;
				value_secondary = 0;
			}
			else
			{
				value = base_value + others_equipments_shared + right_hand_value;
				value_secondary = base_value + others_equipments_shared + left_hand_value;
			}

			if (using_percentage_max)
			{
				value = min(value,100);
				value_secondary = min(value_secondary,100);
			}
		}
	protected:
		//Atualizar as estat�sticas �nicas da classe do her�i
		virtual void UniqueStatsUpdate() = 0;
	public:
		//Construtor
		Hero(const int strength_hp_max_up,const int intelligence_mp_max_up,const int base_hit,const int agility_hit,const int base_evade,const int agility_evade,const int agility_speed,const int base_critical_strike,const bool dual_weapon);

		//Destrutor
		virtual ~Hero();

		//Pegar Dual Weapon
		bool GetDualWeapon() const;

		//Pegar AP
		int GetAP() const;

		//Pegar SP
		int GetSP() const;

		//Pegar Strength
		int GetStrength() const;

		//Pegar Intelligence
		int GetIntelligence() const;

		//Pegar Agility
		int GetAgility() const;

		//Alterar Exp
		void SetExp(const int exp);

		//Pegar Exp
		int GetExp() const;

		//Alterar Next Level
		void SetNextLevel(const int next_level);

		//Pegar Next Level
		int GetNextLevel() const;

		//Alterar Physical Damage Min Secondary
		void SetPhysicalDamageMinSecondary(const int physical_damage_min_secondary);

		//Pegar Physical Damage Min Secondary
		int GetPhysicalDamageMinSecondary() const;

		//Alterar Physical Damage Max Secondary
		void SetPhysicalDamageMaxSecondary(const int physical_damage_max_secondary);

		//Pegar Physical Damage Max Secondary
		int GetPhysicalDamageMaxSecondary() const;

		//Alterar Hit Secondary
		void SetHitSecondary(const int hit_secondary);

		//Pegar Hit Secondary
		int GetHitSecondary() const;

		//Alterar Critical Strike Secondary
		void SetCriticalStrikeSecondary(const int critical_strike_secondary);

		//Pegar Critical Strike Secondary
		int GetCriticalStrikeSecondary() const;

		//Alterar Quick Strike Secondary
		void SetQuickStrikeSecondary(const int quick_strike_secondary);

		//Pegar Quick Strike Secondary
		int GetQuickStrikeSecondary() const;

		//Alterar HP Steal Secondary
		void SetHPStealSecondary(const int hp_steal_secondary);

		//Pegar HP Steal Secondary
		int GetHPStealSecondary() const;

		//Alterar MP Steal Secondary
		void SetMPStealSecondary(const int mp_steal_secondary);

		//Pegar MP Steal Secondary
		int GetMPStealSecondary() const;

		//Pegar Movement
		HeroMovement GetMovement() const;

		//Pegar Elemental Damage Secondary
		Elemental& GetElementalDamageSecondary();

		//Pegar Status Attack Secondary
		StatusNegative& GetStatusAttackSecondary();

		//Pegar Stats
		Stats& GetStats();

		//Pegar Ability
		Ability& GetAbility();

		//Pegar Picked Item Icon
		GPL::Sprite& GetPickedItemIcon();

		//Pegar Picked Item
		Item& GetPickedItem();

		//Pegar Discard Item
		Item& GetDiscardItem();

		//Pegar Inventory
		std::vector<std::unique_ptr<Item>>& GetInventory();

		//Pegar Equipments
		std::vector<std::unique_ptr<Item>>& GetEquipments();

		//Pegar Battle Items
		std::vector<std::unique_ptr<Item>>& GetBattleItems();

		//Pegar Private Chest
		std::vector<std::unique_ptr<Item>>& GetPrivateChest();

		//Pegar Skills
		std::vector<std::unique_ptr<Skill>>& GetSkills();

		//Pegar Main Quests
		std::vector<Quest>& GetMainQuests();

		//Pegar Optional Quests
		std::vector<Quest>& GetOptionalQuests();

		//Pegar Achievements
		std::vector<Achievement>& GetAchievements();

		//Pegar Map Data State
		MapDataState& GetMapDataState();

		//Pegar Character
		std::shared_ptr<Character>& GetCharacter();

		//Pegar Play Time
		GPL::Timer& GetPlayTime();

		//Adicionar forca
		void AddStrength();

		//Adicionar intelig�ncia
		void AddIntelligence();

		//Adicionar agilidade
		void AddAgility();

		//Gastar ponto de habilidade
		void SpendSP();

		//Calcular a experi�ncia do n�vel anterior
		int CalculatePreviousExp() const;

		//Aumentar n�vel
		void LevelUp();

		//Adicionar item no invent�rio
		bool AddItemToInventory(const Item& item);

		//Adicionar item nos itens de batalha
		bool AddItemToBattleItems(const Item& item);

		//Verificando se o invent�rio esta cheio ou n�o
		bool InventoryIsNotFull() const;

		//Verificar se o her�i alcan�ou os requerimentos do item para usar
		bool ItemRequirementNotMet(const Item& item) const;

		//Verificar se o her�i alcan�ou os requerimentos do item pego pelo Mouse para usar
		bool PickedItemRequirementNotMet() const;

		//Verificar se o her�i alcan�ou os requerimentos da habilidade
		bool SkillRequirementNotMet(const Skill& skill) const;

		//Verificar se tem Gold suficiente para comprar o item
		bool GoldEnoughToBuy(const Item& item) const;

		//Comprar o item de algum Shop
		bool BuyItemFromShop(const Item& item);

		//Vender o item para algum Shop
		bool SellItemToShop(Item& item);

		//Verificar se pode equipar o item pego pelo Mouse na m�o
		bool CanEquipPickedItemOnHand(const bool is_left_hand) const;

		//Verificar se vai utilizar as duas m�os separadamente para o ataque
		bool TwoHandsAttack() const;

		//Verificar se � da classe Warrior
		bool IsWarrior() const;

		//Verificar se � da classe Mage
		bool IsMage() const;

		//Atualizar todos os dados do her�i
		void CharacterStatsUpdate();

		//Atualizar o estado do movimento
		void HeroMovementStatsUpdate(int movement = HeroMovementSpeedNormal);

		//Pegar Class Type
		virtual HeroClass GetClassType() const = 0;
	};
}

#endif
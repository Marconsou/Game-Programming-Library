#include "Database.h"

using namespace std;
using namespace GPL;
using namespace RPG;

void Database::LoadDatabase(const FileID language_id)
{
	this->items.resize(ItemMax);
	this->main_quests.resize(MainQuestMax);
	this->optional_quests.resize(OptionalQuestMax);
	this->achievements.resize(AchievementMax);
	this->warrior_skill_levels.resize(1,vector<SkillLevel>(10));
	//this->mage_skill_levels.resize(1,vector<SkillLevel>(10));

	this->LoadLanguageTexts(language_id);
	this->LoadItems();
	this->LoadQuests();
	this->LoadAchievements();
	this->LoadSkillLevels();
}

const string& Database::GetLanguageText(const LanguageTextID language_text_id) const
{
	return this->language_texts[language_text_id];
}

const Item& Database::GetItems(const ItemID item_id) const
{
	return *this->items[item_id].get();
}

const vector<Quest>& Database::GetMainQuests() const
{
	return this->main_quests;
}

const vector<Quest>& Database::GetOptionalQuests() const
{
	return this->optional_quests;
}

const vector<Achievement>& Database::GetAchievements() const
{
	return this->achievements;
}

const vector<vector<SkillLevel>>& Database::GetWarriorSkillLevel() const
{
	return this->warrior_skill_levels;
}

const vector<vector<SkillLevel>>& Database::GetMageSkillLevel() const
{
	return this->mage_skill_levels;
}

void Database::LoadLanguageTexts(const FileID language_id)
{
	//Lendo o arquivo
	unique_ptr<char[]> memory_buffer;
	const size_t size = ResourceFile::Read(language_id,memory_buffer);
	if (!size)
		Log::Error(__FUNCTION__,"Read");

	//Separando os textos por linhas
	Format::Split(this->language_texts,string(memory_buffer.get()),"\r\n");
}

void Database::LoadItems()
{
	for (size_t i = 0; i < this->items.size(); i++)
	{
		if (!this->items[i])
			this->items[i] = make_unique<Item>();
	}

	//Usables
	int index = 0;
	int start_index = 0;
	this->items[index]->SetName(this->language_texts[PhysicalRecoveryLevel1TextID]);
	this->items[index]->GetStats().SetHP(15);
	this->items[index]->SetSellPrice(5);
	this->items[index]->SetDescription(this->language_texts[RecoveryDescriptionTextID] + " " + Convert::NumberToString(this->items[index]->GetStats().GetHP()) + "." );
	index++;

	this->items[index]->SetName(this->language_texts[PhysicalRecoveryLevel2TextID]);
	this->items[index]->GetStats().SetHP(30);
	this->items[index]->SetSellPrice(15);
	this->items[index]->SetDescription(this->language_texts[RecoveryDescriptionTextID] + " " + Convert::NumberToString(this->items[index]->GetStats().GetHP()) + "." );
	index++;

	this->items[index]->SetName(this->language_texts[PhysicalRecoveryLevel3TextID]);
	this->items[index]->GetStats().SetHP(55);
	this->items[index]->SetSellPrice(25);
	this->items[index]->SetDescription(this->language_texts[RecoveryDescriptionTextID] + " " + Convert::NumberToString(this->items[index]->GetStats().GetHP()) + "." );
	index++;

	this->items[index]->SetName(this->language_texts[PhysicalRecoveryLevel4TextID]);
	this->items[index]->GetStats().SetHP(75);
	this->items[index]->SetSellPrice(35);
	this->items[index]->SetDescription(this->language_texts[RecoveryDescriptionTextID] + " " + Convert::NumberToString(this->items[index]->GetStats().GetHP()) + "." );
	index++;

	this->items[index]->SetName(this->language_texts[PhysicalRecoveryLevel5TextID]);
	this->items[index]->GetStats().SetHP(125);
	this->items[index]->SetSellPrice(45);
	this->items[index]->SetDescription(this->language_texts[RecoveryDescriptionTextID] + " " + Convert::NumberToString(this->items[index]->GetStats().GetHP()) + "." );
	index++;

	this->items[index]->SetName(this->language_texts[MagicalRecoveryLevel1TextID]);
	this->items[index]->GetStats().SetMP(5);
	this->items[index]->SetSellPrice(15);
	this->items[index]->SetDescription(this->language_texts[RecoveryDescriptionTextID] + " " + Convert::NumberToString(this->items[index]->GetStats().GetMP()) + "." );
	index++;	

	this->items[index]->SetName(this->language_texts[MagicalRecoveryLevel2TextID]);
	this->items[index]->GetStats().SetMP(15);
	this->items[index]->SetSellPrice(30);
	this->items[index]->SetDescription(this->language_texts[RecoveryDescriptionTextID] + " " + Convert::NumberToString(this->items[index]->GetStats().GetMP()) + "." );
	index++;

	this->items[index]->SetName(this->language_texts[MagicalRecoveryLevel3TextID]);
	this->items[index]->GetStats().SetMP(25);
	this->items[index]->SetSellPrice(50);
	this->items[index]->SetDescription(this->language_texts[RecoveryDescriptionTextID] + " " + Convert::NumberToString(this->items[index]->GetStats().GetMP()) + "." );
	index++;

	this->items[index]->SetName(this->language_texts[MagicalRecoveryLevel4TextID]);
	this->items[index]->GetStats().SetMP(40);
	this->items[index]->SetSellPrice(60);
	this->items[index]->SetDescription(this->language_texts[RecoveryDescriptionTextID] + " " + Convert::NumberToString(this->items[index]->GetStats().GetMP()) + "." );
	index++;

	this->items[index]->SetName(this->language_texts[MagicalRecoveryLevel5TextID]);
	this->items[index]->GetStats().SetMP(65);
	this->items[index]->SetSellPrice(90);
	this->items[index]->SetDescription(this->language_texts[RecoveryDescriptionTextID] + " " + Convert::NumberToString(this->items[index]->GetStats().GetMP()) + "." );
	index++;

	for (int i = start_index; i < index; i++)
	{
		Item& iterator = *this->items[i];

		iterator.SetIcon(static_cast<ItemIcon>(i - start_index));
		iterator.SetClassType(ItemClassUsable);
	}

	//Quest Items
	start_index = index;
	this->items[index]->SetName(this->language_texts[LetterTextID]);
	this->items[index]->SetDescription(this->language_texts[LetterDescriptionTextID]);
	index++;

	for (int i = start_index; i < index; i++)
	{
		Item& iterator = *this->items[i];

		iterator.SetIcon(static_cast<ItemIcon>(i - start_index));
		iterator.SetClassType(ItemClassQuestItem);
	}

	//Swords
	start_index = index;
	this->items[index]->SetName(this->language_texts[ShortSwordTextID]);
	this->items[index]->GetStats().SetPhysicalDamageMin(98);
	this->items[index]->GetStats().SetPhysicalDamageMax(108);
	this->items[index]->GetElementalDamage().SetFire(5);
	this->items[index]->GetElementalDamage().SetIce(56);
	this->items[index]->GetStatusAttack().SetTiredness(11);
	this->items[index]->GetStatusAttack().SetSlowness(1231);
	this->items[index]->SetSellPrice(256);
	this->items[index]->SetHands(1);
	this->items[index]->SetWeight(2);
	this->items[index]->GetStats().SetHit(26);
	this->items[index]->GetStats().SetHPSteal(20);
	this->items[index]->GetStats().SetMPSteal(10);
	index++;

	this->items[index]->SetName(this->language_texts[BroadSwordTextID]);
	this->items[index]->GetStats().SetPhysicalDamageMin(5);
	this->items[index]->GetStats().SetPhysicalDamageMax(11);
	this->items[index]->GetStats().SetMagicalDamageMin(45);
	this->items[index]->GetStats().SetMagicalDamageMax(67);
	this->items[index]->GetElementalDamage().SetFire(3);
	this->items[index]->GetElementalDamage().SetIce(100);
	this->items[index]->GetElementalDamage().SetLightning(17);
	this->items[index]->GetStatusAttack().SetTiredness(13);
	this->items[index]->GetStats().SetQuickStrike(101);
	this->items[index]->SetHands(1);
	this->items[index]->SetSellPrice(26);
	this->items[index]->GetStats().SetQuickStrike(7);
	this->items[index]->SetRequiredLevel(11);
	index++;

	this->items[index]->SetName(this->language_texts[LongSwordTextID]);
	this->items[index]->GetStats().SetPhysicalDamageMin(13);
	this->items[index]->GetStats().SetPhysicalDamageMax(25);
	this->items[index]->GetStats().SetHPRegen(123);
	this->items[index]->SetSellPrice(3);
	this->items[index]->SetHands(2);
	this->items[index]->GetAbility().SetAnalyzer(true);
	this->items[index]->GetAbility().SetTrainer(true);
	this->items[index]->GetAbility().SetBounty(true);
	this->items[index]->GetAbility().SetCustomer(true);
	this->items[index]->GetAbility().SetCoward(true);
	this->items[index]->GetAbility().SetBrave(true);
	this->items[index]->GetAbility().SetRunner(true);
	this->items[index]->GetAbility().SetSkinSlicer(true);
	this->items[index]->GetAbility().SetBoneCrusher(true);
	this->items[index]->GetAbility().SetShellDriller(true);
	this->items[index]->GetAbility().SetHumanEater(true);
	this->items[index]->GetAbility().SetBeastKiller(true);
	this->items[index]->GetAbility().SetUndeadPurifier(true);
	this->items[index]->GetAbility().SetDemonHunter(true);
	this->items[index]->GetAbility().SetDragonSlayer(true);
	index++;

	for (int i = start_index; i < index; i++)
	{
		Item& iterator = *this->items[i];

		iterator.SetIcon(static_cast<ItemIcon>(i - start_index));
		iterator.SetClassType(ItemClassSword);
	}

	//Shields
	start_index = index;
	this->items[index]->SetName(this->language_texts[BucklerTextID]);
	this->items[index]->GetStats().SetPhysicalResist(256);
	this->items[index]->GetStats().SetHPMax(4);
	index++;

	for (int i = start_index; i < index; i++)
	{
		Item& iterator = *this->items[i];

		iterator.SetIcon(static_cast<ItemIcon>(i - start_index));
		iterator.SetClassType(ItemClassShield);
	}

	//Helms
	start_index = index;
	this->items[index]->SetName(this->language_texts[CapTextID]);
	this->items[index]->GetStats().SetPhysicalResist(1);
	this->items[index]->GetStats().SetHPMax(3);
	this->items[index]->GetStats().SetMPMax(2);
	this->items[index]->GetElementalResist().SetIce(4);
	this->items[index]->GetElementalAbsorb().SetDark(6);
	this->items[index]->GetStatusDefense().SetHeadache(5);
	index++;

	for (int i = start_index; i < index; i++)
	{
		Item& iterator = *this->items[i];

		iterator.SetIcon(static_cast<ItemIcon>(i - start_index));
		iterator.SetClassType(ItemClassHelm);
	}

	//Armors
	start_index = index;
	this->items[index]->SetName(this->language_texts[ClothTextID]);
	this->items[index]->GetStats().SetPhysicalResist(5);
	index++;

	for (int i = start_index; i < index; i++)
	{
		Item& iterator = *this->items[i];

		iterator.SetIcon(static_cast<ItemIcon>(i - start_index));
		iterator.SetClassType(ItemClassArmor);
	}

	//Gloves
	start_index = index;
	this->items[index]->SetName(this->language_texts[LeatherGlovesTextID]);
	this->items[index]->GetStats().SetPhysicalResist(2);
	index++;

	for (int i = start_index; i < index; i++)
	{
		Item& iterator = *this->items[i];

		iterator.SetIcon(static_cast<ItemIcon>(i - start_index));
		iterator.SetClassType(ItemClassGloves);
	}

	//Boots
	start_index = index;
	this->items[index]->SetName(this->language_texts[LeatherBootsTextID]);
	this->items[index]->GetStats().SetPhysicalResist(3);
	this->items[index]->GetAbility().SetRunner(true);
	index++;

	for (int i = start_index; i < index; i++)
	{
		Item& iterator = *this->items[i];

		iterator.SetIcon(static_cast<ItemIcon>(i - start_index));
		iterator.SetClassType(ItemClassBoots);
	}

	//Accessories
	start_index = index;
	this->items[index]->SetName(this->language_texts[CommonRingTextID]);
	this->items[index]->GetStats().SetPhysicalResist(4);
	index++;

	for (int i = start_index; i < index; i++)
	{
		Item& iterator = *this->items[i];

		iterator.SetIcon(static_cast<ItemIcon>(i - start_index));
		iterator.SetClassType(ItemClassAccessory);
	}

	//IDs
	for (size_t i = 0; i < this->items.size(); i++)
		this->items[i]->SetID(static_cast<ItemID>(i));
}

void Database::LoadQuests()
{
	//Main Quests
	//this->main_quests[MainQuest0].GetValues().push_back(5);
	//this->main_quests[MainQuest0].GetValues().push_back(9);

	//Optional Quests
	this->optional_quests[OptionalQuest0].GetValues().push_back(3000);
	this->optional_quests[OptionalQuest0].GetValues().push_back(6000);
}

void Database::LoadAchievements()
{

}

void Database::LoadSkillLevels()
{
	//Warrior Skill Levels
	int index = 0;
	for (size_t i = 0; i < this->warrior_skill_levels[index].size(); i++)
	{
		SkillLevel& iterator = this->warrior_skill_levels[index][i];

		iterator.SetPhysicalDamagePercentage((i + 1) * 5);
		iterator.GetStatsBasic().SetCriticalStrike(i + 1);
	}
	index++;

	//Mage Skill Levels
	index = 0;
}
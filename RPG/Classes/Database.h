#ifndef DATABASE_H
#define DATABASE_H

#include "Convert.h"
#include "Format.h"
#include "Log.h"
#include "ResourceFile.h"
#include "Quest.h"
#include "Achievement.h"
#include "SkillLevel.h"
#include "Item.h"
#include "Main.h"

namespace RPG
{
	//Índices dos textos da língua
	enum LanguageTextID
	{
		//General
		ConfirmTextID = 0,
		DefaultTextID,
		BackTextID,
		OffTextID,
		OnTextID,
		SlowTextID,
		NormalTextID,
		FastTextID,

		//Main Menu
		NewGameMenuButtonTextID,
		LoadGameMenuButtonTextID,
		OptionsMenuButtonTextID,
		ExitButtonTextID,

		//New Game Menu
		NewGameMenuAvatarTextID,
		NewGameMenuWarriorClassNameTextID,
		NewGameMenuWarriorDescription0TextID,
		NewGameMenuWarriorDescription1TextID,
		NewGameMenuMageClassNameTextID,
		NewGameMenuMageDescription0TextID,
		NewGameMenuMageDescription1TextID,
		NewGameMenuNameInputDefaultTextID,
		NewGameMenuNameInputErrorTextID,

		//Load Game Menu

		//Options Menu
		OptionsMenuGameplayTextID,
		OptionsMenuVideoTextID,
		OptionsMenuAudioTextID,
		OptionsMenuApplyTextID,
		OptionsMenuLanguageTextID,
		OptionsMenuEnglishTextID,
		OptionsMenuPortugueseTextID,
		OptionsMenuTextSpeedTextID,
		OptionsMenuNormalTextID,
		OptionsMenuFastTextID,
		OptionsMenuInstantlyTextID,
		OptionsMenuDefaultWindowTextID,
		OptionsMenuRedBlackTextID,
		OptionsMenuCustomWindowTextID,
		OptionsMenuLeftTopTextID,
		OptionsMenuRightTopTextID,
		OptionsMenuLeftBottomTextID,
		OptionsMenuRightBottomTextID,
		OptionsMenuResolutionTextID,
		OptionsMenuColorDepthTextID,
		OptionsMenuTextureFilterTextID,
		OptionsMenuNoneTextID,
		OptionsMenuLinearTextID,
		OptionsMenuFullscreenTextID,
		OptionsMenuVSyncTextID,
		OptionsMenuAudioEngineTextID,
		OptionsMenuMusicVolumeTextID,
		OptionsMenuSoundVolumeTextID,

		//Character Menu
		InventoryTextID,
		SkillsTextID,
		QuestsTextID,
		AchievementsTextID,
		//Character Menu General
		ChestTextID,
		PrivateChestTextID,

		//Character Stats >> Main Stats
		ClassTextID,
		LevelTextID,
		ExperienceTextID,
		NextLevelTextID,
		HPTextID,
		MPTextID,
		PhysicalDamageTextID,
		PhysicalResistTextID,
		MagicalDamageTextID,
		MagicalResistTextID,
		HitTextID,
		EvadeTextID,
		SpeedTextID,
		MovementTextID,
		StrengthTextID,
		IntelligenceTextID,
		AgilityTextID,
		AttributePointsTextID,
		GoldTextID,
		//Character Stats >> Elemental Properties
		ElementalPropertiesTextID,
		ElementalEffectTextID,
		FireDamageTextID,
		IceDamageTextID,
		LightningDamageTextID,
		LightDamageTextID,
		DarkDamageTextID,
		FireResistTextID,
		IceResistTextID,
		LightningResistTextID,
		LightResistTextID,
		DarkResistTextID,
		FireAbsorbTextID,
		IceAbsorbTextID,
		LightningAbsorbTextID,
		LightAbsorbTextID,
		DarkAbsorbTextID,
		//Character Stats >> Status Properties
		StatusPropertiesTextID,
		StatusEffectTextID,
		WoundAttackTextID,
		SlownessAttackTextID,
		TirednessAttackTextID,
		HeadacheAttackTextID,
		BlindnessAttackTextID,
		WoundDefenseTextID,
		SlownessDefenseTextID,
		TirednessDefenseTextID,
		HeadacheDefenseTextID,
		BlindnessDefenseTextID,
		//Character Stats >> Natural Properties
		NaturalPropertiesTextID,
		CriticalStrikeTextID,
		QuickStrikeTextID,
		CounterStrikeTextID,
		HPStealTextID,
		MPStealTextID,
		HPRegenTextID,
		MPRegenTextID,
		//Character Stats >> General Abilities
		GeneralAbilitiesTextID,
		AnalyzerTextID,
		TrainerTextID,
		BountyTextID,
		CustomerTextID,
		CowardTextID,
		BraveTextID,
		RunnerTextID,
		SkinSlicerTextID,
		BoneCrusherTextID,
		ShellDrillerTextID,
		HumanEaterTextID,
		BeastKillerTextID,
		UndeadPurifierTextID,
		DemonHunterTextID,
		DragonSlayerTextID,
		//Character Stats Descriptions
		PreviousPageDescriptionTextID,
		NextPageDescriptionTextID,
		TwoHandsAttackDescriptionTextID,
		NameDescriptionTextID,
		ClassDescriptionTextID,
		LevelDescriptionTextID,
		ExperienceDescriptionTextID,
		NextLevelDescriptionTextID,
		HPDescriptionTextID,
		MPDescriptionTextID,
		PhysicalDamageDescriptionTextID,
		PhysicalResistDescriptionTextID,
		MagicalDamageDescriptionTextID,
		MagicalResistDescriptionTextID,
		HitDescriptionTextID,
		EvadeDescriptionTextID,
		SpeedDescriptionTextID,
		MovementDescriptionTextID,
		StrengthDescriptionTextID,
		IntelligenceDescriptionTextID,
		AgilityDescriptionTextID,
		AttributePointsDescriptionTextID,
		AddStrengthDescriptionTextID,
		AddIntelligenceDescriptionTextID,
		AddAgilityDescriptionTextID,
		ElementalEffectDescriptionTextID,
		ElementalDamageDescriptionTextID,
		ElementalEffectRequiredDescriptionTextID,
		ElementalResistDescriptionTextID,
		ElementalAbsorbDescriptionTextID,
		StatusEffectDescriptionTextID,
		StatusAttackDescriptionTextID,
		StatusEffectRequiredDescriptionTextID,
		StatusDefenseDescriptionTextID,
		WoundDescriptionTextID,
		SlownessDescriptionTextID,
		TirednessDescriptionTextID,
		HeadacheDescriptionTextID,
		BlindnessDescriptionTextID,
		CriticalStrikeDescriptionTextID,
		QuickStrikeDescriptionTextID,
		CounterStrikeDescriptionTextID,
		HPStealDescriptionTextID,
		MPStealDescriptionTextID,
		HPRegenDescriptionTextID,
		MPRegenDescriptionTextID,
		AnalyzerDescriptionTextID,
		TrainerDescriptionTextID,
		BountyDescriptionTextID,
		CustomerDescriptionTextID,
		CowardDescriptionTextID,
		BraveDescriptionTextID,
		RunnerDescriptionTextID,
		SkinSlicerDescriptionTextID,
		BoneCrusherDescriptionTextID,
		ShellDrillerDescriptionTextID,
		HumanEaterDescriptionTextID,
		BeastKillerDescriptionTextID,
		UndeadPurifierDescriptionTextID,
		DemonHunterDescriptionTextID,
		DragonSlayerDescriptionTextID,

		//Inventory
		EquipHandTextID,
		EquipHelmTextID,
		EquipArmorTextID,
		EquipGlovesTextID,
		EquipBootsTextID,
		EquipAccessoryTextID,
		DiscardItemTextID,

		//Battle Items
		BattleItemsTextID,

		//Skills Menu
		SkillPointsTextID,
		SkillPointsDescriptionTextID,

		//Skills General
		LearnTextID,
		TypeTextID,
		NaturalTextID,
		ActiveTextID,
		NewSkillTextID,
		LvTextID,
		CurrentSkillLevelTextID,
		NextSkillLevelTextID,
		MeleeWeaponOnlyTextID,
		SkillLearnedTextID,
		SkillLevelUpTextID,
		//Skills >> Warrior
		CutMasteryTextID,
		CutMasteryDescriptionTextID,
		//Skills >> Mage

		//Quests Menu
		MainQuestsClickTextID,
		OptionalQuestsClickTextID,
		QuestCompletedDescriptionTextID,
		QuestStartedTextID,
		QuestCompletedTextID,
		//Main Quests
		MainQuestName0TextID,
		MainQuestDescription0TextID,
		//Optional Quests
		OptionalQuestName0TextID,
		OptionalQuestDescription0TextID,

		//Achievements Menu
		AchievementsClickTextID,
		AchievementUnlockedTextID,
		SkillfulTextID,
		SkillfulDescriptionTextID,

		//Item Types
		UsableTextID,
		QuestItemTextID,
		DaggerTextID,
		SwordTextID,
		AxeTextID,
		MaceTextID,
		StaffTextID,
		SpearTextID,
		BowTextID,
		ShieldTextID,
		HelmTextID,
		ArmorTextID,
		GlovesTextID,
		BootsTextID,
		AccessoryTextID,

		//Items General
		RequiredLevelTextID,
		WeightTextID,
		OneHandTextID,
		TwoHandsTextID,
		HPMaxTextID,
		MPMaxTextID,
		CutTextID,
		SmashTextID,
		PierceTextID,
		RightClickToUseTextID,
		ShiftClickToSellTextID,
		QuestItemRestrictionTextID,

		//Usables
		PhysicalRecoveryLevel1TextID,
		PhysicalRecoveryLevel2TextID,
		PhysicalRecoveryLevel3TextID,
		PhysicalRecoveryLevel4TextID,
		PhysicalRecoveryLevel5TextID,
		MagicalRecoveryLevel1TextID,
		MagicalRecoveryLevel2TextID,
		MagicalRecoveryLevel3TextID,
		MagicalRecoveryLevel4TextID,
		MagicalRecoveryLevel5TextID,
		RecoveredTextID,
		RecoveryDescriptionTextID,

		//Quest Items
		LetterTextID,
		LetterDescriptionTextID,

		//Swords
		ShortSwordTextID,
		BroadSwordTextID,
		LongSwordTextID,

		//Shields
		BucklerTextID,

		//Helms
		CapTextID,

		//Armors
		ClothTextID,

		//Gloves
		LeatherGlovesTextID,

		//Boots
		LeatherBootsTextID,

		//Accessories
		CommonRingTextID,

		//Shop
		ItemShopTextID,
		WeaponShopTextID,
		ArmorShopTextID,

		//Maps
		NPCActionTextID,
		SaveCrystalTextID,
		SaveCrystalActionTextID,
		TeleportTextID,
		TeleportActivatedTextID,
		DestinationTextID,
		OpenTextID,
		GatewayActionTextID,
		CharacterMenuButtonDescriptionTextID,
		PauseMenuButtonDescriptionTextID,
		//Pause Menu
		ResumeButtonTextID,
		//Map Name
		MapArea00TextID,
		MapArea01TextID,
		//NPC Dialogues
		//Map Area 00
		//NPC 0
		MapArea00NPC0NameTextID,
		MapArea00NPC0Dialogue0Text0TextID,
		MapArea00NPC0Dialogue0Text1TextID,
		MapArea00NPC0Dialogue0Text2TextID,
		MapArea00NPC0Dialogue0Option0TextID,
		MapArea00NPC0Dialogue0Option1TextID,
		//Map Area 01
		//NPC 0
		MapArea01NPC0NameTextID,
		MapArea01NPC0Dialogue0Text0TextID,
		MapArea01NPC0Dialogue0Option0TextID,
		MapArea01NPC0Dialogue0Option1TextID,
	};

	class Database
	{
	private:
		//Banco de dados com os textos com base no idioma escolhido
		std::vector<std::string> language_texts;

		//Banco de dados com os items
		std::vector<std::unique_ptr<Item>> items;

		//Banco de dados com os objetivos principais
		std::vector<Quest> main_quests;

		//Banco de dados com os objetivos opcionais
		std::vector<Quest> optional_quests;

		//Banco de ddos com as conquistas
		std::vector<Achievement> achievements;

		//Banco de dados com as habilidades do Warrior
		std::vector<std::vector<SkillLevel>> warrior_skill_levels;

		//Banco de dados com as habilidades do Mage
		std::vector<std::vector<SkillLevel>> mage_skill_levels;

		//Carregar Language Texts
		void LoadLanguageTexts(const FileID language_id);

		//Carregar Items
		void LoadItems();

		//Carregar Quests
		void LoadQuests();

		//Carregar Achievements
		void LoadAchievements();

		//Carregar Skill Levels
		void LoadSkillLevels();
	public:
		//Carregar o banco de dados
		void LoadDatabase(const FileID language_id);

		//Pegar Language Text
		const std::string& GetLanguageText(const LanguageTextID language_text_id) const;

		//Pegar Items
		const Item& GetItems(const ItemID item_id) const;

		//Pegar Main Quests
		const std::vector<Quest>& GetMainQuests() const;

		//Pegar Optional Quests
		const std::vector<Quest>& GetOptionalQuests() const;

		//Pegar Achievements
		const std::vector<Achievement>& GetAchievements() const;

		//Pegar Warrior Skill Level
		const std::vector<std::vector<SkillLevel>>& GetWarriorSkillLevel() const;

		//Pegar Mage Skill Level
		const std::vector<std::vector<SkillLevel>>& GetMageSkillLevel() const;
	};
}

#endif
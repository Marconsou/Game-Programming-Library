#ifndef MAIN_H
#define MAIN_H

namespace RPG
{
	//Índices para todos os arquivos
	enum FileID
	{
		//Font
		FontQlassikBoldMediumFileID = 0,
		FontQlassikBoldSmallFileID,
		FontPerspectiveSansBlackItalicFileID,
		FontNewRockerRegularFileID,

		//Interface
		TextureCommonFileID,
		TextureWindowFileID,
		TextureSelectorFileID,
		TextureGoldFileID,
		//Character
		TextureWarrior0FileID,
		TextureWarrior1FileID,
		TextureWarrior2FileID,
		TextureWarrior3FileID,
		TextureWarrior4FileID,
		TextureMage0FileID,
		TextureMage1FileID,
		TextureMage2FileID,
		TextureMage3FileID,
		TextureMage4FileID,
		TextureCivilian00FileID,
		TextureCivilian01FileID,
		TextureDoor0FileID,
		TextureFountain0FileID,
		TextureSaveCrystalActivatedFileID,
		TextureSaveCrystalDeactivatedFileID,
		TextureChestFileID,
		TextureCharacterShadowFileID,
		//Item
		TextureUsableFileID,
		TextureQuestItemFileID,
		TextureDaggerFileID,
		TextureSwordFileID,
		TextureAxeFileID,
		TextureMaceFileID,
		TextureStaffFileID,
		TextureSpearFileID,
		TextureBowFileID,
		TextureShieldFileID,
		TextureHelmFileID,
		TextureArmorFileID,
		TextureGlovesFileID,
		TextureBootsFileID,
		TextureAccessoryFileID,
		//Skill
		TextureWarriorSkillsFileID,
		TextureMageSkillsFileID,
		//Tile Set
		TextureBackground00FileID,
		TextureBackground01FileID,
		TextureBackground02FileID,
		TextureBackground03FileID,
		TextureBackground04FileID,
		TextureBackground05FileID,
		TextureForeground00FileID,
		//Animation
		TextureSaveCrystalTouchFileID,
		TextureTeleportingFileID,

		//Music
		MusicTitleMusicFileID,
		MusicMusic00FileID,
		MusicMusic01FileID,

		//Sound
		SoundClickFileID,
		SoundErrorFileID,
		SoundCancelFileID,
		SoundPickItemFileID,
		SoundEquipItemFileID,
		SoundDiscardItemFileID,
		SoundUsingRecoveryItemFileID,
		SoundSkillLevelUpFileID,
		SoundQuestStartedFileID,
		SoundQuestCompletedFileID,
		SoundAchievementUnlockedFileID,
		SoundSaveCrystalFileID,
		SoundTeleportFileID,
		SoundChestOpeningFileID,
		SoundChestClosingFileID,
		SoundDoorOpeningFileID,
		SoundBuySellFileID,

		//Data
		EnglishFileID,
		PortugueseFileID,
		MapArea00FileID,
		MapArea01FileID,
		VertexShaderFileID,
		PixelShaderFileID,
	};
}

#endif
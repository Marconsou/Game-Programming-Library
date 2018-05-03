#include "GameRPG.h"

using namespace std;
using namespace GPL;
using namespace RPG;

GameRPG::GameRPG(unique_ptr<Application>&& application) :
Game(move(application)),
show_message_log(false),
animations(AnimationsMax)
{
	ResourceFile::SetResourceFileName("Data.pkg");

	/*
	remove("Data.pkg");
	ResourceFile::Write("Resources/Font/Qlassik Bold.otf");
	ResourceFile::Write("Resources/Font/Qlassik Bold.otf");
	ResourceFile::Write("Resources/Font/Perspective Sans Black Italic.otf");
	ResourceFile::Write("Resources/Font/NewRocker-Regular.otf");
	ResourceFile::Write("Resources/Texture/Interface/Common.png");
	ResourceFile::Write("Resources/Texture/Interface/Window.png");
	ResourceFile::Write("Resources/Texture/Interface/Selector.png");
	ResourceFile::Write("Resources/Texture/Interface/Gold.png");
	ResourceFile::Write("Resources/Texture/Character/Warrior 0.png");
	ResourceFile::Write("Resources/Texture/Character/Warrior 1.png");
	ResourceFile::Write("Resources/Texture/Character/Warrior 2.png");
	ResourceFile::Write("Resources/Texture/Character/Warrior 3.png");
	ResourceFile::Write("Resources/Texture/Character/Warrior 4.png");
	ResourceFile::Write("Resources/Texture/Character/Mage 0.png");
	ResourceFile::Write("Resources/Texture/Character/Mage 1.png");
	ResourceFile::Write("Resources/Texture/Character/Mage 2.png");
	ResourceFile::Write("Resources/Texture/Character/Mage 3.png");
	ResourceFile::Write("Resources/Texture/Character/Mage 4.png");
	ResourceFile::Write("Resources/Texture/Character/Civilian 00.png");
	ResourceFile::Write("Resources/Texture/Character/Civilian 01.png");
	ResourceFile::Write("Resources/Texture/Character/Door 0.png");
	ResourceFile::Write("Resources/Texture/Character/Fountain 0.png");
	ResourceFile::Write("Resources/Texture/Character/Save Crystal Activated.png");
	ResourceFile::Write("Resources/Texture/Character/Save Crystal Deactivated.png");
	ResourceFile::Write("Resources/Texture/Character/Chest.png");
	ResourceFile::Write("Resources/Texture/Character/Character Shadow.png");
	ResourceFile::Write("Resources/Texture/Item/Usable.png");
	ResourceFile::Write("Resources/Texture/Item/Quest Item.png");
	ResourceFile::Write("Resources/Texture/Item/Dagger.png");
	ResourceFile::Write("Resources/Texture/Item/Sword.png");
	ResourceFile::Write("Resources/Texture/Item/Axe.png");
	ResourceFile::Write("Resources/Texture/Item/Mace.png");
	ResourceFile::Write("Resources/Texture/Item/Staff.png");
	ResourceFile::Write("Resources/Texture/Item/Spear.png");
	ResourceFile::Write("Resources/Texture/Item/Bow.png");
	ResourceFile::Write("Resources/Texture/Item/Shield.png");
	ResourceFile::Write("Resources/Texture/Item/Helm.png");
	ResourceFile::Write("Resources/Texture/Item/Armor.png");
	ResourceFile::Write("Resources/Texture/Item/Gloves.png");
	ResourceFile::Write("Resources/Texture/Item/Boots.png");
	ResourceFile::Write("Resources/Texture/Item/Accessory.png");
	ResourceFile::Write("Resources/Texture/Skill/Warrior Skills.png");
	ResourceFile::Write("Resources/Texture/Skill/Mage Skills.png");
	ResourceFile::Write("Resources/Texture/Tile Set/Background 00.png");
	ResourceFile::Write("Resources/Texture/Tile Set/Background 01.png");
	ResourceFile::Write("Resources/Texture/Tile Set/Background 02.png");
	ResourceFile::Write("Resources/Texture/Tile Set/Background 03.png");
	ResourceFile::Write("Resources/Texture/Tile Set/Background 04.png");
	ResourceFile::Write("Resources/Texture/Tile Set/Background 05.png");
	ResourceFile::Write("Resources/Texture/Tile Set/Foreground 00.png");
	ResourceFile::Write("Resources/Texture/Animation/Save Crystal Touch.png");
	ResourceFile::Write("Resources/Texture/Animation/Teleporting.png");
	ResourceFile::Write("Resources/Music/Title Music.ogg");
	ResourceFile::Write("Resources/Music/Music 00.ogg");
	ResourceFile::Write("Resources/Music/Music 01.ogg");
	ResourceFile::Write("Resources/Sound/Click.ogg");
	ResourceFile::Write("Resources/Sound/Error.ogg");
	ResourceFile::Write("Resources/Sound/Cancel.ogg");
	ResourceFile::Write("Resources/Sound/Pick Item.ogg");
	ResourceFile::Write("Resources/Sound/Equip Item.ogg");
	ResourceFile::Write("Resources/Sound/Discard Item.ogg");
	ResourceFile::Write("Resources/Sound/Using Recovery Item.ogg");
	ResourceFile::Write("Resources/Sound/Skill Level Up.ogg");
	ResourceFile::Write("Resources/Sound/Quest Started.ogg");
	ResourceFile::Write("Resources/Sound/Quest Completed.ogg");
	ResourceFile::Write("Resources/Sound/Achievement Unlocked.ogg");
	ResourceFile::Write("Resources/Sound/Save Crystal.ogg");
	ResourceFile::Write("Resources/Sound/Teleport.ogg");
	ResourceFile::Write("Resources/Sound/Chest Opening.ogg");
	ResourceFile::Write("Resources/Sound/Chest Closing.ogg");
	ResourceFile::Write("Resources/Sound/Door Opening.ogg");
	ResourceFile::Write("Resources/Sound/Buy Sell.ogg");
	ResourceFile::Write("Resources/Database/English.txt");
	ResourceFile::Write("Resources/Database/Portuguese.txt");
	ResourceFile::Write("Resources/Database/Map Area 00.txt");
	ResourceFile::Write("Resources/Database/Map Area 01.txt");
	ResourceFile::Write("../Game Programming Library/Shaders/Render.vsh");
	ResourceFile::Write("../Game Programming Library/Shaders/Render.psh");
	*/
}

void GameRPG::SetShowMessageLog(const bool show_message_log)
{
	this->show_message_log = show_message_log;
}

Configuration& GameRPG::GetConfiguration()
{
	return this->configuration;
}

Database& GameRPG::GetDatabase()
{
	return this->database;
}

Hero& GameRPG::GetHero()
{
	return *this->hero;
}

void GameRPG::SetRecentAchievementUnlocked(const string& recent_achievement_unlocked)
{
	this->recent_achievement_unlocked = recent_achievement_unlocked;
}

const string& GameRPG::GetRecentAchievementUnlocked() const
{
	return this->recent_achievement_unlocked;
}

vector<AnimationFrame>& GameRPG::GetAnimations()
{
	return this->animations;
}

void GameRPG::SetWindow(Window& window,const int inner_block_quantity_w,const int inner_block_quantity_h)
{
	window.SetCurrentBackground(this->configuration.GetDefaultWindow().GetCurrent());

	if (this->configuration.GetDefaultWindowSelected())
		window.SetWindow(inner_block_quantity_w,inner_block_quantity_h,5.0f);
	else
		window.SetWindow(inner_block_quantity_w,inner_block_quantity_h,this->configuration.GetColorLeftTop(),this->configuration.GetColorRightTop(),this->configuration.GetColorLeftBottom(),this->configuration.GetColorRightBottom(),5.0f);
}

void GameRPG::SetDialogueBox(DialogueBox& dialogue_box)
{
	dialogue_box.SetWindowCurrentBackground(this->configuration.GetDefaultWindow().GetCurrent());

	if (this->configuration.GetDefaultWindowSelected())
		dialogue_box.SetWindow(5.0f);
	else
		dialogue_box.SetWindow(this->configuration.GetColorLeftTop(),this->configuration.GetColorRightTop(),this->configuration.GetColorLeftBottom(),this->configuration.GetColorRightBottom(),5.0f);
}

float GameRPG::GetTextSpeedInterval()
{
	const int text_speed = this->configuration.GetTextSpeed().GetCurrent();
	if (text_speed == 0)
		return 0.050f;
	else if (text_speed == 1)
		return 0.025f;
	return 0.0f;
}

void GameRPG::CreateGame()
{
	//Inicialização padrão (deve ser 800x600)
	VideoMode video_mode(800,600,(this->configuration.GetColorDepth().GetCurrent() == 0) ? BitsPerPixel::ColorDepth32Bits : BitsPerPixel::ColorDepth16Bits,!this->configuration.GetFullscreen(),this->configuration.GetVSync());
	this->Initialize("RPG v3.4 [Alpha Release]",video_mode,(this->configuration.GetAudioEngine().GetCurrent() == 0) ? AudioEngine::XAudio : AudioEngine::OpenAL,1);

	//Carregar configuração de Video
	this->LoadVideoSettingsFromConfiguration();

	//Carregar configuração de Audio
	this->LoadAudioSettingsFromConfiguration(false);

	//Carregar o banco de dados
	this->LoadDatabase();

	//Carregar os arquivos de recursos
	this->LoadResources();

	//Cor do fundo e Fade
	this->GetScreenEffect().StartFadeInScreen(ScreenEffectFadeMode::Normal);
}

void GameRPG::LoadDatabase()
{
	this->database.LoadDatabase(static_cast<FileID>(EnglishFileID + this->configuration.GetLanguage().GetCurrent()));
}

void GameRPG::LoadResources()
{
	//Shader
	this->GetVideo().LoadVertexShader(VertexShaderFileID);
	this->GetVideo().LoadPixelShader(PixelShaderFileID);

	//Font
	this->GetVideo().LoadFont(FontQlassikBoldMediumFileID,15,' ',254);
	this->GetVideo().LoadFont(FontQlassikBoldSmallFileID,12,' ',254);
	this->GetVideo().LoadFont(FontPerspectiveSansBlackItalicFileID,20,' ',254);
	this->GetVideo().LoadFont(FontNewRockerRegularFileID,19,' ',254);

	//Texture
	this->GetVideo().LoadTexture(TextureCommonFileID);
	this->GetVideo().LoadTexture(TextureWindowFileID);
	this->GetVideo().LoadTexture(TextureSelectorFileID);
	this->GetVideo().LoadTexture(TextureGoldFileID);
	this->GetVideo().LoadTexture(TextureWarrior0FileID);
	this->GetVideo().LoadTexture(TextureWarrior1FileID);
	this->GetVideo().LoadTexture(TextureWarrior2FileID);
	this->GetVideo().LoadTexture(TextureWarrior3FileID);
	this->GetVideo().LoadTexture(TextureWarrior4FileID);
	this->GetVideo().LoadTexture(TextureMage0FileID);
	this->GetVideo().LoadTexture(TextureMage1FileID);
	this->GetVideo().LoadTexture(TextureMage2FileID);
	this->GetVideo().LoadTexture(TextureMage3FileID);
	this->GetVideo().LoadTexture(TextureMage4FileID);
	this->GetVideo().LoadTexture(TextureSaveCrystalActivatedFileID);
	this->GetVideo().LoadTexture(TextureSaveCrystalDeactivatedFileID);
	this->GetVideo().LoadTexture(TextureChestFileID);
	this->GetVideo().LoadTexture(TextureCharacterShadowFileID);
	this->GetVideo().LoadTexture(TextureUsableFileID);
	this->GetVideo().LoadTexture(TextureQuestItemFileID);
	this->GetVideo().LoadTexture(TextureDaggerFileID);
	this->GetVideo().LoadTexture(TextureSwordFileID);
	this->GetVideo().LoadTexture(TextureUsableFileID);
	this->GetVideo().LoadTexture(TextureAxeFileID);
	this->GetVideo().LoadTexture(TextureMaceFileID);
	this->GetVideo().LoadTexture(TextureStaffFileID);
	this->GetVideo().LoadTexture(TextureSpearFileID);
	this->GetVideo().LoadTexture(TextureBowFileID);
	this->GetVideo().LoadTexture(TextureShieldFileID);
	this->GetVideo().LoadTexture(TextureHelmFileID);
	this->GetVideo().LoadTexture(TextureArmorFileID);
	this->GetVideo().LoadTexture(TextureGlovesFileID);
	this->GetVideo().LoadTexture(TextureBootsFileID);
	this->GetVideo().LoadTexture(TextureAccessoryFileID);
	this->GetVideo().LoadTexture(TextureWarriorSkillsFileID);
	this->GetVideo().LoadTexture(TextureMageSkillsFileID);
	this->GetVideo().LoadTexture(TextureSaveCrystalTouchFileID);
	this->GetVideo().LoadTexture(TextureTeleportingFileID);

	Window::WindowsProperties(this->GetVideo().GetTexture(TextureWindowFileID),4,63,1);

	//Music
	this->GetAudio().AddToMusicPlaylist(MusicTitleMusicFileID);
	this->GetAudio().AddToMusicPlaylist(MusicMusic00FileID);
	this->GetAudio().AddToMusicPlaylist(MusicMusic01FileID);

	//Sound
	this->GetAudio().LoadSound(SoundClickFileID);
	this->GetAudio().LoadSound(SoundErrorFileID);
	this->GetAudio().LoadSound(SoundCancelFileID);
	this->GetAudio().LoadSound(SoundPickItemFileID);
	this->GetAudio().LoadSound(SoundEquipItemFileID);
	this->GetAudio().LoadSound(SoundDiscardItemFileID);
	this->GetAudio().LoadSound(SoundUsingRecoveryItemFileID);
	this->GetAudio().LoadSound(SoundSkillLevelUpFileID);
	this->GetAudio().LoadSound(SoundQuestStartedFileID);
	this->GetAudio().LoadSound(SoundQuestCompletedFileID);
	this->GetAudio().LoadSound(SoundAchievementUnlockedFileID);
	this->GetAudio().LoadSound(SoundSaveCrystalFileID);
	this->GetAudio().LoadSound(SoundTeleportFileID);
	this->GetAudio().LoadSound(SoundChestOpeningFileID);
	this->GetAudio().LoadSound(SoundChestClosingFileID);
	this->GetAudio().LoadSound(SoundDoorOpeningFileID);
	this->GetAudio().LoadSound(SoundBuySellFileID);

	//Message Log
	this->message_log.SetMessageLog(this->GetVideo().GetFont(FontQlassikBoldMediumFileID),"",Color::Yellow,20.0f,MessageLogOrientation::Up);
	this->message_log.SetPosition(30.0f,475.0f);

	//Animations
	this->animations[HeroTeleporting].SetAnimationFrame(this->GetTimer(),this->GetVideo().GetTexture(TextureTeleportingFileID),64.0f,100.0f,4,0.075f);
}

void GameRPG::LoadVideoSettingsFromConfiguration()
{
	VideoMode video_mode(this->configuration.GetWidth(),this->configuration.GetHeight(),(this->configuration.GetColorDepth().GetCurrent() == 0) ? BitsPerPixel::ColorDepth32Bits : BitsPerPixel::ColorDepth16Bits,!this->configuration.GetFullscreen(),this->configuration.GetVSync());
	this->GetVideo().ChangeSettings(this->GetApplication(),video_mode);
	this->GetVideo().SetBackBufferClearColor(Color::Black);
	this->GetVideo().SetTextureFilter((this->configuration.GetTextureFilter().GetCurrent() == 0) ? TextureFilter::Point : TextureFilter::Linear);
	this->GetVideo().SetAspectRatio(AspectRatio::Normal4x3);
}

void GameRPG::LoadAudioSettingsFromConfiguration(const bool load_audio_engine)
{
	//Audio Engine
	if (load_audio_engine)
		this->ChangeAudioEngine((this->configuration.GetAudioEngine().GetCurrent() == 0) ? AudioEngine::XAudio : AudioEngine::OpenAL);

	//Music
	this->GetAudio().SetMusicVolume(this->configuration.GetMusicVolume());
	if (this->configuration.GetMusicEnabled())
		this->GetAudio().EnableMusic();
	else
		this->GetAudio().DisableMusic();

	//Sound
	this->GetAudio().SetSoundVolume(this->configuration.GetSoundVolume());
	if (this->configuration.GetSoundEnabled())
		this->GetAudio().EnableSound();
	else
		this->GetAudio().DisableSound();
}

void GameRPG::StartNewGame(const FileID texture_id,const string& name)
{
	//Warrior
	if ((texture_id >= TextureWarrior0FileID) && (texture_id < TextureMage0FileID))
		this->hero = make_unique<Warrior>(this->database.GetWarriorSkillLevel());

	//Mage
	else if (texture_id >= TextureMage0FileID)
		this->hero = make_unique<Mage>(this->database.GetMageSkillLevel());

	//Dados básicos do herói
	this->hero->GetStats().SetName(name);
	this->hero->GetCharacter()->SetCharacterTexture(this->GetVideo().GetTexture(texture_id));
	this->hero->GetCharacter()->SetCharacterShadowTexture(this->GetVideo().GetTexture(TextureCharacterShadowFileID));

	//Copiando do banco de dados
	this->hero->GetMainQuests() = this->database.GetMainQuests();
	this->hero->GetOptionalQuests() = this->database.GetOptionalQuests();
	this->hero->GetAchievements() = this->database.GetAchievements();

	///
	this->hero->AddItemToInventory(this->database.GetItems(ShortSword));
	this->hero->AddItemToInventory(this->database.GetItems(ShortSword));
	this->hero->AddItemToInventory(this->database.GetItems(BroadSword));
	this->hero->AddItemToInventory(this->database.GetItems(BroadSword));
	this->hero->AddItemToInventory(this->database.GetItems(LongSword));
	this->hero->AddItemToInventory(this->database.GetItems(Buckler));
	this->hero->AddItemToInventory(this->database.GetItems(Cap));
	this->hero->AddItemToInventory(this->database.GetItems(Cloth));
	this->hero->AddItemToInventory(this->database.GetItems(LeatherGloves));
	this->hero->AddItemToInventory(this->database.GetItems(LeatherBoots));
	this->hero->AddItemToInventory(this->database.GetItems(CommonRing));
	this->hero->AddItemToInventory(this->database.GetItems(CommonRing));
	this->hero->AddItemToInventory(this->database.GetItems(CommonRing));
	for (int i = PhysicalRecoveryLevel1; i < PhysicalRecoveryLevel1 + 10; i++)
	{
		this->hero->AddItemToInventory(this->database.GetItems(static_cast<ItemID>(i)));
		this->hero->AddItemToBattleItems(this->database.GetItems(static_cast<ItemID>(i)));
	}
	this->hero->AddItemToInventory(this->database.GetItems(Letter));

	this->hero->GetOptionalQuests()[OptionalQuest0].SetQuestState(QuestStateStarted);
	///
}

void GameRPG::FinishCurrentGame()
{
	this->hero.reset();
	this->text_dynamics.clear();
	this->message_log.Clear();
}

bool GameRPG::HeroCreated() const
{
	return (this->hero.get() != nullptr);
}

void GameRPG::NewMessageLogText(const string& message,const Color& color)
{
	this->message_log.NewMessage(this->hero->GetPlayTime(),message,color);
}

void GameRPG::AddMessageLogText(const string& message,const Color& color)
{
	this->message_log.AddMessage(message,color);
}

void GameRPG::ShowTextDynamic()
{
	for (size_t i = 0; i < this->text_dynamics.size(); i++)
	{
		TextDynamic& iterator = *this->text_dynamics[i].get();

		if (!iterator.Show(this->GetVideo(),this->GetTimer()))
		{
			this->text_dynamics.erase(this->text_dynamics.begin() + i);
			i--;
		}
	}
}

void GameRPG::ShowMessageLog()
{
	//Mostrar as mensagens no Log quando necessário
	if ((this->show_message_log) && (this->HeroCreated()))
		this->message_log.ShowMessageLog(this->GetVideo(),this->hero->GetPlayTime());
}
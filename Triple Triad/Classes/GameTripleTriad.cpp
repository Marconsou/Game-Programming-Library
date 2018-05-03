#include "GameTripleTriad.h"

using namespace std;
using namespace GPL;
using namespace TT;

GameTripleTriad::GameTripleTriad(unique_ptr<Application>&& application) :
Game(move(application)),
rules(static_cast<int>(RuleID::Max))
{
	ResourceFile::SetResourceFileName("Data.pkg");

	/*
	remove("Data.pkg");
	ResourceFile::Write("Resources/Font/Segoe UI Bold.ttf");
	ResourceFile::Write("Resources/Font/Tahoma.ttf");
	ResourceFile::Write("Resources/Font/Times New Roman Bold.ttf");
	ResourceFile::Write("Resources/Font/Times New Roman Bold Italic.ttf");
	ResourceFile::Write("Resources/Font/Algerian.ttf");
	ResourceFile::Write("Resources/Texture/Background.png");
	ResourceFile::Write("Resources/Texture/Interface.png");
	ResourceFile::Write("Resources/Texture/Window.png");
	ResourceFile::Write("Resources/Texture/Card Back Face.png");
	ResourceFile::Write("Resources/Texture/Cards Level 01.png");
	ResourceFile::Write("Resources/Texture/Cards Level 02.png");
	ResourceFile::Write("Resources/Texture/Cards Level 03.png");
	ResourceFile::Write("Resources/Texture/Cards Level 04.png");
	ResourceFile::Write("Resources/Texture/Cards Level 05.png");
	ResourceFile::Write("Resources/Texture/Cards Level 06.png");
	ResourceFile::Write("Resources/Texture/Cards Level 07.png");
	ResourceFile::Write("Resources/Texture/Cards Level 08.png");
	ResourceFile::Write("Resources/Texture/Cards Level 09.png");
	ResourceFile::Write("Resources/Texture/Cards Level 10.png");
	ResourceFile::Write("Resources/Texture/Squaresoft Logo.png");
	ResourceFile::Write("Resources/Music/Main Theme.ogg");
	ResourceFile::Write("Resources/Sound/Cursor Move.ogg");
	ResourceFile::Write("Resources/Sound/Cursor Cancel.ogg");
	ResourceFile::Write("Resources/Sound/Cursor Error.ogg");
	ResourceFile::Write("Resources/Sound/Draw Card.ogg");
	ResourceFile::Write("Resources/Sound/Turn Card.ogg");
	ResourceFile::Write("Resources/Sound/Random Player Turn.ogg");
	ResourceFile::Write("../Game Programming Library/Shaders/Render.vsh");
	ResourceFile::Write("../Game Programming Library/Shaders/Render.psh");
	*/

	this->rules[static_cast<int>(RuleID::Open)] = true;
	this->rules[static_cast<int>(RuleID::Random)] = true;
	this->rules[static_cast<int>(RuleID::Elemental)] = false;

	this->player_1.KeyboardKeyActions(KeyboardKey::A,KeyboardKey::D,KeyboardKey::W,KeyboardKey::S,KeyboardKey::N,KeyboardKey::M);
	this->player_2.KeyboardKeyActions(KeyboardKey::A,KeyboardKey::D,KeyboardKey::W,KeyboardKey::S,KeyboardKey::N,KeyboardKey::M);
	this->player_1.JoystickButtonActions(JoystickButton::Button03,JoystickButton::Button02);
	this->player_2.JoystickButtonActions(JoystickButton::Button03,JoystickButton::Button02);
}

void GameTripleTriad::SetMusicPlaying(const bool music_playing)
{
	this->music_playing = music_playing;
}

bool GameTripleTriad::GetMusicPlaying() const
{
	return this->music_playing;
}

Quantity& GameTripleTriad::GetDifficultyLevel()
{
	return this->difficulty_level;
}

Player& GameTripleTriad::GetPlayer1()
{
	return this->player_1;
}

const Player& GameTripleTriad::GetPlayer1() const
{
	return this->player_1;
}

Player& GameTripleTriad::GetPlayer2()
{
	return this->player_2;
}

const Player& GameTripleTriad::GetPlayer2() const
{
	return this->player_2;
}

Player& GameTripleTriad::GetCurrentPlayer()
{
	return *this->current_player;
}

Player& GameTripleTriad::GetOpponentPlayer()
{
	if (this->current_player == &this->player_1)
		return this->player_2;
	return this->player_1;
}

void GameTripleTriad::SetCurrentPlayer(const int player_number)
{
	if (player_number == 0)
		this->current_player = &this->player_1;

	else if (player_number == 1)
		this->current_player = &this->player_2;
}

Board& GameTripleTriad::GetBoard()
{
	return this->board;
}

vector<Card*>& GameTripleTriad::GetCurrentGameCards()
{
	return this->current_game_cards;
}

bool GameTripleTriad::IsPlayer1Turn() const
{
	return (this->current_player == &this->player_1);
}

bool GameTripleTriad::IsPlayer2Turn() const
{
	return (this->current_player == &this->player_2);
}

void GameTripleTriad::PassPlayerTurn()
{
	if (this->current_player == &this->player_1)
		this->current_player = &this->player_2;
	else
		this->current_player = &this->player_1;
}

int GameTripleTriad::CalculateScorePlayer1() const
{
	return this->player_1.CalculateScore(this->current_game_cards);
}

int GameTripleTriad::CalculateScorePlayer2() const
{
	return this->player_2.CalculateScore(this->current_game_cards);
}

bool GameTripleTriad::AnyCardIsBeingCaptured() const
{
	bool any_card_is_being_captured = false;
	for (auto& iterator : this->current_game_cards)
	{
		const CardState card_state = iterator->GetCardState();

		if ((card_state == CardState::CapturingByHorizontal) || (card_state == CardState::CapturingByVertical))
		{
			any_card_is_being_captured = true;
			break;
		}
	}
	return any_card_is_being_captured;
}

void GameTripleTriad::EnableRule(const int index)
{
	this->rules[index] = true;
}

void GameTripleTriad::DisableRule(const int index)
{
	this->rules[index] = false;
}

bool GameTripleTriad::IsRuleEnabled(const int index)
{
	return this->rules[index];
}

void GameTripleTriad::CreateGame()
{
	VideoMode video_mode(800,600,BitsPerPixel::ColorDepth32Bits,true,true);
	this->Initialize("Triple Triad",video_mode,AudioEngine::XAudio,1);
	this->GetApplication().SetShowCursor(true);
	this->GetVideo().SetOrthographicZ(-300.0f,300.0f);
	this->GetVideo().SetTextureFilter(TextureFilter::Linear);

	this->LoadResources();
	this->LoadCards();
	this->board.Initialize(this->GetVideo());
}

void GameTripleTriad::LoadResources()
{
	Video& video = this->GetVideo();
	Audio& audio = this->GetAudio();

	video.LoadFont(static_cast<int>(FileID::FontSegoeUIBold),10,32UL,126UL,2.0f);
	video.LoadFont(static_cast<int>(FileID::FontTahoma),15,32UL,126UL,1.5f);
	video.LoadFont(static_cast<int>(FileID::FontTimesNewRomanBold),18,'0','A',2.0f);
	video.LoadFont(static_cast<int>(FileID::FontTimesNewRomanBoldItalic),45,'+','9',4.0f);
	video.LoadFont(static_cast<int>(FileID::FontAlgerian),36,32UL,126UL,4.0f);

	video.LoadTexture(static_cast<int>(FileID::TextureBackground));
	video.LoadTexture(static_cast<int>(FileID::TextureInterface));
	video.LoadTexture(static_cast<int>(FileID::TextureWindow));
	video.LoadTexture(static_cast<int>(FileID::TextureCardBackFace));
	video.LoadTexture(static_cast<int>(FileID::TextureCardsLevel01));
	video.LoadTexture(static_cast<int>(FileID::TextureCardsLevel02));
	video.LoadTexture(static_cast<int>(FileID::TextureCardsLevel03));
	video.LoadTexture(static_cast<int>(FileID::TextureCardsLevel04));
	video.LoadTexture(static_cast<int>(FileID::TextureCardsLevel05));
	video.LoadTexture(static_cast<int>(FileID::TextureCardsLevel06));
	video.LoadTexture(static_cast<int>(FileID::TextureCardsLevel07));
	video.LoadTexture(static_cast<int>(FileID::TextureCardsLevel08));
	video.LoadTexture(static_cast<int>(FileID::TextureCardsLevel09));
	video.LoadTexture(static_cast<int>(FileID::TextureCardsLevel10));
	video.LoadTexture(static_cast<int>(FileID::TextureSquaresoftLogo));

	Window::WindowsProperties(this->GetVideo().GetTexture(static_cast<int>(FileID::TextureWindow)),4,63,1);

	audio.AddToMusicPlaylist(static_cast<int>(FileID::MusicMainTheme),17.0,113.0);
	audio.LoadSound(static_cast<int>(FileID::SoundCursorMove));
	audio.LoadSound(static_cast<int>(FileID::SoundCursorCancel));
	audio.LoadSound(static_cast<int>(FileID::SoundCursorError));
	audio.LoadSound(static_cast<int>(FileID::SoundDrawCard));
	audio.LoadSound(static_cast<int>(FileID::SoundTurnCard));
	audio.LoadSound(static_cast<int>(FileID::SoundRandomPlayerTurn));

	video.LoadVertexShader(static_cast<int>(FileID::VertexShader));
	video.LoadPixelShader(static_cast<int>(FileID::PixelShader));

	video.CreateRenderTarget(video.GetVirtualWidth(),video.GetVirtualHeight());
}

void GameTripleTriad::LoadCards()
{
	//Level 1
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Geezard,"Geezard",1,5,1,4,1));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Funguar,"Funguar",1,3,5,1,1));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::BiteBug,"Bite Bug",1,5,1,3,3));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::RedBat,"Red Bat",1,2,6,1,1));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Blobra,"Blobra",1,5,2,3,1));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Gayla,"Gayla",1,4,2,1,4,Elemental::Thunder));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Gesper,"Gesper",1,1,1,5,4));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::FastitocalonF,"Fastitocalon-F",1,1,3,5,2,Elemental::Earth));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::BloodSoul,"Blood Soul",1,1,2,1,6));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Caterchipillar,"Caterchipillar",1,3,4,2,4));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Cockatrice,"Cockatrice",1,6,2,1,2,Elemental::Thunder));

	//Level 2
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Grat,"Grat",2,1,7,1,3));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Buel,"Buel",2,3,6,2,2));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Mesmerize,"Mesmerize",2,4,5,3,3));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::GlacialEye,"Glacial Eye",2,3,6,1,4,Elemental::Ice));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Belhelmel,"Belhelmel",2,3,3,4,5));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Thrustaevis,"Thrustaevis",2,5,5,3,2,Elemental::Wind));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Anacondaur,"Anacondaur",2,5,5,1,3,Elemental::Poison));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Creeps,"Creeps",2,2,5,2,5,Elemental::Thunder));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Grendel,"Grendel",2,2,4,4,5,Elemental::Thunder));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Jellyeye,"Jellyeye",2,7,3,2,1));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::GrandMantis,"Grand Mantis",2,3,5,2,5));

	//Level 3
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Forbidden,"Forbidden",3,2,6,6,3));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Armadodo,"Armadodo",3,6,6,3,1,Elemental::Earth));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::TriFace,"Tri-Face",3,5,3,5,5,Elemental::Poison));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Fastitocalon,"Fastitocalon",3,3,7,5,1,Elemental::Earth));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::SnowLion,"Snow Lion",3,3,7,1,5,Elemental::Ice));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Ochu,"Ochu",3,3,5,6,3));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::SAM08G,"SAM08G",3,4,5,6,2,Elemental::Fire));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::DeathClaw,"Death Claw",3,2,4,4,7,Elemental::Fire));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Cactuar,"Cactuar",3,3,6,2,6));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Tonberry,"Tonberry",3,4,3,6,4));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::AbyssWorm,"Abyss Worm",3,5,7,2,3,Elemental::Earth));

	//Level 4
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Turtapod,"Turtapod",4,7,2,3,6));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Vysage,"Vysage",4,5,6,5,4));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::TRexaur,"T-Rexaur",4,7,4,6,2));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Bomb,"Bomb",4,3,2,7,6,Elemental::Fire));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Blitz,"Blitz",4,7,1,6,4,Elemental::Thunder));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Wendigo,"Wendigo",4,6,7,3,1));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Torama,"Torama",4,4,7,4,4));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Imp,"Imp",4,6,3,7,3));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::BlueDragon,"Blue Dragon",4,3,6,2,7,Elemental::Poison));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Adamantoise,"Adamantoise",4,6,4,5,5,Elemental::Earth));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Hexadragon,"Hexadragon",4,3,7,5,4,Elemental::Fire));

	//Level 5
	this->cards_stats.push_back(make_unique<CardStats>(CardID::IronGiant,"Iron Giant",5,5,6,5,6));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Behemoth,"Behemoth",5,7,3,6,5));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Chimera,"Chimera",5,3,7,6,5,Elemental::Water));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::PuPu,"PuPu",5,1,3,10,2));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Elastoid,"Elastoid",5,7,6,2,6));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::GIM47N,"GIM47N",5,4,5,5,7));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Malboro,"Malboro",5,2,7,7,4,Elemental::Poison));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::RubyDragon,"Ruby Dragon",5,4,7,2,7,Elemental::Fire));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Elnoyle,"Elnoyle",5,6,5,3,7));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::TonberryKing,"Tonberry King",5,4,4,6,7));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::BiggsWedge,"Biggs, Wedge",5,7,6,6,2));

	//Level 6
	this->cards_stats.push_back(make_unique<CardStats>(CardID::FujinRaijin,"Fujin, Raijin",6,4,2,8,8));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Elvoret,"Elvoret",6,4,7,8,3,Elemental::Wind));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::XATM092,"X-ATM092",6,3,4,8,7));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Granaldo,"Granaldo",6,5,7,2,8));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Gerogero,"Gerogero",6,3,1,8,8,Elemental::Poison));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Iguion,"Iguion",6,2,8,2,8));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Abadon,"Abadon",6,5,6,8,4));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Trauma,"Trauma",6,6,4,8,5));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Oilboyle,"Oilboyle",6,8,1,8,4));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::ShumiTribe,"Shumi Tribe",6,4,6,5,8));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Krysta,"Krysta",6,1,7,5,8));

	//Level 7
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Propagator,"Propagator",7,8,8,4,4));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::JumboCactuar,"Jumbo Cactuar",7,4,8,8,4));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::TriPoint,"Tri-Point",7,8,8,5,2,Elemental::Thunder));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Gargantua,"Gargantua",7,8,5,6,6));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::MobileType8,"Mobile Type 8",7,3,8,6,7));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Sphinxara,"Sphinxara",7,8,8,3,5));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Tiamat,"Tiamat",7,4,8,8,5));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::BGH251F2,"BGH251F2",7,5,5,7,8));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::RedGiant,"Red Giant",7,7,6,8,4));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Catoblepas,"Catoblepas",7,7,1,8,7));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::UltimaWeapon,"Ultima Weapon",7,8,7,7,2));

	//Level 8
	this->cards_stats.push_back(make_unique<CardStats>(CardID::ChubbyChocobo,"Chubby Chocobo",8,9,4,4,8));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Angelo,"Angelo",8,3,9,6,7));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Gilgamesh,"Gilgamesh",8,6,3,7,9));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::MiniMog,"MiniMog",8,2,9,3,9));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Chocobo,"Chocobo",8,4,9,4,8));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Quezacotl,"Quezacotl",8,4,2,9,9,Elemental::Thunder));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Shiva,"Shiva",8,9,6,7,4,Elemental::Ice));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Ifrit,"Ifrit",8,8,9,6,2,Elemental::Fire));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Siren,"Siren",8,2,8,9,6));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Sacred,"Sacred",8,9,5,1,9,Elemental::Earth));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Minotaur,"Minotaur",8,9,9,5,2,Elemental::Earth));

	//Level 9
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Carbuncle,"Carbuncle",9,4,8,4,10));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Diablos,"Diablos",9,3,5,10,8));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Leviathan,"Leviathan",9,7,7,10,1,Elemental::Water));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Odin,"Odin",9,5,8,10,3));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Pandemona,"Pandemona",9,7,10,1,7,Elemental::Wind));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Cerberus,"Cerberus",9,10,7,4,6));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Alexander,"Alexander",9,2,9,10,4,Elemental::Holy));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Phoenix,"Phoenix",9,10,7,2,7,Elemental::Fire));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Bahamut,"Bahamut",9,6,10,8,2));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Doomtrain,"Doomtrain",9,10,3,1,10,Elemental::Poison));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Eden,"Eden",9,10,4,4,9));

	//Level 10
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Ward,"Ward",10,8,10,7,2));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Kiros,"Kiros",10,10,6,7,6));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Laguna,"Laguna",10,9,5,10,3));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Selphie,"Selphie",10,4,10,8,6));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Quistis,"Quistis",10,2,9,6,10));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Irvine,"Irvine",10,10,2,6,9));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Zell,"Zell",10,6,8,5,10));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Rinoa,"Rinoa",10,10,4,10,2));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Edea,"Edea",10,3,10,10,3));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Seifer,"Seifer",10,4,6,9,10));
	this->cards_stats.push_back(make_unique<CardStats>(CardID::Squall,"Squall",10,9,10,4,6));
}

void GameTripleTriad::AddCards()
{
	const int initial = static_cast<int>(CardID::Geezard);
	const int final = static_cast<int>(CardID::Squall);

	if (this->IsRuleEnabled(static_cast<int>(RuleID::Random)))
	{
		for (size_t i = 0; i < 5; i++)
			this->player_1.AddCard(*this->cards_stats[Random::GenerateNumber(initial,final)]);

		for (size_t i = 0; i < 5; i++)
			this->player_2.AddCard(*this->cards_stats[Random::GenerateNumber(initial,final)]);
	}
	else
	{
		this->player_1.AddCard(*this->cards_stats[static_cast<int>(CardID::Geezard)]);
		this->player_1.AddCard(*this->cards_stats[static_cast<int>(CardID::Squall)]);
		this->player_1.AddCard(*this->cards_stats[static_cast<int>(CardID::Funguar)]);
		this->player_1.AddCard(*this->cards_stats[static_cast<int>(CardID::Quistis)]);
		this->player_1.AddCard(*this->cards_stats[static_cast<int>(CardID::BiteBug)]);

		this->player_2.AddCard(*this->cards_stats[static_cast<int>(CardID::Geezard)]);
		this->player_2.AddCard(*this->cards_stats[static_cast<int>(CardID::Squall)]);
		this->player_2.AddCard(*this->cards_stats[static_cast<int>(CardID::Funguar)]);
		this->player_2.AddCard(*this->cards_stats[static_cast<int>(CardID::Quistis)]);
		this->player_2.AddCard(*this->cards_stats[static_cast<int>(CardID::BiteBug)]);
	}
}

void GameTripleTriad::BuildCards()
{
	Video& video = this->GetVideo();

	for (auto& iterator : this->player_1.GetCards())
		this->current_game_cards.push_back(&iterator);

	for (auto& iterator : this->player_2.GetCards())
		this->current_game_cards.push_back(&iterator);

	this->built_cards_texture = &video.GetLastRenderTarget().GetTexture();

	RenderTargetCard::BuildCards(video,this->render_target_cards,this->current_game_cards,this->built_cards_texture->GetWidth());

	const Texture& card_back_face_texture = video.GetTexture(static_cast<int>(FileID::TextureCardBackFace));

	for (size_t i = 0; i < this->current_game_cards.size(); i++)
	{
		Card& iterator = *this->current_game_cards[i];

		const bool blue = i < 5;

		iterator.ModelTextureUpdate(*this->built_cards_texture,card_back_face_texture,i);
		iterator.SetColor(blue);
		iterator.SetPosition(static_cast<float>(video.GetVirtualWidth()),static_cast<float>(video.GetVirtualHeight()));
	}
}

void GameTripleTriad::NewMatchGame(const bool player_1_is_human_player,const bool player_2_is_human_player)
{
	const Video& video = this->GetVideo();

	const bool human_vs_human = player_1_is_human_player && player_2_is_human_player;
	const bool open_rule = this->IsRuleEnabled(static_cast<int>(RuleID::Open));

	const bool player_1_flip_cards = false;
	const bool player_2_flip_cards = human_vs_human ? true : open_rule;
	const bool player_1_hidden_cards = false;
	const bool player_2_hidden_cards = human_vs_human ? false : !open_rule;

	this->player_1.Initialize(player_1_flip_cards,player_1_hidden_cards,player_1_is_human_player);
	this->player_2.Initialize(player_2_flip_cards,player_2_hidden_cards,player_2_is_human_player);
	this->AddCards();
	this->BuildCards();
	this->board.BuildBoard(video,this->IsRuleEnabled(static_cast<int>(RuleID::Elemental)));
}

void GameTripleTriad::DoneMatchGame()
{
	this->render_target_cards.clear();
	this->current_game_cards.clear();
}

bool GameTripleTriad::PrepareForMatchGameUpdate()
{
	const Video& video = this->GetVideo();
	Audio& audio = this->GetAudio();
	const Timer& timer = this->GetTimer();

	this->board.Update(timer);

	for (auto& iterator : this->render_target_cards)
		iterator->Update();

	this->player_1.Update(video);
	this->player_2.Update(video);

	for (auto& iterator : this->current_game_cards)
		iterator->SetColor(&iterator->GetCapturedPlayer() == &this->player_1);

	this->player_2.PrepareToPlaceCards(timer,100.0f - (Card::GetWidth() / 2.0f),static_cast<float>(video.GetVirtualHeight()));

	if (this->player_2.PlaceCards(audio,timer))
	{
		this->player_1.PrepareToPlaceCards(timer,video.GetVirtualWidth() - 100.0f - (Card::GetWidth() / 2.0f),static_cast<float>(video.GetVirtualHeight()));

		if (this->player_1.PlaceCards(audio,timer))
		{
			this->player_2.PrepareToFlipCards(timer);
			if (this->player_2.FlipCards(timer))
				return true;
		}
	}
	return false;
}

void GameTripleTriad::MatchGameStatedUpdate()
{
	const Timer& timer = this->GetTimer();

	this->player_1.MatchGameStatedUpdate(timer,this->player_2,this->current_game_cards);
	this->player_2.MatchGameStatedUpdate(timer,this->player_1,this->current_game_cards);
}

void GameTripleTriad::Show(const bool show_elementals)
{
	Video& video = this->GetVideo();

	this->board.Show(video,show_elementals);

	for (auto& iterator : this->render_target_cards)
		iterator->Show(video);

	this->player_1.ShowCardsPlacedOnBoard(video);
	this->player_2.ShowCardsPlacedOnBoard(video);

	this->player_1.ShowCardsOnHand(video);
	this->player_2.ShowCardsOnHand(video);

	this->player_1.ShowCardsCapturing(video);
	this->player_2.ShowCardsCapturing(video);
}
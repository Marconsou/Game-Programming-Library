#include "MatchGame.h"

using namespace std;
using namespace GPL;
using namespace TT;

MatchGame::MatchGame()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();
	const Video& video = game.GetVideo();

	const float width = 35.0f;
	const float height = 50.0f;

	this->player_turn_indicator.SetVertexPosition(0,0.0f,0.0f,0.0f);
	this->player_turn_indicator.SetVertexPosition(1,-width / 2.0f,-height,-width / 2.0f);
	this->player_turn_indicator.SetVertexPosition(2,width / 2.0f,-height,-width / 2.0f);
	this->player_turn_indicator.SetVertexPosition(3,0.0f,-height,width / 2.0f);

	this->player_turn_indicator.GetTransform().SetX(0.0f);
	this->player_turn_indicator.GetTransform().SetY(-height / 2.0f);
	this->player_turn_indicator.GetTransform().SetZ(-width / 2.0f);

	this->player_turn_indicator.GetRotate().SetX(15.0f);

	this->player_turn_indicator.SetIndex(0,0);
	this->player_turn_indicator.SetIndex(1,1);
	this->player_turn_indicator.SetIndex(2,2);

	this->player_turn_indicator.SetIndex(3,2);
	this->player_turn_indicator.SetIndex(4,3);
	this->player_turn_indicator.SetIndex(5,0);

	this->player_turn_indicator.SetIndex(6,0);
	this->player_turn_indicator.SetIndex(7,3);
	this->player_turn_indicator.SetIndex(8,1);

	this->player_turn_indicator.SetIndex(9,1);
	this->player_turn_indicator.SetIndex(10,3);
	this->player_turn_indicator.SetIndex(11,2);

	this->player_turn_indicator.SetVertexColor(0,Color::Yellow);
	this->player_turn_indicator.SetVertexColor(1,Color::Gold);
	this->player_turn_indicator.SetVertexColor(2,Color::Bronze);
	this->player_turn_indicator.SetVertexColor(3,Color::Orange);

	this->cursor_selecting_card.SetTexture(video.GetTexture(static_cast<int>(FileID::TextureInterface)));
	this->cursor_selecting_card.SetSize(60.0f,35.0f);

	this->cursor_placing_card.SetTexture(video.GetTexture(static_cast<int>(FileID::TextureInterface)));
	this->cursor_placing_card.SetSize(60.0f,35.0f);

	this->player_1_score.SetText(game.GetVideo().GetFont(static_cast<int>(FileID::FontTimesNewRomanBoldItalic)),"");
	this->player_2_score.SetText(game.GetVideo().GetFont(static_cast<int>(FileID::FontTimesNewRomanBoldItalic)),"");

	this->window.SetWindow(16,1);
	this->window.SetPosition(static_cast<float>(game.GetVideo().GetVirtualWidth() / 2.0f),static_cast<float>(game.GetVideo().GetVirtualHeight()) - this->window.GetH(),true);

	this->info.SetText(game.GetVideo().GetFont(static_cast<int>(FileID::FontSegoeUIBold)),"INFO.",Color::Silver);
	this->info.SetPosition(this->window.GetX() + 10.0f,this->window.GetY());
}

MatchGame::~MatchGame()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	game.DoneMatchGame();
}

void MatchGame::PrepareSpinningIndicator()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();
	const Video& video = game.GetVideo();
	Audio& audio = game.GetAudio();
	const Timer& timer = game.GetTimer();

	this->prepare_spinning_indicator = false;
	this->show_player_turn_indicator = true;
	this->spinning_indicator = true;
	this->selecting_card_from_hand = true;
	this->rotate_accel_indicator = 1.0f;

	audio.PlaySoundFromBuffer(static_cast<int>(FileID::SoundRandomPlayerTurn));

	this->player_turn_indicator.GetTranslate().SetX(video.GetVirtualWidth() / 2.0f);
	this->player_turn_indicator.GetTranslate().SetY((video.GetVirtualHeight() / 2.0f) + 10.0f);

	this->player_turn_indicator.GetScale().SetX(1.75f);
	this->player_turn_indicator.GetScale().SetY(1.75f);

	this->start_spinning_indicator_timer.Synchronize(timer);
	this->finish_spinning_indicator_timer.Synchronize(timer);
}

void MatchGame::StartSpinningIndicator()
{
	static bool change_accel = false;

	const float speed = 2.0f;
	const float initial = 0.0f;
	const float final = 73.0f;

	if (!change_accel)
		this->rotate_accel_indicator = min(this->rotate_accel_indicator + speed,final);
	else
		this->rotate_accel_indicator = max(this->rotate_accel_indicator - speed,initial);

	if (this->rotate_accel_indicator == final)
		change_accel = true;

	else if (this->rotate_accel_indicator == initial)
		change_accel = false;
}

void MatchGame::RandomPlayerTurn()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	Point3D<float>& rotate = this->player_turn_indicator.GetRotate();

	const int player_number = Random::GenerateNumber(0,1);

	game.SetCurrentPlayer(player_number);

	if (player_number == 0)
		rotate.SetZ(270.0f);

	else if (player_number == 1)
		rotate.SetZ(90.0f);
}

void MatchGame::FinishSpinningIndicator()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	const Timer& timer = game.GetTimer();

	this->RandomPlayerTurn();

	this->spinning_indicator = false;

	this->rotate_accel_indicator = 0.0f;

	this->indicator_movement_timer.SetInterval(0.100f);
	this->indicator_movement_timer.Synchronize(timer);
}

void MatchGame::IndicatorMovement()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	Point3D<float>& rotate = this->player_turn_indicator.GetRotate();

	const Point2D<float>& position = game.GetCurrentPlayer().GetPosition();

	Point3D<float>& translate = this->player_turn_indicator.GetTranslate();

	const float translate_speed = (!this->start_match_game) ? 15.0f : 30.0f;

	if (translate.GetX() < position.GetX())
		translate.SetX(translate.GetX() + translate_speed);
	else
		translate.SetX(translate.GetX() - translate_speed);

	if (abs(translate.GetX() - position.GetX()) <= translate_speed)
		translate.SetX(position.GetX());



	if (translate.GetY() < position.GetY())
		translate.SetY(translate.GetY() + translate_speed);
	else
		translate.SetY(translate.GetY() - translate_speed);

	if (abs(translate.GetY() - position.GetY()) <= translate_speed)
		translate.SetY(position.GetY());


	Point3D<float>& scale = this->player_turn_indicator.GetScale();

	const float scale_speed = 0.05f;

	scale.SetX(max(scale.GetX() - scale_speed,1.0f));
	scale.SetY(max(scale.GetY() - scale_speed,1.0f));

	if (!this->start_match_game)
	{
		const float rotate_speed = 0.5f;

		if (game.IsPlayer2Turn())
			this->rotate_accel_indicator -= rotate_speed;

		else if (game.IsPlayer1Turn())
			this->rotate_accel_indicator += rotate_speed;
	}

	if ((translate.GetX() == position.GetX()) && (translate.GetY() == position.GetY()))
	{
		this->start_match_game = true;
	}

	if (this->start_match_game)
		rotate.SetY(rotate.GetY() + 5.0f);
}

void MatchGame::IndicatorRotationUpdate()
{
	Point3D<float>& rotate = this->player_turn_indicator.GetRotate();

	rotate.SetZ(rotate.GetZ() + this->rotate_accel_indicator);
}

void MatchGame::ResetIndicatorRotation()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	Point3D<float>& rotate = this->player_turn_indicator.GetRotate();

	if (game.IsPlayer2Turn())
	{
		if (rotate.GetZ() < 0.0f)
		{
			rotate.SetZ(0.0f);
			this->rotate_accel_indicator = 0.0f;
		}
	}

	else if (game.IsPlayer1Turn())
	{
		if (rotate.GetZ() > 360.0f)
		{
			rotate.SetZ(360.0f);
			this->rotate_accel_indicator = 0.0f;
		}
	}
}

void MatchGame::PlayerSelectsCard()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();
	Audio& audio = game.GetAudio();
	Input& input = game.GetInput();

	bool play_cursor_move = false;

	Player& current_player = game.GetCurrentPlayer();
	Player& opponent_player = game.GetOpponentPlayer();

	if (!current_player.IsHumanPlayer())
	{
		if (!game.GetBoard().IsBoardFull())
		{
			static bool skip_loop{true};
			static Card* current_card{};
			static const Minimax::Card* best_card{};
			static int best_position = INT_MIN;
			static int score = INT_MIN;
			static int cards_on_hand_checked = 0;

			if (!skip_loop)
			{
				if (this->player_turn_indicator.GetTranslate().GetX() == current_player.GetPosition().GetX())
				{
					current_card = &current_player.GetCards()[this->cursor_selecting_card_quantity.GetCurrent()];

					const int cards_on_hand = current_player.CardsOnHand();

					const int difficulty_level = game.GetDifficultyLevel().GetCurrent();

					#ifdef _DEBUG
					const int depth = 5 + difficulty_level - cards_on_hand;
					#else
					const int depth = 6 + difficulty_level - cards_on_hand;
					#endif

					Minimax::ComputerMove(current_card,game.GetCurrentGameCards(),game.GetBoard(),opponent_player,current_player,best_card,best_position,score,depth);

					if (cards_on_hand_checked == cards_on_hand)
					{
						//DELETE ME
						if (!best_card)
						{
							int debug = 1;
						}
						//DELETE ME

						this->cursor_placing_card_quantity.SetCurrent(best_position);
						this->selecting_card = best_card->source_card;

						this->ConfirmPlaceCardOnBoard();

						//Reset
						current_card = nullptr;
						best_card = nullptr;
						best_position = INT_MIN;
						score = INT_MIN;
						cards_on_hand_checked = 0;
					}
					else
					{
						this->MoveCursorSelectingCard(true);
						cards_on_hand_checked++;
						play_cursor_move = true;
						skip_loop = true;
					}
				}
			}
			else
			{
				skip_loop = false;
			}
		}
	}
	else
	{
		if (input.IsKeyboardKeyPressedOnce(current_player.GetKeyboardKeyConfirm()) || (input.IsJoystickButtonPressedOnce(current_player.GetJoystickButtonConfirm())))
		{
			this->selecting_card_from_hand = false;
			this->selecting_place_on_the_board = true;

			this->cursor_placing_card_quantity.SetCurrent(static_cast<int>(BoardSlotLayout::Center));

			play_cursor_move = true;
		}
		else if (input.IsKeyboardKeyPressedOnce(current_player.GetKeyboardKeyCancel()) || (input.IsJoystickButtonPressedOnce(current_player.GetJoystickButtonCancel())))
		{

		}
		else if (input.IsKeyboardKeyPressedOnce(current_player.GetKeyboardKeyDown()) || (input.IsJoystickPOVDown()))
		{
			if (this->MoveCursorSelectingCard(true))
				play_cursor_move = true;
		}
		else if (input.IsKeyboardKeyPressedOnce(current_player.GetKeyboardKeyUp()) || (input.IsJoystickPOVUp()))
		{
			if (this->MoveCursorSelectingCard(false))
				play_cursor_move = true;
		}
	}

	if (play_cursor_move)
		audio.PlaySoundFromBuffer(static_cast<int>(FileID::SoundCursorMove));

	this->SelectingCardUpdate();
}

bool MatchGame::MoveCursorSelectingCard(const bool next)
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	Player& current_player = game.GetCurrentPlayer();

	const int current = this->cursor_selecting_card_quantity.GetCurrent();

	do
	{
		if (next)
			this->cursor_selecting_card_quantity.Next();
		else
			this->cursor_selecting_card_quantity.Previous();

	}
	while (!this->IsSelectingCardOnHand());

	return (current != this->cursor_selecting_card_quantity.GetCurrent());
}

void MatchGame::MoveCursorSelectingCardToFirstOnHand()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	Player& current_player = game.GetCurrentPlayer();

	this->cursor_selecting_card_quantity.SetCurrent(0);

	while (!this->IsSelectingCardOnHand())
	{
		this->cursor_selecting_card_quantity.Next();
	}

	this->SelectingCardUpdate();
}

bool MatchGame::IsSelectingCardOnHand() const
{
	return (GameState::GetGame<GameTripleTriad>().GetCurrentPlayer().GetCard(this->cursor_selecting_card_quantity.GetCurrent()).GetCardState() == CardState::OnHand);
}

void MatchGame::SelectingCardUpdate()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	Player& current_player = game.GetCurrentPlayer();

	this->selecting_card = &current_player.GetCard(this->cursor_selecting_card_quantity.GetCurrent());

	const float cursor_half_width = this->cursor_selecting_card.GetW() / 2.0f;
	const float card_half_width = Card::GetWidth() / 2.0f;
	const float adjust_x = 15.0f;

	const float added_x = (game.IsPlayer1Turn() ? (-card_half_width - cursor_half_width - adjust_x) : (card_half_width + cursor_half_width + adjust_x));
	const float added_y = 15.0f;

	this->cursor_selecting_card.SetPosition(this->selecting_card->GetX() + (Card::GetWidth() / 2.0f) + added_x,this->selecting_card->GetY() + (Card::GetHeight() / 2.0f) + added_y,true);
	this->cursor_selecting_card.SetTurnHorizontal(game.IsPlayer2Turn());
	this->cursor_selecting_card.SetColor(Color(this->cursor_selecting_card.GetColor(),1.0f));
}

void MatchGame::ConfirmPlaceCardOnBoard()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	this->placing_card_on_the_board = true;
	this->placing_card = this->selecting_card;
	this->raising_card = true;
	this->raising_card_y_accel = 0.0f;
	this->placing_card->SetCardState(CardState::RaisingFromHand);
	game.GetAudio().PlaySoundFromBuffer(static_cast<int>(FileID::SoundDrawCard));
}

void MatchGame::PlayerPlacesCardOnBoard()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();
	Audio& audio = game.GetAudio();
	Input& input = game.GetInput();

	bool play_cursor_move = false;

	Player& current_player = game.GetCurrentPlayer();

	int current = this->cursor_placing_card_quantity.GetCurrent();

	if (input.IsKeyboardKeyPressedOnce(current_player.GetKeyboardKeyConfirm()) || input.IsJoystickButtonPressedOnce(current_player.GetJoystickButtonConfirm()))
	{
		if (!&game.GetBoard().GetBoardSlotCard(this->cursor_placing_card_quantity.GetCurrent()))
		{
			this->ConfirmPlaceCardOnBoard();
			play_cursor_move = true;
		}
		else
			audio.PlaySoundFromBuffer(static_cast<int>(FileID::SoundCursorError));
	}
	else if (input.IsKeyboardKeyPressedOnce(current_player.GetKeyboardKeyCancel()) || input.IsJoystickButtonPressedOnce(current_player.GetJoystickButtonCancel()))
	{
		this->selecting_card_from_hand = true;
		this->selecting_place_on_the_board = false;
		audio.PlaySoundFromBuffer(static_cast<int>(FileID::SoundCursorCancel));
	}
	else if (input.IsKeyboardKeyPressedOnce(current_player.GetKeyboardKeyLeft()) || input.IsJoystickPOVLeft())
	{
		if (current % 3 != 0)
		{
			this->cursor_placing_card_quantity.SetCurrent(current - 1);
			play_cursor_move = true;
		}
	}
	else if (input.IsKeyboardKeyPressedOnce(current_player.GetKeyboardKeyRight()) || input.IsJoystickPOVRight())
	{
		if (current % 3 != 2)
		{
			this->cursor_placing_card_quantity.SetCurrent(current + 1);
			play_cursor_move = true;
		}
	}
	else if (input.IsKeyboardKeyPressedOnce(current_player.GetKeyboardKeyDown()) || (input.IsJoystickPOVDown()))
	{
		if (current - 5 <= 0)
		{
			this->cursor_placing_card_quantity.SetCurrent(current + 3);
			play_cursor_move = true;
		}
	}
	else if (input.IsKeyboardKeyPressedOnce(current_player.GetKeyboardKeyUp()) || input.IsJoystickPOVUp())
	{
		if (current - 2 > 0)
		{
			this->cursor_placing_card_quantity.SetCurrent(current - 3);
			play_cursor_move = true;
		}
	}

	if (play_cursor_move)
		audio.PlaySoundFromBuffer(static_cast<int>(FileID::SoundCursorMove));

	this->cursor_selecting_card.SetColor(Color(this->cursor_selecting_card.GetColor(),0.5f));
}

void MatchGame::StartMatchGameUpdate()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	if (this->selecting_card)
		this->selecting_card->AdvancePosition(game.GetVideo());

	const Point2D<float>& current_board_slot_position = game.GetBoard().GetBoardSlotPosition(this->cursor_placing_card_quantity.GetCurrent());

	this->cursor_placing_card.SetPosition(current_board_slot_position.GetX() - this->cursor_placing_card.GetW(),current_board_slot_position.GetY());
}

void MatchGame::RaisingCard()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();
	const Video& video = game.GetVideo();
	const Timer& timer = game.GetTimer();

	const Board& board = game.GetBoard();

	const Point2D<float>& current_board_slot_position = board.GetBoardSlotPosition(this->cursor_placing_card_quantity.GetCurrent());

	if (this->raising_card_timer.Action(timer))
	{
		this->raising_card_y_accel += 1.5f;

		float scale = this->placing_card->GetScale();

		if (this->raising_card)
			scale += 0.015f;
		else
		{
			if (current_board_slot_position.GetY() == board.GetBoardSlotPosition(static_cast<int>(BoardSlotLayout::Top)).GetY())
				scale -= 0.030f;

			else if (current_board_slot_position.GetY() == board.GetBoardSlotPosition(static_cast<int>(BoardSlotLayout::Center)).GetY())
				scale -= 0.023f;

			else if (current_board_slot_position.GetY() == board.GetBoardSlotPosition(static_cast<int>(BoardSlotLayout::Bottom)).GetY())
				scale -= 0.019f;
		}

		this->placing_card->SetScale(min(max(scale,1.0f),1.5f));
	}

	//Carta sendo levantada e está fora da tela
	if ((this->raising_card) && (this->placing_card->GetY() + Card::GetHeight() < 0.0f))
	{
		if (this->raising_card)
			this->RaisedCardOffScreen();

		this->raising_card = false;
	}

	const float raising_card_y = this->placing_card->GetY() + ((this->raising_card) ? (-this->raising_card_y_accel) : (this->raising_card_y_accel));

	this->placing_card->SetY(raising_card_y);

	if (!this->raising_card)
	{
		//Carta está indo em direção ao ponto central do Board Slot
		if (this->placing_card->GetY() + (Card::GetHeight() / 2.0f) > current_board_slot_position.GetY())
			this->CardPlacedOnBoard();
	}
}

void MatchGame::RaisedCardOffScreen()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();
	const Board& board = game.GetBoard();

	this->selecting_card = nullptr;
	this->raising_card_y_accel = 0.0f;

	const Point2D<float>& current_board_slot_position = board.GetBoardSlotPosition(this->cursor_placing_card_quantity.GetCurrent());

	this->placing_card->SetPosition(current_board_slot_position.GetX() - (Card::GetWidth() / 2.0f),0.0f - (Card::GetHeight() * 2.0f));
	this->placing_card->SetScale(1.65f);
	this->placing_card->SetRotateY(0.0f);
}

void MatchGame::CardPlacedOnBoard()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();
	Audio& audio = game.GetAudio();
	Board& board = game.GetBoard();

	const Point2D<float>& current_board_slot_position = board.GetBoardSlotPosition(this->cursor_placing_card_quantity.GetCurrent());

	this->placing_card->SetPosition(current_board_slot_position.GetX(),current_board_slot_position.GetY(),true);
	this->placing_card->SetScale(1.0f);

	this->selecting_card_from_hand = true;
	this->selecting_place_on_the_board = false;
	this->placing_card_on_the_board = false;
	board.SetBoardSlotCard(this->cursor_placing_card_quantity.GetCurrent(),*this->placing_card);
	board.BoardSlotElementalsUpdate();
	this->placing_card->SetCardState(CardState::PlacedOnBoard);

	if (Rule::CheckForBasicRule(board,*this->placing_card,game.IsRuleEnabled(static_cast<int>(RuleID::Elemental))))
	{
		audio.PlaySoundFromBuffer(static_cast<int>(FileID::SoundTurnCard));
		this->wait_for_cards_being_captured = true;
	}
	else
		this->PassPlayerTurn();

	this->placing_card = nullptr;
}

void MatchGame::PassPlayerTurn()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	if (!game.AnyCardIsBeingCaptured())
	{
		if (!game.GetBoard().IsBoardFull())
		{
			game.PassPlayerTurn();

			this->MoveCursorSelectingCardToFirstOnHand();
			this->wait_for_cards_being_captured = false;
		}
		else
		{
			this->MatchEnded();
		}
	}
}

void MatchGame::PlayerScoreUpdate()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	const Video& video = game.GetVideo();

	const Point2D<float>* position = &game.GetPlayer1().GetPosition();

	this->player_1_score.SetString(Convert::NumberToString(game.CalculateScorePlayer1()));
	this->player_1_score.SetPosition(position->GetX(),video.GetVirtualHeight() - this->player_1_score.GetH(),true);
	this->player_1_score.SetColorBottom(Color::Gray);


	position = &game.GetPlayer2().GetPosition();

	this->player_2_score.SetString(Convert::NumberToString(game.CalculateScorePlayer2()));
	this->player_2_score.SetPosition(position->GetX(),video.GetVirtualHeight() - this->player_2_score.GetH(),true);
	this->player_2_score.SetColorBottom(Color::Gray);
}

void MatchGame::CardName()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	const Card& board_slot_card = game.GetBoard().GetBoardSlotCard(this->cursor_placing_card_quantity.GetCurrent());

	const string& placed_card_name = (&board_slot_card) ? board_slot_card.GetCardStats().GetName() : "";

	const string& name = ((this->selecting_card) && (this->selecting_card_from_hand)) ? this->selecting_card->GetCardStats().GetName() :
		((!placed_card_name.empty()) && (this->selecting_place_on_the_board)) ? placed_card_name : "";

	bool remove_info = (name.empty()) || ((this->selecting_card_from_hand) && (game.GetCurrentPlayer().IsHiddenCards()));

	if (remove_info)
	{
		this->window.RemoveControl();
		this->info.RemoveControl();
		this->card_name.RemoveControl();
	}
	else
	{
		this->card_name.SetText(game.GetVideo().GetFont(static_cast<int>(FileID::FontTahoma)),name,Color::Platinum);
		this->card_name.SetPosition(this->window.GetX() + (this->window.GetW() / 2.0f),this->window.GetY() + (this->window.GetH() / 2.0f),true);

		this->window.AddControl();
		this->info.AddControl();
		this->card_name.AddControl();
	}
}

void MatchGame::Update()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();
	const Timer& timer = game.GetTimer();

	bool close_menu = false;

	if (!this->match_ended)
	{
		if (game.PrepareForMatchGameUpdate())
		{
			if (this->prepare_spinning_indicator)
				this->PrepareSpinningIndicator();

			if (this->spinning_indicator)
			{
				if (this->start_spinning_indicator_timer.Action(timer))
					this->StartSpinningIndicator();

				if (this->finish_spinning_indicator_timer.Action(timer))
					this->FinishSpinningIndicator();
			}
			else
			{
				if (this->indicator_movement_timer.Action(timer))
				{
					const float new_interval = 0.015f;

					if (this->indicator_movement_timer.GetInterval() != new_interval)
						this->indicator_movement_timer.SetInterval(new_interval);
					else
						this->IndicatorMovement();
				}
			}

			this->IndicatorRotationUpdate();

			if (this->start_match_game)
			{
				this->ResetIndicatorRotation();

				if (!this->placing_card_on_the_board)
				{
					if (this->selecting_card_from_hand)
					{
						if (!this->wait_for_cards_being_captured)
							this->PlayerSelectsCard();
					}

					else if (this->selecting_place_on_the_board)
						this->PlayerPlacesCardOnBoard();
				}
				else
					this->RaisingCard();

				this->StartMatchGameUpdate();
			}

			if (this->wait_for_cards_being_captured)
				this->PassPlayerTurn();

			game.MatchGameStatedUpdate();

			this->PlayerScoreUpdate();
			this->CardName();
		}
	}
	else
	{
		if ((game.GetInput().IsAnyKeyboardKeyPressedOnce() != KeyboardKey::Unknown) || (game.GetInput().IsAnyJoystickButtonPressedOnce() != JoystickButton::Unknown))
		{
			close_menu = true;
		}
	}

	//DELETE ME
	if ((close_menu) || ((game.GetInput().IsKeyboardKeyPressed(KeyboardKey::Esc) || (game.GetInput().IsJoystickButtonPressedOnce(JoystickButton::Button10)))))
	{
		game.GetAudio().PlaySoundFromBuffer(static_cast<int>(FileID::SoundCursorCancel));
		GameState::AddGameState(nullptr,GameStateAction::DeleteCurrentGameState);
	}
	//DELETE ME
}

void MatchGame::MatchEnded()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();

	if (game.GetBoard().IsBoardFull())
	{
		this->match_ended = true;

		int player_1_score = game.CalculateScorePlayer1();
		int player_2_score = game.CalculateScorePlayer2();

		if (player_1_score > player_2_score)
		{
			this->match_result.SetText(game.GetVideo().GetFont(static_cast<int>(FileID::FontAlgerian)),"Player Won!",Color(0.75f,0.85f,1.0f));
		}
		else if (player_1_score < player_2_score)
		{
			this->match_result.SetText(game.GetVideo().GetFont(static_cast<int>(FileID::FontAlgerian)),"Player Won!",Color(0.82f,0.50f,0.62f));
		}
		else
		{
			this->match_result.SetText(game.GetVideo().GetFont(static_cast<int>(FileID::FontAlgerian)),"Draw",Color(0.30f,0.88f,0.30f));
		}

		this->match_result.SetAlpha(0.25f);
		this->match_result.SetScaleX(0.25f);
		this->match_result.SetScaleY(0.25f);
		this->match_result.SetTransformX(this->match_result.GetW() / 2.0f);
		this->match_result.SetTransformY(this->match_result.GetH() / 2.0f);

		this->selecting_card = nullptr;
		this->placing_card = nullptr;
	}
}

void MatchGame::Show()
{
	GameTripleTriad& game = GameState::GetGame<GameTripleTriad>();
	Video& video = game.GetVideo();

	game.Show(this->show_player_turn_indicator);

	if (!game.GetBoard().IsBoardFull())
	{
		if (this->show_player_turn_indicator)
			video.Draw(this->player_turn_indicator);

		if (this->start_match_game)
		{
			if (!this->placing_card_on_the_board)
			{
				if (!this->wait_for_cards_being_captured)
				{
					this->cursor_selecting_card.Show(video);

					if (this->selecting_place_on_the_board)
						this->cursor_placing_card.Show(video);
				}
			}
		}
	}
	else
	{
		if (this->match_ended)
		{
			static Interval interval(0.015f);

			if (interval.Action(game.GetTimer()))
			{
				float alpha_increment = 0.02f;
				float scale_increment = 0.06f;

				this->match_result.SetAlpha(min(this->match_result.GetAlpha() + alpha_increment,1.0f));
				this->match_result.SetScaleX(min(this->match_result.GetScaleX() + scale_increment,1.50f));
				this->match_result.SetScaleY(min(this->match_result.GetScaleY() + scale_increment,1.50f));
			}

			this->match_result.SetPosition(game.GetVideo().GetVirtualWidth() / 2.0f,game.GetVideo().GetVirtualHeight() / 2.0f,true);
			this->match_result.Show(game.GetVideo());
		}
	}

	this->player_1_score.Show(video);
	this->player_2_score.Show(video);
}
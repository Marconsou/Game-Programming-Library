#include "Player.h"

using namespace std;
using namespace GPL;
using namespace TT;

Player::Player() :
kk_left{},
kk_right{},
kk_up{},
kk_down{},
kk_confirm{},
kk_cancel{}
{

}

KeyboardKey Player::GetKeyboardKeyLeft() const
{
	return this->kk_left;
}

KeyboardKey Player::GetKeyboardKeyRight() const
{
	return this->kk_right;
}

KeyboardKey Player::GetKeyboardKeyUp() const
{
	return this->kk_up;
}

KeyboardKey Player::GetKeyboardKeyDown() const
{
	return this->kk_down;
}

KeyboardKey Player::GetKeyboardKeyConfirm() const
{
	return this->kk_confirm;
}

KeyboardKey Player::GetKeyboardKeyCancel() const
{
	return this->kk_cancel;
}

JoystickButton Player::GetJoystickButtonConfirm() const
{
	return this->jb_confirm;
}

JoystickButton Player::GetJoystickButtonCancel() const
{
	return this->jb_cancel;
}

const Point2D<float>& Player::GetPosition() const
{
	return this->position;
}

Card& Player::GetCard(const size_t index)
{
	return this->cards[index];
}

Player::Cards& Player::GetCards()
{
	return this->cards;
}

const Player::Cards& Player::GetCards() const
{
	return this->cards;
}

bool Player::IsHumanPlayer() const
{
	return this->human_player;
}

bool Player::IsHiddenCards() const
{
	return this->hidden_cards;
}

void Player::Initialize(const bool flip_cards,const bool hidden_cards,bool is_human_player)
{
	this->add_card_index = 0;
	this->human_player = is_human_player;
	this->prepare_to_place_cards = true;
	this->placing_cards = false;
	this->prepare_to_flip_cards = false;
	this->flipping_cards = false;
	this->hidden_cards = hidden_cards;
	this->raising_from_hand = false;
	this->raising_from_hand_card = nullptr;

	for (auto& iterator : this->cards)
	{
		iterator.SetScale(1.0f);
		iterator.SetRotateY((flip_cards || hidden_cards) ? 180.0f : 0.0f);
		iterator.SetCardState(CardState::OnHand);
		iterator.SetElementalModifier(ElementalModifier::None);
	}
}

int Player::CalculateScore(const vector<Card*>& current_game_cards) const
{
	int score = 0;
	for (auto& iterator : current_game_cards)
	{
		if (&iterator->GetCapturedPlayer() == this)
			score++;
	}
	return score;
}

int Player::CardsOnHand() const
{
	int quantity = 0;
	for (auto& iterator : this->cards)
	{
		if (iterator.GetCardState() == CardState::OnHand)
			quantity++;
	}
	return quantity;
}

void Player::KeyboardKeyActions(const KeyboardKey left,const KeyboardKey right,const KeyboardKey up,const KeyboardKey down,const KeyboardKey confirm,const KeyboardKey cancel)
{
	this->kk_left = left;
	this->kk_right = right;
	this->kk_up = up;
	this->kk_down = down;
	this->kk_confirm = confirm;
	this->kk_cancel = cancel;
}

void Player::JoystickButtonActions(const JoystickButton confirm,const JoystickButton cancel)
{
	this->jb_confirm = confirm;
	this->jb_cancel = cancel;
}

void Player::AddCard(const CardStats& card_stats)
{
	Card& card = this->cards[this->add_card_index];

	card.SetCardStats(card_stats);
	card.SetCapturedPlayer(*this);

	this->add_card_index++;
}

void Player::PrepareToPlaceCards(const Timer& timer,const float initial_x,const float initial_y)
{
	if (this->prepare_to_place_cards)
	{
		this->prepare_to_place_cards = false;
		this->placing_cards = true;

		this->position.SetX(initial_x + (Card::GetWidth() / 2.0f));
		this->position.SetY(75.0f);

		for (size_t i = 0; i < this->cards_animation.size(); i++)
		{
			CardAnimation& iterator = this->cards_animation[i];

			Card& card = this->cards[i];

			card.SetPosition(initial_x,initial_y);

			iterator.start_placing_card = false;
			iterator.card_placed = false;

			iterator.placing_card_limit = 50.0f + (i * (Card::GetHeight() / 2.0f));
			iterator.placing_card_accel = 60.0f - (i * 11.0f);

			iterator.start_placing_card_timer.SetInterval(i * 0.085f);
			iterator.start_placing_card_timer.Synchronize(timer);

			iterator.placing_card_accel_timer.SetInterval(0.015f);
			iterator.placing_card_accel_timer.Synchronize(timer);
		}
	}
}

bool Player::PlaceCards(Audio& audio,const Timer& timer)
{
	if (this->placing_cards)
	{
		for (size_t i = 0; i < this->cards_animation.size(); i++)
		{
			CardAnimation& iterator = this->cards_animation[i];

			if (iterator.start_placing_card_timer.Action(timer))
			{
				if (!iterator.start_placing_card)
					audio.PlaySoundFromBuffer(static_cast<int>(FileID::SoundDrawCard));

				iterator.start_placing_card = true;
			}

			if ((iterator.start_placing_card) && (!iterator.card_placed))
			{
				Card& card = this->cards[i];

				if (iterator.placing_card_accel_timer.Action(timer))
				{
					card.SetY(max(card.GetY() - iterator.placing_card_accel,iterator.placing_card_limit));

					if (card.GetY() == iterator.placing_card_limit)
						iterator.card_placed = true;
				}
			}
		}

		this->placing_cards = !this->cards_animation.back().card_placed;

		if (!this->placing_cards)
			this->prepare_to_flip_cards = true;
	}

	return !this->placing_cards;
}

void Player::PrepareToFlipCards(const Timer& timer)
{
	if (this->prepare_to_flip_cards)
	{
		if (!this->hidden_cards)
		{
			this->prepare_to_flip_cards = false;
			this->flipping_cards = true;

			for (size_t i = 0; i < this->cards_animation.size(); i++)
			{
				CardAnimation& iterator = this->cards_animation[i];

				iterator.start_flipping_card = false;
				iterator.card_flipped = false;

				iterator.start_flipping_card_timer.SetInterval((this->cards_animation.size() - i) * 0.085f);
				iterator.start_flipping_card_timer.Synchronize(timer);
			}
		}
	}
}

bool Player::FlipCards(const GPL::Timer& timer)
{
	if (this->flipping_cards)
	{
		for (size_t i = 0; i < this->cards_animation.size(); i++)
		{
			CardAnimation& iterator = this->cards_animation[i];

			if (iterator.start_flipping_card_timer.Action(timer))
				iterator.start_flipping_card = true;

			if ((iterator.start_flipping_card) && (!iterator.card_flipped))
			{
				if (iterator.flipping_card_accel_timer.Action(timer))
				{
					Card& card = this->cards[i];

					const float rotate_y = card.GetRotateY();

					if (rotate_y > 0.0f)
						card.SetRotateY(max(rotate_y - 7.0f,0.0f));
					else
						iterator.card_flipped = true;
				}
			}
		}

		this->flipping_cards = !this->cards_animation.front().card_flipped;
	}

	return !this->flipping_cards;
}

void Player::MovingCardsDown(const Timer& timer)
{
	if (!this->raising_from_hand)
	{
		for (auto& iterator : this->cards)
		{
			if (iterator.GetCardState() == CardState::RaisingFromHand)
			{
				this->raising_from_hand_card = &iterator;
				this->raising_from_hand = true;
				break;
			}
		}

		if (this->raising_from_hand)
		{
			for (size_t i = 0; i < this->cards.size(); i++)
			{
				Card& card_iterator = this->cards[i];

				if (&card_iterator != this->raising_from_hand_card)
				{
					if (card_iterator.GetCardState() == CardState::OnHand)
					{
						this->cards_moving_down.push_back(&card_iterator);

						for (size_t j = i + 1; j < this->cards.size(); j++)
						{
							const Card& next_card_iterator = this->cards[j];

							if ((next_card_iterator.GetCardState() == CardState::OnHand) || (this->raising_from_hand_card == &next_card_iterator))
							{
								this->cards_moving_down_y.push_back(next_card_iterator.GetY());
								break;
							}
						}
					}
				}
				else
				{
					if (this->cards_moving_down.empty())
						this->raising_from_hand_card = nullptr;
					break;
				}
			}
		}
	}
	else
	{
		if (this->adjust_card_timer.Action(timer))
		{
			bool clear = false;

			for (size_t i = 0; i < this->cards_moving_down.size(); i++)
			{
				Card& iterator = *this->cards_moving_down[i];

				const float limit_y = this->cards_moving_down_y[i];

				iterator.SetY(min(iterator.GetY() + 5.0f,limit_y));

				if (iterator.GetY() == limit_y)
					clear = true;
			}

			if (clear)
			{
				this->raising_from_hand_card = nullptr;
				this->cards_moving_down.clear();
				this->cards_moving_down_y.clear();
			}
		}

		if (!this->raising_from_hand_card)
		{
			bool some_card_is_raising_from_hand = false;

			for (auto& iterator : this->cards)
			{
				if (iterator.GetCardState() == CardState::RaisingFromHand)
				{
					some_card_is_raising_from_hand = true;
					break;
				}
			}

			this->raising_from_hand = some_card_is_raising_from_hand;
		}
	}
}

void Player::CheckCaptureCards(const Timer& timer,const Player& player_opponent,const vector<Card*>& current_game_cards)
{
	if (this->capturing_card_timer.Action(timer))
	{
		for (auto& iterator : current_game_cards)
		{
			if (&iterator->GetCapturedPlayer() == this)
			{
				const bool captured_from_horizontal = (iterator->GetCardState() == CardState::CapturingByHorizontal);
				const bool captured_from_vertical = (iterator->GetCardState() == CardState::CapturingByVertical);

				if ((captured_from_horizontal) || (captured_from_vertical))
				{
					float rotate = (captured_from_horizontal) ? iterator->GetRotateY() : iterator->GetRotateX();

					rotate += 12.0f;

					if (!iterator->GetCapturingCardFalling())
						rotate = min(rotate,180.0f);
					else
						rotate = min(rotate,360.0f);


					if (!iterator->GetCapturingCardFalling())
						iterator->SetScale(1.0f + (rotate / 360.0f));
					else
						iterator->SetScale(1.5f + (((180.0f - rotate) / 180.0f) * 0.5f));

					if (captured_from_horizontal)
						iterator->SetRotateY(rotate);
					else
						iterator->SetRotateX(rotate);


					if (rotate == 180.0f)
					{
						iterator->SetCapturingCardFalling(true);
						iterator->SetCapturedPlayer(player_opponent);
					}

					else if (rotate == 360.0f)
					{
						iterator->SetCapturingCardFalling(false);
						iterator->SetScale(1.0f);
						iterator->SetRotateX(0.0f);
						iterator->SetRotateY(0.0f);
						iterator->SetCardState(CardState::PlacedOnBoard);
					}
				}
			}
		}
	}
}

void Player::Update(const Video& video)
{
	for (auto& iterator : this->cards)
		iterator.Update(video);
}

void Player::MatchGameStatedUpdate(const Timer& timer,const Player& player_opponent,const vector<Card*>& current_game_cards)
{
	this->MovingCardsDown(timer);
	this->CheckCaptureCards(timer,player_opponent,current_game_cards);
}

void Player::ShowCardsOnHand(Video& video)
{
	for (auto& iterator : this->cards)
	{
		const CardState card_state = iterator.GetCardState();

		if ((card_state == CardState::OnHand) || (card_state == CardState::RaisingFromHand))
			iterator.Show(video);
	}
}

void Player::ShowCardsPlacedOnBoard(Video& video)
{
	for (auto& iterator : this->cards)
	{
		const CardState card_state = iterator.GetCardState();

		if (card_state == CardState::PlacedOnBoard)
			iterator.Show(video);
	}
}

void Player::ShowCardsCapturing(Video& video)
{
	for (auto& iterator : this->cards)
	{
		const CardState card_state = iterator.GetCardState();

		if ((card_state == CardState::CapturingByHorizontal) || (card_state == CardState::CapturingByVertical))
			iterator.Show(video);
	}
}
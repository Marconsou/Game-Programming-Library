#include "Board.h"

using namespace std;
using namespace GPL;
using namespace TT;

void Board::SetBoardSlotCard(const size_t index,Card& card)
{
	this->board_slots[index].card = &card;
}

Card& Board::GetBoardSlotCard(const size_t index)
{
	return *this->board_slots[index].card;
}

const Card& Board::GetBoardSlotCard(const size_t index) const
{
	return *this->board_slots[index].card;
}

const Point2D<float>& Board::GetBoardSlotPosition(const size_t index) const
{
	return this->board_slots[index].position;
}

BoardSlotLayout Board::GetBoardSlotLayout(const Card& placed_card) const
{
	BoardSlotLayout board_slot_layout{};
	const float half_card_width = static_cast<float>(static_cast<int>(Card::GetWidth() / 2.0f));
	const float half_card_height = static_cast<float>(static_cast<int>(Card::GetHeight() / 2.0f));
	for (size_t i = 0; i < this->board_slots.size(); i++)
	{
		const Point2D<float>& position = this->board_slots[i].position;

		if (((placed_card.GetX() + half_card_width) == position.GetX()) && ((placed_card.GetY() + half_card_height) == position.GetY()))
		{
			board_slot_layout = static_cast<BoardSlotLayout>(i);
			break;
		}
	}
	return board_slot_layout;
}

void Board::GetNeighborCards(const Card& placed_card,Card*& left_card,Card*& right_card,Card*& top_card,Card*& bottom_card)
{
	int board_slot_layout_index = static_cast<int>(this->GetBoardSlotLayout(placed_card));

	const int mod_value = board_slot_layout_index % 3;

	//Add left
	if (mod_value != 0)
		left_card = &this->GetBoardSlotCard(board_slot_layout_index - 1);

	//Add right
	if (mod_value != 2)
		right_card = &this->GetBoardSlotCard(board_slot_layout_index + 1);

	//Add top
	if (board_slot_layout_index - 2 > 0)
		top_card = &this->GetBoardSlotCard(board_slot_layout_index - 3);

	//Add bottom
	if (board_slot_layout_index - 5 <= 0)
		bottom_card = &this->GetBoardSlotCard(board_slot_layout_index + 3);
}

bool Board::IsBoardFull() const
{
	size_t counter = 0;
	for (auto& iterator : this->board_slots)
	{
		if (iterator.card)
			counter++;
	}

	return (counter == this->board_slots.size());
}

void Board::Initialize(const Video& video)
{
	for (auto& iterator : this->board_slots)
		iterator.card = nullptr;

	const float space_between_cards = 3.0f;

	BoardSlot& board_slot_center = this->board_slots[static_cast<int>(BoardSlotLayout::Center)];
	board_slot_center.position.SetX(video.GetVirtualWidth() / 2.0f);
	board_slot_center.position.SetY(video.GetVirtualHeight() / 2.0f);

	BoardSlot& board_slot_left = this->board_slots[static_cast<int>(BoardSlotLayout::Left)];
	board_slot_left.position.SetX(board_slot_center.position.GetX() - Card::GetWidth() - space_between_cards);
	board_slot_left.position.SetY(board_slot_center.position.GetY());

	BoardSlot& board_slot_right = this->board_slots[static_cast<int>(BoardSlotLayout::Right)];
	board_slot_right.position.SetX(board_slot_center.position.GetX() + Card::GetWidth() + space_between_cards);
	board_slot_right.position.SetY(board_slot_center.position.GetY());


	BoardSlot& board_slot_top = this->board_slots[static_cast<int>(BoardSlotLayout::Top)];
	board_slot_top.position.SetX(board_slot_center.position.GetX());
	board_slot_top.position.SetY(board_slot_center.position.GetY() - Card::GetHeight() - space_between_cards);

	BoardSlot& board_slot_left_top = this->board_slots[static_cast<int>(BoardSlotLayout::LeftTop)];
	board_slot_left_top.position.SetX(board_slot_top.position.GetX() - Card::GetWidth() - space_between_cards);
	board_slot_left_top.position.SetY(board_slot_top.position.GetY());

	BoardSlot& board_slot_right_top = this->board_slots[static_cast<int>(BoardSlotLayout::RightTop)];
	board_slot_right_top.position.SetX(board_slot_top.position.GetX() + Card::GetWidth() + space_between_cards);
	board_slot_right_top.position.SetY(board_slot_top.position.GetY());


	BoardSlot& board_slot_bottom = this->board_slots[static_cast<int>(BoardSlotLayout::Bottom)];
	board_slot_bottom.position.SetX(board_slot_center.position.GetX());
	board_slot_bottom.position.SetY(board_slot_center.position.GetY() + Card::GetHeight() + space_between_cards);

	BoardSlot& board_slot_left_bottom = this->board_slots[static_cast<int>(BoardSlotLayout::LeftBottom)];
	board_slot_left_bottom.position.SetX(board_slot_bottom.position.GetX() - Card::GetWidth() - space_between_cards);
	board_slot_left_bottom.position.SetY(board_slot_bottom.position.GetY());

	BoardSlot& board_slot_right_bottom = this->board_slots[static_cast<int>(BoardSlotLayout::RightBottom)];
	board_slot_right_bottom.position.SetX(board_slot_bottom.position.GetX() + Card::GetWidth() + space_between_cards);
	board_slot_right_bottom.position.SetY(board_slot_bottom.position.GetY());
}

void Board::BuildBoard(const Video& video,const bool elemental)
{
	for (auto& iterator : this->board_slots)
	{
		iterator.card = nullptr;
		iterator.elemental = Elemental::None;
	}

	if (elemental)
	{
		this->enlarge_elemental = false;
		this->elemental_scale = 1.00f;

		for (auto& iterator : this->board_slots)
		{
			Sprite& elemental_sprite = iterator.elemental_sprite;

			elemental_sprite.SetTexture(video.GetTexture(static_cast<int>(FileID::TextureInterface)));
			elemental_sprite.SetSize(28.0f,28.0f);
			elemental_sprite.SetTransformX(elemental_sprite.GetW() / 2.0f);
			elemental_sprite.SetTransformY(elemental_sprite.GetH() / 2.0f);
			elemental_sprite.SetPosition(iterator.position.GetX(),iterator.position.GetY(),true);
			elemental_sprite.SetColor(Color(Color::White,0.5f));
			
		}

		this->RandomElementals();
	}
}

void Board::RandomElementals()
{
	bool elemental_randomized = false;

	const int size = static_cast<int>(BoardSlotLayout::Max);

	int i = 0;
	do
	{
		if (i == size)
		{
			i = 0;
			if (elemental_randomized)
				break;
		}

		BoardSlot& iterator = this->board_slots[i];

		const int random = Random::GenerateNumber(0,10);

		if (random == 0)
			iterator.elemental = static_cast<Elemental>(Random::GenerateNumber(static_cast<int>(Elemental::Fire),static_cast<int>(Elemental::Max) - 1));

		if (iterator.elemental != Elemental::None)
		{
			iterator.elemental_sprite.SetTexturePosition(73.0f + ((static_cast<int>(iterator.elemental) - 1) * (iterator.elemental_sprite.GetW() + 3.0f)),0.0f);
			elemental_randomized = true;
		}

		i++;

	} while ((!elemental_randomized) || (i <= size));
}

void Board::BoardSlotElementalsUpdate()
{
	for (auto& iterator : this->board_slots)
	{
		iterator.elemental_sprite.SetScaleX(this->elemental_scale);
		iterator.elemental_sprite.SetScaleY(this->elemental_scale);

		if (iterator.card)
		{
			if (iterator.elemental != Elemental::None)
			{
				const Elemental card_elemental = iterator.card->GetCardStats().GetElemental();

				if (iterator.card->GetCardStats().GetElemental() == iterator.elemental)
					iterator.card->SetElementalModifier(ElementalModifier::Bonus);
				else
					iterator.card->SetElementalModifier(ElementalModifier::Penalty);
			}
			else
				iterator.card->SetElementalModifier(ElementalModifier::None);
		}
	}
}

void Board::Update(const Timer& timer)
{
	if (this->elemental_animation_timer.Action(timer))
	{
		const float speed = 0.05f;

		if (this->enlarge_elemental)
			this->elemental_scale += speed;
		else
			this->elemental_scale -= speed;

		if (this->elemental_scale >= 1.25f)
			this->enlarge_elemental = false;

		else if (this->elemental_scale <= 0.75f)
			this->enlarge_elemental = true;
	}

	this->BoardSlotElementalsUpdate();
}

void Board::Show(Video& video,const bool show_elementals)
{
	if (show_elementals)
	{
		for (auto& iterator : this->board_slots)
		{
			if (iterator.elemental != Elemental::None)
				iterator.elemental_sprite.Show(video);
		}
	}
}
#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Random.h"
#include "Interval.h"
#include "Card.h"
#include "Main.h"

namespace TT
{
	enum class BoardSlotLayout
	{
		LeftTop,
		Top,
		RightTop,
		Left,
		Center,
		Right,
		LeftBottom,
		Bottom,
		RightBottom,
		Max,
	};

	class Board
	{
	public:
		Board() = default;
		void SetBoardSlotCard(const size_t index,Card& card);
		Card& GetBoardSlotCard(const size_t index);
		const Card& GetBoardSlotCard(const size_t index) const;
		const GPL::Point2D<float>& GetBoardSlotPosition(const size_t index) const;
		BoardSlotLayout GetBoardSlotLayout(const Card& placed_card) const;
		void GetNeighborCards(const Card& placed_card,Card*& left_card,Card*& right_card,Card*& top_card,Card*& bottom_card);
		bool IsBoardFull() const;
		void Initialize(const GPL::Video& video);
		void BuildBoard(const GPL::Video& video,const bool elemental);
		void RandomElementals();
		void BoardSlotElementalsUpdate();
		void Update(const GPL::Timer& timer);
		void Show(GPL::Video& video,const bool show_elementals);
	private:
		struct BoardSlot
		{
			Card* card{};
			Elemental elemental;
			GPL::Sprite elemental_sprite;
			GPL::Point2D<float> position;
			BoardSlot() = default;
			BoardSlot(const BoardSlot&) = delete;
			BoardSlot& operator=(const BoardSlot&) = delete;
		};
		bool enlarge_elemental{};
		float elemental_scale{};
		GPL::Interval elemental_animation_timer{0.015f};
		std::array<BoardSlot,static_cast<int>(BoardSlotLayout::Max)> board_slots;
		Board(const Board&) = delete;
		Board& operator=(const Board&) = delete;
	};
}

#endif
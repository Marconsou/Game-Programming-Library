#include "Rule.h"

using namespace std;
using namespace TT;

bool Rule::CheckForBasicRule(Board& board,const Card& placed_card,const bool elemental)
{
	Card* left_card{};
	Card* right_card{};
	Card* top_card{};
	Card* bottom_card{};

	bool card_captured = false;

	board.GetNeighborCards(placed_card,left_card,right_card,top_card,bottom_card);

	if (left_card)
	{
		if (Rule::CheckNeighborCardValue(placed_card,*left_card,Neighbor::Left,elemental))
			card_captured = true;
	}

	if (right_card)
	{
		if (Rule::CheckNeighborCardValue(placed_card,*right_card,Neighbor::Right,elemental))
			card_captured = true;
	}

	if (top_card)
	{
		if (Rule::CheckNeighborCardValue(placed_card,*top_card,Neighbor::Top,elemental))
			card_captured = true;
	}

	if (bottom_card)
	{
		if (Rule::CheckNeighborCardValue(placed_card,*bottom_card,Neighbor::Bottom,elemental))
			card_captured = true;
	}

	return card_captured;
}

bool Rule::CheckNeighborCardValue(const Card& placed_card,Card& target_card,const Neighbor neighbor,const bool elemental)
{
	if (&placed_card.GetCapturedPlayer() != &target_card.GetCapturedPlayer())
	{
		function<int(void)> value_method;
		function<int(void)> opposite_value_method;

		if (neighbor == Neighbor::Left)
		{
			value_method = bind(&CardStats::GetLeft,ref(placed_card.GetCardStats()));
			opposite_value_method = bind(&CardStats::GetRight,ref(target_card.GetCardStats()));
		}
		else if (neighbor == Neighbor::Right)
		{
			value_method = bind(&CardStats::GetRight,ref(placed_card.GetCardStats()));
			opposite_value_method = bind(&CardStats::GetLeft,ref(target_card.GetCardStats()));
		}
		else if (neighbor == Neighbor::Top)
		{
			value_method = bind(&CardStats::GetTop,ref(placed_card.GetCardStats()));
			opposite_value_method = bind(&CardStats::GetBottom,ref(target_card.GetCardStats()));
		}
		else if (neighbor == Neighbor::Bottom)
		{
			value_method = bind(&CardStats::GetBottom,ref(placed_card.GetCardStats()));
			opposite_value_method = bind(&CardStats::GetTop,ref(target_card.GetCardStats()));
		}

		const int value_elemental_modifier = ((placed_card.GetElementalModifier() == ElementalModifier::Bonus) ? 1 : (placed_card.GetElementalModifier() == ElementalModifier::Penalty) ? -1 : 0);
		const int opposite_value_elemental_modifier = ((target_card.GetElementalModifier() == ElementalModifier::Bonus) ? 1 : (target_card.GetElementalModifier() == ElementalModifier::Penalty) ? -1 : 0);

		const int placed_card_value = value_method() + value_elemental_modifier;
		const int target_card_value = opposite_value_method() + opposite_value_elemental_modifier;

		if (placed_card_value > target_card_value)
		{
			if ((neighbor == Neighbor::Left) || (neighbor == Neighbor::Right))
				target_card.SetCardState(CardState::CapturingByHorizontal);

			else if ((neighbor == Neighbor::Top) || (neighbor == Neighbor::Bottom))
				target_card.SetCardState(CardState::CapturingByVertical);

			return true;
		}
	}
	return false;
}
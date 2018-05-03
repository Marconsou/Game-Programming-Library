#ifndef RULE_H
#define RULE_H

#include "Board.h"
#include "Player.h"

namespace TT
{
	enum class RuleID
	{
		Open,
		Random,
		/*SuddenDeath,*/
		Elemental,
		/*Same,
		SameWall,
		Plus,*/
		Max,
	};

	class Rule
	{
	public:
		static bool CheckForBasicRule(Board& board,const Card& placed_card,const bool elemental);
	private:
		enum class Neighbor
		{
			Left,
			Right,
			Top,
			Bottom,
		};

		Rule() = delete;
		Rule(const Rule&) = delete;
		Rule& operator=(const Rule&) = delete;
		static bool CheckNeighborCardValue(const Card& placed_card,Card& target_card,const Neighbor neighbor,const bool elemental);
	};
}

#endif
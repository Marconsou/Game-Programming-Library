#ifndef GAMETOPINTERFACE_H
#define GAMETOPINTERFACE_H

#include "GameState.h"
#include "GameTripleTriad.h"

namespace TT
{
	class GameTopInterface : public GPL::GameState
	{
	public:
		GameTopInterface() = default;
	private:
		GameTopInterface(const GameTopInterface&) = delete;
		GameTopInterface& operator=(const GameTopInterface&) = delete;
		void Update() override;
		void Show() override;
	};
}

#endif
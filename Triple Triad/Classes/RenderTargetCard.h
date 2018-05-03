#ifndef RENDERTARGETCARD_H
#define RENDERTARGETCARD_H

#include "Convert.h"
#include "Text.h"
#include "Card.h"
#include "Main.h"

namespace TT
{
	class RenderTargetCard
	{
	public:
		explicit RenderTargetCard(const Card& card);
		void Update();
		void Show(GPL::Video& video);
		static void BuildCards(const GPL::Video& video,std::vector<std::unique_ptr<RenderTargetCard>>& render_target_cards,const std::vector<Card*>& current_game_cards,const int built_cards_width);
	private:
		GPL::Text left;
		GPL::Text top;
		GPL::Text right;
		GPL::Text bottom;
		GPL::Text element_modifier;
		GPL::Sprite element;
		GPL::Sprite sprite;
		const Card* const card{};
		RenderTargetCard(const RenderTargetCard&) = delete;
		RenderTargetCard& operator=(const RenderTargetCard&) = delete;
		void SetPosition(const float x,const float y);
	};
}

#endif
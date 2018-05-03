#ifndef CARD_H
#define CARD_H

#include "Sprite.h"
#include "CardStats.h"

namespace TT
{
	enum class ElementalModifier
	{
		None,
		Bonus,
		Penalty,
	};

	enum class CardState
	{
		OnHand,
		RaisingFromHand,
		PlacedOnBoard,
		CapturingByHorizontal,
		CapturingByVertical,
	};

	class Player;
	class Card
	{
	public:
		Card();
		void SetElementalModifier(const ElementalModifier elemental_modifier);
		ElementalModifier GetElementalModifier() const;
		void SetCardState(const CardState card_state);
		CardState GetCardState() const;
		void SetCapturingCardFalling(const bool capturing_card_falling);
		bool GetCapturingCardFalling() const;
		void SetCardStats(const CardStats& card_stats);
		const CardStats& GetCardStats() const;
		void SetCapturedPlayer(const Player& captured_player);
		const Player& GetCapturedPlayer() const;
		void SetX(const float x);
		float GetX() const;
		void SetY(const float y);
		float GetY() const;
		void SetPosition(const float x,const float y,const bool centralize = false);
		void SetRotateX(const float rotate);
		float GetRotateX() const;
		void SetRotateY(const float rotate);
		float GetRotateY() const;
		void SetRotateZ(const float rotate);
		float GetRotateZ() const;
		void SetScale(const float scale);
		float GetScale() const;
		void SetColor(const bool blue);
		void ModelTextureUpdate(const GPL::Texture& built_cards_texture,const GPL::Texture& card_back_face_texture,const size_t index);
		void AdvancePosition(const GPL::Video& video);
		void Update(const GPL::Video& video);
		void Show(GPL::Video& video);
		static float GetWidth();
		static float GetHeight();
		static float GetTotalWidth();
		static float GetTotalHeight();
		static float GetAdvanceX();
		static GPL::Point2D<float> GetTexturePosition(const size_t index,const int texture_width = 0);
	private:
		ElementalModifier elemental_modifier;
		CardState card_state;
		bool cursor_over_card{};
		bool player_owner_changed_once{};
		bool capturing_card_falling{};
		const CardStats* card_stats{};
		const Player* captured_player{};
		GPL::Model model_back{GPL::PrimitiveType::TriangleStrip,2,4,4};
		GPL::Model model_color{GPL::PrimitiveType::TriangleStrip,2,4,4};
		GPL::Model model_front{GPL::PrimitiveType::TriangleStrip,2,4,4};
		Card(const Card&) = delete;
		Card& operator=(const Card&) = delete;
		void InitializeModel(GPL::Model& model,const bool invert = false) const;
		void ModelTextureCoordinate(const GPL::Texture& texture,GPL::Model& model,const GPL::Point2D<float>& texture_coordinate) const;
	};
}

#endif
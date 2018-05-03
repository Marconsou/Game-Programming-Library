#include "RenderTargetCard.h"

using namespace std;
using namespace GPL;
using namespace TT;

RenderTargetCard::RenderTargetCard(const Card& card) :
card(&card)
{

}

void RenderTargetCard::SetPosition(const float x,const float y)
{
	this->sprite.SetPosition(x,y);

	this->left.SetPosition(x + 5.0f,y + 35.0f);
	this->top.SetPosition(this->left.GetX() + (this->left.GetW() / 2.0f),this->left.GetY() - this->left.GetH());
	this->right.SetPosition(this->left.GetX() + this->left.GetW(),this->left.GetY());
	this->bottom.SetPosition(this->top.GetX(),this->top.GetY() + (this->top.GetH() * 2.0f));

	this->element.SetPosition(this->top.GetX() + 80.0f,this->top.GetY());
}

void RenderTargetCard::Update()
{
	const ElementalModifier element_modifier = this->card->GetElementalModifier();

	if (element_modifier == ElementalModifier::None)
		this->element_modifier.SetString("");

	else if (element_modifier == ElementalModifier::Bonus)
		this->element_modifier.SetString("+1");

	else if (element_modifier == ElementalModifier::Penalty)
		this->element_modifier.SetString("-1");

	this->element_modifier.SetPosition(this->sprite.GetX() + (Card::GetWidth() / 2.0f),this->sprite.GetY() + (Card::GetHeight() / 2.0f),true);
}

void RenderTargetCard::Show(Video& video)
{
	this->sprite.Show(video);

	if (!this->card->GetCardStats().GetName().empty())
	{
		this->left.Show(video);
		this->top.Show(video);
		this->right.Show(video);
		this->bottom.Show(video);
		this->element.Show(video);
		this->element_modifier.Show(video);
	}
}

void RenderTargetCard::BuildCards(const Video& video,vector<unique_ptr<RenderTargetCard>>& render_target_cards,const vector<Card*>& current_game_cards,const int built_cards_width)
{
	const RenderTarget& render_target = video.GetRenderTarget(0);

	const Font& font = video.GetFont(static_cast<int>(FileID::FontTimesNewRomanBold));

	float x = 0.0f;
	float y = 0.0f;

	const int cards_by_level = 11;

	for (size_t i = 0; i < current_game_cards.size(); i++)
	{
		render_target_cards.push_back(make_unique<RenderTargetCard>(*current_game_cards[i]));

		RenderTargetCard& iterator = *render_target_cards.back();

		Sprite& sprite = iterator.sprite;

		const CardStats& card_stats = iterator.card->GetCardStats();

		const Point2D<float> texture_position = Card::GetTexturePosition(static_cast<int>(card_stats.GetID()) % cards_by_level,built_cards_width);

		sprite.SetRenderTarget(render_target);
		sprite.SetSize(Card::GetWidth(),Card::GetHeight());
		sprite.SetTexture(video.GetTexture(static_cast<int>(FileID::TextureCardsLevel01) + card_stats.GetLevel() - 1));
		sprite.SetTexturePosition(texture_position.GetX(),texture_position.GetY());

		if (!card_stats.GetName().empty())
		{
			const int max_value_int = 10;
			const string max_value_char("A");

			iterator.left.SetRenderTarget(render_target);
			iterator.left.SetText(font,(card_stats.GetLeft() != max_value_int) ? Convert::NumberToString(card_stats.GetLeft()) : max_value_char);

			iterator.top.SetRenderTarget(render_target);
			iterator.top.SetText(font,(card_stats.GetTop() != max_value_int) ? Convert::NumberToString(card_stats.GetTop()) : max_value_char);

			iterator.right.SetRenderTarget(render_target);
			iterator.right.SetText(font,(card_stats.GetRight() != max_value_int) ? Convert::NumberToString(card_stats.GetRight()) : max_value_char);

			iterator.bottom.SetRenderTarget(render_target);
			iterator.bottom.SetText(font,(card_stats.GetBottom() != max_value_int) ? Convert::NumberToString(card_stats.GetBottom()) : max_value_char);

			Sprite& element = iterator.element;

			if (card_stats.GetElemental() != Elemental::None)
			{
				element.SetRenderTarget(render_target);
				element.SetTexture(video.GetTexture(static_cast<int>(FileID::TextureInterface)));
				element.SetSize(28.0f,28.0f);
				element.SetTexturePosition(73.0f + ((static_cast<int>(card_stats.GetElemental()) - 1) * (element.GetW() + 3.0f)),0.0f);
			}

			iterator.element_modifier.SetRenderTarget(render_target);
			iterator.element_modifier.SetText(video.GetFont(static_cast<int>(FileID::FontTimesNewRomanBoldItalic)),"");
		}

		iterator.SetPosition(x,y);

		if (i == (video.GetVirtualWidth() / static_cast<int>(Card::GetTotalWidth())) - 1)
		{
			x = 0.0f;
			y += Card::GetTotalHeight();
		}
		else
			x += Card::GetTotalWidth();
	}
}
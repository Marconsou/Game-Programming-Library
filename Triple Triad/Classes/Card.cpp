#include "Card.h"

using namespace std;
using namespace GPL;
using namespace TT;

Card::Card() :
elemental_modifier{},
card_state{}
{
	this->InitializeModel(this->model_back,true);
	this->InitializeModel(this->model_color);
	this->InitializeModel(this->model_front);
}

void Card::SetElementalModifier(const ElementalModifier elemental_modifier)
{
	this->elemental_modifier = elemental_modifier;
}

ElementalModifier Card::GetElementalModifier() const
{
	return this->elemental_modifier;
}

void Card::SetCardState(const CardState card_state)
{
	this->card_state = card_state;
}

CardState Card::GetCardState() const
{
	return this->card_state;
}

void Card::SetCapturingCardFalling(const bool capturing_card_falling)
{
	this->capturing_card_falling = capturing_card_falling;
}

bool Card::GetCapturingCardFalling() const
{
	return this->capturing_card_falling;
}

void Card::SetCardStats(const CardStats& card_stats)
{
	this->card_stats = &card_stats;
}

const CardStats& Card::GetCardStats() const
{
	return *this->card_stats;
}

void Card::SetCapturedPlayer(const Player& captured_player)
{
	if (!this->player_owner_changed_once)
	{
		if (this->captured_player != &captured_player)
		{
			this->player_owner_changed_once = true;
			this->captured_player = &captured_player;
		}
	}
}

const Player& Card::GetCapturedPlayer() const
{
	return *this->captured_player;
}

void Card::SetX(const float x)
{
	const float ceiled_x = ceil(x);

	this->model_back.GetTranslate().SetX(ceiled_x);
	this->model_color.GetTranslate().SetX(ceiled_x);
	this->model_front.GetTranslate().SetX(ceiled_x);
}

float Card::GetX() const
{
	return this->model_back.GetTranslate().GetX();
}

void Card::SetY(const float y)
{
	const float ceiled_y = ceil(y);

	this->model_back.GetTranslate().SetY(ceiled_y);
	this->model_color.GetTranslate().SetY(ceiled_y);
	this->model_front.GetTranslate().SetY(ceiled_y);
}

float Card::GetY() const
{
	return this->model_back.GetTranslate().GetY();
}

void Card::SetPosition(const float x,const float y,const bool centralize)
{
	const float center_x = (centralize) ? (Card::GetWidth() / 2.0f) : 0.0f;
	const float center_y = (centralize) ? (Card::GetHeight() / 2.0f) : 0.0f;

	this->SetX(x - center_x);
	this->SetY(y - center_y);
}

void Card::SetRotateX(const float rotate)
{
	this->model_back.GetRotate().SetX(rotate);
	this->model_color.GetRotate().SetX(rotate);
	this->model_front.GetRotate().SetX(rotate);
}

float Card::GetRotateX() const
{
	return this->model_back.GetRotate().GetX();
}

void Card::SetRotateY(const float rotate)
{
	this->model_back.GetRotate().SetY(rotate);
	this->model_color.GetRotate().SetY(rotate);
	this->model_front.GetRotate().SetY(rotate);
}

float Card::GetRotateY() const
{
	return this->model_back.GetRotate().GetY();
}

void Card::SetRotateZ(const float rotate)
{
	this->model_back.GetRotate().SetZ(rotate);
	this->model_color.GetRotate().SetZ(rotate);
	this->model_front.GetRotate().SetZ(rotate);
}

float Card::GetRotateZ() const
{
	return this->model_back.GetRotate().GetZ();
}

void Card::SetScale(const float scale)
{
	this->model_back.GetScale().SetX(scale);
	this->model_color.GetScale().SetX(scale);
	this->model_front.GetScale().SetX(scale);

	this->model_back.GetScale().SetY(scale);
	this->model_color.GetScale().SetY(scale);
	this->model_front.GetScale().SetY(scale);
}

float Card::GetScale() const
{
	return this->model_back.GetScale().GetX();
}

void Card::SetColor(const bool blue)
{
	const Color* top{};
	const Color* bottom{};

	const float top_r = 0.75f;
	const float top_g = 0.85f;
	const float top_b = 1.0f;

	const float bottom_r = 0.25f;
	const float bottom_g = 0.30f;
	const float bottom_b = 0.50f;

	const Color top_blue(top_r,top_g,top_b);
	const Color bottom_blue(bottom_r,bottom_g,bottom_b);

	const Color top_red(top_b,top_r,top_g);
	const Color bottom_red(bottom_b,bottom_r,bottom_g);

	if (blue)
	{
		top = &top_blue;
		bottom = &bottom_blue;
	}
	else
	{
		top = &top_red;
		bottom = &bottom_red;
	}

	this->model_color.SetVertexColor(0,*top);
	this->model_color.SetVertexColor(1,*top);
	this->model_color.SetVertexColor(2,*bottom);
	this->model_color.SetVertexColor(3,*bottom);
}

void Card::InitializeModel(Model& model,const bool invert) const
{
	int first_index = 0;
	int second_index = 1;
	int third_index = 2;
	int fourth_index = 3;

	if (invert)
	{
		first_index = 1;
		second_index = 0;
		third_index = 3;
		fourth_index = 2;
	}

	model.SetVertexPosition(first_index,0.0f,0.0f);
	model.SetVertexPosition(second_index,Card::GetWidth(),0.0f);
	model.SetVertexPosition(third_index,0.0f,Card::GetHeight());
	model.SetVertexPosition(fourth_index,Card::GetWidth(),Card::GetHeight());

	model.GetTransform().SetX(Card::GetWidth() / 2.0f);
	model.GetTransform().SetY(Card::GetHeight() / 2.0f);

	for (size_t i = 0; i < model.GetIndices().size(); i++)
		model.SetIndex(i,i);
}

void Card::ModelTextureCoordinate(const Texture& texture,Model& model,const Point2D<float>& texture_coordinate) const
{
	model.SetTexture(texture);

	float u = texture_coordinate.GetX() / model.GetTexture().GetWidth();
	float v = texture_coordinate.GetY() / model.GetTexture().GetHeight();

	float uw = Card::GetWidth() / model.GetTexture().GetWidth();
	float vh = Card::GetHeight() / model.GetTexture().GetHeight();

	float x_1 = u;
	float y_1 = v;

	float x_2 = x_1 + uw;
	float y_2 = y_1 + vh;

	model.SetVertexTextureCoordinate(0,x_1,y_1);
	model.SetVertexTextureCoordinate(1,x_2,y_1);
	model.SetVertexTextureCoordinate(2,x_1,y_2);
	model.SetVertexTextureCoordinate(3,x_2,y_2);
}

void Card::ModelTextureUpdate(const Texture& built_cards_texture,const Texture& card_back_face_texture,const size_t index)
{
	this->ModelTextureCoordinate(card_back_face_texture,this->model_back,Card::GetTexturePosition(0));
	this->ModelTextureCoordinate(built_cards_texture,this->model_front,Card::GetTexturePosition(index,built_cards_texture.GetWidth()));
}

void Card::AdvancePosition(const Video& video)
{
	this->cursor_over_card = true;
	this->SetX(this->GetX() + ((this->GetX() > video.GetVirtualWidth() / 2.0f) ? -Card::GetAdvanceX() : Card::GetAdvanceX()));
}

void Card::Update(const Video& video)
{
	if (this->cursor_over_card)
		this->SetX(this->GetX() + ((this->GetX() > video.GetVirtualWidth() / 2.0f) ? Card::GetAdvanceX() : -Card::GetAdvanceX()));

	this->cursor_over_card = false;

	if ((this->card_state != CardState::CapturingByHorizontal) && (this->card_state != CardState::CapturingByVertical))
		this->player_owner_changed_once = false;
}

void Card::Show(Video& video)
{
	video.Draw(this->model_back);
	video.Draw(this->model_color);
	video.Draw(this->model_front);
}

float Card::GetWidth()
{
	return 129.0f;
}

float Card::GetHeight()
{
	return 166.0f;
}

float Card::GetTotalWidth()
{
	return Card::GetWidth() + 3.0f;
}

float Card::GetTotalHeight()
{
	return Card::GetHeight() + 3.0f;
}

float Card::GetAdvanceX()
{
	return 30.0f;
}

Point2D<float> Card::GetTexturePosition(const size_t index,const int texture_width)
{
	const int frame_quantity_x = texture_width / static_cast<int>(Card::GetTotalWidth());

	const float x = (texture_width > 0) ? (Card::GetTotalWidth() * (index % frame_quantity_x)) : 0;
	const float y = (texture_width > 0) ? (Card::GetTotalHeight() * (index / frame_quantity_x)) : 0;

	return Point2D<float>(x,y);
}
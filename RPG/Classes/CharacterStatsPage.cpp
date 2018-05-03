#include "CharacterStatsPage.h"

using namespace std;
using namespace GPL;
using namespace RPG;

CharacterStatsPage::CharacterStatsPage(const Point2D<float>& position,const size_t size) :
	Menu(size),
	position(position)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	//Stats Labels
	for (size_t i = 0; i < this->GetControlTotal(); i++)
	{
		Label& iterator = this->CreateControl<Label>();

		iterator.SetToolTip(this->GetDefaultFontSmall(),this->GetDefaultEdgeDistance());
	}

	//Adicionar os controles
	this->ControlsUpdate(true);
}

float CharacterStatsPage::GetX()
{
	return this->position.GetX() + 15.0f;
}

float CharacterStatsPage::GetY()
{
	return this->position.GetY() + 15.0f;
}

void CharacterStatsPage::SetStatsLabel(int& index,const float x,float& y,const string& label,const Color& label_color,const bool double_line_skip)
{
	Label& stats_label = this->GetControl<Label>(index);

	stats_label.SetText(this->GetDefaultFontSmall(),label,label_color);
	stats_label.SetPosition(x,y);

	y += stats_label.GetH() * (static_cast<int>(double_line_skip) + 1);
	index++;
}

void CharacterStatsPage::SetStatsLabel(int& index,const float x,float& y,const string& label,const string& value,const Color& label_color,const Color& value_color,const bool double_line_skip)
{
	Label& stats_label = this->GetControl<Label>(index);

	stats_label.SetText(this->GetDefaultFontSmall(),label,label_color);
	stats_label.AddText(" " + value,value_color);
	stats_label.SetPosition(x,y);

	y += stats_label.GetH() * (static_cast<int>(double_line_skip) + 1);
	index++;
}

const Label& CharacterStatsPage::GetStatsLabel(const int index) const
{
	return this->GetControl<Label>(index);
}

void CharacterStatsPage::AddStatsLabelControl(const int index)
{
	this->GetControl<Label>(index).AddControl();
}

void CharacterStatsPage::NewToolTipTextLine(int& index,const string& string_text,const Color& color,const ToolTipTextAlign text_align)
{
	this->GetControl<Label>(index).NewToolTipTextLine(string_text,color,text_align);
	index++;
}

void CharacterStatsPage::AddToolTipTextLine(int& index,const string& string_text,const Color& color)
{
	this->GetControl<Label>(index).AddToolTipTextLine(string_text,color);
	index++;
}
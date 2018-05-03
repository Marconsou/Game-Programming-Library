#include "ToolTip.h"

using namespace std;
using namespace GPL;

const float ToolTip::background_padding(10.0f);

ToolTip::ToolTip() :
	font(nullptr),
	edge_distance(0.0f),
	data_update(true),
	background(PrimitiveType::TriangleList,6,8,18)
{
	this->background.SetIndex(0,0);
	this->background.SetIndex(1,1);
	this->background.SetIndex(2,2);

	this->background.SetIndex(3,2);
	this->background.SetIndex(4,3);
	this->background.SetIndex(5,0);

	this->background.SetIndex(6,0);
	this->background.SetIndex(7,3);
	this->background.SetIndex(8,7);

	this->background.SetIndex(9,7);
	this->background.SetIndex(10,3);
	this->background.SetIndex(11,4);

	this->background.SetIndex(12,4);
	this->background.SetIndex(13,5);
	this->background.SetIndex(14,6);

	this->background.SetIndex(15,6);
	this->background.SetIndex(16,7);
	this->background.SetIndex(17,4);
}

float ToolTip::GetX() const
{
	return this->rect.GetPosition().GetX();
}

float ToolTip::GetY() const
{
	return this->rect.GetPosition().GetY();
}

float ToolTip::GetW() const
{
	return this->rect.GetSize().GetX();
}

float ToolTip::GetH() const
{
	return this->rect.GetSize().GetY();
}

void ToolTip::SetPosition(const float x,const float y,const bool centralize)
{
	const float center_x = (centralize) ? (this->GetW() / 2.0f) : 0.0f;
	const float center_y = (centralize) ? (this->GetH() / 2.0f) : 0.0f;

	this->CheckForDataUpdate(this->GetX(),x - center_x);
	this->CheckForDataUpdate(this->GetY(),y - center_y);

	this->rect.SetPosition(x,y,centralize);
}

void ToolTip::SetToolTip(const Font& font,const float edge_distance,const Color& background_color)
{
	this->font = &font;
	this->edge_distance = edge_distance;
	this->background_color = background_color;
}

void ToolTip::WidthUpdate()
{
	this->rect.GetSize().SetX(max(this->rect.GetSize().GetX(),this->text_lines.back()->text.GetW() + (ToolTip::background_padding * 2.0f)));
	this->data_update = true;
}

void ToolTip::NewTextLine(const string& string_text,const Color& color,const ToolTipTextAlign text_align)
{
	//Nova linha de texto
	this->text_lines.push_back(make_unique<TextLine>(*this->font,string_text,color,text_align));

	//Atualizando a maior largura para o fundo
	this->rect.GetSize().SetY((this->text_lines.size() * this->text_lines.back()->text.GetH()) + (ToolTip::background_padding * 2.0f));

	//Atualizar largura
	this->WidthUpdate();
}

void ToolTip::AddTextLine(const string& string_text,const Color& color)
{
	if (!this->text_lines.empty())
	{
		//Adicionar texto ao texto já existente
		this->text_lines.back()->text.AddText(string_text,color);

		//Atualizar largura
		this->WidthUpdate();
	}
}

void ToolTip::DataUpdate(Video& video)
{
	if (this->data_update)
	{
		//	  (x12,y12)	1--------------2 (x21,y21)
		//             /                \
		//	(x11,y11) 0                  3 (x22,y22)
		//			  |    BACKGROUND	 |
		//	(x11,y42) 7					 4 (x22,y31)
		//             \				/
		//	  (x12,y41) 6--------------5 (xx21,y32)
		const float background_w = this->rect.GetSize().GetX();
		const float background_h = this->rect.GetSize().GetY();

		const float base_x = max(this->rect.GetPosition().GetX(),ToolTip::background_padding);
		const float base_y = max(this->rect.GetPosition().GetY(),ToolTip::background_padding);

		const float boundary_x = min(base_x + background_w,video.GetVirtualWidth() - background_w - ToolTip::background_padding);
		const float boundary_y = min(base_y + background_h,video.GetVirtualHeight() - background_h - ToolTip::background_padding);

		const float min_x = min(base_x,boundary_x);
		const float min_y = min(base_y,boundary_y);

		const float background_x = video.LimitX(min_x,background_w,ToolTip::background_padding);
		const float background_y = video.LimitY(min_y,background_h,ToolTip::background_padding);

		//Vertex Position
		float x_1_1 = background_x;
		float y_1_1 = background_y + this->edge_distance;

		float x_1_2 = x_1_1 + this->edge_distance;
		float y_1_2 = background_y;

		float x_2_1 = x_1_1 + background_w - this->edge_distance;
		float y_2_1 = y_1_2;

		float x_2_2 = x_2_1 + this->edge_distance;
		float y_2_2 = y_1_1;

		float y_3_1 = y_2_1 + background_h - this->edge_distance;
		float y_3_2 = y_3_1 + this->edge_distance;
		float y_4_1 = y_1_2 + background_h;
		float y_4_2 = y_4_1 - this->edge_distance;

		this->background.SetVertexPosition(0,x_1_1,y_1_1);
		this->background.SetVertexPosition(1,x_1_2,y_1_2);
		this->background.SetVertexPosition(2,x_2_1,y_2_1);
		this->background.SetVertexPosition(3,x_2_2,y_2_2);
		this->background.SetVertexPosition(4,x_2_2,y_3_1);
		this->background.SetVertexPosition(5,x_2_1,y_3_2);
		this->background.SetVertexPosition(6,x_1_2,y_4_1);
		this->background.SetVertexPosition(7,x_1_1,y_4_2);

		//Color
		for (size_t i = 0; i < this->background.GetVertexTotal(); i++)
			this->background.SetVertexColor(i,this->background_color);

		//Textos
		float line_y = 0.0f;
		for (size_t i = 0; i < this->text_lines.size(); i++)
		{
			TextLine& iterator = *this->text_lines[i];

			const float align_x = (iterator.text_align == ToolTipTextAlign::Center) ? ((background_w - (ToolTip::background_padding * 2.0f)) / 2.0f) - (iterator.text.GetW() / 2.0f) :
				(iterator.text_align == ToolTipTextAlign::Left) ? 0.0f :
				(iterator.text_align == ToolTipTextAlign::Right) ? (background_w - (ToolTip::background_padding * 2.0f)) - iterator.text.GetW() : 0.0f;
			//Posição do texto
			iterator.text.SetPosition(background_x + align_x + ToolTip::background_padding,background_y + line_y + ToolTip::background_padding);

			//Atualizar posição da próxima linha
			line_y += iterator.text.GetH();
		}

		this->data_update = false;
	}
}

void ToolTip::ShowToolTip(Video& video)
{
	//Se tiver linhas de texto
	if (!this->text_lines.empty())
	{
		//Atualizar dados
		this->DataUpdate(video);

		//Fundo
		video.Draw(this->background);

		//Textos
		for (size_t i = 0; i < this->text_lines.size(); i++)
			this->text_lines[i]->text.Show(video);
	}
}

void ToolTip::Clear()
{
	this->text_lines.clear();
	this->rect.SetSize(0.0f,0.0f);
	this->data_update = true;
}
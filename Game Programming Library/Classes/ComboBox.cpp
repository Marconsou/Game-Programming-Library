#include "ComboBox.h"

using namespace std;
using namespace GPL;

ComboBox::ComboBox() :
	font(nullptr),
	dropped_down(false),
	border_thickness(0.0f),
	background(PrimitiveType::TriangleStrip,2,4),
	border(PrimitiveType::TriangleList,8,12,24),
	selection(PrimitiveType::TriangleStrip,2,4),
	cursor(PrimitiveType::TriangleList,2,6)
{
	this->border.SetIndex(0,0);
	this->border.SetIndex(1,1);
	this->border.SetIndex(2,2);

	this->border.SetIndex(3,2);
	this->border.SetIndex(4,1);
	this->border.SetIndex(5,3);

	this->border.SetIndex(6,3);
	this->border.SetIndex(7,4);
	this->border.SetIndex(8,5);

	this->border.SetIndex(9,5);
	this->border.SetIndex(10,4);
	this->border.SetIndex(11,6);

	this->border.SetIndex(12,4);
	this->border.SetIndex(13,7);
	this->border.SetIndex(14,8);

	this->border.SetIndex(15,8);
	this->border.SetIndex(16,9);
	this->border.SetIndex(17,4);

	this->border.SetIndex(18,10);
	this->border.SetIndex(19,9);
	this->border.SetIndex(20,2);

	this->border.SetIndex(21,2);
	this->border.SetIndex(22,11);
	this->border.SetIndex(23,10);

	this->cursor.SetVertexColor(0,Color::Black);
	this->cursor.SetVertexColor(1,Color::Black);
	this->cursor.SetVertexColor(2,Color::Black);

	this->AddEventOnMouseClick(&ComboBox::OnMouseClick,*this);
	this->AddEventOnLeave(&ComboBox::OnLeave,*this);
}

void ComboBox::SetSelectedIndex(const int index)
{
	const Text& text = *this->text_items[min(index,static_cast<int>(this->text_items.size()) - 1)];
	this->old_selected_string_text = this->selected_text_item.GetString();
	this->change_selected_string_text = text.GetString();
}

int ComboBox::GetSelectedIndex() const
{
	for (size_t i = 0; i < this->text_items.size(); i++)
	{
		//Utilizar esse valor pois existe a chance do texto selecionado não ter sido atualizado
		if (this->change_selected_string_text == this->text_items[i]->GetString())
			return i;
	}
	return -1;
}

const string& ComboBox::GetSelectedTextItem() const
{
	//Utilizar esse valor pois existe a chance do texto selecionado não ter sido atualizado
	return this->change_selected_string_text;
}

void ComboBox::SetComboBox(const Font& font,const float width,const float border_thickness,const Color& background_color,const Color& border_color,const Color& selection_color)
{
	//Fonte
	this->font = &font;

	//Expessura da borda
	this->border_thickness = max(border_thickness,0.0f);

	//Background
	for (size_t i = 0; i < this->background.GetVertexTotal(); i++)
		this->background.SetVertexColor(i,background_color);

	//Border
	for (size_t i = 0; i < this->border.GetVertexTotal(); i++)
		this->border.SetVertexColor(i,border_color);

	//Selection
	for (size_t i = 0; i < this->selection.GetVertexTotal(); i++)
		this->selection.SetVertexColor(i,selection_color);

	//Tamanho do ComboBox
	this->GetRect().SetSize(width + (this->border_thickness * 2.0f),this->font->GetLineHeight() + (this->border_thickness * 2.0f));
}

void ComboBox::AddTextItem(const string& string_text,const Color& color)
{
	this->text_items.push_back(make_unique<Text>(*this->font,string_text,color));
}

int ComboBox::FindTextItem(const string& search_item)
{
	for (size_t i = 0; i < this->text_items.size(); i++)
	{
		if (this->text_items[i]->GetString().find(search_item) != string::npos)
			return i;
	}

	//Não encontrou
	return -1;
}

void ComboBox::DataUpdate(const float height)
{
	if (this->GetDataUpdate())
	{
		// (x1,y1) 0----------------------------1 (x4,y1)
		//         |      BORDER THICKNESS      |
		// (x1,y2) 2---11-------------------5---3 (x4,y2)
		//         |   | (x2,y2)    (x3,y2) |   |
		//         |   |                    |   |
		//         |   |                    |   |
		//         |   |     BACKGROUND     |   |
		//         |   |                    |   |
		//         |   |                    |   |
		//         |   | (x2,y3)    (x3,y3) |   |
		// (x1,y3) 9---10-------------------6---4 (x4,y3)
		//         |                            |
		// (x1,y4) 8----------------------------7 (x4,y4)

		//Atualizando a altura do controle
		this->GetRect().GetSize().SetY(height + (this->border_thickness * 2.0f));

		//Border
		const float background_width = this->GetRect().GetSize().GetX() - (this->border_thickness * 2.0f);
		const float background_height = this->GetRect().GetSize().GetY() - (this->border_thickness * 2.0f);

		float x = this->GetX();
		float y = this->GetY();

		float x_1 = x;
		float y_1 = y;

		float x_2 = x_1 + this->border_thickness;
		float y_2 = y_1 + this->border_thickness;

		float x_3 = x_2 + background_width;
		const float y_3 = y_2 + background_height;

		const float x_4 = x_3 + this->border_thickness;
		const float y_4 = y_3 + this->border_thickness;

		this->border.SetVertexPosition(0,x_1,y_1);
		this->border.SetVertexPosition(1,x_4,y_1);
		this->border.SetVertexPosition(2,x_1,y_2);
		this->border.SetVertexPosition(3,x_4,y_2);

		this->border.SetVertexPosition(4,x_4,y_3);
		this->border.SetVertexPosition(5,x_3,y_2);
		this->border.SetVertexPosition(6,x_3,y_3);

		this->border.SetVertexPosition(7,x_4,y_4);
		this->border.SetVertexPosition(8,x_1,y_4);
		this->border.SetVertexPosition(9,x_1,y_3);

		this->border.SetVertexPosition(10,x_2,y_3);
		this->border.SetVertexPosition(11,x_2,y_2);

		//Background
		const float background_x = x + this->border_thickness;
		const float background_y = y + this->border_thickness;

		this->background.SetVertexPosition(0,background_x,background_y);
		this->background.SetVertexPosition(1,background_x + background_width,background_y);
		this->background.SetVertexPosition(2,background_x,background_y + background_height);
		this->background.SetVertexPosition(3,background_x + background_width,background_y + background_height);

		//Cursor
		const float square = this->font->GetLineHeight();
		const float size = square / 2.0f;
		const float space = 1.0f;

		x = this->GetX() + this->GetW() - (square / 2.0f) - (size / 2.0f) - this->border_thickness;
		y = this->GetY() + (square / 2.0f) - (size / 2.0f) + this->border_thickness;

		x_1 = x;
		y_1 = y;

		x_2 = x_1 + size;
		y_2 = y_1 + size;

		x_3 = x_2 - (size / 2.0f);

		this->cursor.SetVertexPosition(0,x_1 + space,y_1 + space);
		this->cursor.SetVertexPosition(1,x_2 + space,y_1 + space);
		this->cursor.SetVertexPosition(2,x_3 + space,y_2 + space);

		this->cursor.SetVertexPosition(3,x_1,y_1);
		this->cursor.SetVertexPosition(4,x_2,y_1);
		this->cursor.SetVertexPosition(5,x_3,y_2);

		Color inverted_color(this->background.GetVertexColor(0).GetInvertedColor());
		inverted_color.SetAlpha(1.0f);

		this->cursor.SetVertexColor(3,inverted_color);
		this->cursor.SetVertexColor(4,inverted_color);
		this->cursor.SetVertexColor(5,inverted_color);

		this->SetDataUpdate(false);
	}
}

int ComboBox::CalculateIndexFromPosition(const float mouse_y)
{
	//Altura padrão
	const float height = this->text_items.front()->GetH();

	//Valor de Y do início da área de seleção
	float base_y = this->GetY() + this->border_thickness + height;

	//Calculando o índice
	return static_cast<int>((mouse_y - base_y) / height);
}

bool ComboBox::MouseHoverOnSelectionArea(const float mouse_x,const float mouse_y)
{
	return (!Rect<float>(this->GetX(),this->GetY(),this->GetW(),this->text_items.front()->GetH()).PointInRect(mouse_x,mouse_y));
}

bool ComboBox::MouseHoverAnItem(const float mouse_x,const float mouse_y)
{
	//Altura padrão
	const float height = this->text_items.front()->GetH();

	const float x = this->GetX() + this->border_thickness;
	const float y = this->GetY() + this->border_thickness + height;

	return (Rect<float>(x,y,this->GetW() - (this->border_thickness * 2.0f) - 1.0f,this->GetH() - (this->border_thickness * 2.0f) - height - 1.0f).PointInRect(mouse_x,mouse_y));
}

void ComboBox::CheckForSpecificEvents()
{
	if (this->selected_text_item.GetString() != this->old_selected_string_text)
	{
		this->on_selected_item_changed(*this);
		this->old_selected_string_text = this->selected_text_item.GetString();
	}
}

bool ComboBox::IsHighPriorityControl() const
{
	return true;
}

bool ComboBox::Show(const Input& input,Video& video,const Timer& timer)
{
	//Altura padrão
	const float height = this->font->GetLineHeight();

	//Atualizar dados
	this->DataUpdate(((!this->dropped_down) ? (height) : ((this->text_items.size() + 1) * height)));

	//Border
	video.Draw(this->border);

	//Background
	video.Draw(this->background);

	//Cursor
	video.Draw(this->cursor);

	//Se precisar mudar o texto selecionado e tiver pelo menos algum texto na lista de item
	if ((this->change_selected_string_text != this->selected_text_item.GetString()) && (!this->text_items.empty()))
	{
		const Text& text_item = *this->text_items.front();
		this->selected_text_item.SetText(text_item.GetFont(),this->change_selected_string_text,text_item.GetColor());
	}

	//Selected Text
	this->selected_text_item.SetPosition(this->GetX() + this->border_thickness,this->GetY() + this->border_thickness);
	this->selected_text_item.Show(video);

	//Se tiver mostrando o menu
	if (this->dropped_down)
	{
		const float x = this->GetX() + this->border_thickness;
		float y = this->GetY() + this->border_thickness + height;

		//Calculando o índice
		const float mouse_y = static_cast<float>(input.GetMouseY());
		const int index = this->CalculateIndexFromPosition(mouse_y);

		for (size_t i = 0; i < this->text_items.size(); i++)
		{
			Text& iterator = *this->text_items[i];

			//Mostrar o texto
			iterator.SetPosition(x,y);
			iterator.Show(video);

			if (index == i)
			{
				//Se estiver dentro do controle
				if (this->GetMouseHover())
				{
					//Se tiver dentro da área de seleção
					const float mouse_x = static_cast<float>(input.GetMouseX());
					if (this->MouseHoverOnSelectionArea(mouse_x,mouse_y))
					{
						//Mouse sobre algum item
						if (this->MouseHoverAnItem(mouse_x,mouse_y))
						{
							const float w = this->GetW() - (this->border_thickness * 2.0f);
							const float h = iterator.GetH();

							this->selection.SetVertexPosition(0,x,y);
							this->selection.SetVertexPosition(1,x + w,y);
							this->selection.SetVertexPosition(2,x,y + h);
							this->selection.SetVertexPosition(3,x + w,y + h);

							//Mostrar a seleção
							video.Draw(this->selection);
						}
					}
				}
			}

			//Atualizar posição do texto
			y += iterator.GetH();
		}
	}

	return this->dropped_down;
}

void ComboBox::OnEnabledChanged(const Control& control)
{
	const bool change = !this->GetEnabled();

	this->background.SetGrayScale(change);
	this->border.SetGrayScale(change);
	this->selection.SetGrayScale(change);
	this->selected_text_item.SetGrayScale(change);
	this->cursor.SetGrayScale(change);

	for (size_t i = 0; i < this->text_items.size(); i++)
		this->text_items[i]->SetGrayScale(change);
}

void ComboBox::OnMouseClick(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y)
{
	//Clique com o botão esquerdo
	if (mouse_button == MouseButton::Left)
	{
		//Se tiver algum item
		if (!this->text_items.empty())
		{
			//Se o menu estiver aparecendo
			if (this->dropped_down)
			{
				//Se tiver dentro da área de seleção
				if (this->MouseHoverOnSelectionArea(mouse_x,mouse_y))
				{
					//Mouse sobre algum item
					if (this->MouseHoverAnItem(mouse_x,mouse_y))
					{
						//Item selecionado
						this->SetSelectedIndex(this->CalculateIndexFromPosition(mouse_y));
					}
				}
			}
			this->dropped_down = !this->dropped_down;
			this->SetDataUpdate(true);
		}
	}
}

void ComboBox::OnLeave(const Control& control)
{
	this->dropped_down = false;
	this->SetDataUpdate(true);
}

void ComboBox::Clear()
{
	this->text_items.clear();
	this->old_selected_string_text.clear();
	this->change_selected_string_text.clear();
}
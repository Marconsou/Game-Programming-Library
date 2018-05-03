#include "TextBox.h"

using namespace std;
using namespace GPL;

const float TextBox::cursor_width(1.0f);
const float TextBox::background_padding(3.0f);

TextBox::TextBox() :
input_type{},
	max_length(0),
	border_thickness(0.0f),
	cursor(PrimitiveType::TriangleStrip,2,4),
	background(PrimitiveType::TriangleStrip,2,4),
	border(PrimitiveType::TriangleList,8,12,24)
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
}

const string& TextBox::GetString() const
{
	return this->text.GetString();
}

void TextBox::SetTextBox(const Font& font,const TextBoxInputType input_type,const size_t max_length,const float border_thickness,const Color& text_color,const Color& cursor_color,const Color& background_color,const Color& border_color)
{
	this->input_type = input_type;
	this->max_length = max_length;

	//Expessura da borda
	this->border_thickness = max(border_thickness,0.0f);

	//Text
	this->text.SetText(font,"",text_color);

	//Multiplica-se por 2 porque é considerado a espessura e preenchimento do início e fim
	const float size = (this->border_thickness * 2.0f) + (TextBox::background_padding *  2.0f);
	this->GetRect().SetSize((font.GetMaxAdvanceWidth() * max_length) + TextBox::cursor_width + size,Text::TextSize(font,"").GetY() + size);

	//Cursor
	for (size_t i = 0; i < this->cursor.GetVertexTotal(); i++)
		this->cursor.SetVertexColor(i,cursor_color);

	//Background
	for (size_t i = 0; i < this->background.GetVertexTotal(); i++)
		this->background.SetVertexColor(i,background_color);

	//Border
	for (size_t i = 0; i < this->border.GetVertexTotal(); i++)
		this->border.SetVertexColor(i,border_color);
}

void TextBox::SetText(const string& string_text)
{
	this->CheckForDataUpdate(this->text.GetString(),string_text);
	this->old_string_text = this->text.GetString();
	this->text.SetString(string_text);
}

void TextBox::SetBackgroundText(const string& string_text,const Color& color)
{
	this->background_text.SetText(this->text.GetFont(),string_text,color);
}

void TextBox::DataUpdate()
{
	if (this->GetDataUpdate())
	{
		// (x1,y1) 0----------------------------1 (x4,y1)
		//         |      BORDER THICKNESS      |
		// (x1,y2) 2---11-------------------5---3 (x4,y2)
		//         |   | (x2,y2)    (x3,y2) |   |
		//         |   |     BACKGROUND     |   |
		//         |   |       PADDING      |   |
		//         |   |                    |   |
		//         |   |        TEXT >>     |   |
		//         |   |                    |   |
		//         |   | (x2,y3)    (x3,y3) |   |
		// (x1,y3) 9---10-------------------6---4 (x4,y3)
		//         |                            |
		// (x1,y4) 8----------------------------7 (x4,y4)

		//Border
		const float background_width = this->GetRect().GetSize().GetX() - (this->border_thickness * 2.0f);
		const float background_height = this->GetRect().GetSize().GetY() - (this->border_thickness * 2.0f);

		const float x = this->GetX();
		const float y = this->GetY();

		const float x_1 = x;
		const float y_1 = y;

		const float x_2 = x_1 + this->border_thickness;
		const float y_2 = y_1 + this->border_thickness;

		const float x_3 = x_2 + background_width;
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

		//Avançar o cursor para o final do texto
		float cursor_advance = 0.0f;
		for (size_t i = 0; i < this->text.GetString().size(); i++)
			cursor_advance += Text::TextSize(this->text.GetFont(),string(1,this->text.GetString()[i])).GetX();

		//Cursor
		const float cursor_x = background_x + TextBox::background_padding + cursor_advance;
		const float cursor_y = background_y + TextBox::background_padding;
		const float cursor_height = this->text.GetH();

		this->cursor.SetVertexPosition(0,cursor_x,cursor_y);
		this->cursor.SetVertexPosition(1,cursor_x + TextBox::cursor_width,cursor_y);
		this->cursor.SetVertexPosition(2,cursor_x,cursor_y + cursor_height);
		this->cursor.SetVertexPosition(3,cursor_x + TextBox::cursor_width,cursor_y + cursor_height);

		//Text
		this->text.SetPosition(cursor_x - cursor_advance,cursor_y);

		//Background Text
		this->background_text.SetPosition(this->text.GetX(),this->text.GetY());

		this->SetDataUpdate(false);
	}
}

void TextBox::AddCharacter(const char character)
{
	bool valid_char = false;

	if (this->input_type == TextBoxInputType::NameInput)
	{
		if (((character >= 'a') && (character <= 'z')) ||
			((character >= 'A') && (character <= 'Z')) ||
			(character == '_'))
			valid_char = true;
	}

	else if (this->input_type == TextBoxInputType::CharacterOnly)
	{
		if (((character >= 'a') && (character <= 'z')) ||
			((character >= 'A') && (character <= 'Z')))
			valid_char = true;
	}

	else if (this->input_type == TextBoxInputType::NumberOnly)
	{
		if ((character >= '0') && (character <= '9'))
			valid_char = true;
	}

	if (valid_char)
	{
		if (this->max_length > this->text.GetString().size())
			this->SetText(this->text.GetString() + string(1,character));
	}
}

void TextBox::RemoveLastCharacter()
{
	string current_text(this->text.GetString());

	if (!current_text.empty())
	{
		current_text.pop_back();
		this->SetText(current_text);
	}
}

void TextBox::CheckForSpecificEvents()
{
	if (this->text.GetString() != this->old_string_text)
	{
		this->on_text_changed(*this);
		this->old_string_text = this->text.GetString();
	}
}

bool TextBox::Show(const Input& input,Video& video,const Timer& timer)
{
	static Control* current_control = nullptr;
	static Interval cursor_timer(0.5f,timer);
	static bool show_cursor = false;

	//Sincronizar o cursor caso houver troca de controle no foco
	if (!current_control->IsControlFocused())
	{
		cursor_timer.Synchronize(timer);
		show_cursor = true;
	}

	//Atualizar dados
	this->DataUpdate();

	//Atualizando o texto digitado
	const bool enabled_focused = (this->GetEnabled()) && (this->IsControlFocused());
	if (enabled_focused)
	{
		const char last_character_typed = input.GetLastCharacterTyped();
		const char backspace = '\b';

		//Se apertou o Backspace
		if (last_character_typed == backspace)
			this->RemoveLastCharacter();

		//Se for outro caractere
		else if (last_character_typed)
			this->AddCharacter(last_character_typed);
	}

	//Border
	video.Draw(this->border);

	//Background
	video.Draw(this->background);

	//Text
	this->text.Show(video);

	//Background Text
	if ((!enabled_focused) && (this->text.GetValidCharacterTotal() == 0))
		this->background_text.Show(video);

	//Cursor
	if (enabled_focused)
	{
		if (cursor_timer.Action(timer))
			show_cursor = !show_cursor;

		if (show_cursor)
			video.Draw(this->cursor);
	}

	//Atualizando controle
	current_control = &Control::GetControlFocused();
	return false;
}

void TextBox::OnEnabledChanged(const Control& control)
{
	const bool change = !this->GetEnabled();

	this->text.SetGrayScale(change);
	this->background_text.SetGrayScale(change);
	this->cursor.SetGrayScale(change);
	this->background.SetGrayScale(change);
	this->border.SetGrayScale(change);
}
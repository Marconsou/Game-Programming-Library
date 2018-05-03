#include "Text.h"

using namespace std;
using namespace GPL;

const size_t Text::vertex_rect_total{4};

Text::Text()
{

}

Text::Text(const Font& font,const string& string_text,const Color& color)
{
	this->SetText(font,string_text,color);
}

const Font& Text::GetFont() const
{
	return *this->font;
}

void Text::SetRenderTarget(const RenderTarget& render_target)
{
	this->model.SetRenderTarget(render_target);
}

const RenderTarget& Text::GetRenderTarget() const
{
	return this->model.GetRenderTarget();
}

void Text::SetView(const View& view)
{
	this->model.SetView(view);
}

const View& Text::GetView() const
{
	return this->model.GetView();
}

void Text::SetPixelateGridSize(const float pixelate_grid_size)
{
	this->model.SetPixelateGridSize(pixelate_grid_size);
}

void Text::SetInvertColor(const bool invert_color)
{
	this->model.SetInvertColor(invert_color);
}

void Text::SetGrayScale(const bool gray_scale)
{
	this->model.SetGrayScale(gray_scale);
}

void Text::SetTransformX(const float transform_x)
{
	this->model.GetTransform().SetX(transform_x);
}

float Text::GetTransformX() const
{
	return this->model.GetTransform().GetX();
}

void Text::SetTransformY(const float transform_y)
{
	this->model.GetTransform().SetY(transform_y);
}

float Text::GetTransformY() const
{
	return this->model.GetTransform().GetY();
}

void Text::SetScaleX(const float scale_x)
{
	this->model.GetScale().SetX(scale_x);
}

float Text::GetScaleX() const
{
	return this->model.GetScale().GetX();
}

void Text::SetScaleY(const float scale_y)
{
	this->model.GetScale().SetY(scale_y);
}

float Text::GetScaleY() const
{
	return this->model.GetScale().GetY();
}

void Text::SetRotate(const float rotate)
{
	this->model.GetRotate().SetZ(rotate);
}

float Text::GetRotate() const
{
	return this->model.GetRotate().GetZ();
}

void Text::SetX(const float x)
{
	this->model.GetTranslate().SetX(ceil(x));
}

float Text::GetX() const
{
	return this->model.GetTranslate().GetX();
}

void Text::SetY(const float y)
{
	this->model.GetTranslate().SetY(ceil(y));
}

float Text::GetY() const
{
	return this->model.GetTranslate().GetY();
}

void Text::SetPosition(const float x,const float y,const bool centralize)
{
	const float center_x = (centralize) ? (this->GetW() / 2.0f) : 0.0f;
	const float center_y = (centralize) ? (this->GetH() / 2.0f) : 0.0f;

	this->SetX(x - center_x);
	this->SetY(y - center_y);
}

float Text::GetW() const
{
	return this->size.GetX();
}

float Text::GetH() const
{
	return this->size.GetY();
}

void Text::SetAlpha(const float alpha)
{
	for (size_t i = 0; i < this->valid_character_total; i++)
		this->SetAlpha(i,alpha);
}

void Text::SetAlpha(const int index,const float alpha)
{
	size_t vertex_color_index = index * Text::vertex_rect_total;
	const size_t size = vertex_color_index + Text::vertex_rect_total;

	for (size_t i = vertex_color_index; i < size; i++)
		this->model.SetVertexColor(i,Color(this->model.GetVertexColor(i),alpha));
}

float Text::GetAlpha(const int index) const
{
	return this->GetColor(index).GetAlpha();
}

void Text::SetColorBySide(const Color& color,const size_t first_index,const size_t second_index)
{
	const size_t size = this->valid_character_total * Text::vertex_rect_total;

	for (size_t i = 0; i < size; i += Text::vertex_rect_total)
	{
		this->model.SetVertexColor(i + first_index,color);
		this->model.SetVertexColor(i + second_index,color);
	}
}

void Text::SetColorLeft(const Color& color_left)
{
	this->SetColorBySide(color_left,0,2);
}

void Text::SetColorTop(const Color& color_top)
{
	this->SetColorBySide(color_top,0,1);
}

void Text::SetColorRight(const Color& color_right)
{
	this->SetColorBySide(color_right,1,3);
}

void Text::SetColorBottom(const Color& color_bottom)
{
	this->SetColorBySide(color_bottom,2,3);
}

void Text::SetColor(const Color& color)
{
	for (size_t i = 0; i < this->valid_character_total; i++)
		this->SetColor(i,color);
}

void Text::SetColor(const int index,const Color& color)
{
	size_t color_index = index * Text::vertex_rect_total;
	const size_t size = color_index + Text::vertex_rect_total;

	for (size_t i = color_index; i < size; i++)
		this->model.SetVertexColor(i,color);
}

const Color& Text::GetColor(const int index) const
{
	return this->model.GetVertexColor(index * Text::vertex_rect_total);
}

void Text::SetString(const string& string_text)
{
	//String
	this->CheckForDataUpdate(this->string_text,string_text);
	this->string_text = string_text;

	//Resetando os valores padrões
	float width_total = 0.0f;
	this->valid_character_total = this->string_text.size();

	//Loop pelo texto incluindo os espaços
	for (size_t i = 0; i < this->string_text.size(); i++)
	{
		const FT_Byte character = this->string_text[i];

		//Se for caractere de espaço
		if (Font::IsCharacterSpace(character))
		{
			//Descontando os caracteres de espaço
			this->valid_character_total--;
		}

		//Atualizando a largura do texto mesmo com o caractere de espaço
		width_total += this->font->GetCharacterAdvanceWidth(character);
	}

	this->size.SetX(width_total);
	this->size.SetY(this->font->GetLineHeight());

	//Calculando o tamanho correto para os vértices e índices
	const size_t size = this->valid_character_total * Text::vertex_rect_total;

	//Redimensionando os vértices e índices
	this->model.ResizeVertices(size);

	//Alterando a quantidade de primitivas com base no total de vértices já calculado
	this->model.SetPrimitiveCount(this->model.GetVertexTotal() - 2);
}

const string& Text::GetString() const
{
	return this->string_text;
}

size_t Text::GetValidCharacterTotal() const
{
	return this->valid_character_total;
}

void Text::SetText(const Font& font,const string& string_text,const Color& color)
{
	//Font
	this->CheckForDataUpdate(this->font,&font);
	this->font = &font;
	this->model.SetTexture(this->font->GetTexture());

	//String
	this->SetString(string_text);

	//Color
	this->SetColor(color);
}

void Text::AddText(const string& string_text,const Color& color)
{
	//Quantidade de caracteres válidos atuais
	const size_t old_size = this->valid_character_total;

	//Atualizando texto
	this->SetString(this->string_text + string_text);

	//Quantidade de caracteres válidos incluindo os adicionados
	const size_t new_size = this->valid_character_total;

	//Atualizando a cor somente para os caracteres adicionados
	for (size_t i = old_size; i < new_size; i++)
		this->SetColor(i,color);
}

void Text::DataUpdate()
{
	//Se precisar atualizar os dados
	if (this->data_update)
	{
		size_t index = 0;
		float advance_width = 0.0f;

		//Loop pelo texto incluindo os espaços
		for (size_t i = 0; i < this->string_text.size(); i++)
		{
			const FT_Byte character = this->string_text[i];

			//Se não for caractere de espaço
			if (!Font::IsCharacterSpace(character))
			{
				const float x = advance_width + this->font->GetCharacterLeft(character);
				const float y = this->font->GetMaxBearing() - this->font->GetCharacterTop(character);

				const float w = this->font->GetCharacterWidth(character);
				const float h = this->font->GetCharacterHeight(character);

				const float texture_position_x = this->font->GetCharacterTexturePositionX(character);
				const float texture_position_y = this->font->GetCharacterTexturePositionY(character);

				this->CharacterDataUpdate(index,x,y,w,h,texture_position_x,texture_position_y);

				index += Text::vertex_rect_total;
			}

			//Atualizar para a proxima posição X mesmo sendo caractere de espaço
			advance_width += this->font->GetCharacterAdvanceWidth(character);
		}

		this->data_update = false;
	}
}

void Text::CharacterDataUpdate(const int index,const float x,const float y,const float w,const float h,const float texture_position_x,const float texture_position_y)
{
	// (x1,y1) 0----1 (x2,y1)
	//		   |   /|
	//		   |  / |
	//		   | /  |
	// (x1,y2) 2----3 (x2,y2)

	const int first_index = index + 0;
	const int second_index = index + 1;
	const int third_index = index + 2;
	const int fourth_index = index + 3;

	//Vertex Position
	float x_1 = x;
	float y_1 = y;

	float x_2 = x_1 + w;
	float y_2 = y_1 + h;

	this->model.SetVertexPosition(first_index,x_1,y_1);
	this->model.SetVertexPosition(second_index,x_2,y_1);
	this->model.SetVertexPosition(third_index,x_1,y_2);
	this->model.SetVertexPosition(fourth_index,x_2,y_2);

	//Vertex Texture Coordinate
	const float u = texture_position_x / this->model.GetTexture().GetWidth();
	const float v = texture_position_y / this->model.GetTexture().GetHeight();

	const float uw = w / this->model.GetTexture().GetWidth();
	const float vh = h / this->model.GetTexture().GetHeight();

	x_1 = u;
	y_1 = v;

	x_2 = x_1 + uw;
	y_2 = y_1 + vh;

	this->model.SetVertexTextureCoordinate(first_index,x_1,y_1);
	this->model.SetVertexTextureCoordinate(second_index,x_2,y_1);
	this->model.SetVertexTextureCoordinate(third_index,x_1,y_2);
	this->model.SetVertexTextureCoordinate(fourth_index,x_2,y_2);
}

void Text::Show(Video& video,const int show_text_index_max)
{
	//Se tiver caractere e fonte
	if ((this->valid_character_total > 0) && (this->font))
	{
		//Caso não for usar o texto todo
		if (show_text_index_max >= 0)
		{
			const size_t size = min(show_text_index_max,static_cast<int>(this->valid_character_total)) * Text::vertex_rect_total;

			this->model.SetUseLimitedVertexTotal(size);

			//Alterando a quantidade de primitivas com base no total de vértices que será usado no momento
			this->model.SetPrimitiveCount(this->model.GetVertexTotal() - 2);
		}

		this->DataUpdate();
		video.Draw(this->model);
	}
}

void Text::Clear()
{
	this->valid_character_total = 0;
	this->string_text.clear();
	this->model.ResizeVertices(0);
	this->size.SetX(0.0f);
	this->size.SetY(0.0f);
}

Point2D<float> Text::TextSize(const Font& font,const string& string_text)
{
	const Text text(font,string_text,Color::Black);
	return Point2D<float>(text.GetW(),text.GetH());
}
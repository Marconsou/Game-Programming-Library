#ifndef TOOLTIP_H
#define TOOLTIP_H

#include "Text.h"

namespace GPL
{
	enum class ToolTipTextAlign
	{
		Center,
		Left,
		Right,
	};

	class ToolTip
	{
	private:
		//Estrutura que representa a linha de textos
		struct TextLine
		{
			//Texto contendo a informação
			Text text;

			//Tipo de alinhamento do texto
			ToolTipTextAlign text_align;

			//Construtor
			TextLine(const Font& font,const std::string& string_text,const Color& color,const ToolTipTextAlign text_align) :
				text(font,string_text,color),text_align(text_align) {}
		};

		//Fonte para ser usada em todos os textos
		const Font* font;

		//Distância entre a posição inicial de cada vértices próximos
		float edge_distance;

		//Atualizar dados
		bool data_update;

		//Dimensões do fundo
		Rect<float> rect;

		//Model para renderizar o fundo do ToolTip
		Model background;

		//Cor do fundo
		Color background_color;

		//Linhas com textos e informações
		std::vector<std::unique_ptr<TextLine>> text_lines;

		//Tamanho do preenchimento interno do fundo
		static const float background_padding;

		//Atualizar a largura máxima após adicionar um texto
		void WidthUpdate();

		//Atualizar dados
		void DataUpdate(Video& video);

		//Verificar se precisará atualizar os dados
		template<typename Type> void CheckForDataUpdate(const Type& value_old,const Type& value_new) { if (value_old != value_new) this->data_update = true; }
	public:
		//Construtor
		GPL_DLL ToolTip();

		//Pegar X
		GPL_DLL float GetX() const;

		//Pegar Y
		GPL_DLL float GetY() const;

		//Pegar W
		GPL_DLL float GetW() const;

		//Pegar H
		GPL_DLL float GetH() const;

		//Alterar Position
		GPL_DLL void SetPosition(const float x,const float y,const bool centralize = false);

		//Alterar ToolTip
		GPL_DLL void SetToolTip(const Font& font,const float edge_distance = 0.0f,const Color& background_color = Color(Color::Black.GetRed(),Color::Black.GetGreen(),Color::Black.GetBlue(),0.5f));

		//Nova linha de texto
		GPL_DLL void NewTextLine(const std::string& string_text,const Color& color,const ToolTipTextAlign text_align = ToolTipTextAlign::Center);

		//Adicionar texto na última linha
		GPL_DLL void AddTextLine(const std::string& string_text,const Color& color);

		//Mostrar ToolTip
		GPL_DLL void ShowToolTip(Video& video);

		//Limpar as linhas de texto do ToolTip
		GPL_DLL void Clear();
	};
}

#endif
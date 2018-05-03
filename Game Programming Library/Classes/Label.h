#ifndef LABEL_H
#define LABEL_H

#include "Control.h"
#include "ToolTip.h"

namespace GPL
{
	class Label : public Control
	{
	private:
		//Texto principal do Label
		Text text;

		//ToolTip para informações quando o Mouse estiver sobre o Label
		ToolTip tooltip;

		//Mostrar conteúdo adicional
		GPL_DLL virtual void ShowAdditionalContent(const Input& input,Video& video,const Timer& timer);

		//Mostrar o controle
		GPL_DLL bool Show(const Input& input,Video& video,const Timer& timer) override;

		//Evento para mudar cores do controle
		GPL_DLL virtual void OnEnabledChanged(const Control& control);
	public:
		//Alterar Text String
		GPL_DLL void SetTextString(const std::string& string_text);

		//Pegar Text String
		GPL_DLL const std::string& GetTextString() const;

		//Alterar Text
		GPL_DLL void SetText(const Font& font,const std::string& string_text,const Color& color = Color::White);

		//Alterar Text Color
		GPL_DLL void SetTextColor(const Color& color);

		//Pegar Text Color
		GPL_DLL const Color& GetTextColor() const;

		//Alterar ToolTip
		GPL_DLL void SetToolTip(const Font& font,const float edge_distance = 0.0f,const Color& background_color = Color(Color::Black.GetRed(),Color::Black.GetGreen(),Color::Black.GetBlue(),0.5f));

		//Adicionar texto
		GPL_DLL void AddText(const std::string& string_text,const Color& color);

		//Limpar texto
		GPL_DLL void ClearText();

		//Nova linha de texto para o ToolTip
		GPL_DLL void NewToolTipTextLine(const std::string& string_text,const Color& color,const ToolTipTextAlign text_align = ToolTipTextAlign::Center);

		//Adicionar texto na última linha para o ToolTip
		GPL_DLL void AddToolTipTextLine(const std::string& string_text,const Color& color);

		//Alterar Position
		GPL_DLL virtual void SetPosition(const float x,const float y,const bool centralize = false);
	};
}

#endif
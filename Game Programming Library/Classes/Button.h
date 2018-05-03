#ifndef BUTTON_H
#define BUTTON_H

#include "Control.h"
#include "ToolTip.h"
#include "Sprite.h"

namespace GPL
{
	class Button : public Control
	{
	private:
		//Escala usada pelo botão ao clicar com o Mouse e manter pressionado
		const float scale;

		//Tecla de atalho
		KeyboardKey keyboard_key_shortcut;

		//Texto principal do botão
		Text text;

		//Cursor para o texto
		Model cursor_text;

		//Sprite para imagem do botão
		Sprite sprite;

		//ToolTip para informações quando o Mouse estiver sobre o botão
		ToolTip tooltip;

		//Adicionar texto
		void AddText(const Font& font,const std::string& string_text,const Color& color);

		//Atualizar a escala dos objetos
		void ScaleUpdate(const bool scaled);

		//Evento para mudar a escala do botão
		void OnLeave(const Control& control);

		//Evento para mudar a escala do botão
		void OnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento para mudar a escala do botão
		void OnMouseUp(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y);


		GPL_DLL virtual KeyboardKey GetKeyboardKeyShortcut() const;

		//Mostrar conteúdo adicional
		GPL_DLL virtual void ShowAdditionalContent(const Input& input,Video& video,const Timer& timer);

		//Evento para mudar cores do controle
		GPL_DLL virtual void OnEnabledChanged(const Control& control);
	protected:
		//Mostrar o controle
		GPL_DLL bool Show(const Input& input,Video& video,const Timer& timer) override;
	public:
		//Construtor
		GPL_DLL Button();

		//Alterar Key Shortcut
		GPL_DLL void SetKeyboardKeyShortcut(const KeyboardKey keyboard_key_shortcut);

		//Pegar Texture
		GPL_DLL const Texture& GetTexture() const;

		//Pegar Texture Position
		GPL_DLL const Point2D<float>& GetTexturePosition() const;

		//Alterar Color
		GPL_DLL void SetColor(const Color& color);

		//Alterar Button
		GPL_DLL void SetButton(const float x,const float y,const float w,const float h,const bool centralize = false);

		//Alterar Button
		GPL_DLL void SetButton(const Font& font,const std::string& string_text,const Color& text_color = Color::White,const Color& cursor_text_color = Color::White);

		//Alterar Button
		GPL_DLL void SetButton(const Texture& texture,const float w,const float h,const float texture_position_x = 0.0f,const float texture_position_y = 0.0f);

		//Alterar ToolTip
		GPL_DLL void SetToolTip(const Font& font,const float edge_distance = 0.0f,const Color& background_color = Color(Color::Black.GetRed(),Color::Black.GetGreen(),Color::Black.GetBlue(),0.5f));

		//Adicionar texto ao botão já com algum texto
		GPL_DLL void AddButtonText(const std::string& string_text,const Color& color,const bool clear_current_text = false);

		//Nova linha de texto para o ToolTip
		GPL_DLL void NewToolTipTextLine(const std::string& string_text,const Color& color,const ToolTipTextAlign text_align = ToolTipTextAlign::Center);

		//Adicionar texto na última linha para o ToolTip
		GPL_DLL void AddToolTipTextLine(const std::string& string_text,const Color& color);

		//Limpar ToolTip
		GPL_DLL void ClearToolTip();
	};
}

#endif
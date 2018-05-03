#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include "Control.h"
#include "ToolTip.h"
#include "AnimationFrame.h"

namespace GPL
{
	class PictureBox : public Control
	{
	private:
		//Sprite
		Sprite sprite;

		//Animação
		AnimationFrame animation_frame;

		//ToolTip para informações quando o Mouse estiver sobre o Label
		ToolTip tooltip;

		//Mostrar conteúdo adicional
		GPL_DLL virtual void ShowAdditionalContent(const Input& input,Video& video,const Timer& timer);

		//Mostrar o controle
		GPL_DLL bool Show(const Input& input,Video& video,const Timer& timer) override;

		//Evento para mudar cores do controle
		GPL_DLL virtual void OnEnabledChanged(const Control& control);
	public:
		//Alterar Sprite
		GPL_DLL void SetSprite(const Texture& texture,const float w,const float h,const float texture_position_x,const float texture_position_y,const Color& color = Color::White);

		//Alterar Animation Frame
		GPL_DLL void SetAnimationFrame(const Timer& timer,const Texture& texture,const float frame_width,const float frame_height,const int frame_quantity,const float interval,const int pixel_gap = 0);

		//Alterar ToolTip
		GPL_DLL void SetToolTip(const Font& font,const float edge_distance = 0.0f,const Color& background_color = Color(Color::Black.GetRed(),Color::Black.GetGreen(),Color::Black.GetBlue(),0.5f));

		//Nova linha de texto para o ToolTip
		GPL_DLL void NewToolTipTextLine(const std::string& string_text,const Color& color,const ToolTipTextAlign text_align = ToolTipTextAlign::Center);

		//Adicionar texto na última linha para o ToolTip
		GPL_DLL void AddToolTipTextLine(const std::string& string_text,const Color& color);

		//Alterar Position
		GPL_DLL virtual void SetPosition(const float x,const float y,const bool centralize = false);
	};
}

#endif
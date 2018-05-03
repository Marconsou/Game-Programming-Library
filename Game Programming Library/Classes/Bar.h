#ifndef BAR_H
#define BAR_H

#include "Interval.h"
#include "Control.h"
#include "Sprite.h"

namespace GPL
{
	class Bar : public Control
	{
	private:
		//Mostrar a barra do fundo
		bool show_background_bar;

		//Valor em porcentagem da barra da frente
		int percentage;

		//Valor em porcentagem da barra do fundo
		int background_percentage;

		//Tamanho da largura inicial da barra
		float bar_width_initial;

		//Temporizador para a barra do fundo
		Interval background_bar_change_timer;

		//Posição da barra em relação ao fundo
		Point2D<float> bar_position_relative;

		//Fundo da barra
		Sprite background;

		//Barra do fundo
		Sprite background_bar;

		//Barra da frente
		Sprite foreground_bar;

		//Alterar dados básicos de uma barra
		void SetBarBase(Sprite& bar,const Texture& texture,const Color& color,const Rect<float>& texture_rect);

		//Atualizar dados do controle antes de mostrá-lo
		void Update(const Input& input,const Timer& timer) override;

		//Mostrar o controle
		bool Show(const Input& input,Video& video,const Timer& timer) override;

		//Evento para mudar cores do controle
		virtual void OnEnabledChanged(const Control& control);
	public:
		//Construtor
		GPL_DLL Bar();

		//Alterar Bar
		GPL_DLL void SetBar(const Texture& texture,const Color& background_color,const Color& background_bar_color,const Color& foreground_bar_color,const Rect<float>& background_texture_rect,const Rect<float>& bar_texture_rect,const Point2D<float>& bar_position_relative = Point2D<float>());

		//Alterar Show Background Bar
		GPL_DLL void SetShowBackgroundBar(const bool show_background_bar);

		//Alterar Percentage
		GPL_DLL void SetPercentage(const int value_base,const int value_max);

		//Pegar Percentage
		GPL_DLL int GetPercentage() const;

		//Pegar Background Percentage
		GPL_DLL int GetBackgroundPercentage() const;
	};
}

#endif
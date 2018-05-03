#ifndef TRACKBAR_H
#define TRACKBAR_H

#include "Control.h"
#include "Video.h"

namespace GPL
{
	enum class TrackBarOrientation
	{
		Horizontal,
		Vertical,
	};

	class TrackBar : public Control
	{
	private:
		using Event = Signal<void,const Control&>;

		//Valor atual
		int value;

		//Valor antigo do Value
		int old_value;

		//Valor máximo
		int value_max;

		//Orientação do TrackBar
		TrackBarOrientation orientation;

		//Mouse passando sobre a barra
		bool mouse_click_on_bar;

		//Mouse passando sobre o cursor
		bool mouse_click_on_cursor;

		//Dimensões da barra
		Rect<float> bar_rect;

		//Dimensões do cursor
		Rect<float> cursor_rect;

		//Model para mostrar a barra
		Model bar;

		//Model para mostrar o cursor indicador para mudar o valor na barra
		Model cursor;

		//Evento quando o valor é alterado
		Event on_value_changed;

		//Atualizar posições com base na orientação
		void DataUpdate(const Input& input);

		//Calculando o valor com base na posição do Mouse
		int CalculateValueByPosition(const float mouse_position,const float track_bar_position,const float track_bar_size,const float cursor_position,const float cursor_size) const;

		//Resetar valores
		void Reset();

		//Evento para incrementar/decrementar o valor
		void OnKeyDown(const Control& control,const KeyboardKey keyboard_key);

		//Evento para verifcar aonde está o Mouse dentro do controle no momento do clique
		void OnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento para resetar valores do Mouse
		void OnMouseUp(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Verificar por eventos específicos do controle
		virtual void CheckForSpecificEvents();

		//Mostrar o controle
		bool Show(const Input& input,Video& video,const Timer& timer) override;

		//Evento para mudar cores do controle
		virtual void OnEnabledChanged(const Control& control);

		//Atualizar dados das dimensões
		static void RectUpdate(const Rect<float>& rect,Model& model);
	public:
		//Construtor
		GPL_DLL TrackBar();

		//Alterar Value
		GPL_DLL void SetValue(const int value);

		//Pegar Value
		GPL_DLL int GetValue() const;

		//Alterar Track Bar
		GPL_DLL void SetTrackBar(const int value_max,const float bar_length,const float bar_thickness,const float cursor_thickness,const float cursor_length,const Color& bar_color,const Color& cursor_color,const TrackBarOrientation orientation = TrackBarOrientation::Horizontal);

		template<class Event,class Object> void AddEventOnValueChanged(const Event& event,Object& object) { this->on_value_changed.Add(event,object,std::placeholders::_1); }
	};
}

#endif
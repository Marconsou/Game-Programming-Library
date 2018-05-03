#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Control.h"
#include "Text.h"
#include "Sprite.h"

namespace GPL
{
	class CheckBox : public Control
	{
	private:
		using Event = Signal<void,const Control&>;

		//Se a caixa do CheckBox está marcada
		bool checked;

		//Valor antigo do Checked
		bool old_checked;

		//Texto exibido próximo ao CheckBox
		Text text;

		//Fundo
		Sprite background;

		//Sprite para exibir o objeto quando o Check Box estiver marcado
		Sprite check;

		//Evento quando é marcado ou desmarcado
		Event on_checked_changed;

		//Espaçamento para o texto
		static const float text_space;

		//Atualizar dados dos objetos
		void DataUpdate();

		//Evento para (des)marcar o Check Box
		void OnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Verificar por eventos específicos do controle
		virtual void CheckForSpecificEvents();

		//Mostrar o controle
		bool Show(const Input& input,Video& video,const Timer& timer) override;

		//Evento para mudar cores do controle
		virtual void OnEnabledChanged(const Control& control);
	public:
		//Construtor
		GPL_DLL CheckBox();

		//Alterar Checked
		GPL_DLL void SetChecked(const bool checked);

		//Pegar Checked
		GPL_DLL bool GetChecked() const;

		//Alterar Check Box
		GPL_DLL void SetCheckBox(const Font& font,const std::string& string_text,const Color& text_color,const Texture& texture,const float background_w,const float background_h,const float background_texture_coordinate_x,const float background_texture_coordinate_y,const float check_w,const float check_h,const float check_texture_coordinate_x,const float check_texture_coordinate_y);

		template<class Event,class Object> void AddEventOnCheckedChanged(const Event& event,Object& object) { this->on_checked_changed.Add(event,object,std::placeholders::_1); }
	};
}

#endif
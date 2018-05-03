#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <map>
#include "Control.h"
#include "Text.h"
#include "Sprite.h"

namespace GPL
{
	class RadioButton : public Control
	{
	private:
		using Event = Signal<void,const Control&>;
		using RadioGroup = std::multimap<const std::string,RadioButton&>;

		//Se o rádio do RadioButton está marcado
		bool checked;

		//Valor antigo do Checked
		bool old_checked;

		//Texto exibido próximo ao RadioButton
		Text text;

		//Fundo
		Sprite background;

		//Sprite para exibir o objeto quando o Radio Button estiver marcado
		Sprite check;

		//Evento quando é marcado ou desmarcado
		Event on_checked_changed;

		//Espaçamento para o texto
		static const float text_space;

		//Grupo de rádios para controlar quem deverá ser marcado dentro de um mesmo Radio Group
		static RadioGroup radio_groups;

		//Atualizar dados dos objetos
		void DataUpdate();

		//Evento para marcar o Radio Button
		void OnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento para desmarcar outros Radio Buttons do mesmo grupo
		void OnCheckedChanged(const Control& control);

		//Verificar por eventos específicos do controle
		virtual void CheckForSpecificEvents();

		//Mostrar o controle
		bool Show(const Input& input,Video& video,const Timer& timer) override;

		//Evento para mudar cores do controle
		virtual void OnEnabledChanged(const Control& control);
	public:
		//Construtor
		GPL_DLL RadioButton();

		//Destrutor
		GPL_DLL virtual ~RadioButton();

		//Alterar Checked
		GPL_DLL void SetChecked(const bool checked);

		//Pegar Checked
		GPL_DLL bool GetChecked() const;

		//Alterar Radio Button
		GPL_DLL void SetRadioButton(const Font& font,const std::string& string_text,const Color& text_color,const Texture& texture,const float w,const float h,const float texture_position_x,const float texture_position_y,const std::string& radio_group_name = "Default");

		template<class Event,class Object> void AddEventOnCheckedChanged(const Event& event,Object& object) { this->on_checked_changed.Add(event,object,std::placeholders::_1); }
	};
}

#endif
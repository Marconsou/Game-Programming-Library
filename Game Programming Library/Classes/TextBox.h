#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Interval.h"
#include "Control.h"
#include "Text.h"

namespace GPL
{
	enum class TextBoxInputType
	{
		NameInput,
		CharacterOnly,
		NumberOnly,
	};

	class TextBox : public Control
	{
	private:
		using Event = Signal<void,const Control&>;

		//Tipo de entrada de dados
		TextBoxInputType input_type;

		//Tamanho máximo de caracteres
		size_t max_length;

		//Espessura da borda
		float border_thickness;

		//Texto
		Text text;

		//Texto de fundo
		Text background_text;

		//Cursor
		Model cursor;

		//Fundo
		Model background;

		//Borda
		Model border;

		//Valor antigo do texto
		std::string old_string_text;

		//Evento quando o texto é alterado
		Event on_text_changed;

		//Largura do cursor
		static const float cursor_width;

		//Tamanho do preenchimento interno do fundo
		static const float background_padding;

		//Atualizar dados dos objetos
		void DataUpdate();

		//Adicionar um caractere ao texto
		void AddCharacter(const char character);

		//Remover o último caractere
		void RemoveLastCharacter();

		//Verificar por eventos específicos do controle
		virtual void CheckForSpecificEvents();

		//Mostrar o controle
		bool Show(const Input& input,Video& video,const Timer& timer) override;

		//Evento para mudar cores do controle
		virtual void OnEnabledChanged(const Control& control);
	public:
		//Construtor
		GPL_DLL TextBox();

		//Pegar String
		GPL_DLL const std::string& GetString() const;

		//Alterar Text Box
		GPL_DLL void SetTextBox(const Font& font,const TextBoxInputType input_type,const size_t max_length = 20,const float border_thickness = 1.0f,const Color& text_color = Color::Black,const Color& cursor_color = Color::Black,const Color& background_color = Color::White,const Color& border_color = Color::Black);

		//Alterar Text
		GPL_DLL void SetText(const std::string& string_text);

		//Alterar Background Text
		GPL_DLL void SetBackgroundText(const std::string& string_text,const Color& color);

		template<class Event,class Object> void AddEventOnTextChanged(const Event& event,Object& object) { this->on_text_changed.Add(event,object,std::placeholders::_1); }
	};
}

#endif
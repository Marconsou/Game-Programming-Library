#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#include <sstream>
#include "Interval.h"
#include "Window.h"
#include "Button.h"

namespace GPL
{
	class DialogueBox : public Control
	{
	private:
		//Evento para as op��es do Dialogue Box
		using EventOption = Signal<void,const Control&,const int>;

		//Estrutura que representa a linha de textos
		struct TextLine
		{
			//�ndice para os caracteres do texto que ser� mostrado
			size_t current_character_index;

			//Texto da linha toda
			Text text;

			//Construtor
			TextLine(const Font& font,const std::string& string_text,const Color& color) :
				current_character_index(0),text(font,string_text,color) {}
		};

		//Estrutura para representar um par�grafo que cont�m v�rias linhas de texto
		struct Paragraph
		{
			//Linha de texto atual
			size_t current_text_line_index;

			//Linhas de textos
			std::vector<std::unique_ptr<TextLine>> text_lines;

			//Construtor
			Paragraph() :
				current_text_line_index(0) {}
		};

		//Estrutura para dados das op��es
		struct Option
		{
			//Espa�amento para a op��o
			const float tab_space_x;

			//Evento ao selecionar a op��o e esperar Dialogue Box ser removido
			EventOption on_option_selected;

			//Op��o
			Button option;

			//Construtor
			Option(const float tab_space_x) :
				tab_space_x(tab_space_x) {}
		};

		//Centralizar no pr�ximo loop
		bool center_next_loop;

		//Come�ar a abrir o DialogueBox
		bool opening_dialogue_box;

		//Come�ar a fechar o DialogueBox
		bool closing_dialogue_box;

		//Se a largura da janela alcan�ou o limite
		bool width_reach_limit;

		//�ndice da �ltima op��o selecionada
		int last_option_selected_index;

		//Quantidade m�xima de linhas de texto por par�grafo
		size_t text_lines_per_paragraph;

		//Par�grafo atual
		size_t current_paragraph_index;

		//Op��o que ser� mostrada
		size_t current_option_index;

		//Temporizador para mostrar cada caracterer
		Interval character_timer;

		//Temporizador para mostrar cada op��o
		Interval show_option_timer;

		//Temporizador para mudar o tamanho da janela o DialogueBox
		Interval window_resize_timer;

		//�rea virtual do par�grafo
		Rect<float> text_area;

		//Tamanho da janela durante o processo de finaliza��o
		Point2D<int> closing_window_inner_border_quantity;

		//Janela do fundo
		Window window;

		//T�tulo padr�o para todos os textos
		Text title;

		//Indicador para passar para o pr�ximo par�grafo
		Model cursor;

		//Par�grafos contendo todos os textos
		std::vector<std::unique_ptr<Paragraph>> paragraphs;

		//Op��es que poder�o ser selecionadas
		std::vector<std::unique_ptr<Option>> options;

		//Atualizar dados das dimens�es dos objetos com base na janela
		void RectUpdate();

		//Resetar valores para o �nicio do DialogueBox
		void Reset();

		//Limpar o Dialogue Box
		void Clear();

		//Adicionar nova linha de texto
		void NewTextLine(const std::string& string_text,const Color& color);

		//Adicionar novo par�grafo j� com uma linha de texto
		void NewParagraph(const std::string& string_text,const Color& color);

		//Verificar se chegou no �ltimo par�grafo
		bool IsLastParagraph() const;

		//Verificar se chegou � �ltima linha de texto de uma par�grafo
		bool IsLastTextLine(const Paragraph& paragraph) const;

		//Verificar se chegou ao �ltimo caractere de uma linha de texto
		bool IsLastCharacter(const TextLine& text_line) const;

		//Passando para o pr�ximo par�grafo
		void NextParagraph();

		//Passando para a pr�xima linha de texto
		void NextTextLine();

		//Passando para o pr�ximo caractere
		void NextCharacter();

		//For�ar o par�grafo atual a se mostrar instant�neamente
		void SnapshotParagraph();

		//Intera��o com o Dialogue Box
		void Interaction();

		//Come�ar a fechar o Dialogue Box
		void Close();

		//Verificar se o Dialogue Box chegou ao limite (mostrando o m�nimo da janela) para fechar
		bool IsAlmostClosed();

		//Adicionar op��es dinamicamente
		void AddOptionsDynamically(const Timer& timer);

		//Atualizar as posi��es
		void UpdatePositions();

		//Calcular um valor estimado do total da altura no atual momento
		float EstimateTotalHeight() const;

		//Automaticamente alterar o tamanho da janela quando necess�rio
		void AutoSizeWindow(const Timer& timer);

		//Mostrar o cursor
		void ShowCursor(Video& video,const Timer& timer);

		//Mostrar um texto
		void Show(Video& video,Text& text,const int index);

		//Verificar por eventos On Option Selected das op��es
		void CheckForOnOptionSelected();

		//Evento ao clicar em alguma op��o
		void OptionOnClick(const Control& control);

		//Evento ao apertar uma tecla do Keyboard passar para o pr�ximo par�grafo ou encerrar o DialogueBox
		void OnKeyDown(const Control& control,const KeyboardKey keyboard_key);

		//Evento ao apertar um o clique do Mouse passar para o pr�ximo par�grafo ou encerrar o DialogueBox
		void OnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Atualizar dados do controle antes de mostr�-lo
		void Update(const Input& input,const Timer& timer) override;

		//Mostrar o controle
		bool Show(const Input& input,Video& video,const Timer& timer) override;

		//Evento para mudar cores do controle
		virtual void OnEnabledChanged(const Control& control);

		//Dividir strings pelo espa�o
		static void SplitString(const std::string& string_text,std::vector<std::string>& splitted_string_texts);
	public:
		//Construtor
		GPL_DLL DialogueBox();

		//Alterar Dialog Box
		GPL_DLL void SetDialogueBox(const Font& font,const size_t text_lines_per_paragraph,const float text_area_width,const float text_area_padding_x = 0.0f,const float text_area_padding_y = 0.0f,const float text_speed_interval = 0.050f,const std::string& title_text = "",const Color& color = Color::White);

		//Alterar Window Current Background
		GPL_DLL void SetWindowCurrentBackground(const int current_background);

		//Alterar Window Show Border
		GPL_DLL void SetWindowShowBorder(const bool show_border);

		//Alterar Window
		GPL_DLL void SetWindow(const float edge_distance = 0.0f);

		//Alterar Window
		GPL_DLL void SetWindow(const Color& color_left_top,const Color& color_right_top,const Color& color_left_bottom,const Color& color_right_bottom,const float edge_distance = 0.0f);

		//Alterar Option Text
		GPL_DLL void SetOptionText(const int index,const std::string& string_text,const Color& color);

		//Pegar Options Total
		GPL_DLL int GetOptionsTotal() const;

		//Adicionar texto
		GPL_DLL void AddText(const std::string& string_text,const Color& color);

		//Adicionar op��o antes de finalizar o DialogueBox
		GPL_DLL void AddOption(const std::string& string_text,const Color& color,const float tab_space_x = 0.0f,const Color& cursor_text_color = Color::White);

		//Adicionar texto � �ltima op��o adicionada
		GPL_DLL void AddOptionText(const std::string& string_text,const Color& color);

		//Adicionar tecla de atalho para uma op��o
		GPL_DLL void AddOptionKeyShortcut(const int index,const KeyboardKey keyboard_key_shortcut);

		template<class Event,class Object> void AddOptionEventOnClick(const int index,const Event& event,Object& object) { this->options[index]->option.AddEventOnClick(event,object); }
		template<class Event,class Object> void AddOptionEventOnOptionSelected(const int index,const Event& event,Object& object) { this->options[index]->on_option_selected.Add(event,object,std::placeholders::_1,std::placeholders::_2); }

		//Alterar Position
		GPL_DLL virtual void SetPosition(const float x,const float y,const bool centralize = false);

		//Adicionar controle que pode ser processado, devem ser adicionados na ordem que s�o mostrados na tela
		GPL_DLL virtual void AddControl();

		//Remover controle
		GPL_DLL virtual void RemoveControl();
	};
}

#endif
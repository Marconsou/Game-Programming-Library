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
		//Evento para as opções do Dialogue Box
		using EventOption = Signal<void,const Control&,const int>;

		//Estrutura que representa a linha de textos
		struct TextLine
		{
			//Índice para os caracteres do texto que será mostrado
			size_t current_character_index;

			//Texto da linha toda
			Text text;

			//Construtor
			TextLine(const Font& font,const std::string& string_text,const Color& color) :
				current_character_index(0),text(font,string_text,color) {}
		};

		//Estrutura para representar um parágrafo que contém várias linhas de texto
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

		//Estrutura para dados das opções
		struct Option
		{
			//Espaçamento para a opção
			const float tab_space_x;

			//Evento ao selecionar a opção e esperar Dialogue Box ser removido
			EventOption on_option_selected;

			//Opção
			Button option;

			//Construtor
			Option(const float tab_space_x) :
				tab_space_x(tab_space_x) {}
		};

		//Centralizar no próximo loop
		bool center_next_loop;

		//Começar a abrir o DialogueBox
		bool opening_dialogue_box;

		//Começar a fechar o DialogueBox
		bool closing_dialogue_box;

		//Se a largura da janela alcançou o limite
		bool width_reach_limit;

		//Índice da última opção selecionada
		int last_option_selected_index;

		//Quantidade máxima de linhas de texto por parágrafo
		size_t text_lines_per_paragraph;

		//Parágrafo atual
		size_t current_paragraph_index;

		//Opção que será mostrada
		size_t current_option_index;

		//Temporizador para mostrar cada caracterer
		Interval character_timer;

		//Temporizador para mostrar cada opção
		Interval show_option_timer;

		//Temporizador para mudar o tamanho da janela o DialogueBox
		Interval window_resize_timer;

		//Área virtual do parágrafo
		Rect<float> text_area;

		//Tamanho da janela durante o processo de finalização
		Point2D<int> closing_window_inner_border_quantity;

		//Janela do fundo
		Window window;

		//Título padrão para todos os textos
		Text title;

		//Indicador para passar para o próximo parágrafo
		Model cursor;

		//Parágrafos contendo todos os textos
		std::vector<std::unique_ptr<Paragraph>> paragraphs;

		//Opções que poderão ser selecionadas
		std::vector<std::unique_ptr<Option>> options;

		//Atualizar dados das dimensões dos objetos com base na janela
		void RectUpdate();

		//Resetar valores para o ínicio do DialogueBox
		void Reset();

		//Limpar o Dialogue Box
		void Clear();

		//Adicionar nova linha de texto
		void NewTextLine(const std::string& string_text,const Color& color);

		//Adicionar novo parágrafo já com uma linha de texto
		void NewParagraph(const std::string& string_text,const Color& color);

		//Verificar se chegou no último parágrafo
		bool IsLastParagraph() const;

		//Verificar se chegou à última linha de texto de uma parágrafo
		bool IsLastTextLine(const Paragraph& paragraph) const;

		//Verificar se chegou ao último caractere de uma linha de texto
		bool IsLastCharacter(const TextLine& text_line) const;

		//Passando para o próximo parágrafo
		void NextParagraph();

		//Passando para a próxima linha de texto
		void NextTextLine();

		//Passando para o próximo caractere
		void NextCharacter();

		//Forçar o parágrafo atual a se mostrar instantâneamente
		void SnapshotParagraph();

		//Interação com o Dialogue Box
		void Interaction();

		//Começar a fechar o Dialogue Box
		void Close();

		//Verificar se o Dialogue Box chegou ao limite (mostrando o mínimo da janela) para fechar
		bool IsAlmostClosed();

		//Adicionar opções dinamicamente
		void AddOptionsDynamically(const Timer& timer);

		//Atualizar as posições
		void UpdatePositions();

		//Calcular um valor estimado do total da altura no atual momento
		float EstimateTotalHeight() const;

		//Automaticamente alterar o tamanho da janela quando necessário
		void AutoSizeWindow(const Timer& timer);

		//Mostrar o cursor
		void ShowCursor(Video& video,const Timer& timer);

		//Mostrar um texto
		void Show(Video& video,Text& text,const int index);

		//Verificar por eventos On Option Selected das opções
		void CheckForOnOptionSelected();

		//Evento ao clicar em alguma opção
		void OptionOnClick(const Control& control);

		//Evento ao apertar uma tecla do Keyboard passar para o próximo parágrafo ou encerrar o DialogueBox
		void OnKeyDown(const Control& control,const KeyboardKey keyboard_key);

		//Evento ao apertar um o clique do Mouse passar para o próximo parágrafo ou encerrar o DialogueBox
		void OnMouseDown(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Atualizar dados do controle antes de mostrá-lo
		void Update(const Input& input,const Timer& timer) override;

		//Mostrar o controle
		bool Show(const Input& input,Video& video,const Timer& timer) override;

		//Evento para mudar cores do controle
		virtual void OnEnabledChanged(const Control& control);

		//Dividir strings pelo espaço
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

		//Adicionar opção antes de finalizar o DialogueBox
		GPL_DLL void AddOption(const std::string& string_text,const Color& color,const float tab_space_x = 0.0f,const Color& cursor_text_color = Color::White);

		//Adicionar texto à última opção adicionada
		GPL_DLL void AddOptionText(const std::string& string_text,const Color& color);

		//Adicionar tecla de atalho para uma opção
		GPL_DLL void AddOptionKeyShortcut(const int index,const KeyboardKey keyboard_key_shortcut);

		template<class Event,class Object> void AddOptionEventOnClick(const int index,const Event& event,Object& object) { this->options[index]->option.AddEventOnClick(event,object); }
		template<class Event,class Object> void AddOptionEventOnOptionSelected(const int index,const Event& event,Object& object) { this->options[index]->on_option_selected.Add(event,object,std::placeholders::_1,std::placeholders::_2); }

		//Alterar Position
		GPL_DLL virtual void SetPosition(const float x,const float y,const bool centralize = false);

		//Adicionar controle que pode ser processado, devem ser adicionados na ordem que são mostrados na tela
		GPL_DLL virtual void AddControl();

		//Remover controle
		GPL_DLL virtual void RemoveControl();
	};
}

#endif
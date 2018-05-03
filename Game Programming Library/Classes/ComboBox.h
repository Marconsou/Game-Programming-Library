#ifndef COMBOBOX_H
#define COMBOBOX_H

#include "Control.h"
#include "Text.h"

namespace GPL
{
	class ComboBox : public Control
	{
	private:
		using Event = Signal<void,const Control&>;

		//Fonte usando pelos itens de texto
		const Font* font;

		//Se o menu de itens do ComboBox está aparecendo
		bool dropped_down;

		//Espessura da borda
		float border_thickness;

		//Fundo
		Model background;

		//Borda
		Model border;

		//Seleção quando o Mouse estiver sobre um item
		Model selection;

		//Indicador do ComboBox
		Model cursor;

		//Item selecionado exibido no início do controle
		Text selected_text_item;

		//Lista de itens de texto
		std::vector<std::unique_ptr<Text>> text_items;

		//Valor antigo do item de texto selecionado
		std::string old_selected_string_text;

		//Texto do item selecionado
		std::string change_selected_string_text;

		//Evento quando o item de texto selecionado é alterado
		Event on_selected_item_changed;

		//Atualizar dados
		void DataUpdate(const float height);

		//Calcular o índice de uma posição
		int CalculateIndexFromPosition(const float mouse_y);

		//Mouse passa sobre a área de seleção
		bool MouseHoverOnSelectionArea(const float mouse_x,const float mouse_y);

		//Mouse passa sobre algum item
		bool MouseHoverAnItem(const float mouse_x,const float mouse_y);

		//Evento para quando for selecionar um item de texto
		void OnMouseClick(const Control& control,const MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento para garantir o fechamento o ComboBox
		void OnLeave(const Control& control);

		//Verificar por eventos específicos do controle
		virtual void CheckForSpecificEvents();

		//Se é um controle de alta prioridade, para ser verificado os eventos
		virtual bool IsHighPriorityControl() const;

		//Mostrar o controle
		bool Show(const Input& input,Video& video,const Timer& timer) override;

		//Evento para mudar cores do controle
		virtual void OnEnabledChanged(const Control& control);
	public:
		//Construtor
		GPL_DLL ComboBox();

		//Alterar Selected Index
		GPL_DLL void SetSelectedIndex(const int index);

		//Pegar Selected Index
		GPL_DLL int GetSelectedIndex() const;

		//Pegar Selected Text Item
		GPL_DLL const std::string& GetSelectedTextItem() const;

		//Alterar Combo Box
		GPL_DLL void SetComboBox(const Font& font,const float width,const float border_thickness = 1.0f,const Color& background_color = Color::White,const Color& border_color = Color::Black,const Color& selection_color = Color(Color::Black.GetRed(),Color::Black.GetGreen(),Color::Black.GetBlue(),0.5f));

		//Adicionar um item de texto
		GPL_DLL void AddTextItem(const std::string& string_text,const Color& color);

		//Encontrar o item de texto e obter o índice
		GPL_DLL int FindTextItem(const std::string& search_item);

		//Limpar lista
		GPL_DLL void Clear();

		template<class Event,class Object> void AddEventOnSelectedItemChanged(const Event& event,Object& object) { this->on_selected_item_changed.Add(event,object,std::placeholders::_1); }
	};
}

#endif
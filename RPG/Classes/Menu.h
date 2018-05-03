#ifndef MENU_H
#define MENU_H

#include "GameState.h"
#include "GameRPG.h"

namespace RPG
{
	class Menu : public GPL::GameState
	{
	private:
		using Event = GPL::Signal<void,const Menu&>;

		//Evento quando o Menu é fechado
		Event on_close;

		//Índice de criação dos controles
		int creation_index;

		//Fonte padrão pequeno
		const GPL::Font& default_font_small;

		//Fonte padrão medium
		const GPL::Font& default_font_medium;

		//Todos os controles do Menu
		std::vector<std::unique_ptr<GPL::Control>> controls;
	protected:
		//Pegar Default Edge Distance
		float GetDefaultEdgeDistance() const;

		//Pegar Default Font Small
		const GPL::Font& GetDefaultFontSmall() const;

		//Pegar Default Font Medium
		const GPL::Font& GetDefaultFontMedium() const;

		//Pegar Control Total
		size_t GetControlTotal() const;

		//Redimensionar a quantidade de controles
		void ResizeControls(const size_t size);

		//Habilitar ou desabilitar todos os controles
		void EnableControls(const bool enable);

		//Deixar visível ou esconder todos os controles
		void VisibleControls(const bool visible);

		template<class Type> 
		Type& GetControl(const int index) 
		{ 
			return static_cast<Type&>(*this->controls[index].get());
		}

		template<class Type>
		const Type& GetControl(const int index) const
		{
			return static_cast<Type&>(*this->controls[index].get());
		}

		//Criar um controle com base no tipo e retorná-lo
		template<class Type> 
		Type& CreateControl() 
		{ 
			this->controls[this->creation_index] = std::make_unique<Type>(); 
			this->creation_index++; return static_cast<Type&>(*this->controls[this->creation_index - 1].get()); 
		}

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();

		//Mostrar todo o conteúdo
		virtual void Show();

		//Extrair dados de um texto corretamente, substituindo símbolos por valores quando necessário
		static void ExtractInformation(const std::string& text_string,const std::vector<int>& values,std::vector<std::string>& strings,std::vector<GPL::Color>& colors);
	public:
		//Construtor
		Menu(const size_t size = 0);

		//Destrutor
		virtual ~Menu() = 0;

		//Atualizar todos os controles
		void ControlsUpdate(const bool add_controls);

		//Evento geral para On Click
		void GeneralOnClick(const GPL::Control& control);

		template<class Event,class Object> 
		void AddEventOnClose(const Event& event,Object& object) 
		{ 
			this->on_close.Add(event,object,std::placeholders::_1); 
		}
	};
}

#endif
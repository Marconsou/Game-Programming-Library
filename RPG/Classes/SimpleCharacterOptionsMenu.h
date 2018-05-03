#ifndef SIMPLECHARACTEROPTIONSMENU_H
#define SIMPLECHARACTEROPTIONSMENU_H

#include "Menu.h"

namespace RPG
{
	class SimpleCharacterOptionsMenu : public Menu
	{
	private:
		//Referência da posição do Menu
		const GPL::Point2D<float>& position;

		//Referência para mudar posição das janelas de forma sincronizada
		const bool& change_window_position;

		//Quantidade de botões antes da opção Back para pré calcular sua posição
		const int buttons_before_back_button;

		//Velocidade da aceleração da janela de opções
		float window_speed_x;

		//Atualizar as posições dos controles
		void PositionUpdate();

		//Evento do botão Back
		void BackOnClick(const GPL::Control& control);
	protected:
		//IDs dos controles do Simple Character Options Menu
		enum SimpleCharacterOptionsMenuControlID
		{
			OptionsWindow = 0,
			BackButton,
			SimpleCharacterOptionsMenuControlMax,
		};

		//Pegar Position
		const GPL::Point2D<float>& GetPosition() const;

		//Pegar Change Window Position
		bool GetChangeWindowPosition() const;

		//Pegar Options Window X
		float GetOptionsWindowX() const;

		//Pegar Options Window Y
		float GetOptionsWindowY() const;

		//Pegar Back Button X
		float GetBackButtonX() const;

		//Pegar Back Button H
		float GetBackButtonH() const;

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		SimpleCharacterOptionsMenu(const GPL::Point2D<float>& position,const bool& change_window_position,const float contents_window_width,const int buttons_before_back_button = 0,const size_t size_added = 0,const int inner_block_quantity_w = 4,const int inner_block_quantity_h = 0);

		//Pegar Options Window W
		float GetOptionsWindowW() const;
	};
}

#endif
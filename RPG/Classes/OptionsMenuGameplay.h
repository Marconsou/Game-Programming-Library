#ifndef OPTIONSMENUGAMEPLAY_H
#define OPTIONSMENUGAMEPLAY_H

#include "TrackBar.h"
#include "ComboBox.h"
#include "Label.h"
#include "RadioButton.h"
#include "Menu.h"

namespace RPG
{
	class OptionsMenuGameplay : public Menu
	{
	private:
		//IDs dos controles do Options Menu Gameplay
		enum OptionsMenuGameplayControlID
		{
			LanguageLabel = 0,
			LanguageComboBox,
			TextSpeedLabel,
			TextSpeedComboBox,
			DefaultWindowRadioButton,
			DefaultWindowComboBox,
			CustomWindowRadioButton,
			CustomWindowComboBox,
			RedComponentTrackBar,
			GreenComponentTrackBar,
			BlueComponentTrackBar,
			AlphaComponentTrackBar,
			SampleWindow,
			OptionsMenuGameplayControlMax,
		};

		//Cor esquerda superior da janela
		GPL::Color color_left_top;

		//Cor direita superior da janela
		GPL::Color color_right_top;

		//Cor esquerda inferior da janela
		GPL::Color color_left_bottom;

		//Cor direita inferior da janela
		GPL::Color color_right_bottom;

		//Atualizar os controles com relação ao Custom Window
		void CustomWindowControlsUpdate();

		//Atualizar a janela de avaliação
		void SampleWindowUpdate();

		//Cor selecionada do canto da janela
		GPL::Color& CornerSelectedColor();

		//Atualizar cor selecionada para posteriormente alterar na janela de avaliação
		void CornerColorUpdate();

		//Atualizar os Track Bars de componentes de cores
		void TrackBarColorUpdate();

		//Evento geral On Mouse Down
		void GeneralOnMouseDown(const GPL::Control& control,const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento do Default Window Radio Button
		void DefaultWindowOnCheckedChanged(const GPL::Control& control);

		//Evento do Default Window Combo Box
		void DefaultWindowOnSelectedItemChanged(const GPL::Control& control);

		//Evento do Custom Window Combo Box
		void CustomWindowOnSelectedItemChanged(const GPL::Control& control);

		//Evento do Track Bar Red Component
		void RedComponentOnValueChanged(const GPL::Control& control);

		//Evento do Green Component Track Bar
		void GreenComponentOnValueChanged(const GPL::Control& control);

		//Evento do Blue Component Track Bar
		void BlueComponentOnValueChanged(const GPL::Control& control);

		//Evento do Alpha Component Track Bar
		void AlphaComponentOnValueChanged(const GPL::Control& control);


		void Hiding() override;


		void Showing() override;
	public:
		//Construtor
		OptionsMenuGameplay(const float start_x,const float start_y);

		//Carregar o conteúdo
		void LoadContents(const bool load_once,const float start_x,const float start_y);

		//Carregar configurações padrões
		void DefaultConfiguration();

		//Salvar todas as configurações
		void SaveConfiguration();
	};
}

#endif
#ifndef OPTIONSMENUVIDEO_H
#define OPTIONSMENUVIDEO_H

#include "ComboBox.h"
#include "Label.h"
#include "CheckBox.h"
#include "Menu.h"

namespace RPG
{
	class OptionsMenuVideo : public Menu
	{
	private:
		//IDs dos controles do Options Menu Video
		enum OptionsMenuVideoControlID
		{
			VideoInformationLabel = 0,
			ResolutionLabel,
			ResolutionComboBox,
			ColorDepthLabel,
			ColorDepthComboBox,
			TextureFilterLabel,
			TextureFilterComboBox,
			FullscreenCheckBox,
			VSyncCheckBox,
			OptionsMenuVideoControlMax,
		};

		//Carregar as resoluções suportadas
		void LoadSupportedResolutions(std::vector<std::string>& supported_resolutions) const;

		//Atualizar o Resolution Combo Box
		void ResolutionComboBoxUpdate(const bool load_once);

		//Evento geral On Mouse Down
		void GeneralOnMouseDown(const GPL::Control& control,const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento do Combo Box Color Depth
		void ColorDepthOnSelectedItemChanged(const GPL::Control& control);

		//Evento do Check Box Fullscreen
		void FullscreenOnCheckedChanged(const GPL::Control& control);


		void Hiding() override;


		void Showing() override;
	public:
		//Construtor
		OptionsMenuVideo(const float start_x,const float start_y);

		//Carregar o conteúdo
		void LoadContents(const bool load_once,const float start_x,const float start_y);

		//Carregar configurações padrões
		void DefaultConfiguration();

		//Salvar todas as configurações
		void SaveConfiguration();
	};
}

#endif
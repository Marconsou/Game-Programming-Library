#ifndef OPTIONSMENUAUDIO_H
#define OPTIONSMENUAUDIO_H

#include "TrackBar.h"
#include "ComboBox.h"
#include "Label.h"
#include "CheckBox.h"
#include "Menu.h"

namespace RPG
{
	class OptionsMenuAudio : public Menu
	{
	private:
		//IDs dos controles do Options Menu Audio
		enum OptionsMenuAudioControlID
		{
			AudioInformationLabel = 0,
			AudioEngineLabel,
			AudioEngineComboBox,
			MusicVolumeCheckBox,
			MusicVolumeValueTrackBar,
			MusicVolumeValueLabel,
			SoundVolumeCheckBox,
			SoundVolumeValueTrackBar,
			SoundVolumeValueLabel,
			OptionsMenuAudioControlMax,
		};

		//Último Engine de Audio alterada
		GPL::AudioEngine last_audio_engine;

		//Evento geral On Mouse Down
		void GeneralOnMouseDown(const GPL::Control& control,const GPL::MouseButton mouse_button,const float mouse_x,const float mouse_y);

		//Evento do Check Box Music Volume
		void MusicVolumeOnCheckedChanged(const GPL::Control& control);

		//Evento do Check Box Sound Volume
		void SoundVolumeOnCheckedChanged(const GPL::Control& control);

		//Evento do Track Bar Music Volume Value
		void MusicVolumeValueOnValueChanged(const GPL::Control& control);

		//Evento do Track Bar Sound Volume Value
		void SoundVolumeValueOnValueChanged(const GPL::Control& control);


		void Hiding() override;


		void Showing() override;
	public:
		//Construtor
		OptionsMenuAudio(const float start_x,const float start_y);

		//Carregar o conteúdo
		void LoadContents(const bool load_once,const float start_x,const float start_y);

		//Carregar configurações padrões
		void DefaultConfiguration();

		//Salvar todas as configurações
		void SaveConfiguration();
	};
}

#endif
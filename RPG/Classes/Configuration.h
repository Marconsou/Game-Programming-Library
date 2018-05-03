#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <algorithm>
#include <fstream>
#include "Color.h"
#include "Quantity.h"
#include "Directory.h"

namespace RPG
{
	class Configuration
	{
	private:
		//Diretório para Saves
		const std::string save_path;

		//Nome do arquivo de configuração
		const std::string game_config_file_name;

		//Cor esquerda superior da janela
		const GPL::Color default_color_left_top;

		//Cor direita superior da janela
		const GPL::Color default_color_right_top;

		//Cor esquerda inferior da janela
		const GPL::Color default_color_left_bottom;

		//Cor direita inferior da janela
		const GPL::Color default_color_right_bottom;

		//Cor esquerda superior da janela
		GPL::Color color_left_top;

		//Cor direita superior da janela
		GPL::Color color_right_top;

		//Cor esquerda inferior da janela
		GPL::Color color_left_bottom;

		//Cor direita inferior da janela
		GPL::Color color_right_bottom;

		//Linguagem do texto utilizado
		GPL::Quantity language;

		//Velocidade do texto de diálogo
		GPL::Quantity text_speed;

		//Interface das janela
		GPL::Quantity default_window;

		//Profundidade de cores
		GPL::Quantity color_depth;

		//Filtro de textura
		GPL::Quantity texture_filter;

		//Engine de Audio
		GPL::Quantity audio_engine;

		//Se o Default Window foi selecionado
		bool default_window_selected;

		//Se está em tela cheia
		bool fullscreen;

		//Se está com a sincronização vertical ligada
		bool vsync;

		//Se a música está habilitada
		bool music_enabled;

		//Se o som está habilitado
		bool sound_enabled;

		//Largura da resolução
		int width;

		//Altura da resolução
		int height;

		//Volume da música
		float music_volume;

		//Volume do som
		float sound_volume;

		//Salvar dados
		template<typename Type> void SaveSingleData(std::ofstream& save,const std::string& id,const Type data) const { save << id << " " << data << std::endl; }

		//Carregar dados
		template<typename Type> Type LoadSingleData(std::ifstream& load,const Type min_value = 0,const Type max_value = 1) const
		{
			//Lendo o identificador
			string buffer_id;
			load >> buffer_id;

			//Lendo o dado
			Type data = 0;
			load >> data;

			//Limitando e retornando o dado
			return min(max(data,min_value),max_value);
		}
	public:
		//Construtor
		Configuration();

		//Pegar Default Color Left Top
		const GPL::Color& GetDefaultColorLeftTop() const;

		//Pegar Default Color Right Top
		const GPL::Color& GetDefaultColorRightTop() const;

		//Pegar Default Color Left Bottom
		const GPL::Color& GetDefaultColorLeftBottom() const;

		//Pegar Default Color Right Bottom
		const GPL::Color& GetDefaultColorRightBottom() const;

		//Pegar Color Left Top
		GPL::Color& GetColorLeftTop();

		//Pegar Color Right Top
		GPL::Color& GetColorRightTop();

		//Pegar Color Left Bottom
		GPL::Color& GetColorLeftBottom();

		//Pegar Color Right Bottom
		GPL::Color& GetColorRightBottom();

		//Pegar Language
		GPL::Quantity& GetLanguage();

		//Pegar Text Speed
		GPL::Quantity& GetTextSpeed();

		//Pegar Default Window
		GPL::Quantity& GetDefaultWindow();

		//Pegar Color Depth
		GPL::Quantity& GetColorDepth();

		//Pegar Texture Filter
		GPL::Quantity& GetTextureFilter();

		//Pegar Audio Engine
		GPL::Quantity& GetAudioEngine();

		//Alterar Default Window Selected
		void SetDefaultWindowSelected(const bool default_window_selected);

		//Pegar Default Window Selected
		bool GetDefaultWindowSelected() const;

		//Alterar Fullscreen
		void SetFullscreen(const bool fullscreen);

		//Pegar Fullscreen
		bool GetFullscreen() const;

		//Alterar VSync
		void SetVSync(const bool vsync);

		//Pegar VSync
		bool GetVSync() const;

		//Alterar Music Enabled
		void SetMusicEnabled(const bool music_enabled);

		//Pegar Music Enabled
		bool GetMusicEnabled() const;

		//Alterar Sound Enabled
		void SetSoundEnabled(const bool sound_enabled);

		//Pegar Sound Enabled
		bool GetSoundEnabled() const;

		//Alterar Width
		void SetWidth(const int width);

		//Pegar Width
		int GetWidth() const;

		//Alterar Height
		void SetHeight(const int height);

		//Pegar Height
		int GetHeight() const;

		//Alterar Music Volume
		void SetMusicVolume(const float music_volume);

		//Pegar Music Volume
		float GetMusicVolume() const;

		//Alterar Sound Volume
		void SetSoundVolume(const float sound_volume);

		//Pegar Sound Volume
		float GetSoundVolume() const;

		//Salva o arquivo de configuração
		void SaveToFile() const;

		//Carrega o arquivo de configuração
		void LoadFromFile();
	};
}

#endif
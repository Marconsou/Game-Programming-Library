#ifndef WINDOW_H
#define WINDOW_H

#include "Control.h"
#include "Sprite.h"

namespace GPL
{
	class Window : public Control
	{
	private:
		//Fundo atual
		int current_background;

		//Controle de índice para as bordas
		int border_index;

		//Distância entre a posição inicial de cada vértices próximos
		float edge_distance;

		//Mostrar Borda
		bool show_border;

		//Referência da textura do fundo que será usada para alterar o fundo na atualização dos dados
		const Texture* background_texture;

		//Cor esquerda superior da janela
		Color color_left_top;

		//Cor direita superior da janela
		Color color_right_top;

		//Cor esquerda inferior da janela
		Color color_left_bottom;

		//Cor direita inferior da janela
		Color color_right_bottom;

		//Model para renderizar o fundo da janela
		Model background;

		//Sprites para renderizar as bordas parte por parte
		std::vector<std::unique_ptr<Sprite>> borders;

		//Textura padrão dos fundos e bordas
		static const Texture* texture;

		//Quantidade total de janelas
		static int background_quantity;

		//Valor do intervalo de Pixels para cada fundo e borda na textura
		static int pixel_gap;

		//Tamanho da área de cada fundo
		static float background_size;

		//Valor do bloco (pedaço) da janela
		static float block_size;

		//Atualizar cada parte da borda
		void SingleBorderUpdate(const float x,const float y,const float border_texture_position_x,const float border_texture_position_y);

		//Atualizar cada linha da borda
		void LineBorderUpdate(const float border_texture_position_x,const float border_texture_position_y,const bool last_line);

		//Atualizar dados dos objetos do fundo
		void BackgroundDataUpdate(float& background_texture_position_x,float& background_texture_position_y);

		//Atualizar dados dos objetos da borda
		void BorderDataUpdate(const float background_texture_position_x,const float background_texture_position_y);

		//Mostrar o controle
		bool Show(const Input& input,Video& video,const Timer& timer) override;

		//Evento para mudar cores do controle
		virtual void OnEnabledChanged(const Control& control);
	public:
		//Construtor
		GPL_DLL Window();

		//Alterar Current Background
		GPL_DLL void SetCurrentBackground(const int current_background);

		//Alterar Show Border
		GPL_DLL void SetShowBorder(const bool show_border);

		//Pegar Color Left Top
		GPL_DLL const Color& GetColorLeftTop() const;

		//Pegar Color Right Top
		GPL_DLL const Color& GetColorRightTop() const;

		//Pegar Color Left Bottom
		GPL_DLL const Color& GetColorLeftBottom() const;

		//Pegar Color Right Bottom
		GPL_DLL const Color& GetColorRightBottom() const;

		//Alterar Inner Block Quantity
		GPL_DLL void SetInnerBlockQuantity(const int inner_block_quantity_w,const int inner_block_quantity_h);

		//Pegar Inner Block Quantity W
		GPL_DLL int GetInnerBlockQuantityW() const;

		//Pegar Inner Block Quantity H
		GPL_DLL int GetInnerBlockQuantityH() const;

		//Pegar Block Quantity W
		GPL_DLL int GetBlockQuantityW() const;

		//Pegar Block Quantity H
		GPL_DLL int GetBlockQuantityH() const;

		//Alterar Window
		GPL_DLL void SetWindow(const int inner_block_quantity_w,const int inner_block_quantity_h,const float edge_distance = 0.0f);

		//Alterar Window
		GPL_DLL void SetWindow(const int inner_block_quantity_w,const int inner_block_quantity_h,const Color& color_left_top,const Color& color_right_top,const Color& color_left_bottom,const Color& color_right_bottom,const float edge_distance = 0.0f);

		//Pegar Background Total
		GPL_DLL static int GetBackgroundTotal();

		//Pegar Block Size
		GPL_DLL static float GetBlockSize();

		//Alterar propriedades comuns de todas as janelas
		GPL_DLL static void WindowsProperties(const Texture& texture,const int background_quantity,const float background_size,const int pixel_gap = 0);
	};
}

#endif
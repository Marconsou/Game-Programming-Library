#ifndef CHARACTERMENU_H
#define CHARACTERMENU_H

#include "InformationMenu.h"
#include "FullCharacterOptionsMenu.h"

namespace RPG
{
	class CharacterMenu : public Menu
	{
	private:
		//IDs dos controles do Character Menu
		enum CharacterMenuControlID
		{
			ContentsWindow = 0,
			CharacterMenuControlMax,
		};

		//Posição da janela de conteúdos Menu
		GPL::Point2D<float> position;

		//Mudar posição das janelas de forma sincronizada usando o temporizador
		bool change_window_position;

		//Velocidade da aceleração da janela de conteúdos
		float contents_window_speed_x;

		//Largura da janela de opçãoes para ser usado como limitador da janela de conteúdos
		float options_window_w;

		//Atualizar as posições dos controles
		void PositionUpdate();

		//Atualizar o ícone indicando que tem pontos para gastar
		void SpendIconPictureBoxUpdate(const int value,bool& control_added,GPL::PictureBox& picture_box);

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	protected:
		//Pegar Position
		const GPL::Point2D<float>& GetPosition() const;
	public:
		//Construtor
		CharacterMenu(const bool full_character_options_menu);
	};
}

#endif
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

		//Posi��o da janela de conte�dos Menu
		GPL::Point2D<float> position;

		//Mudar posi��o das janelas de forma sincronizada usando o temporizador
		bool change_window_position;

		//Velocidade da acelera��o da janela de conte�dos
		float contents_window_speed_x;

		//Largura da janela de op��oes para ser usado como limitador da janela de conte�dos
		float options_window_w;

		//Atualizar as posi��es dos controles
		void PositionUpdate();

		//Atualizar o �cone indicando que tem pontos para gastar
		void SpendIconPictureBoxUpdate(const int value,bool& control_added,GPL::PictureBox& picture_box);

		//Atualizar dados e a l�gica de todo o conte�do
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
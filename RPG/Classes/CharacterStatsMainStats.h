#ifndef CHARACTERSTATSMAINSTATS_H
#define CHARACTERSTATSMAINSTATS_H

#include "Bar.h"
#include "PictureBox.h"
#include "CharacterStatsPage.h"

namespace RPG
{
	class CharacterStatsMainStats : public CharacterStatsPage
	{
	private:
		//IDs de alguns controles adicionais diferentes dos Labels do Character Stats Main Stats
		enum CharacterStatsMainStatsControlID
		{
			StrengthButton = 0,
			IntelligenceButton,
			AgilityButton,
			PortraitPictureBox,
			ExpBar,
			HPBar,
			MPBar,
			CharacterStatsMainStatsControlAdded,
		};

		//Atualizar as posições dos controles
		void PositionUpdate();

		//Verificar se precisa habilitar ou desabilitar os botões dos atributos
		void AttributeButtonsUpdate();

		//Evento do botão para aumentar o atributo força
		void AddStrengthOnClick(const GPL::Control& control);

		//Evento do botão para aumentar o atributo inteligência
		void AddIntelligenceOnClick(const GPL::Control& control);

		//Evento do botão para aumentar o atributo agilidade
		void AddAgilityOnClick(const GPL::Control& control);

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		CharacterStatsMainStats(const GPL::Point2D<float>& position,const size_t size);
	};
}

#endif
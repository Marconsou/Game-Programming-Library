#ifndef CHARACTERSTATS_H
#define CHARACTERSTATS_H

#include "CharacterStatsMainStats.h"
#include "CharacterStatsElementalProperties.h"
#include "CharacterStatsStatusProperties.h"
#include "CharacterStatsNaturalProperties.h"
#include "CharacterStatsGeneralAbilities.h"

namespace RPG
{
	class CharacterStats : public Menu
	{
	private:
		//IDs dos controles do Character Stats
		enum CharacterMenuControlID
		{
			PreviousPageButton = 0,
			NextPageButton,
			CharacterStatsControlMax,
		};

		//Refer�ncia da posi��o do Menu
		const GPL::Point2D<float>& position;

		//Quantidade e controle de p�ginas
		GPL::Quantity page_quantity;

		//Atualizar as posi��es dos controles
		void PositionUpdate();

		//Atualizar todos os controles espec�ficos da p�gina atual
		void PageControlsUpdate();

		//Evento do bot�o Previous Page
		void PreviousPageOnClick(const GPL::Control& control);

		//Evento do bot�o Next Page
		void NextPageOnClick(const GPL::Control& control);

		//Atualizar dados e a l�gica de todo o conte�do
		virtual void Update();
	public:
		//Construtor
		CharacterStats(const GPL::Point2D<float>& position);
	};
}

#endif
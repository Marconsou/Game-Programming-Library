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

		//Referência da posição do Menu
		const GPL::Point2D<float>& position;

		//Quantidade e controle de páginas
		GPL::Quantity page_quantity;

		//Atualizar as posições dos controles
		void PositionUpdate();

		//Atualizar todos os controles específicos da página atual
		void PageControlsUpdate();

		//Evento do botão Previous Page
		void PreviousPageOnClick(const GPL::Control& control);

		//Evento do botão Next Page
		void NextPageOnClick(const GPL::Control& control);

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		CharacterStats(const GPL::Point2D<float>& position);
	};
}

#endif
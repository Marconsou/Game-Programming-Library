#ifndef CHARACTERSTATSSTATUSPROPERTIES_H
#define CHARACTERSTATSSTATUSPROPERTIES_H

#include "CharacterStatsPage.h"

namespace RPG
{
	class CharacterStatsStatusProperties : public CharacterStatsPage
	{
	private:
		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		CharacterStatsStatusProperties(const GPL::Point2D<float>& position,const size_t size);
	};
}

#endif
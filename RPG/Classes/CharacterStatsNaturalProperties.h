#ifndef CHARACTERSTATSNATURALPROPERTIES_H
#define CHARACTERSTATSNATURALPROPERTIES_H

#include "CharacterStatsPage.h"

namespace RPG
{
	class CharacterStatsNaturalProperties : public CharacterStatsPage
	{
	private:
		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		CharacterStatsNaturalProperties(const GPL::Point2D<float>& position,const size_t size);
	};
}

#endif
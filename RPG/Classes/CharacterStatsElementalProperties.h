#ifndef CHARACTERSTATSELEMENTALPROPERTIES_H
#define CHARACTERSTATSELEMENTALPROPERTIES_H

#include "CharacterStatsPage.h"

namespace RPG
{
	class CharacterStatsElementalProperties : public CharacterStatsPage
	{
	private:
		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		CharacterStatsElementalProperties(const GPL::Point2D<float>& position,const size_t size);
	};
}

#endif
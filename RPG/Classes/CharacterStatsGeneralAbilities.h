#ifndef CHARACTERSTATSGENERALABILITIES_H
#define CHARACTERSTATSGENERALABILITIES_H

#include "CharacterStatsPage.h"

namespace RPG
{
	class CharacterStatsGeneralAbilities : public CharacterStatsPage
	{
	private:
		using PointerGetBool = bool (Ability::*)() const;

		//Pointeiro de m�todo para todos os valores para habilidades
		std::vector<PointerGetBool> pointers_get_bool;

		//Atualizar dados e a l�gica de todo o conte�do
		virtual void Update();
	public:
		//Construtor
		CharacterStatsGeneralAbilities(const GPL::Point2D<float>& position,const size_t size);
	};
}

#endif
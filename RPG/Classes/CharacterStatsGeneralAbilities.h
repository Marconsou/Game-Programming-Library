#ifndef CHARACTERSTATSGENERALABILITIES_H
#define CHARACTERSTATSGENERALABILITIES_H

#include "CharacterStatsPage.h"

namespace RPG
{
	class CharacterStatsGeneralAbilities : public CharacterStatsPage
	{
	private:
		using PointerGetBool = bool (Ability::*)() const;

		//Pointeiro de método para todos os valores para habilidades
		std::vector<PointerGetBool> pointers_get_bool;

		//Atualizar dados e a lógica de todo o conteúdo
		virtual void Update();
	public:
		//Construtor
		CharacterStatsGeneralAbilities(const GPL::Point2D<float>& position,const size_t size);
	};
}

#endif
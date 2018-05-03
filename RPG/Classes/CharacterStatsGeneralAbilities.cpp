#include "CharacterStatsGeneralAbilities.h"

using namespace GPL;
using namespace RPG;

CharacterStatsGeneralAbilities::CharacterStatsGeneralAbilities(const Point2D<float>& position,const size_t size) :
	CharacterStatsPage(position,size),
	pointers_get_bool(size - 1)
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	int index = 1;
	for (int i = 0; i <= DragonSlayerDescriptionTextID - AnalyzerDescriptionTextID; i++)
		this->NewToolTipTextLine(index,game.GetDatabase().GetLanguageText(static_cast<LanguageTextID>(AnalyzerDescriptionTextID + i)));

	//Abilities
	this->pointers_get_bool[0] = &Ability::GetAnalyzer;
	this->pointers_get_bool[1] = &Ability::GetTrainer;
	this->pointers_get_bool[2] = &Ability::GetBounty;
	this->pointers_get_bool[3] = &Ability::GetCustomer;
	this->pointers_get_bool[4] = &Ability::GetCoward;
	this->pointers_get_bool[5] = &Ability::GetBrave;
	this->pointers_get_bool[6] = &Ability::GetRunner;
	this->pointers_get_bool[7] = &Ability::GetSkinSlicer;
	this->pointers_get_bool[8] = &Ability::GetBoneCrusher;
	this->pointers_get_bool[9] = &Ability::GetShellDriller;
	this->pointers_get_bool[10] = &Ability::GetHumanEater;
	this->pointers_get_bool[11] = &Ability::GetBeastKiller;
	this->pointers_get_bool[12] = &Ability::GetUndeadPurifier;
	this->pointers_get_bool[13] = &Ability::GetDemonHunter;
	this->pointers_get_bool[14] = &Ability::GetDragonSlayer;
}

void CharacterStatsGeneralAbilities::Update()
{
	GameRPG& game = GameState::GetGame<GameRPG>();

	const Ability& ability = game.GetHero().GetAbility();
	const Database& database = game.GetDatabase();

	//Remover todos os Labels das habilidades para logo em seguida ir adicionando somente os necessários
	this->ControlsUpdate(false);

	float y = this->GetY();
	const float x = this->GetX();
	int index = 0;

	this->AddStatsLabelControl(index);
	this->SetStatsLabel(index,x,y,database.GetLanguageText(GeneralAbilitiesTextID),Color::Green,true);

	//Abilities
	for (size_t i = 0; i < this->pointers_get_bool.size(); i++)
	{
		if ((ability.*this->pointers_get_bool[i])())
		{
			this->AddStatsLabelControl(index);	
			this->SetStatsLabel(index,x,y,database.GetLanguageText(static_cast<LanguageTextID>(AnalyzerTextID + i))); 
		}
		else
			index++;
	}
}
#include "Warrior.h"

using namespace std;
using namespace RPG;

Warrior::Warrior(const vector<vector<SkillLevel>>& skill_levels) :
	Hero(3,1,75,15,5,20,2,10,true)
{
	//Skills
	int index = 0;
	this->GetSkills()[index] = make_unique<SkillNatural>(skill_levels[index]);
	index++;
}

HeroClass Warrior::GetClassType() const
{
	return HeroClassWarrior;
}

void Warrior::UniqueStatsUpdate()
{

}
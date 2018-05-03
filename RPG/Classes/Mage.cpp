#include "Mage.h"

using namespace std;
using namespace RPG;

Mage::Mage(const vector<vector<SkillLevel>>& skill_levels) :
	Hero(2,3,60,20,10,15,2,4,false)
{
	//Skills
	this->GetSkills().clear();
}

HeroClass Mage::GetClassType() const
{
	return HeroClassMage;
}

void Mage::UniqueStatsUpdate()
{

}
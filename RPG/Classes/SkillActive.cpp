#include "SkillActive.h"

using namespace std;
using namespace RPG;

SkillActive::SkillActive(const vector<SkillLevel>& skill_levels,const int required_level,const int level) :
	Skill(skill_levels,required_level,level),
	single_target(true)
{

}

void SkillActive::SetSingleTarget(const bool single_target)
{
	this->single_target = single_target;
}

bool SkillActive::GetSingleTarget() const
{
	return this->single_target;
}

SKillClass SkillActive::GetClassType() const
{
	return SKillClassActive;
}
#include "SkillNatural.h"

using namespace std;
using namespace RPG;

SkillNatural::SkillNatural(const vector<SkillLevel>& skill_levels,const int required_level,const int level) :
	Skill(skill_levels,required_level,level)
{

}

SKillClass SkillNatural::GetClassType() const
{
	return SKillClassNatural;
}
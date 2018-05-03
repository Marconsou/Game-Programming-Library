#include "Skill.h"

using namespace std;
using namespace RPG;

Skill::Skill(const vector<SkillLevel>& skill_levels,const int required_level,const int level) :
	level(level),
	required_level(required_level),
	current_skill_level(nullptr),
	next_skill_level(&skill_levels[0])
{

}

int Skill::GetLevel() const
{
	return this->level;
}

int Skill::GetRequiredLevel() const
{
	return this->required_level;
}

const SkillLevel& Skill::GetCurrentSkillLevel() const
{
	return *this->current_skill_level;
}

const SkillLevel& Skill::GetNextSkillLevel() const
{
	return *this->next_skill_level;
}

bool Skill::SkillLearned() const
{
	return (this->level != 0);
}

bool Skill::SkillIsLevelMax() const
{
	return (this->level == 10);
}

void Skill::LevelUp(const vector<SkillLevel>& skill_levels,const int level)
{
	this->level += level;
	if (!this->SkillIsLevelMax())
		this->required_level += level;

	this->current_skill_level = &skill_levels[this->level - 1];
	this->next_skill_level = &skill_levels[min(this->level,static_cast<int>(skill_levels.size()) - 1)];
}

bool Skill::IsNatural() const
{
	return this->GetClassType() == SKillClassNatural;
}

bool Skill::IsActive() const
{
	return this->GetClassType() == SKillClassActive;
}
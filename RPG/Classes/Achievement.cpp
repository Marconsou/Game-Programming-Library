#include "Achievement.h"

using namespace std;
using namespace RPG;

Achievement::Achievement() :
	unlocked(false)
{

}

void Achievement::SetUnlocked(const bool unlocked)
{
	this->unlocked = unlocked;
}

bool Achievement::GetUnlocked() const
{
	return this->unlocked;
}

vector<int>& Achievement::GetValues()
{
	return this->values;
}
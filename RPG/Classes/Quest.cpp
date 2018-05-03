#include "Quest.h"

using namespace std;
using namespace RPG;

Quest::Quest() :
	quest_state(QuestStateUnknown)
{

}

void Quest::SetQuestState(const QuestState quest_state)
{
	this->quest_state = quest_state;
}

QuestState Quest::GetQuestState() const
{
	return this->quest_state;
}

vector<int>& Quest::GetValues()
{
	return this->values;
}

bool Quest::IsUnknown() const
{
	return (this->quest_state == QuestStateUnknown);
}

bool Quest::IsStarted() const
{
	return (this->quest_state == QuestStateStarted);
}

bool Quest::IsCompleted() const
{
	return (this->quest_state == QuestStateCompleted);
}
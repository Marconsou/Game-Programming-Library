#ifndef QUEST_H
#define QUEST_H

#include <vector>

namespace RPG
{
	//Tipos de estado dos objetivos
	enum QuestState
	{
		QuestStateUnknown = 0,
		QuestStateStarted,
		QuestStateCompleted,
	};

	//ID dos objetivos principais
	enum MainQuestID
	{
		MainQuest0 = 0,
		MainQuestMax,
	};

	//ID dos objetivos opcionais
	enum OptionalQuestID
	{
		OptionalQuest0 = 0,
		OptionalQuestMax,
	};

	class Quest
	{
	private:
		//Estado atual da Quest
		QuestState quest_state;

		//Valores livres que podem ser usados na construção de uma Quest
		std::vector<int> values;
	public:
		//Construtor
		Quest();

		//Alterar Quest State
		void SetQuestState(const QuestState quest_state);

		//Pegar Quest State
		QuestState GetQuestState() const;

		//Pegar Values
		std::vector<int>& GetValues();

		//Quest desconhecida
		bool IsUnknown() const;

		//Quest iniciada
		bool IsStarted() const;

		//Quest completada
		bool IsCompleted() const;
	};
}

#endif
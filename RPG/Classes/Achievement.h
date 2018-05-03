#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <vector>

namespace RPG
{
	//ID das conquistas
	enum AchievementID
	{
		Skillful = 0,
		AchievementMax,
	};

	class Achievement
	{
	private:
		//Conquista desbloqueada
		bool unlocked;

		//Valores livres que podem ser usados para auxiliar a conquista
		std::vector<int> values;
	public:
		//Construtor
		Achievement();

		//Alterar Unlocked
		void SetUnlocked(const bool unlocked);

		//Pegar Unlocked
		bool GetUnlocked() const;

		//Pegar Values
		std::vector<int>& GetValues();
	};
}

#endif
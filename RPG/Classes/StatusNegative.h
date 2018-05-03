#ifndef STATUSNEGATIVE_H
#define STATUSNEGATIVE_H

namespace RPG
{
	class StatusNegative
	{
	private:
		//Ferimento
		int wound;

		//Lentidão
		int slowness;

		//Cansaço
		int tiredness;

		//Enxaqueca
		int headache;

		//Cegueira
		int blindness;
	public:
		//Construtor
		StatusNegative();

		//Alterar Wound
		void SetWound(const int wound);

		//Pegar Wound
		int GetWound() const;

		//Alterar Slowness
		void SetSlowness(const int slowness);

		//Pegar Slowness
		int GetSlowness() const;

		//Alterar Tiredness
		void SetTiredness(const int tiredness);

		//Pegar Tiredness
		int GetTiredness() const;

		//Alterar Headache
		void SetHeadache(const int headache);

		//Pegar Headache
		int GetHeadache() const;

		//Alterar Blindness
		void SetBlindness(const int blindness);

		//Pegar Blindness
		int GetBlindness() const;
	};
}

#endif
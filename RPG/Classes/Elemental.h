#ifndef ELEMENTAL_H
#define ELEMENTAL_H

namespace RPG
{
	class Elemental
	{
	private:
		//Fogo
		int fire;

		//Gelo
		int ice;

		//Raio
		int lightning;

		//Luz
		int light;

		//Trevas
		int dark;
	public:
		//Construtor
		Elemental();

		//Alterar Fire
		void SetFire(const int fire);

		//Pegar Fire
		int GetFire() const;

		//Alterar Ice
		void SetIce(const int ice);

		//Pegar Ice
		int GetIce() const;

		//Alterar Lightning
		void SetLightning(const int lightning);

		//Pegar Lightning
		int GetLightning() const;

		//Alterar Light
		void SetLight(const int light);

		//Pegar Light
		int GetLight() const;

		//Alterar Dark
		void SetDark(const int dark);

		//Pegar Dark
		int GetDark() const;
	};
}

#endif
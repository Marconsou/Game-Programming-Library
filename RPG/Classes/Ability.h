#ifndef ABILITY_H
#define ABILITY_H

namespace RPG
{
	class Ability
	{
	private:
		//Ver barra de ação dos inimigos e itens não identificados em batalha
		bool analyzer;

		//Ganhar mais experiência ao derrotar inimigos
		bool trainer;

		//Ganhar mais dinheiro ao derrotar inimigos
		bool bounty;

		//Desconto na compra de itens
		bool customer;

		//Diminuir a chance de batalha
		bool coward;

		//Aumentar a chance de batalha
		bool brave;

		//Aumentar a velocidade do movimento fora da batalha
		bool runner;

		//Remover a penalidade de armas baseado em Cut para causar dano completo no alvo
		bool skin_slicer;

		//Remover a penalidade de armas baseado em Smash para causar dano completo no alvo
		bool bone_crusher;

		//Remover a penalidade de armas baseado em Pierce para causar dano completo no alvo
		bool shell_driller;

		//Aumentar o dano final contra inimigos do tipo Human
		bool human_eater;

		//Aumentar o dano final contra inimigos do tipo Beast
		bool beast_killer;

		//Aumentar o dano final contra inimigos do tipo Undead
		bool undead_purifier;

		//Aumentar o dano final contra inimigos do tipo Demon
		bool demon_hunter;

		//Aumentar o dano final contra inimigos do tipo Dragon
		bool dragon_slayer;
	public:
		//Construtor
		Ability();

		//Alterar Analyzer
		void SetAnalyzer(const bool analyzer);

		//Pegar Analyzer
		bool GetAnalyzer() const;

		//Alterar Trainer
		void SetTrainer(const bool trainer);

		//Pegar Trainer
		bool GetTrainer() const;

		//Alterar Bounty
		void SetBounty(const bool bounty);

		//Pegar Bounty
		bool GetBounty() const;

		//Alterar Customer
		void SetCustomer(const bool customer);

		//Pegar Customer
		bool GetCustomer() const;

		//Alterar Coward
		void SetCoward(const bool coward);

		//Pegar Coward
		bool GetCoward() const;

		//Alterar Brave
		void SetBrave(const bool brave);

		//Pegar Brave
		bool GetBrave() const;

		//Alterar Runner
		void SetRunner(const bool runner);

		//Pegar Runner
		bool GetRunner() const;

		//Alterar Skin Slicer
		void SetSkinSlicer(const bool skin_slicer);

		//Pegar Skin Slicer
		bool GetSkinSlicer() const;

		//Alterar Bone Crusher
		void SetBoneCrusher(const bool bone_crusher);

		//Pegar Bone Crusher
		bool GetBoneCrusher() const;

		//Alterar Shell Driller
		void SetShellDriller(const bool shell_driller);

		//Pegar Shell Driller
		bool GetShellDriller() const;

		//Alterar Human Eater
		void SetHumanEater(const bool human_eater);

		//Pegar Human Eater
		bool GetHumanEater() const;

		//Alterar Beast Killer
		void SetBeastKiller(const bool beast_killer);

		//Pegar Beast Killer
		bool GetBeastKiller() const;

		//Alterar Undead Purifier
		void SetUndeadPurifier(const bool undead_purifier);

		//Pegar Undead Purifier
		bool GetUndeadPurifier() const;

		//Alterar Demon Hunter
		void SetDemonHunter(const bool demon_hunter);

		//Pegar Demon Hunter
		bool GetDemonHunter() const;

		//Alterar Dragon Slayer
		void SetDragonSlayer(const bool dragon_slayer);

		//Pegar Dragon Slayer
		bool GetDragonSlayer() const;
	};
}

#endif
#include "Ability.h"

using namespace RPG;

Ability::Ability() :
	analyzer(false),
	trainer(false),
	bounty(false),
	customer(false),
	coward(false),
	brave(false),
	runner(false),
	skin_slicer(false),
	bone_crusher(false),
	shell_driller(false),
	human_eater(false),
	beast_killer(false),
	undead_purifier(false),
	demon_hunter(false),
	dragon_slayer(false)
{

}

void Ability::SetAnalyzer(const bool analyzer)
{
	this->analyzer = analyzer;
}

bool Ability::GetAnalyzer() const
{
	return this->analyzer;
}

void Ability::SetTrainer(const bool trainer)
{
	this->trainer = trainer;
}

bool Ability::GetTrainer() const
{
	return this->trainer;
}

void Ability::SetBounty(const bool bounty)
{
	this->bounty = bounty;
}

bool Ability::GetBounty() const
{
	return this->bounty;
}

void Ability::SetCustomer(const bool customer)
{
	this->customer = customer;
}

bool Ability::GetCustomer() const
{
	return this->customer;
}

void Ability::SetCoward(const bool coward)
{
	this->coward = coward;
}

bool Ability::GetCoward() const
{
	return this->coward;
}

void Ability::SetBrave(const bool brave)
{
	this->brave = brave;
}

bool Ability::GetBrave() const
{
	return this->brave;
}

void Ability::SetRunner(const bool runner)
{
	this->runner = runner;
}

bool Ability::GetRunner() const
{
	return this->runner;
}

void Ability::SetSkinSlicer(const bool skin_slicer)
{
	this->skin_slicer = skin_slicer;
}

bool Ability::GetSkinSlicer() const
{
	return this->skin_slicer;
}

void Ability::SetBoneCrusher(const bool bone_crusher)
{
	this->bone_crusher = bone_crusher;
}

bool Ability::GetBoneCrusher() const
{
	return this->bone_crusher;
}

void Ability::SetShellDriller(const bool shell_driller)
{
	this->shell_driller = shell_driller;
}

bool Ability::GetShellDriller() const
{
	return this->shell_driller;
}

void Ability::SetHumanEater(const bool human_eater)
{
	this->human_eater = human_eater;
}

bool Ability::GetHumanEater() const
{
	return this->human_eater;
}

void Ability::SetBeastKiller(const bool beast_killer)
{
	this->beast_killer = beast_killer;
}

bool Ability::GetBeastKiller() const
{
	return this->beast_killer;
}

void Ability::SetUndeadPurifier(const bool undead_purifier)
{
	this->undead_purifier = undead_purifier;
}

bool Ability::GetUndeadPurifier() const
{
	return this->undead_purifier;
}

void Ability::SetDemonHunter(const bool demon_hunter)
{
	this->demon_hunter = demon_hunter;
}

bool Ability::GetDemonHunter() const
{
	return this->demon_hunter;
}

void Ability::SetDragonSlayer(const bool dragon_slayer)
{
	this->dragon_slayer = dragon_slayer;
}

bool Ability::GetDragonSlayer() const
{
	return this->dragon_slayer;
}
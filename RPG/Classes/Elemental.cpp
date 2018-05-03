#include "Elemental.h"

using namespace RPG;

Elemental::Elemental() :
	fire(0),
	ice(0),
	lightning(0),
	light(0),
	dark(0)
{
}

void Elemental::SetFire(const int fire)
{
	this->fire = fire;
}

int Elemental::GetFire() const
{
	return this->fire;
}

void Elemental::SetIce(const int ice)
{
	this->ice = ice;
}

int Elemental::GetIce() const
{
	return this->ice;
}

void Elemental::SetLightning(const int lightning)
{
	this->lightning = lightning;
}

int Elemental::GetLightning() const
{
	return this->lightning;
}

void Elemental::SetLight(const int light)
{
	this->light = light;
}

int Elemental::GetLight() const
{
	return this->light;
}

void Elemental::SetDark(const int dark)
{
	this->dark = dark;
}

int Elemental::GetDark() const
{
	return this->dark;
}
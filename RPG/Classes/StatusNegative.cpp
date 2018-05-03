#include "StatusNegative.h"

using namespace RPG;

StatusNegative::StatusNegative() :
	wound(0),
	slowness(0),
	tiredness(0),
	headache(0),
	blindness(0)
{
}

void StatusNegative::SetWound(const int wound)
{
	this->wound = wound;
}

int StatusNegative::GetWound() const
{
	return this->wound;
}

void StatusNegative::SetSlowness(const int slowness)
{
	this->slowness = slowness;
}

int StatusNegative::GetSlowness() const
{
	return this->slowness;
}

void StatusNegative::SetTiredness(const int tiredness)
{
	this->tiredness = tiredness;
}

int StatusNegative::GetTiredness() const
{
	return this->tiredness;
}

void StatusNegative::SetHeadache(const int headache)
{
	this->headache = headache;
}

int StatusNegative::GetHeadache() const
{
	return this->headache;
}

void StatusNegative::SetBlindness(const int blindness)
{
	this->blindness = blindness;
}

int StatusNegative::GetBlindness() const
{
	return this->blindness;
}
#include "Quantity.h"

using namespace GPL;

Quantity::Quantity(const int current,const int total,const bool loop) :
current(current),
total(total),
loop(loop)
{
}

void Quantity::SetCurrent(const int current)
{
	this->current = current;
}

int Quantity::GetCurrent() const
{
	return this->current;
}

void Quantity::SetTotal(const int total)
{
	this->total = total;
}

int Quantity::GetTotal() const
{
	return this->total;
}

void Quantity::SetLoop(const bool loop)
{
	this->loop = loop;
}

void Quantity::Previous()
{
	if (!this->IsAtTheBeginning())
		this->current--;
	else
	{
		if (this->loop)
			this->End();
	}
}

void Quantity::Next()
{
	if (!this->IsAtTheEnd())
		this->current++;
	else
	{
		if (this->loop)
			this->Begin();
	}
}

void Quantity::Begin()
{
	this->current = 0;
}

void Quantity::End()
{
	this->current = this->total - 1;
}

bool Quantity::IsAtTheBeginning() const
{
	return (this->current == 0);
}

bool Quantity::IsAtTheEnd() const
{
	return (this->current >= this->total - 1);
}
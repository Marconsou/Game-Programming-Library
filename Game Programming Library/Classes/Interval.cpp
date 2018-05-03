#include "Interval.h"

using namespace GPL;

Interval::Interval(const float interval) :
interval(interval)
{
}

Interval::Interval(const float interval,const Timer& timer) :
Interval(interval)
{
	this->Synchronize(timer);
}

void Interval::SetInterval(const float interval)
{
	this->interval = interval;
}

float Interval::GetInterval() const
{
	return this->interval;
}

void Interval::Synchronize(const Timer& timer)
{
	this->time = this->interval + timer.CurrentTime();
}

bool Interval::Action(const Timer& timer)
{
	//Hora da ação
	if (this->time < timer.CurrentTime())
	{
		//Atualizar o tempo auxiliar
		this->Synchronize(timer);
		return true;
	}
	return false;
}
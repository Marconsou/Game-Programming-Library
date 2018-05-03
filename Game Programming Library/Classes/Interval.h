#ifndef INTERVAL_H
#define INTERVAL_H

#include "Timer.h"

namespace GPL
{
	class Interval
	{
	public:
		GPL_DLL explicit Interval(const float interval = 0.0f);
		GPL_DLL Interval(const float interval,const Timer& timer);
		GPL_DLL void SetInterval(const float interval);
		GPL_DLL float GetInterval() const;
		GPL_DLL void Synchronize(const Timer& timer);
		GPL_DLL bool Action(const Timer& timer);
	private:
		float interval{};
		float time{};
		Interval(const Interval&) = delete;
		Interval& operator=(const Interval&) = delete;
	};
}

#endif
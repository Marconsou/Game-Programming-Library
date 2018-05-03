#ifndef TIMER_H
#define TIMER_H

#include <algorithm>
#include <vector>
#include <chrono>
#include "BuildDLL.h"

namespace GPL
{
	class Timer
	{
	public:
		GPL_DLL Timer();
		GPL_DLL void SetStartTime(const float start_time);
		GPL_DLL bool GetPause() const;
		GPL_DLL float CurrentTime() const;
		GPL_DLL int CurrentTimeAsMilliseconds() const;
		GPL_DLL void Pause(const bool pause);
		GPL_DLL static void AddSubTimer(Timer& sub_timer);
		GPL_DLL static void RemoveSubTimer(Timer& sub_timer);
		GPL_DLL static float FPS(const float update_time = 0.5f);
	private:
		float start_time{};
		float pause_time{};
		bool pause{};
		static const std::chrono::high_resolution_clock::time_point real_start;
		static std::vector<Timer*> sub_timers;
		Timer(const Timer&) = delete;
		Timer& operator=(const Timer&) = delete;
		static float RealTime();
	};
}

#endif
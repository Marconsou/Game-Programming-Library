#ifndef COLORCHANGER_H
#define COLORCHANGER_H

#include "Color.h"
#include "Interval.h"

namespace GPL
{
	class ColorChanger
	{
	public:
		GPL_DLL ColorChanger() = default;
		GPL_DLL ColorChanger(const Color& begin_color,const Color& end_color,const float interval,const float total_time);
		GPL_DLL void SetColorChanger(const Timer& timer,const Color& begin_color,const Color& end_color,const float interval,const float total_time);
		GPL_DLL const Color& RunColorChanger(const Timer& timer);
	private:
		Color change_color;
		Color begin_color;
		Color end_color;
		Interval interval;
		float total_time{};
		float interval_elapsed{};
		bool run_begin_to_end_color{true};
		ColorChanger(const ColorChanger&) = delete;
		ColorChanger& operator=(const ColorChanger&) = delete;
	};
}

#endif
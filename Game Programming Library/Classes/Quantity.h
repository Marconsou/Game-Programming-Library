#ifndef QUANTITY_H
#define QUANTITY_H

#include "BuildDLL.h"

namespace GPL
{
	class Quantity
	{
	public:
		GPL_DLL Quantity(const int current = 0,const int total = 1,const bool loop = true);
		GPL_DLL void SetCurrent(const int current);
		GPL_DLL int GetCurrent() const;
		GPL_DLL void SetTotal(const int total);
		GPL_DLL int GetTotal() const;
		GPL_DLL void SetLoop(const bool loop);
		GPL_DLL void Previous();
		GPL_DLL void Next();
		GPL_DLL void Begin();
		GPL_DLL void End();
		GPL_DLL bool IsAtTheBeginning() const;
		GPL_DLL bool IsAtTheEnd() const;
	private:
		int current{};
		int total{};
		bool loop{};
	};
}

#endif
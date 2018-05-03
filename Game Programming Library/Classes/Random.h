#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include "BuildDLL.h"

namespace GPL
{
	class Random
	{
	public:
		GPL_DLL static int GenerateNumber(const int min,const int max);
	private:
		Random() = delete;
	};
}

#endif
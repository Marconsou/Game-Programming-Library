#ifndef CONVERT_H
#define CONVERT_H

#include <string>
#include "BuildDLL.h"

namespace GPL
{
	class Convert
	{
	public:
		GPL_DLL static std::string NumberToString(const int value);
		GPL_DLL static std::string NumberToString(const float value);
		GPL_DLL static int StringToNumber(const std::string& value);
	private:
		Convert() = delete;
	};
}

#endif
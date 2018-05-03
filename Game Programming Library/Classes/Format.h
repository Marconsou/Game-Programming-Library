#ifndef FORMAT_H
#define FORMAT_H

#include <sstream>
#include <regex>
#include "BuildDLL.h"

namespace GPL
{
	class Format
	{
	public:
		GPL_DLL static void Split(std::vector<std::string>& string_parts,const std::string& base_string);
		GPL_DLL static void Split(std::vector<std::string>& string_parts,const std::string& base_string,const std::string& delimiter);
	private:
		Format() = delete;
	};
}

#endif
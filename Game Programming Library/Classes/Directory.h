#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <filesystem>
#include "BuildDLL.h"

namespace GPL
{
	class Directory
	{
	public:
		GPL_DLL static void NewDirectory(const std::string& directory);
		GPL_DLL static void DeleteDirectory(const std::string& directory);
		GPL_DLL static bool CheckDirectory(const std::string& directory);
	private:
		Directory() = delete;
	};
}

#endif
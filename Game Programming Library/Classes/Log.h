#ifndef LOG_H
#define LOG_H

#include <time.h>
#include <fstream>
#include "BuildDLL.h"

namespace GPL
{
	class Log
	{
	public:
		static void Warning(const std::string& message);
		static void Warning(const std::string& function_macro,const std::string& sub_method_name,const std::string& additional = "");
		static void Error(const std::string& message);
		GPL_DLL static void Error(const std::string& function_macro,const std::string& sub_method_name,const std::string& additional = "");
	private:
		Log() = delete;
		static std::string CurrentDateTime();
		static void Write(const std::string& type,const std::string& message);
	};
}

#endif
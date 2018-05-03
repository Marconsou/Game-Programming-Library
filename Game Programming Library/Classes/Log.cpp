#include "Log.h"

using namespace std;
using namespace GPL;

string Log::CurrentDateTime()
{
	time_t now = time(nullptr);
	string date_time(ctime(&now));

	//Remover a quebra de linha
	date_time.pop_back();

	return date_time;
}

void Log::Write(const string& type,const string& message)
{
	ofstream log("Log.txt",ofstream::out | ofstream::app);
	if (log.is_open())
	{
		const string& space = " ";
		log << Log::CurrentDateTime().c_str() << space.c_str() << type.c_str() << space.c_str() << message.c_str() << endl;
		log.close();
	}
}

void Log::Warning(const string& message)
{
	Log::Write("[WARNING]",message);
}

void Log::Warning(const string& function_macro,const string& sub_method_name,const string& additional)
{
	Log::Warning(function_macro + ">>" + sub_method_name + additional);
}

void Log::Error(const string& message)
{
	Log::Write("[ERROR]",message);
	exit(EXIT_FAILURE);
}

void Log::Error(const string& function_macro,const string& sub_method_name,const string& additional)
{
	Log::Error(function_macro + ">>" + sub_method_name + additional);
}
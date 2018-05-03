#include "Convert.h"

using namespace std;
using namespace GPL;

string Convert::NumberToString(const int value)
{
	static char buffer[16];
	return string(buffer,sprintf(buffer,"%i",value));
}

string Convert::NumberToString(const float value)
{
	static char buffer[16];
	return string(buffer,sprintf(buffer,"%.2f",value));
}

int Convert::StringToNumber(const string& value)
{
	return atoi(value.c_str());
}
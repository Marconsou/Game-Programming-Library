#include "Directory.h"

using namespace std;
using namespace std::tr2::sys;
using namespace GPL;

void Directory::NewDirectory(const string& directory)
{
	create_directory(path(directory));
}

void Directory::DeleteDirectory(const string& directory)
{
	remove_all(path(directory));
}

bool Directory::CheckDirectory(const string& directory)
{
	return is_directory(path(directory));
}
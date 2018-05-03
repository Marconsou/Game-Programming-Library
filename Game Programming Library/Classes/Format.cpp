#include "Format.h"

using namespace std;
using namespace GPL;

void Format::Split(vector<string>& string_parts,const string& base_string)
{
	string_parts.clear();
	copy(istream_iterator<string>(istringstream(base_string)),istream_iterator<string>(),back_inserter<vector<string>>(string_parts));
}

void Format::Split(vector<string>& string_parts,const string& base_string,const string& delimiter)
{
	string_parts.clear();
	copy(sregex_token_iterator(base_string.begin(),base_string.end(),regex(delimiter),-1),sregex_token_iterator(),back_inserter<vector<string>>(string_parts));
}
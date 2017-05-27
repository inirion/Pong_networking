#include "Helpers.h"

char * Helpers::immutableStringToCharPtr(const std::string &str)
{
	char * tmp = new char[str.size() + 1];
	std::copy(str.begin(), str.end(), tmp);
	tmp[str.size()] = '\0';
	return tmp;
}

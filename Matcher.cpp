
#include <string>
#include <stdexcept>
#include <regex.h>

#include "Matcher.h"

using namespace std;

Matcher::Matcher(const string& expression)
{
	if (regcomp(&_re, expression.c_str(), REG_NOSUB|REG_EXTENDED) != 0)
	{
		throw runtime_error("internal error during regcomp()");
	}
}

Matcher::~Matcher()
{
	regfree(&_re);
}

bool Matcher::match(const string& value)
{
	return (regexec(&_re, value.c_str(), 0, NULL, 0) == 0);
}


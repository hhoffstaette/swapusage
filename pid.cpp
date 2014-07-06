
#include <string>
#include <stdexcept>
#include <regex.h>

#include "pid.h"

using namespace std;

static const char* PID_REGEXP = "^[0-9]+$";

class Matcher
{
private:
	regex_t _re;

public:
	Matcher()
	{
		if (regcomp(&_re, PID_REGEXP, REG_NOSUB|REG_EXTENDED) != 0)
		{
			throw runtime_error("internal error during regcomp()");
		}
	}

	~Matcher()
	{
		regfree(&_re);
	}

	bool match(const string& value)
	{
		return (regexec(&_re, value.c_str(), 0, NULL, 0) == 0);
	}
};

static Matcher _matcher;

pid_t to_pid(const string& value)
{
	return _matcher.match(value) ? stoi(value) : UNKNOWN_PID;
}


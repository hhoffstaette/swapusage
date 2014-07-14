
#include <stdexcept>
#include <string>
#include <regex.h>

#include "pid.h"

using namespace std;

class Matcher
{
private:
	regex_t _re;

public:
	Matcher(const std::string& expression)
	{
		if (regcomp(&_re, expression.c_str(), REG_NOSUB|REG_EXTENDED) != 0)
		{
			throw runtime_error("internal error during regcomp()");
		}
	}

	Matcher(const Matcher& other) = delete;
	Matcher& operator = (const Matcher& other) = delete;

	~Matcher()
	{
		regfree(&_re);
	}

	bool match(const std::string& value)
	{
		return (regexec(&_re, value.c_str(), 0, NULL, 0) == 0);
	}
};

static Matcher is_pid("^[0-9]+$");

pid_t to_pid(const string& value)
{
	return is_pid.match(value) ? stoi(value) : UNKNOWN_PID;
}


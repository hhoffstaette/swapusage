
#include <string>

#include "Matcher.h"
#include "pid.h"

using namespace std;

static Matcher _matcher("^[0-9]+$");

pid_t to_pid(const string& value)
{
	return _matcher.match(value) ? stoi(value) : UNKNOWN_PID;
}


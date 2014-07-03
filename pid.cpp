
#include <regex>
#include <string>

#include "pid.h"

using namespace std;

// for matching /proc/<pid> entries
static const regex is_number("\\d+");

pid_t to_pid(const string& value)
{
	return regex_match(value, is_number) ? stoi(value) : UNKNOWN_PID;
}


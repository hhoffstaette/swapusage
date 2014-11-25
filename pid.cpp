
#include "pid.h"

#include <string>
#include <limits>

using namespace std;

const int UNKNOWN_PID = numeric_limits<pid_t>::max();

pid_t to_pid(const string& value)
{
	for (const char c: value)
	{
		if (!isdigit(c))
		{
			return UNKNOWN_PID;
		}
	}

	return stoi(value);
}


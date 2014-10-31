
#include <algorithm>
#include <cstring>
#include <string>

#include "pid.h"

using namespace std;

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


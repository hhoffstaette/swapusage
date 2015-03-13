
#include "pid.h"

#include <ctype.h>
#include <stdlib.h>
#include <limits>

using namespace std;

const int UNKNOWN_PID = numeric_limits<pid_t>::max();

pid_t to_pid(const char* value)
{
	for (const char* v = value; *v != '\0'; v++)
	{
		if (!isdigit(*v))
		{
			return UNKNOWN_PID;
		}
	}

	return atoi(value);
}


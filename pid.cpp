
#include <algorithm>
#include <cstring>
#include <string>

#include "pid.h"

using namespace std;

static auto is_digit = [](char c)
{
	return isdigit(c);
};

pid_t to_pid(const string& value)
{
	bool valid = all_of(value.cbegin(), value.cend(), is_digit);
	return valid ? stoi(value) : UNKNOWN_PID;
}


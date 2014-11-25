
#include "swap.h"
#include "substring.h"

#include <limits>
#include <stdio.h>

using namespace std;

const long UNKNOWN_SWAP = numeric_limits<long>::min();

static const string PREFIX = "Swap:";
static const string SUFFIX = " 0 kB";

static bool has_swap(const string& line)
{
	return (line.compare(0, PREFIX.length(), PREFIX) == 0)
	&& !(line.compare(line.length() - SUFFIX.length(), SUFFIX.length(), SUFFIX) == 0);
}

static long get_swap(const string& line)
{
	const string value = substring_at(line, " ", 1);
	long kb = 0;

	if (sscanf(value.c_str(), "%ld", &kb) == 1)
	{
		return kb;
	}

	return UNKNOWN_SWAP;
}

long get_swap_for_pid(pid_t pid)
{
	long swap = 0;

	const string input_name = "/proc/" + to_string(pid) + "/smaps";
	FILE* input = fopen(input_name.c_str(), "r");
	if (input != nullptr)
	{
		string line;
		char inputline[64];
		while (fgets(inputline, 63, input) != nullptr)
		{
			line = inputline;
			if (has_swap(line))
			{
				swap += get_swap(line);
			}
		}

		fclose(input);
	}

	// tricky: the proc entry is marked readable but really is not,
	// so we get EPERM only when trying to read.
	return (errno == 0 ? swap : UNKNOWN_SWAP);
}


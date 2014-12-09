
#include "swap.h"

#include <cstring>
#include <cstdio>
#include <limits>
#include <string>

using namespace std;

const long UNKNOWN_SWAP = numeric_limits<long>::min();

static const string PREFIX = "Swap:";
static const string SUFFIX = " 0 kB";

static bool has_swap(const char* line)
{
	return (strncmp(line, PREFIX.c_str(), PREFIX.length()) == 0) &&
	!(strncmp(line + (strlen(line) - SUFFIX.length()), SUFFIX.c_str(), SUFFIX.length()) == 0);
}

static long get_swap(const char* line)
{
	long kb = 0;

	if (sscanf(line + PREFIX.length(), "%ld", &kb) == 1)
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
		char line[64];
		while (fgets(line, 63, input) != nullptr)
		{
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


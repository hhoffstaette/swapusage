
#include "swap.h"

#include <cstring>
#include <cstdio>
#include <limits>
#include <string>

using namespace std;

const long UNKNOWN_SWAP = numeric_limits<long>::min();

static const string INPUT_NAME_FORMAT = "/proc/%u/smaps";
static const string SWAP_PREFIX = "Swap:";
static const string SWAP_SUFFIX = " 0 kB";

static bool has_swap(const char* line)
{
	// check prefix
	if (strncmp(line, SWAP_PREFIX.c_str(), SWAP_PREFIX.length()) == 0)
	{
		// check suffix
		const char* suffix = line + (strlen(line) - SWAP_SUFFIX.length());
		return (strncmp(suffix, SWAP_SUFFIX.c_str(), SWAP_SUFFIX.length()) != 0);
	}

	// no Swap
	return false;
}

static long get_swap(const char* line)
{
	long kb = UNKNOWN_SWAP;
	const char* swap_value = line + SWAP_PREFIX.length();

	sscanf(swap_value, "%ld", &kb);
	return kb;
}

long get_swap_for_pid(pid_t pid)
{
	long swap = UNKNOWN_SWAP;

	char input_name[128];
	if (sprintf(input_name, INPUT_NAME_FORMAT.c_str(), pid) > 0)
	{
		FILE* input = fopen(input_name, "r");

		if (input != nullptr)
		{
			char line[64];
			swap = 0;

			while (fgets(line, 63, input) != nullptr)
			{
				if (has_swap(line))
				{
					swap += get_swap(line);
				}
			}

			fclose(input);
		}
	}

	// tricky: the proc entry is marked readable but really is not,
	// so we get EPERM only when trying to read.
	return (errno == 0 ? swap : UNKNOWN_SWAP);
}



#include <string>
#include <stdio.h>

#include "swap.h"
#include "substring.h"

using namespace std;

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
	const string filename = "/proc/" + to_string(pid) + "/smaps";
	long swap = 0;

	FILE* input = fopen(filename.c_str(), "r");
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

	return (errno == 0 ? swap : UNKNOWN_SWAP);
}


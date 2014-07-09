
#include <fstream>
#include <string>

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

	return 0;
}

long get_swap_for_pid(pid_t pid)
{
	const string filename = "/proc/" + to_string(pid) + "/smaps";
	long swap = 0;

	ifstream in(filename);
	if (in.is_open())
	{
		string line;
		while (getline(in, line))
		{
			if (has_swap(line))
			{
				swap += get_swap(line);
			}
		}

		in.close();
	}

	return (in.bad() ? UNKNOWN_SWAP : swap);
}


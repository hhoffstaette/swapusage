
#include <fstream>
#include <sstream>
#include <string>

#include "swap.h"
#include "substring.h"

using namespace std;

static const string SWAP_PREFIX = "Swap:";

static long get_swap_for_smaps_fragment(const string& line)
{
	if (!line.compare(0, SWAP_PREFIX.length(), SWAP_PREFIX))
	{
		string value = substring_at(line, " ", 1);
		if (value != "0")
		{
			long kb = 0;
			istringstream iss(value);
			if (!(iss >> std::dec >> kb).fail())
			{
				return kb;
			}
		}
	}

	return 0;
}

long get_swap_for_pid(const string& pid)
{
	const string filename = "/proc/" + pid + "/smaps";
	long swap = -1;

	ifstream in(filename);
	if (in.is_open())
	{
		swap = 0;
		string line;
		while (getline(in, line))
		{
			swap += get_swap_for_smaps_fragment(line);
		}

		in.close();
	}

	return swap;
}


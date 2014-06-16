
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "swap.h"
#include "substring.h"

using namespace std;

static long get_swap_for_smaps_fragment(const string& line)
{
	if (line.length() > 5 && line[0] == 'S' && line[1] == 'w' && line[2] == 'a'
			&& line[3] == 'p' && line[4] == ':')
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


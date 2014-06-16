
#include <string>

#include "substring.h"

using namespace std;

string substring_at(const string& arg, const string& delimiter, int index)
{
	int matched = 0;

	for (size_t current = 0; current != string::npos;)
	{
		size_t start = arg.find_first_not_of(delimiter, current);
		size_t end = arg.find_first_of(delimiter, start);

		if (matched == index)
		{
			return arg.substr(start, end - start);
		}

		matched++;
		current = end;
	}

	return "";
}


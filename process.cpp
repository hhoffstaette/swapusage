
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <dirent.h>

#include "process.h"
#include "swap.h"

using namespace std;

// for matching /proc/<pid> entries
static const regex is_number("\\d+");

pid_t to_pid(const string& value)
{
	return regex_match(value, is_number) ? stoi(value) : UNKNOWN_PID;
}

string get_process_name(pid_t pid)
{
	const string filename = "/proc/" + to_string(pid) + "/comm";
	string line = UNKNOWN_PROCESS_NAME;

	ifstream in(filename);
	if (in.is_open())
	{
		getline(in, line);
		in.close();
	}

	return line;
}

ProcessInfo get_process_info(pid_t pid)
{
	return {pid, get_process_name(pid), get_swap_for_pid(pid)};
}

vector<ProcessInfo> get_process_info()
{
	vector<ProcessInfo> procs;

	DIR* dir = opendir("/proc");
	if (dir != NULL)
	{
		struct dirent* entry;
		while ((entry = readdir(dir)) != NULL)
		{
			pid_t pid = to_pid(entry->d_name);
			if (pid != UNKNOWN_PID)
			{
				long swap = get_swap_for_pid(pid);
				if (swap > 0)
				{
					ProcessInfo proc = {pid, get_process_name(pid), swap};
					procs.push_back(proc);
				}
			}
		}
		closedir(dir);
	}

	return procs;
}


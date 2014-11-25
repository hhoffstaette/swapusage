
#include <string>
#include <vector>
#include <dirent.h>
#include <stdio.h>

#include "pid.h"
#include "process.h"
#include "swap.h"

using namespace std;

string get_process_name(pid_t pid)
{
	const string filename = "/proc/" + to_string(pid) + "/comm";
	string name = UNKNOWN_PROCESS_NAME;

	FILE* input = fopen(filename.c_str(), "r");
	if (input != nullptr)
	{
		char line[64];
		if (fscanf(input, "%s63", line) == 1)
		{
			name = line;
		}

		fclose(input);
	}

	return name;
}

ProcessInfo get_process_info(pid_t pid)
{
	return {pid, get_swap_for_pid(pid), get_process_name(pid)};
}

vector<ProcessInfo> get_process_info()
{
	vector<ProcessInfo> procs;

	DIR* dir = opendir("/proc");
	if (dir != nullptr)
	{
		struct dirent* entry = nullptr;
		while ((entry = readdir(dir)) != nullptr)
		{
			pid_t pid = to_pid(entry->d_name);
			if (pid != UNKNOWN_PID)
			{
				long swap = get_swap_for_pid(pid);
				if (swap > 0)
				{
					procs.emplace_back(pid, swap, get_process_name(pid));
				}
			}
		}

		closedir(dir);
	}

	return procs;
}


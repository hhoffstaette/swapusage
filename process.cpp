
#include "pid.h"
#include "process.h"
#include "swap.h"

#include <dirent.h>
#include <stdio.h>

using namespace std;

const string UNKNOWN_PROCESS_NAME = "<unknown>";

string get_process_name(pid_t pid)
{
	string process_name;

	const string input_name = "/proc/" + to_string(pid) + "/comm";
	FILE* input = fopen(input_name.c_str(), "r");
	if (input != nullptr)
	{
		char line[64];
		if (fscanf(input, "%s63", line) == 1)
		{
			process_name = line;
		}

		fclose(input);
	}
	else
	{
		// should never happen
		process_name = UNKNOWN_PROCESS_NAME;
	}

	return process_name;
}

ProcessInfo get_process_info(pid_t pid)
{
	return {pid, get_swap_for_pid(pid), get_process_name(pid)};
}

vector<ProcessInfo> get_process_infos()
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



#include "pid.h"
#include "process.h"
#include "swap.h"

#include <dirent.h>
#include <stdio.h>

using namespace std;

const string UNKNOWN_PROCESS_NAME = "<unknown>";

static const string INPUT_NAME_FORMAT = "/proc/%u/comm";

string get_process_name(pid_t pid)
{
	char input_name[128];

	if (sprintf(input_name, INPUT_NAME_FORMAT.c_str(), pid) > 0)
	{
		FILE* input = fopen(input_name, "r");

		if (input != nullptr)
		{
			string process_name = UNKNOWN_PROCESS_NAME;
			char line[64];

			if (fscanf(input, "%s63", line) == 1)
			{
				process_name = line;
			}

			fclose(input);
			return process_name;
		}
	}

	// should never happen
	return UNKNOWN_PROCESS_NAME;
}

vector<unique_ptr<ProcessInfo>> get_process_infos()
{
	vector<unique_ptr<ProcessInfo>> procs;

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
					procs.emplace_back(make_unique<ProcessInfo>(pid, swap, get_process_name(pid)));
				}
			}
		}

		closedir(dir);
	}

	return procs;
}


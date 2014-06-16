
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "process.h"
#include "swap.h"

using namespace std;

// for matching /proc/<pid> entries
static const regex is_number("\\d+");

bool is_valid_pid(const string& value)
{
    return regex_match(value, is_number);
}

string get_process_name(const string& pid)
{
	const string filename = "/proc/" + pid + "/comm";
	string line = UNKNOWN_PROCESS_NAME;

	ifstream in(filename);
	if (in.is_open())
	{
		getline(in, line);
		in.close();
	}

	return line;
}

ProcessInfo get_process_info(const string& pid)
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
            const string pid = entry->d_name;
            if (is_valid_pid(pid))
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


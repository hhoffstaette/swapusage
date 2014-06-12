
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

string get_process_name(const string& pid) {
	const string filename = "/proc/" + pid + "/comm";

	ifstream in(filename);
	if (in.is_open()) {
		string line;
		getline(in, line);
		return line;
		in.close();
	}

	return "<unknown>";
}

SwappedProcess get_process_info(string pid) {
	return {pid, get_process_name(pid), get_swap_for_pid(pid)};
}

vector<SwappedProcess> get_process_info() {
	vector<SwappedProcess> procs;

	DIR* dir = opendir("/proc");
	if (dir != NULL)
    {
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
        	const char* name = entry->d_name;
        	if (regex_match(name, is_number)) {
        		string pid = string(name);
        		long swap = get_swap_for_pid(pid);
        		if (swap > 0) {
				    SwappedProcess proc = {pid, get_process_name(pid), swap};
					procs.push_back(proc);
        		}
        	}
        }
        closedir(dir);
    }

    return procs;
}


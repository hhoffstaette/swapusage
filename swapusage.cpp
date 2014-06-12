
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "process.h"

using namespace std;

static void usage() {
	cerr << "Usage: swapusage [<pid>]" << endl;
}

int main(int argc, char* argv[]) {
	vector<SwappedProcess> procs;

	switch (argc) {
		case 1: {
			procs = get_process_info();
			break;
		}
		case 2: {
			string pid(argv[1]);
			SwappedProcess proc = get_process_info(pid);
			if (proc.swap == -1) {
				cerr << "No such process: " << pid << endl;
				return EXIT_FAILURE;
			}
			else if (proc.swap > 0) {
				procs.push_back(proc);
			}
			// else swap == 0: ignore
			break;
		}
		default: {
			usage();
			return EXIT_FAILURE;
		}
	}

	if (procs.empty()) {
		cout << "No swap used." << endl ;
	}
	else {
		for (SwappedProcess& p: procs) {
			cout << "pid: " << p.pid;
			cout << " name: " << p.name;
			cout << " swap: " << p.swap << " KB";
			cout << endl;
		}
	}

	return EXIT_SUCCESS;
}


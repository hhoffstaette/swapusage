
#include <iostream>
#include <string>
#include <vector>

#include "process.h"

using namespace std;

static void usage()
{
	cerr << "Usage: swapusage [<pid>]" << endl;
}

int main(int argc, char* argv[])
{
	vector<ProcessInfo> procs;

	if (argc == 1)
	{
		// no pid: collect all processes
		procs = get_process_info();
	}
	else
	{
		const string pidarg = argv[1];

		if (pidarg == "-h" || pidarg == "--help")
		{
			usage();
			return EXIT_SUCCESS;
		}

		if (!is_valid_pid(pidarg))
		{
			cerr << "Not a process id: " << pidarg << endl;
			return EXIT_SUCCESS;
		}

		ProcessInfo proc = get_process_info(pidarg);
		if (proc.name == UNKNOWN_PROCESS_NAME)
		{
			cerr << "No such process: " << pidarg << endl;
			return EXIT_FAILURE;
		}

		// finally collect process with swap
		if (proc.swap > 0)
		{
			procs.push_back(proc);
		}
	}

	if (procs.empty())
	{
		cout << "No swap used." << endl ;
	}
	else
	{
		for (ProcessInfo& p: procs)
		{
			cout << "pid: " << p.pid;
			cout << " name: " << p.name;
			cout << " swap: " << p.swap << " KB";
			cout << endl;
		}
	}

	return EXIT_SUCCESS;
}


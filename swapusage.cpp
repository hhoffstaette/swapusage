
#include <iostream>
#include <string>
#include <vector>

#include "process.h"
#include "swap.h"

using namespace std;

static void usage()
{
	cerr << "Usage: swapusage [pid]" << endl;
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

		int pid = to_pid(pidarg);
		if (pid == UNKNOWN_PID)
		{
			cerr << "Not a process id: " << pidarg << endl;
			return EXIT_FAILURE;
		}

		ProcessInfo proc = get_process_info(pid);

		if (proc.name == UNKNOWN_PROCESS_NAME)
		{
			cerr << "No such process: " << pid << endl;
			return EXIT_FAILURE;
		}

		if (proc.swap == UNKNOWN_SWAP)
		{
			cerr << "Cannot read swap for pid: " << pid << endl;
			return EXIT_FAILURE;
		}

		// finally collect valid process info
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


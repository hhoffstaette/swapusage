
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "pid.h"
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
		sort(procs.begin(), procs.end(), [](ProcessInfo& first, ProcessInfo& second)
		{
			return first.swap > second.swap;
		});

		cout << "====================================" << endl;
		cout << "kB\tpid\tname" << endl;
		cout << "====================================" << endl;

		for (ProcessInfo& p: procs)
		{
			cout << p.swap << "\t"<< p.pid << "\t" << p.name << endl;
		}

		cout << "------------------------------------" << endl;

		long swap = 0;
		for_each(procs.begin(), procs.end(), [&swap](ProcessInfo &proc)
		{
			swap += proc.swap;
		});

		cout << "Overall Swap used: " << swap << endl;
	}

	return EXIT_SUCCESS;
}



#include "pid.h"
#include "process.h"
#include "swap.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// lambda for sorting by swap
static auto orderBySwap = [](const unique_ptr<ProcessInfo>& first, const unique_ptr<ProcessInfo>& second)
{
	return first->swap > second->swap;
};

int main(int argc, char* argv[])
{
	vector<unique_ptr<ProcessInfo>> procs;
	bool all_procs = true;

	if (argc == 1)
	{
		// no pid: collect all processes
		procs = get_process_infos();
	}
	else
	{
		const string pidarg = argv[1];

		if (pidarg == "-h" || pidarg == "--help")
		{
			cerr << "Usage: swapusage [pid]" << endl;
			return EXIT_SUCCESS;
		}

		int pid = to_pid(pidarg.c_str());
		if (pid == UNKNOWN_PID)
		{
			cerr << "Not a process id: " << pidarg << endl;
			return EXIT_FAILURE;
		}

		string name = get_process_name(pid);
		if (name == UNKNOWN_PROCESS_NAME)
		{
			cerr << "No such process: " << pid << endl;
			return EXIT_FAILURE;
		}

		long swap = get_swap_for_pid(pid);
		if (swap == UNKNOWN_SWAP)
		{
			cerr << "Cannot read swap for pid: " << pid << endl;
			return EXIT_FAILURE;
		}

		// finally collect valid process info
		if (swap > 0)
		{
			procs.emplace_back(make_unique<ProcessInfo>(pid, swap, name));
			all_procs = false;
		}
	}

	if (procs.empty())
	{
		cout << "No swap used." << endl ;
	}
	else
	{
		// sort by swap
		sort(procs.begin(), procs.end(), orderBySwap);

		cout << "====================================" << endl;
		cout << setw(8) << "Swap kB";
		cout << setw(6) << "PID";
		cout << "  ";
		cout << setw(16) << left << "Name" << endl;
		cout << "====================================" << endl;

		long all_swap = 0;

		for (unique_ptr<ProcessInfo>& p: procs)
		{
			cout << setw(8) << right << p->swap;
			cout << setw(6) << right << p->pid;
			cout << "  ";
			cout << setw(16) << left << p->name << endl;
			all_swap += p->swap;
		}

		if (all_procs)
		{
			cout << "------------------------------------" << endl;
			cout << setw(8) << right << all_swap << " kB total." << endl;
		}
	}

	return EXIT_SUCCESS;
}


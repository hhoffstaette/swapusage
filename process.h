
#ifndef PROCESS_H_
#define PROCESS_H_

#include <string>
#include <unistd.h>
#include <vector>

struct ProcessInfo
{
	pid_t pid;
	long swap;
	std::string name;

	ProcessInfo(pid_t new_pid, long new_swap, std::string new_name)
	  : pid(new_pid), swap(new_swap), name(new_name)
	{
	}
};

// returned when the name of a process could not be determined
extern const std::string UNKNOWN_PROCESS_NAME;

// get only the name of a specific process
std::string get_process_name(pid_t pid);

// get info for specific process
ProcessInfo get_process_info(pid_t pid);

// get infos for all processes
std::vector<ProcessInfo> get_process_infos();

#endif /* PROCESS_H_ */


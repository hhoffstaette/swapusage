
#ifndef PROCESS_H_
#define PROCESS_H_

#include <string>
#include <vector>

// {pid, name, swap in kb}
struct ProcessInfo
{
	pid_t pid;
	std::string name;
	long swap;
};

// returned when the name of a process could not be determined
static const std::string UNKNOWN_PROCESS_NAME = "<unknown>";

// get info for all processes
std::vector<ProcessInfo> get_process_info();

// get info for specific process
ProcessInfo get_process_info(pid_t pid);

#endif /* PROCESS_H_ */


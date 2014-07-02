
#ifndef PROCESS_H_
#define PROCESS_H_

#include <limits>
#include <string>
#include <vector>

// {pid, name, swap in kb}
struct ProcessInfo
{
	pid_t pid;
	std::string name;
	long swap;
};

static const int UNKNOWN_PID = std::numeric_limits<pid_t>::max();
static const std::string UNKNOWN_PROCESS_NAME = "<unknown>";

// returns value as pid or UNKNOWN_PID
pid_t to_pid(const std::string& value);

// get info for all processes
std::vector<ProcessInfo> get_process_info();

// get info for specific process
ProcessInfo get_process_info(pid_t pid);

#endif /* PROCESS_H_ */



#ifndef PROCESS_H_
#define PROCESS_H_

#include <string>
#include <tuple>
#include <vector>

// {pid, name, swap in kb}
struct ProcessInfo
{
	std::string pid;
	std::string name;
	long swap;
};

static const std::string UNKNOWN_PROCESS_NAME = "<unknown>";

// check whether a value denotes a valid pid
bool is_valid_pid(const std::string& value);

// get info for all processes
std::vector<ProcessInfo> get_process_info();

// get info for specific process
ProcessInfo get_process_info(const std::string& pid);

#endif /* PROCESS_H_ */


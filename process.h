
#ifndef PROCESS_H_
#define PROCESS_H_

#include <string>
#include <tuple>
#include <vector>

// {pid, name, swap in kb}
struct SwappedProcess {
	std::string pid;
	std::string name;
	long swap;
};

// get info for all processes
std::vector<SwappedProcess> get_process_info();

// get info for specific process
SwappedProcess get_process_info(std::string pid);

#endif /* PROCESS_H_ */


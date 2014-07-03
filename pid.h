
#ifndef PID_H_
#define PID_H_

#include <limits>
#include <string>

// marks an illegal pid_t value
static const int UNKNOWN_PID = std::numeric_limits<pid_t>::max();

// returns value as pid or UNKNOWN_PID
pid_t to_pid(const std::string& value);

#endif /* PID_H_ */


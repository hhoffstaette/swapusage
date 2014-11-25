
#ifndef PID_H_
#define PID_H_

#include <string>
#include <unistd.h>

// marks an illegal pid_t value
extern const pid_t UNKNOWN_PID;

// returns value as pid or UNKNOWN_PID
pid_t to_pid(const std::string& value);

#endif /* PID_H_ */


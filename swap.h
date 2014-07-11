
#ifndef SWAP_H_
#define SWAP_H_

#include <limits>

static const long UNKNOWN_SWAP = std::numeric_limits<long>::min();

// returns the swap for the given process in KB or UNKNOWN_SWAP
// (e.g. due to lack of permissions)
long get_swap_for_pid(pid_t pid);

#endif /* SWAP_H_ */

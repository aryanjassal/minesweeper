#pragma once

#include "utils/types.hpp"

// The `smart_sleep` function sleeps for the precisely the specified time. To
// achieve this, the program sleeps for 95% of sleep time, after which it runs a
// loop to keep the CPU busy until the time is finished. This mitigates the
// inaccuracy of `sleep()` methods while not wasting CPU cycles in a loop.
void smart_sleep(f64 time);

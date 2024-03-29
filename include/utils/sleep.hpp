#pragma once

// The `smart_sleep` function sleeps for the precisely the specified time. To
// achieve this, the program sleeps until `time - margin`, after which it runs a
// loop to keep the CPU busy until the time is finished. This mitigates the
// inaccuracy of `sleep()` methods while not wasting CPU cycles in a loop. 
//
// The 'time' parameter controls the exact amount of time to sleep for.
// The 'margin' parameter controls the margin when the sleep ends and the loop starts.
void smart_sleep(double time, double margin);

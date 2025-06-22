#include "CustomTimer.h"

using namespace std::chrono;

CustomTimer::CustomTimer()
{
	last = steady_clock::now();
}

float CustomTimer::Mark()
{
    const auto old = last;                    // Save the previous timestamp
    last = steady_clock::now();              // Update to the current time
    const duration<float> frameTime = last - old; // Get time delta in seconds
    return frameTime.count();                // Return delta in seconds
}

float CustomTimer::Peek() const
{
	return duration<float>(steady_clock::now() - last).count();
}
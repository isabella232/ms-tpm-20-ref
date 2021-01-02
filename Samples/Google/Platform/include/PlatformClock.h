#ifndef _PLATFORM_CLOCK_H_
#define _PLATFORM_CLOCK_H_

// Must implement
uint64_t _plat__RealTimeNs(void);

// We use a nanosecond real clock, so CLOCK_NOMINAL is the number of ticks per
// mS, which is 10^9 / 10^3 = 10^6 = 1,000,000.
#define CLOCK_NOMINAL 1000000
// A 1% change in rate is 10,000 ns
#define CLOCK_ADJUST_COARSE 10000
// A 0.1% change in rate is 1,000 ns
#define CLOCK_ADJUST_MEDIUM 1000
// A minimum change in rate is 10 ns
#define CLOCK_ADJUST_FINE 10
// The clock tolerance is +/-15% (150,000 ns)
#define CLOCK_ADJUST_LIMIT 150000

#endif // _PLATFORM_CLOCK_H_
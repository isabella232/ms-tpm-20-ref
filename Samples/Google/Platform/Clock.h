// TODO(joerichey): Document this

#ifndef _GOOGLE_PLATFORM_CLOCK_H_
#define _GOOGLE_PLATFORM_CLOCK_H_

#include <stdint.h>

// Called externally
void _plat__TimerReset(void);
// Must implement
uint64_t _plat__RealTimeNs(void);

#endif // _GOOGLE_PLATFORM_CLOCK_H_

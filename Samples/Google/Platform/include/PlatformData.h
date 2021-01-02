// This file contains the instance data for the Platform module. It is collected
// in this file so that the state of the module is easier to manage.

#ifndef _PLATFORM_DATA_H_
#define _PLATFORM_DATA_H_

#include <stdbool.h>
#include <stdint.h>

#include "TpmProfile.h" // For NV_MEMORY_SIZE

#ifdef  _PLATFORM_DATA_C_
#define EXTERN
#else
#define EXTERN  extern
#endif

//** From Clock.c
// The current conversion rate between the read NS clock and the TPM clock.
EXTERN uint64_t s_nanosPerClock;
// The effective last result from _plat__RealTimeNs
EXTERN uint64_t s_realPrev;
// The last value returned by _plat__TimerRead
EXTERN uint64_t s_tpmTime;
// Flags for keeping track of timer reset events
EXTERN bool s_timerReset;
EXTERN bool s_timerStopped;

//** From NVMem.c
// Copy of NVData in static RAM
EXTERN uint8_t s_NV[NV_MEMORY_SIZE];
// NVData was committed since the last call to _plat__IsNvAvailable
EXTERN bool s_NvCommitted;

//** From Start.c
EXTERN bool s_powerLost;

#endif // _PLATFORM_DATA_H_
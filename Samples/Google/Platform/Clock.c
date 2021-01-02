// TODO(joerichey): Document this
//
// This file contains the routines that are used by the simulator to mimic
// a hardware clock on a TPM.
//
// In this implementation, all the time values are measured in millisecond.
// However, the precision of the clock functions may be implementation
// dependent.
#include "Platform.h"

void _plat__TimerReset(void) {
  s_nanosPerClock = CLOCK_NOMINAL;
  s_realPrev = 0;
  s_tpmTime = 0;

  s_timerReset = true;
  s_timerStopped = true;
}

uint64_t _plat__TimerRead() {
  uint64_t realNext = _plat__RealTimeNs();

  // Initialize time if this is the first call
  if (s_realPrev == 0) {
    s_realPrev = realNext;
    s_tpmTime = 0;
    return s_tpmTime;
  }

  // Don't allow the clock to move backwards
  if (realNext <= s_realPrev) {
    return s_tpmTime;
  }

  // Compute the number of ms we should report have passed
  uint64_t realDiff = realNext - s_realPrev;
  uint64_t tpmDiff = realDiff / s_nanosPerClock;
  s_tpmTime += tpmDiff;

  // We can't do: s_realPrev += realDiff, that will lead to rounding errors.
  uint64_t effectiveRealDiff = tpmDiff * s_nanosPerClock;
  s_realPrev += effectiveRealDiff;

  return s_tpmTime;
}

int _plat__TimerWasReset() {
  bool ret = s_timerReset;
  s_timerReset = false;
  return ret;
}

int _plat__TimerWasStopped() {
  bool ret = s_timerStopped;
  s_timerStopped = false;
  return ret;
}

void _plat__ClockAdjustRate(int adjust) {
  // newRate is signed to prevent underflow.
  int64_t newRate = (int64_t)s_nanosPerClock + (int64_t)adjust;
  // Don't allow the caller to set the rate outside of fixed bounds.
  if (newRate > (CLOCK_NOMINAL + CLOCK_ADJUST_LIMIT)) {
    s_nanosPerClock = CLOCK_NOMINAL + CLOCK_ADJUST_LIMIT;
  } else if (newRate < (CLOCK_NOMINAL - CLOCK_ADJUST_LIMIT)) {
    s_nanosPerClock = CLOCK_NOMINAL - CLOCK_ADJUST_LIMIT;
  } else {
    s_nanosPerClock = newRate;
  }
}

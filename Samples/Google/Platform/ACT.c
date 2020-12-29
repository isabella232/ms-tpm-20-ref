// We don't implement any Authenticated Countdown Timers, so we just provide
// empty stubs for all of the ACT platform functions.

#include "Platform_fp.h"

int _plat__ACT_GetImplemented(uint32_t act) {
  (void)act;
  return 0;
}
uint32_t _plat__ACT_GetRemaining(uint32_t act) {
  (void)act;
  return 0;
}
int _plat__ACT_GetSignaled(uint32_t act) {
  (void)act;
  return 0;
}
void _plat__ACT_SetSignaled(uint32_t act, int on) {
  (void)act;
  (void)on;
}
int _plat__ACT_UpdateCounter(uint32_t act, uint32_t newValue) {
  (void)act;
  (void)newValue;
  return 0;
}
void _plat__ACT_EnableTicks(int enable) { (void)enable; }
int _plat__ACT_Initialize() { return 0; }

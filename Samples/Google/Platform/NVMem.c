// This file contains read/diff/write/clear/move methods for an in-RAM copy of
// NVData. This implementation assumes that memory will be written/read to s_NV
// before/after invoking the _plat__* entry points. Thus, we can safely assume
// that the memory is always available. We use enable/commit for dirty tracking
// optimizations, but these methods will still always succeed.
#include "Platform.h"

#include <assert.h>
#include <string.h>

int _plat__NVEnable(void *platParameter) {
  (void)(platParameter);
  return 0;
}
int _plat__IsNvAvailable() {
  s_NvCommitted = false;
  return 0;
}
int _plat__NvCommit() {
  s_NvCommitted = true;
  return 0;
}

void _plat__NvMemoryRead(unsigned int start, unsigned int size, void *data) {
  assert(start + size <= NV_MEMORY_SIZE);
  memcpy(data, &s_NV[start], size);
}

int _plat__NvIsDifferent(unsigned int start, unsigned int size, void *data) {
  assert(start + size <= NV_MEMORY_SIZE);
  return memcmp(&s_NV[start], data, size) != 0;
}

int _plat__NvMemoryWrite(unsigned int start, unsigned int size, void *data) {
  assert(start + size <= NV_MEMORY_SIZE);
  memcpy(&s_NV[start], data, size);
  return true; // Bounds checked by assert, return type should be void.
}

void _plat__NvMemoryClear(unsigned int start, unsigned int size) {
  assert(start + size <= NV_MEMORY_SIZE);
  // In this implementation, assume that the erase value for NV is all 1s
  memset(&s_NV[start], 0xff, size);
}

void _plat__NvMemoryMove(unsigned int sourceOffset, unsigned int destOffset,
                         unsigned int size) {
  assert(sourceOffset + size <= NV_MEMORY_SIZE);
  assert(destOffset + size <= NV_MEMORY_SIZE);
  memmove(&s_NV[destOffset], &s_NV[sourceOffset], size);
}

// We don't implement non-zero localities; no OSes support it regardless.

#include "Platform_fp.h"

uint8_t _plat__LocalityGet() { return 0; }

// We don't implement cancellation; the vTPM is fast enough to not need it.

#include "Platform_fp.h"

int _plat__IsCanceled() { return 0; }

// We don't implement cancellation; the vTPM is fast enough to not need it.
#include "Platform.h"

int _plat__IsCanceled() { return 0; }

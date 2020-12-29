// A vTPM (necessarily) has no meaningful concept of Physical Presence, so we
// just always assert Physical Presence to avoid test failures.

#include "Platform_fp.h"

int _plat__PhysicalPresenceAsserted() { return 1; }

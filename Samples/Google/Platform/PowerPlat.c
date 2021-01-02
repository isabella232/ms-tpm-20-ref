// This file handles setting and clearing the s_powerLost flag.
#include "Platform.h"

int _plat__Signal_PowerOn() {
    // Reset the timer
    _plat__TimerReset();
    // Need to indicate that we lost power
    s_powerLost = true;
    return 0;
}

int _plat__WasPowerLost(void) {
    int retVal = s_powerLost;
    s_powerLost = false;
    return retVal;
}

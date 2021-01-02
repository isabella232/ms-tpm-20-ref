#include "Start.h"
#include "Platform.h"

// This doesn't actually work
uint64_t _plat__RealTimeNs(void) {
    return 43;
}

int main(int argc, const char *argv[]) {
    switch (argc) {
    case 1:
        return _plat__Manufacture();
    case 2:
        return _plat__Reset();
    case 3: {
        uint32_t size = *(uint32_t*)(argv[1]);
        const uint8_t* data = (const uint8_t*)(argv[2]);
        return _plat__SendRTM(size, data);
    }
    case 4: {
        uint32_t reqSize = *(uint32_t*)(argv[1]);
        const uint8_t* req = (const uint8_t*)(argv[2]);
        uint8_t buf[4096];
        uint8_t* resp = buf;
        uint32_t respSize = sizeof(buf); 
        _plat__RunCommand(reqSize, req, &respSize, &resp);
        return 0;
    }
    default:
        return 1;
    }
}

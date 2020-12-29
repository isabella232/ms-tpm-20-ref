// Entrypoints into the TPM 2.0 Simulator

#ifndef _GOOGLE_PLATFORM_START_H_
#define _GOOGLE_PLATFORM_START_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

// Manufacture the TPM's NVData. TODO(joerichey): Document this
bool _plat__Manufacture(void);

// Reset the TPM. This serves as a power-on indication and should always be
// called as the TPM powers on and before calling _plat__RunCommand.
bool _plat__Reset(void);

// Send RTM data directly to the TPM. If the TPM has been reset but not yet
// started, this will be the H-CRTM data, extended into HCRTM_PCR. If the TPM
// has been started, this will be the DRTM data, extended into DRTM_PCR.
bool _plat__SendRTM(uint32_t size, const uint8_t *data);

// This version of RunCommand will set up a jum_buf and call ExecuteCommand().
// If the command executes without failing, it will return and RunCommand will
// return. If there is a failure in the command, then _plat__Fail() is called
// and it will longjump back to RunCommand which will call ExecuteCommand again.
// However, this time, the TPM will be in failure mode so ExecuteCommand will
// simply build a failure response and return.
// TODO(joerichey): Document this
bool _plat__RunCommand(uint32_t requestSize,   // IN: command buffer size
                       const uint8_t *request, // IN: command buffer
                       uint32_t *responseSize, // IN/OUT: response buffer size
                       uint8_t **response      // IN/OUT: response buffer
);

#ifdef __cplusplus
}
#endif

#endif // _GOOGLE_PLATFORM_START_H_

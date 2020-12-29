// The functions declared in this file are those used by libtpm. All of these
// functions must have implementations (either in this directory or elsewhere)
// for the simulator to properly link. This file is modified from the reference
// code's Platform_fp.h to remove any functions not used by libtpm.

#ifndef _PLATFORM_FP_H_
#define _PLATFORM_FP_H_

#include <stdint.h>

//***_plat__IsCanceled()
// Check if the cancel flag is set
//  Return Type: int
//      TRUE(1)         if cancel flag is set
//      FALSE(0)        if cancel flag is not set
int _plat__IsCanceled(void);

//***_plat__TimerRead()
// This function provides access to the tick timer of the platform. The TPM code
// uses this value to drive the TPM Clock.
//
// The tick timer is supposed to run when power is applied to the device. This
// timer should not be reset by time events including _TPM_Init. It should only
// be reset when TPM power is re-applied.
//
// If the TPM is run in a protected environment, that environment may provide
// the tick time to the TPM as long as the time provided by the environment is
// not allowed to go backwards. If the time provided by the system can go
// backwards during a power discontinuity, then the _plat__Signal_PowerOn should
// call _plat__TimerReset().
uint64_t _plat__TimerRead(void);

//*** _plat__TimerWasReset()
// This function is used to interrogate the flag indicating if the tick timer
// has been reset.
//
// If the resetFlag parameter is SET, then the flag will be CLEAR before the
// function returns.
int _plat__TimerWasReset(void);

//*** _plat__TimerWasStopped()
// This function is used to interrogate the flag indicating if the tick timer
// has been stopped. If so, this is typically a reason to roll the nonce.
//
// This function will CLEAR the s_timerStopped flag before returning. This
// provides functionality that is similar to status register that is cleared
// when read. This is the model used here because it is the one that has the
// most impact on the TPM code as the flag can only be accessed by one entity in
// the TPM. Any other implementation of the hardware can be made to look like a
// read-once register.
int _plat__TimerWasStopped(void);

//***_plat__ClockAdjustRate()
// Adjust the clock rate
void _plat__ClockAdjustRate(int adjust // IN: adjust number (positive/negative)
);

//*** _plat__GetEntropy()
// This function is used to get available hardware entropy. In a hardware
// implementation of this function, there would be no call to the system
// to get entropy.
//  Return Type: int32_t
//  < 0        hardware failure of the entropy generator, this is sticky
// >= 0        the returned amount of entropy (bytes)
//
int32_t _plat__GetEntropy(uint8_t *entropy, // output buffer
                          uint32_t amount   // amount requested
);

//** From LocalityPlat.c

//***_plat__LocalityGet()
// Get the most recent command locality in locality value form.
// This is an integer value for locality and not a locality structure
// The locality can be 0-4 or 32-255. 5-31 is not allowed.
uint8_t _plat__LocalityGet(void);

//***_plat__NVEnable()
// Enable NV memory.
//
// In a real TPM, with NV on chip, this function would verify the integrity of
// the saved context. If the NV memory was not on chip but was in something like
// RPMB, the NV state would be read in, decrypted and integrity checked.
//
// The recovery from an integrity failure depends on where the error occurred.
// If it was in the data discarded by TPM Reset, then the error is recoverable
// by resetting the TPM. Otherwise, the TPM must go into failure mode.
//  Return Type: int
//      0           if success
//      > 0         if receive recoverable error
//      <0          if unrecoverable error
int _plat__NVEnable(void *);

//***_plat__IsNvAvailable()
// Check if NV is available
//  Return Type: int
//      0               NV is available
//      1               NV is not available due to write failure
//      2               NV is not available due to rate limit
int _plat__IsNvAvailable(void);

//***_plat__NvMemoryRead()
// Function: Read a chunk of NV memory
void _plat__NvMemoryRead(unsigned int startOffset, // IN: read start
                         unsigned int size,        // IN: size of bytes to read
                         void *data                // OUT: data buffer
);

//*** _plat__NvIsDifferent()
// This function checks to see if the NV is different from the test value. This
// is so that NV will not be written if it has not changed.
//  Return Type: int
//      TRUE(1)         the NV location is different from the test value
//      FALSE(0)        the NV location is the same as the test value
int _plat__NvIsDifferent(unsigned int startOffset, // IN: read start
                         unsigned int size,        // IN: size of bytes to read
                         void *data                // IN: data buffer
);

//***_plat__NvMemoryWrite()
// This function is used to update NV memory. The "write" is to a memory copy of
// NV. At the end of the current command, any changes are written to
// the actual NV memory.
// NOTE: A useful optimization would be for this code to compare the current
// contents of NV with the local copy and note the blocks that have changed.
// Then only write those blocks when _plat__NvCommit() is called.
int _plat__NvMemoryWrite(unsigned int startOffset, // IN: write start
                         unsigned int size,        // IN: size of bytes to write
                         void *data                // IN: data buffer
);

//***_plat__NvMemoryClear()
// Function is used to set a range of NV memory bytes to an
// implementation-dependent value. The value represents the erase state of the
// memory.
void _plat__NvMemoryClear(unsigned int start, // IN: clear start
                          unsigned int size   // IN: number of bytes to clear
);

//***_plat__NvMemoryMove()
// Function: Move a chunk of NV memory from source to destination
//      This function should ensure that if there overlap, the original data is
//      copied before it is written
void _plat__NvMemoryMove(unsigned int sourceOffset, // IN: source offset
                         unsigned int destOffset,   // IN: destination offset
                         unsigned int size // IN: size of data being moved
);

//***_plat__NvCommit()
// This function writes the local copy of NV to NV for permanent store. It will
// write NV_MEMORY_SIZE bytes to NV. If a file is use, the entire file is
// written.
//  Return Type: int
//  0       NV write success
//  non-0   NV write fail
int _plat__NvCommit(void);

//*** _plat__WasPowerLost()
// Test whether power was lost before a _TPM_Init.
//
// This function will clear the "hardware" indication of power loss before
// return. This means that there can only be one spot in the TPM code where this
// value gets read. This method is used here as it is the most difficult to
// manage in the TPM code and, if the hardware actually works this way, it is
// hard to make it look like anything else. So, the burden is placed on the TPM
// code rather than the platform code
//  Return Type: int
//      TRUE(1)         power was lost
//      FALSE(0)        power was not lost
int _plat__WasPowerLost();

//***_plat__PhysicalPresenceAsserted()
// Check if physical presence is signaled
//  Return Type: int
//      TRUE(1)         if physical presence is signaled
//      FALSE(0)        if physical presence is not signaled
int _plat__PhysicalPresenceAsserted();

//***_plat__Fail()
// This is the platform depended failure exit for the TPM.
_Noreturn void _plat__Fail();

//*** _plat__ACT_GetImplemented()
// This function tests to see if an ACT is implemented. It is a belt and
// suspenders function because the TPM should not be calling to manipulate an
// ACT that is not implemented. However, this could help the simulator code
// which doesn't necessarily know if an ACT is implemented or not.
int _plat__ACT_GetImplemented(uint32_t act);

//*** _plat__ACT_GetRemaining()
// This function returns the remaining time. If an update is pending, 'newValue'
// is returned. Otherwise, the current counter value is returned. Note that
// since the timers keep running, the returned value can get stale immediately.
// The actual count value will be no greater than the returned value.
uint32_t _plat__ACT_GetRemaining(uint32_t act);

//*** _plat__ACT_GetSignaled()
int _plat__ACT_GetSignaled(uint32_t act);

//*** _plat__ACT_SetSignaled()
void _plat__ACT_SetSignaled(uint32_t act, int on);

//*** _plat__ACT_UpdateCounter()
// This function is used to write the newValue for the counter. If an update is
// pending, then no update occurs and the function returns FALSE. If
// 'setSignaled' is TRUE, then the ACT signaled state is SET and if 'newValue'
// is 0, nothing is posted.
int _plat__ACT_UpdateCounter(uint32_t act,     // IN: ACT to update
                             uint32_t newValue // IN: the value to post
);

//***_plat__ACT_EnableTicks()
// This enables and disables the processing of the once-per-second ticks. This
// should be turned off ('enable' = FALSE) by _TPM_Init and turned on ('enable'
// = TRUE) by TPM2_Startup() after all the initializations have completed.
void _plat__ACT_EnableTicks(int enable);

//***_plat__ACT_Initialize()
// This function initializes the ACT hardware and data structures
int _plat__ACT_Initialize(void);

#endif // _PLATFORM_FP_H_

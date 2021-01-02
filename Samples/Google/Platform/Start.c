// This module provides the platform specific entry and fail processing. The
// _plat__RunCommand() function is used to call to ExecuteCommand() in the TPM
// code. This function does whatever processing is necessary to set up the
// platform in anticipation of the call to the TPM including settup for error
// processing.
//
// The _plat__Fail() function is called when there is a failure in the TPM. The
// TPM code will have set the flag to indicate that the TPM is in failure mode.
// This call will then recursively call ExecuteCommand in order to build the
// failure mode response. When ExecuteCommand() returns to _plat__Fail(), the
// platform will do some platform specif operation to return to the environment
// in which the TPM is executing. For a simulator, setjmp/longjmp is used. For
// an OS, a system exit to the OS would be appropriate.

// TODO(joerichey): Document that this merges:
//  - RunCommand.c (_plat__RunCommand + _plat__Fail)
//  - Manufacture.c (TPM_Manufacture)
//  - Hash.c (_plat__SendHCRTM + _TPM_Hash_{Start,Data,End})
#include "Start.h"
#include "Platform.h"

#include <setjmp.h>

#include "ExecCommand_fp.h"
#include "Manufacture_fp.h"
#include "_TPM_Hash_Data_fp.h"
#include "_TPM_Hash_End_fp.h"
#include "_TPM_Hash_Start_fp.h"
#include "_TPM_Init_fp.h"

// Failure proccessing
static jmp_buf s_jumpBuffer;
_Noreturn void _plat__Fail(void) { longjmp(&s_jumpBuffer[0], 1); }

bool _plat__Manufacture(void) {
  if (setjmp(s_jumpBuffer) != 0) {
    return false;
  }
  if (_plat__NVEnable(0) != 0) {
    return false;
  }
  return TPM_Manufacture(1) == 0;
}

bool _plat__Reset(void) {
  _plat__Signal_PowerOn();
  _TPM_Init();
  return true;
}

bool _plat__SendRTM(uint32_t size, const uint8_t *data) {
  if (setjmp(s_jumpBuffer) != 0) {
    return false;
  }
  _TPM_Hash_Start();
  _TPM_Hash_Data(size, (uint8_t *)data);
  _TPM_Hash_End();
  return true;
}

void _plat__RunCommand(uint32_t requestSize, const uint8_t *request,
                       uint32_t *responseSize, uint8_t **response) {
  setjmp(s_jumpBuffer);
  ExecuteCommand(requestSize, (uint8_t *)request, responseSize, response);
}

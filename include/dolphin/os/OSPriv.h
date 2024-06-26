#ifndef _DOLPHIN_OSPRIV
#define _DOLPHIN_OSPRIV

#ifdef __cplusplus
extern "C" {
#endif

#include "dolphin/os.h"

__OSExceptionHandler __OSGetExceptionHandler(__OSException exception);
__OSExceptionHandler __OSSetExceptionHandler(__OSException exception, __OSExceptionHandler handler);
OSTime __OSGetSystemTime(void);
OSTime __OSTimeToSystemTime(OSTime);

#ifdef __cplusplus
};
#endif

#endif // _DOLPHIN_OSPRIV

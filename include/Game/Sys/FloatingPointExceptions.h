#ifndef _FLOATINGPOINTEXCEPTIONS_H_
#define _FLOATINGPOINTEXCEPTIONS_H_

#include "dolphin/os/OSContext.h"

void InstallFloatingPointExceptionHandler();
void FloatingPointErrorHandler(unsigned short, OSContext*, unsigned long, unsigned long);

#endif // _FLOATINGPOINTEXCEPTIONS_H_

#ifndef _CALLSTACKDUMPER_H_
#define _CALLSTACKDUMPER_H_

#include "dolphin/os/OSContext.h"

void InstallCallStackDumper();
void ErrorHandler(unsigned short, OSContext*, unsigned long, unsigned long);

#endif // _CALLSTACKDUMPER_H_

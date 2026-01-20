#ifndef _NLPRINT_H_
#define _NLPRINT_H_

#include "printf.h"

int nlVSNPrintf(char*, unsigned long, const char*, __va_list arg);
int nlSNPrintf(char*, unsigned long, const char*, ...);

#endif // _NLPRINT_H_

#ifndef _GLMEMORY_H_
#define _GLMEMORY_H_

#include "NL/glx/glxMemory.h"

void glResourceRelease(unsigned long long);
unsigned long long glResourceMark();
void* glFrameAlloc(unsigned long size, eGLMemory type);
void* glResourceAlloc(unsigned long size, eGLMemory type);

#endif // _GLMEMORY_H_

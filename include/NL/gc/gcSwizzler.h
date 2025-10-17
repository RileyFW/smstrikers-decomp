#ifndef _GCSWIZZLER_H_
#define _GCSWIZZLER_H_

#include "types.h"
#include "NL/glx/glxTexture.h"

u32 GCTextureSize(eGXTextureFormat, int, int, int, unsigned long);
void GCSwizzle(void*, const void*, unsigned short, unsigned short, eGXTextureFormat, bool);

#endif // _GCSWIZZLER_H_

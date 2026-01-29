#ifndef _GLTEXTURE_H_
#define _GLTEXTURE_H_

#include "types.h"

void glTextureReplace(unsigned long, const void*, unsigned long);
void glTextureAdd(unsigned long, const void*, unsigned long);
int glTextureGetNumBits(int);
u32 glTextureGetHeight();
u32 glTextureGetWidth();
bool glTextureLoad(unsigned long);

#endif // _GLTEXTURE_H_

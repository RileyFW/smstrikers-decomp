#ifndef _GLXDISPLAYLIST_H_
#define _GLXDISPLAYLIST_H_

#include "NL/gl/glUserData.h"

struct DisplayList
{
    /* 0x00 */ u32 magic;
    /* 0x04 */ void* list;
    /* 0x08 */ u32 size;
    /* 0x0C */ unsigned short* indices;
}; // total size: 0x10

DisplayList* dlMakeDisplayList(const glModelPacket*, bool);
u32 dlGetSize(unsigned long);
void* dlGetDisplayList(unsigned long);
bool dlIsDisplayList(unsigned long);
DisplayList* dlGetStruct(unsigned long);

#endif // _GLXDISPLAYLIST_H_

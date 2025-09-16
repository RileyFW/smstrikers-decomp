#ifndef _GLMODEL_H_
#define _GLMODEL_H_

#include "NL/gl/glUserData.h"

struct glModel
{
    /* 0x00 */ u32 numPackets;
    /* 0x04 */ u32 id;
    /* 0x08 */ u32 pad;
    /* 0x0C */ glModelPacket* packets;
}; // total size: 0x10

void* glModelDupArrayNoStreams(const glModel*, unsigned long, bool, bool);
glModel* glModelDupNoStreams(const glModel*, bool, bool);
glModel* glModelDup(const glModel*, bool);
void glModelPacketDup(const glModelPacket*, bool);

#endif // _GLMODEL_H_

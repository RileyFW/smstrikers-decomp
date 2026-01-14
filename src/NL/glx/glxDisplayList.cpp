#include "NL/glx/glxDisplayList.h"
#include "NL/gl/glMemory.h"
#include "NL/nlString.h"
#include "dolphin/os/OSCache.h"
#include "dolphin/PPCArch.h"

#define DISPLAY_LIST_HEADER 0xBA7EF00D

static unsigned char opcodes[6] = {
    0x90,
    0x98,
    0xA0,
    0x80,
    0xA8,
    0xB0,
};

struct DisplayListEx
{
    /* 0x00 */ u32 m_header;
    /* 0x04 */ void* m_displayList;
    /* 0x08 */ u32 m_size;
    /* 0x0C */ u16 m_numStreams;
    /* 0x0E */ u16 m_hasColorStream;
};

/**
 * Offset/Address/Size: 0x0 | 0x801C1E5C | size: 0x2A8
 * TODO: 82.35% match - inner loops use addic./bne instead of bdnz ...
 */
DisplayList* dlMakeDisplayList(const glModelPacket* packet, bool permanent)
{
    u32 dlSize;
    u32 allocSize;
    u8 hasColorStream;
    u8* displayList;

    u8 numStreams = packet->numStreams;
    hasColorStream = 0;
    u8* streams = (u8*)packet->streams;
    s32 offset = 0;

    // Check for color stream (id 0x0C)
    u32 i;
    for (i = numStreams; i > 0; i--)
    {
        s32 idx = offset + 4;
        if (streams[idx] == 0x0C)
        {
            hasColorStream = 1;
            break;
        }
        offset += 6;
    }

    // Calculate display list size
    if (hasColorStream)
    {
        u16 numVerts = packet->numVertices;
        s32 factor = (numStreams - 1) << 1;
        u32 product = numVerts * factor;
        dlSize = product + 3;
        dlSize = dlSize + numVerts;
    }
    else
    {
        u16 numVerts = packet->numVertices;
        dlSize = numVerts * (numStreams << 1) + 3;
    }

    // Align to 32 bytes
    allocSize = (dlSize + 0x1F) & ~0x1F;

    // Allocate display list buffer
    if (permanent)
    {
        displayList = (u8*)glResourceAlloc(allocSize, GLM_VertexData);
    }
    else
    {
        displayList = (u8*)glFrameAlloc(allocSize, GLM_VertexData);
    }

    // Zero padding
    nlZeroMemory(displayList + dlSize, allocSize - dlSize);

    // Write GX display list header
    u8 primType = packet->primType;
    u16 nv = packet->numVertices;
    u8* dst = displayList + 3;
    u8 opcode = opcodes[primType];
    u8 hasCol = hasColorStream;
    u16* indexBuf = (u16*)packet->indexBuffer;
    u32 vertIdx = 0;
    displayList[0] = opcode;
    u16 numV = packet->numVertices;
    *(u16*)(displayList + 1) = nv;

    // Write vertex indices for each vertex
    while (vertIdx < numV)
    {
        u32 n, unroll;

        if (hasCol)
        {
            // Color stream present - write 0xFF marker, then indices for other streams
            u8 ns = packet->numStreams;
            *dst++ = 0xFF;
            n = ns - 1;
            if (n > 0)
            {
                unroll = n >> 3;
                if (unroll > 0)
                {
                    do
                    {
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                    } while (--unroll);
                    n &= 7;
                    if (n == 0)
                        goto next;
                }
                do
                {
                    *(u16*)dst = *indexBuf;
                    dst += 2;
                } while (--n);
            }
        }
        else
        {
            // No color stream - write indices for all streams
            u8 ns = packet->numStreams;
            n = ns;
            if (n > 0)
            {
                unroll = n >> 3;
                if (unroll > 0)
                {
                    do
                    {
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                        *(u16*)dst = *indexBuf;
                        dst += 2;
                    } while (--unroll);
                    n &= 7;
                    if (n == 0)
                        goto next;
                }
                do
                {
                    *(u16*)dst = *indexBuf;
                    dst += 2;
                } while (--n);
            }
        }
    next:
        vertIdx++;
        indexBuf++;
    }

    // Allocate and fill DisplayList structure
    DisplayList* result;
    if (permanent)
    {
        result = (DisplayList*)glResourceAlloc(0x10, GLM_Header);
    }
    else
    {
        result = (DisplayList*)glFrameAlloc(0x10, GLM_Header);
    }

    result->magic = DISPLAY_LIST_HEADER;
    result->list = displayList;
    result->size = allocSize;
    ((u16*)&result->indices)[0] = packet->numStreams;
    ((u16*)&result->indices)[1] = ((u32)(-hasColorStream | hasColorStream) >> 0x1F);

    // Flush display list to main memory
    DCFlushRangeNoSync(result->list, result->size);
    PPCSync();

    return result;
}

/**
 * Offset/Address/Size: 0x2A8 | 0x801C2104 | size: 0x30
 */
u32 dlGetSize(unsigned long addr)
{
    DisplayList* dl = (DisplayList*)addr;

    if (dl == NULL)
    {
        dl = NULL;
    }
    else
    {
        dl = (dl->magic == DISPLAY_LIST_HEADER) ? dl : NULL;
    }

    return dl->size;
}

/**
 * Offset/Address/Size: 0x2D8 | 0x801C2134 | size: 0x30
 */
void* dlGetDisplayList(unsigned long addr)
{
    DisplayList* dl = (DisplayList*)addr;

    if (dl == NULL)
    {
        dl = NULL;
    }
    else
    {
        dl = (dl->magic == DISPLAY_LIST_HEADER) ? dl : NULL;
    }

    return dl->list;
}

/**
 * Offset/Address/Size: 0x308 | 0x801C2164 | size: 0x38
 */
bool dlIsDisplayList(unsigned long addr)
{
    DisplayList* dl = (DisplayList*)addr;

    if (dl == NULL)
    {
        dl = NULL;
    }
    else
    {
        dl = (dl->magic == DISPLAY_LIST_HEADER) ? dl : NULL;
    }

    return dl != NULL;
}

/**
 * Offset/Address/Size: 0x340 | 0x801C219C | size: 0x28
 */
DisplayList* dlGetStruct(unsigned long addr)
{
    DisplayList* dl = (DisplayList*)addr;

    if (dl == NULL)
    {
        return NULL;
    }

    if (dl->magic != DISPLAY_LIST_HEADER)
    {
        return NULL;
    }

    return dl;
}

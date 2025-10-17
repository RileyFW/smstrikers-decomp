#include "Dolphin/types.h"
#include "NL/nlMemory.h"
#include "NL/glx/glxMemory.h"
#include "NL/gl/glMatrix.h"
#include "NL/gl/glConstant.h"
#include "NL/nlDebug.h"
#include "Dolphin/os.h"
#include "Game/Sys/debug.h"
#include "Game/GL/GLInventory.h"

bool glx_MemoryDump;
u32 ResourceMemSize;
u32 FrameMemSizeReal;
u32 FrameMemSizeVirt;
u32 p_phys;
u32 n_phys;
u32 i_frame;
u32 glx_mem0;
u32 g_uResourceMarker = 0;

u32 p_frame[4];
u32 n_frame[4];
u32 FrameMemSizes[2] = { FrameMemSizeReal = 0xE00000, FrameMemSizeVirt = 0xA00000 }; // Add this line
GLXMemoryInfo g_uResourceAlloc[16];

GLInventory glInventory;

const char* szMemoryNames[] = {
    "header",
    "matrix",
    "index",
    "vert",
    "tex",
    "target"
};

/**
 * Offset/Address/Size: 0x0 | 0x801B6928 | size: 0x20
 */
void glplatSetMatrix(unsigned long addr, const nlMatrix4& matrix)
{
    GLMatrix* matrixPtr = (GLMatrix*)addr;
    matrixPtr->Set(matrix);
}

/**
 * Offset/Address/Size: 0x20 | 0x801B6948 | size: 0x20
 */
void glplatGetMatrix(unsigned long addr, nlMatrix4& matrix)
{
    GLMatrix* matrixPtr = (GLMatrix*)addr;
    matrixPtr->Get(matrix);
}

/**
 * Offset/Address/Size: 0x40 | 0x801B6968 | size: 0x100
 */
void glplatFrameAllocNextFrame()
{
}

/**
 * Offset/Address/Size: 0x140 | 0x801B6A68 | size: 0xC0
 */
u32 glplatFrameAlloc(unsigned long, eGLMemory)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x200 | 0x801B6B28 | size: 0x110
 */
void glplatResourceRelease(unsigned long long resourceId)
{
}

/**
 * Offset/Address/Size: 0x310 | 0x801B6C38 | size: 0x130
 */
void glplatResourceMark()
{
}

/**
 * Offset/Address/Size: 0x440 | 0x801B6D68 | size: 0xB4
 */
unsigned long glplatResourceAlloc(unsigned long arg0, eGLMemory arg1)
{
    s32 temp_r30;
    s32 temp_r3;
    u32* temp_r5;

    temp_r30 = (p_phys + (n_phys + 0x1F)) & 0xFFFFFFE0;
    temp_r3 = arg0 + (temp_r30 - p_phys);
    n_phys = temp_r3;
    if (temp_r3 > ResourceMemSize)
    {
        OSReport("out of resource memory (%s)\n", szMemoryNames[arg1]);
        nlBreak();
    }
    temp_r5 = (u32*)&g_uResourceAlloc[g_uResourceMarker];
    temp_r5[temp_r3] = temp_r5[temp_r3] + arg0;
    return temp_r30;
}

/**
 * Offset/Address/Size: 0x4F4 | 0x801B6E1C | size: 0x3F0
 */
bool glxInitMemory()
{
    return true;
}

/**
 * Offset/Address/Size: 0x8E4 | 0x801B720C | size: 0x4
 */
void glx_FreeMemory1(const char*)
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0x8E8 | 0x801B7210 | size: 0x14
 */
void glx_FreeMemory0()
{
    glx_mem0 = ResourceMemSize - n_phys;
}

/**
 * Offset/Address/Size: 0x8FC | 0x801B7224 | size: 0x10
 */
u32 glx_GetFreeMemory()
{
    return ResourceMemSize - n_phys;
}

/**
 * Offset/Address/Size: 0x90C | 0x801B7234 | size: 0x24
 */
GLXMemoryInfo::GLXMemoryInfo()
{
    for (int i = 0; i < 6; i++)
    {
        m_uBytes[i] = 0;
    }
    m_uTexBundle = 0;
}

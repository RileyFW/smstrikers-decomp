#include "dolphin/types.h"
#include "NL/nlMemory.h"
#include "NL/glx/glxMemory.h"
#include "NL/glx/glxTexture.h"
#include "NL/gl/glMatrix.h"
#include "NL/gl/glConstant.h"
#include "NL/nlDebug.h"
#include "dolphin/os.h"
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
u32 glplatFrameAlloc(unsigned long size, eGLMemory mem)
{
    u32 isLow;
    switch (mem)
    {
    case GLM_Header:
    case GLM_Matrix:
    case GLM_IndexData:
        isLow = 1;
        break;
    default:
        isLow = 0;
        break;
    }

    u32(*nf)[2] = (u32(*)[2])n_frame;
    u32(*pf)[2] = (u32(*)[2])p_frame;
    u32 out;
    u32 n = nf[i_frame][isLow];
    u32 p = pf[i_frame][isLow];
    u32 sum = p + n + 0x1F;
    out = sum & ~0x1F;
    u32 next = size + (out - p);

    if (next > FrameMemSizes[isLow])
    {
        OSReport("out of frame memory (%s)\n", szMemoryNames[mem]);
        nlBreak();
        out = 0;
    }
    else
    {
        nf[i_frame][isLow] = next;
    }

    return out;
}

/**
 * Offset/Address/Size: 0x200 | 0x801B6B28 | size: 0x110
 * TODO: 87.1% match - loop uses addic./bne instead of mtctr/bdnz (CTR loop),
 * causing register allocation differences (r8 vs r4 accumulator) and loop setup reordering
 */
void glplatResourceRelease(unsigned long long resourceId)
{
    int level = (int)(resourceId & 0xFFFFFFFF);

    n_phys = (u32)(resourceId >> 32);

    glx_BackupTexMarkerLevel(level);
    gl_ConstantMarkerBackup(level);
    glInventory.ResourceRelease(level);

    while ((s32)g_uResourceMarker != level)
    {
        g_uResourceMarker--;
    }

    u32 totalAlloc = 0;
    u32 totalTex = 0;
    s32 n = g_uResourceMarker;
    s32 count = n + 1;
    GLXMemoryInfo* p = g_uResourceAlloc;
    if (n >= 0)
    {
        do
        {
            u32 a = p->m_uBytes[0];
            u32 b = p->m_uBytes[1];
            u32 c = p->m_uBytes[2];
            a = a + b;
            b = p->m_uBytes[3];
            a = a + c;
            u32 e = p->m_uBytes[4];
            a = a + b;
            u32 g = p->m_uTexBundle;
            u32 f = p->m_uBytes[5];
            a = a + e;
            u32 tex = e - g;
            p++;
            a = a + f;
            totalAlloc = totalAlloc + a;
            totalTex = totalTex + tex;
        } while (--count != 0);
    }

    f32 fConst = 1.0f / 1024.0f;
    f32 fMB = (f32)totalAlloc * fConst;
    tDebugPrintManager::Print(DC_GLPLAT, "res release: %dK tex %dK (%.2fM)\n", totalAlloc >> 10, totalTex >> 10, fMB * fConst);
}

/**
 * Offset/Address/Size: 0x310 | 0x801B6C38 | size: 0x130
 */
unsigned long long glplatResourceMark()
{
    return 0;
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

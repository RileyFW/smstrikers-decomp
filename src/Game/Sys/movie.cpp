#include "Game/Sys/movie.h"

extern "C" {
void GXSetDrawDone(void);
void GXFlush(void);
void GXWaitDrawDone(void);
void GXInvalidateTexAll(void);
int THPSimpleDecode(int);
void THPSimpleAudioStart(void);
}
void nlServiceFileSystem(void);
void* glx_GetSharedMemory(void);
void glx_LockSharedMemory(void);

static bool g_bMovieMustStop;
static bool start;
static unsigned char* buffer;
static PlatTexture* pTex[4];

/**
 * Offset/Address/Size: 0x28C | 0x801CBA48 | size: 0x4F0
 */
void MovieStart(const char*, bool, bool)
{
}

/**
 * Offset/Address/Size: 0x124 | 0x801CB8E0 | size: 0x168
 */
void MovieStop()
{
}

/**
 * Offset/Address/Size: 0x3C | 0x801CB7F8 | size: 0xE8
 */
bool MoviePlay()
{
    if (!g_bActive) {
        return false;
    }

    if (start) {
        if (buffer == (unsigned char*)glx_GetSharedMemory()) {
            glx_LockSharedMemory();
        }
    }

    if (g_bMovieMustStop) {
        return false;
    }

    GXSetDrawDone();
    GXFlush();
    nlServiceFileSystem();
    OSYieldThread();
    GXWaitDrawDone();

    int error = THPSimpleDecode(0);
    if (error == 1 || error == 2) {
        return false;
    }

    GXInvalidateTexAll();
    pTex[0]->Prepare();
    pTex[1]->Prepare();
    pTex[2]->Prepare();

    if (start) {
        THPSimpleAudioStart();
        start = false;
    }

    return true;
}

/**
 * Offset/Address/Size: 0x0 | 0x801CB7BC | size: 0x3C
 */
bool IsMoviePlayingInStrikers101()
{
    return false;
}

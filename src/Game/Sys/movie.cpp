#include "Game/Sys/movie.h"
#include "Game/Audio/AudioLoader.h"
#include "Game/Audio/StreamTrack.h"
#include "Game/Sys/debug.h"
#include "NL/glx/glxTarget.h"
#include "NL/glx/glxTexture.h"
#include "NL/nlMemory.h"
#include "NL/nlString.h"
#include "NL/gl/glMemory.h"

extern "C"
{
    void GXSetDrawDone(void);
    void GXFlush(void);
    void GXWaitDrawDone(void);
    void GXInvalidateTexAll(void);
    int THPSimpleDecode(int);
    void THPSimpleAudioStart(void);
    int THPSimpleGetTotalFrame(void);
    int THPSimpleGetCurrentFrame(void);
    void THPSimpleAudioStop(void);
    void THPSimpleLoadStop(void);
    void THPSimpleClose(void);
    void THPSimpleQuit(void);
}
void nlServiceFileSystem(void);

static bool g_bMovieMustStop;
static bool start;
static unsigned char* buffer;
static PlatTexture* pTex[4];
static unsigned long long resourceMarker;
static bool bMustFreeBuffer;
static void* g_GrabTextureData;
static unsigned long g_GrabTextureSize;
static unsigned long GrabTextureHandle;

/**
 * Offset/Address/Size: 0x28C | 0x801CBA48 | size: 0x4F0
 */
void MovieStart(const char*, bool, bool)
{
}

/**
 * Offset/Address/Size: 0x124 | 0x801CB8E0 | size: 0x168
 */
bool MovieStop()
{
    if (!g_bActive)
    {
        return false;
    }

    if (glx_GetSharedLock())
    {
        glx_UnlockSharedMemory();
    }

    int lastFrame = THPSimpleGetTotalFrame() - 1;
    int currentFrame = (int)(unsigned int)THPSimpleGetCurrentFrame();
    if ((unsigned int)currentFrame != (unsigned int)lastFrame)
    {
        tDebugPrintManager::Print(DC_RENDER, "MOVIE did not finish playback.\n");
    }

    THPSimpleAudioStop();
    THPSimpleLoadStop();
    THPSimpleClose();
    THPSimpleQuit();

    if (bMustFreeBuffer && buffer != NULL)
    {
        nlFree(buffer);
    }

    buffer = NULL;
    pTex[0] = NULL;
    pTex[1] = NULL;
    pTex[2] = NULL;
    pTex[3] = NULL;

    glResourceRelease(resourceMarker);

    if (nlTaskManager::m_pInstance->m_CurrState != 4)
    {
        if (GameInfoManager::GetInstance()->mIsInStrikers101Mode)
        {
            AudioStreamTrack::TrackManagerBase* trackMgr = g_pTrackManager;
            AudioStreamTrack::StreamTrack* track = trackMgr->GetTrack(nlStringLowerHash("Announcer"));
            track->Resume();
        }
    }

    if (g_GrabTextureData != NULL)
    {
        PlatTexture* tex = glx_GetTex(GrabTextureHandle, true, true);
        memcpy(tex->m_SwizzledData, g_GrabTextureData, g_GrabTextureSize);
        tex->Prepare();
        nlVirtualFree(g_GrabTextureData);
        g_GrabTextureData = NULL;
    }

    g_bActive = false;
    return true;
}

/**
 * Offset/Address/Size: 0x3C | 0x801CB7F8 | size: 0xE8
 */
bool MoviePlay()
{
    if (!g_bActive)
    {
        return false;
    }

    if (start)
    {
        if (buffer == (unsigned char*)glx_GetSharedMemory())
        {
            glx_LockSharedMemory();
        }
    }

    if (g_bMovieMustStop)
    {
        return false;
    }

    GXSetDrawDone();
    GXFlush();
    nlServiceFileSystem();
    OSYieldThread();
    GXWaitDrawDone();

    int error = THPSimpleDecode(0);
    if (error == 1 || error == 2)
    {
        return false;
    }

    GXInvalidateTexAll();
    pTex[0]->Prepare();
    pTex[1]->Prepare();
    pTex[2]->Prepare();

    if (start)
    {
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
    if (nlTaskManager::m_pInstance->m_CurrState != 4
        && nlSingleton<GameInfoManager>::s_pInstance->mIsInStrikers101Mode
        && g_bActive)
    {
        return true;
    }
    return false;
}

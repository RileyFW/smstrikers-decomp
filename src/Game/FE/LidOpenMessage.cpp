#include "Game/FE/LidOpenMessage.h"
#include "types.h"
#include "Game/Audio/AudioLoader.h"
#include "Game/Audio/AudioStream.h"
#include "Game/Audio/CrowdMood.h"
#include "Game/Game.h"
#include "Game/ResetTask.h"
#include "Game/TransitionTask.h"
#include "Game/Sys/movie.h"
#include "NL/nlFileGC.h"
#include "NL/nlString.h"
#include "NL/nlTask.h"

extern int g_Language;

struct LoadingTextEntry
{
    int x;
    int y;
    unsigned long param;
    const unsigned char* text;
};

extern LoadingTextEntry LOADING_TEXT_DATA[];

static int lastImageWidth;
static int lastImageHeight;
static int lastImageSize;
static const unsigned char* lastImageData;
static u8 ResetWasPaused;
static bool CanGetResetPauseState;
static int OpenCloseRefCount;

extern "C"
{
    void GXDrawDone(void);
    void GXFlush(void);
    void GXCopyDisp(void*, unsigned char);
    void GXPokeColorUpdate(unsigned char);
    void GXPokeBlendMode(int, int, int, int);
    void GXPokeARGB(unsigned short, unsigned short, unsigned long);
    void VIWaitForRetrace(void);
    void VISetBlack(unsigned char);
    void VIFlush(void);
    void VISetNextFrameBuffer(void*);
}

void* glxGetDisplayedBuffer();
void* glxGetBackBuffer();
void glx_ClearXFB(void*);

static inline void UncompressLidMessage(const unsigned char* compressed, int compressedSize, unsigned char* uncompressed)
{
    int index = 0;
    int i = 0;
    int k = 0;

    while (i < (compressedSize - 1))
    {
        unsigned char value = compressed[i];
        if (value == 0)
        {
            int run = 0;
            unsigned char* dst = uncompressed + index;
            while (run < compressed[i + 1])
            {
                *dst = (unsigned char)k;
                index++;
                dst++;
                run++;
            }
            i++;
        }
        else
        {
            uncompressed[index] = value;
            index++;
        }
        i++;
    }

    uncompressed[index] = compressed[compressedSize - 1];
}

/**
 * Offset/Address/Size: 0x624 | 0x80094540 | size: 0x26C
 * TODO: 96.81% match - arg0 register r18 vs r21, expanded r20 vs r26,
 * pass/xStart/xEnd shifted by 7 registers, missing addi r10,r4,1 and mr r19,r5.
 * Likely -inline deferred register allocation difference.
 */
void DisplayMessage(int arg0, int arg1, const unsigned char* arg2, int arg3, unsigned long arg4, bool arg5)
{
    unsigned int centeredFlag;
    int pass;
    int xStart;
    int xEnd;
    int yCenter;
    int yBottom;
    int rowBytes;
    void* fb;

    GXDrawDone();
    VIWaitForRetrace();
    VISetBlack(1);
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();

    lastImageWidth = arg0;
    lastImageHeight = arg1;
    lastImageData = arg2;
    lastImageSize = arg3;

    unsigned char* expanded = (unsigned char*)nlMalloc((unsigned long)((arg0 * arg1) / 8), 0x20, 1);

    UncompressLidMessage(arg2, arg3, expanded);

    GXPokeColorUpdate(1);
    GXPokeBlendMode(0, 1, 0, 0xF);

    xStart = (0x280 - arg0) / 2;
    centeredFlag = ((unsigned char)arg5 == 0);
    pass = 0;
    xEnd = xStart + arg0;
    yCenter = (0x1C0 - arg1) / 2;
    yBottom = 0x1A0 - arg1;
    rowBytes = arg0 / 8;

    while (pass < 4)
    {
        int yStart;
        int y;
        int yEnd;

        if ((pass == 0) || (pass == 2))
        {
            fb = glxGetDisplayedBuffer();
        }
        else
        {
            fb = glxGetBackBuffer();
        }

        glx_ClearXFB(fb);

        yStart = yBottom;
        if (centeredFlag != 0)
        {
            yStart = yCenter;
        }

        y = yStart;
        yEnd = yStart + arg1;
        while (y < yEnd)
        {
            int x = xStart;
            int rowOffset = rowBytes * (y - yStart);
            unsigned char* row = expanded + rowOffset;

            while (x < xEnd)
            {
                int pixel = x - xStart;
                if ((row[pixel / 8] & (1 << (pixel % 8))) != 0)
                {
                    GXPokeARGB((unsigned short)x, (unsigned short)y, arg4);
                }
                x++;
            }
            y++;
        }

        GXCopyDisp(fb, 1);
        GXDrawDone();
        GXFlush();
        pass++;
    }

    GXPokeColorUpdate(0);
    delete[] expanded;

    VIWaitForRetrace();
    VIWaitForRetrace();
    VISetBlack(0);
    VISetNextFrameBuffer(fb);
    VIFlush();
    VIWaitForRetrace();
}

/**
 * Offset/Address/Size: 0x278 | 0x80094194 | size: 0x3AC
 */
void DisplayDVDMessageSebring(int)
{
}

/**
 * Offset/Address/Size: 0x58 | 0x80093F74 | size: 0x220
 */
void DVDAllClearSebring(int)
{
    AudioStreamTrack::TrackManagerBase* trackMgr;

    DisplayMessage(lastImageWidth, lastImageHeight, lastImageData, lastImageSize, 0, false);

    while (nlAsyncReadsPending(NULL))
    {
        nlServiceFileSystem();
    }

    if (g_pGame != NULL)
    {
        TRANSITION_STATE transState = TransitionTask::sm_pGlobalTask != NULL
                                        ? TransitionTask::sm_pGlobalTask->m_TransitionState
                                        : eTS_Unknown;

        if (transState == eTS_InState)
        {
            if (nlTaskManager::m_pInstance->m_CurrState != 1)
            {
                PriorityStream* ps = Audio::GetPriorityStream();
                if (ps != NULL)
                {
                    if (IsMoviePlayingInStrikers101())
                    {
                        Audio::GetPriorityStream()->m_Track.Stop(0);
                    }
                    else
                    {
                        Audio::GetPriorityStream()->FakeResume(false);
                    }
                }
                CrowdMood::RestartLoops();
                CrowdMood::SetCrowdVolume(0x7F, 0);
            }
            else
            {
                if (!IsMoviePlayingInStrikers101())
                {
                    trackMgr = g_pTrackManager;
                    AudioStreamTrack::StreamTrack* track = trackMgr->GetTrack(nlStringLowerHash("sebring_music"));
                    if (track != NULL)
                    {
                        track->Resume();
                    }
                }
            }
        }
        else
        {
            trackMgr = g_pTrackManager;
            AudioStreamTrack::StreamTrack* track = trackMgr->GetTrack(nlStringLowerHash("music"));
            if (track != NULL)
            {
                track->Resume();
            }
            trackMgr = g_pTrackManager;
            track = trackMgr->GetTrack(nlStringLowerHash("crowd"));
            if (track != NULL)
            {
                track->Resume();
            }
        }
    }
    else
    {
        trackMgr = g_pTrackManager;
        if (trackMgr != NULL)
        {
            AudioStreamTrack::StreamTrack* track = trackMgr->GetTrack(nlStringLowerHash("music"));
            if (track != NULL)
            {
                track->Resume();
            }
            trackMgr = g_pTrackManager;
            track = trackMgr->GetTrack(nlStringLowerHash("crowd"));
            if (track != NULL)
            {
                track->Resume();
            }
        }
    }

    OpenCloseRefCount--;
    ResetTask::s_resetPaused = ResetWasPaused;
    CanGetResetPauseState = true;
    ResetTask::s_checkCardRemoved = false;
}

/**
 * Offset/Address/Size: 0x0 | 0x80093F1C | size: 0x58
 */
void DisplayLoadingMessageFast()
{
    int lang = g_Language;
    if (lang > 6)
    {
        lang = 0;
    }

    DisplayMessage(
        LOADING_TEXT_DATA[lang].x,
        LOADING_TEXT_DATA[lang].y,
        LOADING_TEXT_DATA[lang].text,
        LOADING_TEXT_DATA[lang].param,
        0xFFFFA800,
        true);
}

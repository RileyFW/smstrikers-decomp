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

/**
 * Offset/Address/Size: 0x624 | 0x80094540 | size: 0x26C
 */
void DisplayMessage(int, int, const unsigned char*, int, unsigned long, bool)
{
    FORCE_DONT_INLINE;
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

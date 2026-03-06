#include "Game/ReplayChoreo.h"
#include "Game/Camera/CameraMan.h"
#include "Game/Game.h"
#include "Game/Team.h"
#include "NL/nlTask.h"

struct GoalScoredDataExt
{
    GoalScoredData data;
    int sideOfInterest;
};

// /**
//  * Offset/Address/Size: 0xEC4 | 0x80129A38 | size: 0xD74
//  */
// void FormatImpl<BasicString<char, Detail::TempStringAllocator>>::operator%<const char*>(const char* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x150 | 0x80128CC4 | size: 0xD74
//  */
// void FormatImpl<BasicString<char, Detail::TempStringAllocator>>::operator%<int>(const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80128B74 | size: 0x150
//  */
// void Format<BasicString<char, Detail::TempStringAllocator>, const char*, const char*, const char*, int>(const BasicString<char, Detail::TempStringAllocator>&, const char* const&, const char* const&, const char* const&, const int&)
// {
// }

ReplayChoreo& ReplayChoreo::Instance()
{
    static ReplayChoreo instance;
    return instance;
}

/**
 * Offset/Address/Size: 0x0 | 0x801287C0 | size: 0x3B4
 */
void ReplayChoreo::DoFunctionCall(unsigned int)
{
}

// /**
//  * Offset/Address/Size: 0x34 | 0x80128764 | size: 0x5C
//  */
// ReplayCamera::~ReplayCamera()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80128730 | size: 0x34
//  */
// void ReplayChoreo::Highlight::Highlight()
// {
// }

/**
 * Offset/Address/Size: 0xCC8 | 0x80128334 | size: 0x314
 */
void ReplayChoreo::LoadScript()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0xA9C | 0x80128108 | size: 0x22C
 */
void ReplayChoreo::EventHandler(Event* event)
{
    if (!g_pGame)
        return;

    if (event->m_uEventID == 5)
    {
        GoalScoredDataExt* gsd;
        s32 id = event->m_data.GetID();
        if (id == -1)
        {
            nlPrintf("Error: Trying to get event data on event with none!\n");
            gsd = 0;
        }
        else
        {
            id = event->m_data.GetID();
            if (id != 0x18A)
            {
                nlPrintf("Error: GetData() failed! Data types do not match!\n");
                gsd = 0;
            }
            else
            {
                gsd = (GoalScoredDataExt*)&event->m_data;
            }
        }

        if (gsd != 0)
        {
            mGoalScoredData = gsd->data;
            mReplayPad = gsd->sideOfInterest;

            if ((mGoalScoredData.uGoalType == 6 || mGoalScoredData.uGoalType == 2) && mGoalScoredData.uIsHyper)
            {
                mGoalScoredData.uGoalType = 8;
            }

            mCamera.SetSideOfInterest((gsd->data.uTeamIndex + 1) % 2);
        }
    }

    if (event->m_uEventID == 0xF)
    {
        GoalieSaveData* gsd;
        s32 id = event->m_data.GetID();
        if (id == -1)
        {
            nlPrintf("Error: Trying to get event data on event with none!\n");
            gsd = 0;
        }
        else
        {
            id = event->m_data.GetID();
            if (id != 0x13C)
            {
                nlPrintf("Error: GetData() failed! Data types do not match!\n");
                gsd = 0;
            }
            else
            {
                gsd = (GoalieSaveData*)&event->m_data;
            }
        }

        if (gsd != 0)
        {
            if (gsd->isSTS)
                return;

            int teamSide = gsd->pGoalie->m_pTeam->m_nSide;
            mGoalScoredData.uTeamIndex = (teamSide + 1) % 2;
            mGoalScoredData.uGoalType = gsd->saveType;
            mGoalScoredData.pScorer = gsd->pShooter;
            mCamera.SetSideOfInterest(teamSide);
        }
    }
}

/**
 * Offset/Address/Size: 0xA78 | 0x801280E4 | size: 0x24
 */
void ReplayChoreo::Reset()
{
    cCameraManager::Remove(mCamera);
}

/**
 * Offset/Address/Size: 0x698 | 0x80127D04 | size: 0x3E0
 */
void ReplayChoreo::CalcAutoReplayScriptName(ReplayType) const
{
}

/**
 * Offset/Address/Size: 0x428 | 0x80127A94 | size: 0x270
 */
void ReplayChoreo::StartAutoReplay(ReplayType)
{
}

/**
 * Offset/Address/Size: 0x408 | 0x80127A74 | size: 0x20
 */
void ReplayChoreo::FlushHighlights()
{
    mHighlightIndex = -1;
    mNumHighlights = 0;
    mHighlights[0].mSideOfInterest = 0;
    mHighlights[1].mSideOfInterest = 0;
    mHighlights[2].mSideOfInterest = 0;
}

/**
 * Offset/Address/Size: 0x390 | 0x801279FC | size: 0x78
 */
void ReplayChoreo::Update(float dt)
{
    if (nlTaskManager::m_pInstance->m_CurrState == 0x10)
    {
        if (mRunningFor)
        {
            mRunForTimeLeft -= dt;
        }
        Run();
        mCamera.ManualUpdate(dt);
    }
}

/**
 * Offset/Address/Size: 0x344 | 0x801279B0 | size: 0x4C
 */
bool ReplayChoreo::Done() const
{
    bool result = false;
    if (IsFinished())
    {
        if (nlTaskManager::m_pInstance->m_CurrState == 0x10)
        {
            result = true;
        }
    }
    return result;
}

/**
 * Offset/Address/Size: 0x108 | 0x80127774 | size: 0x23C
 */
void ReplayChoreo::SaveHighlight(ReplayChoreo::HighlightQuality)
{
}

/**
 * Offset/Address/Size: 0x8C | 0x801276F8 | size: 0x7C
 */
int ReplayChoreo::NumHighlights() const
{
    ReplayChoreo* self = const_cast<ReplayChoreo*>(this);
    self->mReplayManager = ReplayManager::Instance();
    int count = 0;
    self->mReplay = mReplayManager->mReplay;
    for (int i = 0; i < 3; i++)
    {
        if (mReplay->IsReelValid(i + 1))
        {
            count++;
        }
    }
    return count;
}

/**
 * Offset/Address/Size: 0x0 | 0x8012766C | size: 0x8C
 */
ReplayChoreo::~ReplayChoreo()
{
}

#include "Game/Debug/TimeRegions.h"

#include "Game/BasicStadium.h"
#include "NL/nlTask.h"
#include "Game/Ball.h"

#include "Game/Debug/FrameCounter.h"
#include "NL/nlPrint.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x801627A8 | size: 0x2C
//  */
// void nlListAddEnd<ListEntry<TimeRegion*>>(ListEntry<TimeRegion*>**, ListEntry<TimeRegion*>**, ListEntry<TimeRegion*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801626A8 | size: 0x100
//  */
// TimeRegion::~TimeRegion()
// {
// }

/**
 * Offset/Address/Size: 0x838 | 0x80162658 | size: 0x50
 */
void WriteFrameRateStatsToFile()
{
    char buffer[0x78];
    BasicStadium* stadium = BasicStadium::GetCurrentStadium();
    nlSNPrintf(buffer, sizeof(buffer), "\n\nStats collected in %s\n", stadium->m_szBaseName);
    g_FrameCounter.WriteFrameRateStatsToFile(buffer);
}

/**
 * Offset/Address/Size: 0x820 | 0x80162640 | size: 0x18
 */
bool IsDuringGameplay()
{
    return (nlTaskManager::m_pInstance->m_CurrState == 0x2);
}

/**
 * Offset/Address/Size: 0x7B8 | 0x801625D8 | size: 0x68
 */
void CentreOfField()
{
}

/**
 * Offset/Address/Size: 0x6DC | 0x801624FC | size: 0xDC
 */
void LeftSideOfField()
{
}

/**
 * Offset/Address/Size: 0x600 | 0x80162420 | size: 0xDC
 */
void RightSideOfField()
{
}

/**
 * Offset/Address/Size: 0x5E8 | 0x80162408 | size: 0x18
 */
bool IsDuringNIS()
{
    return (nlTaskManager::m_pInstance->m_CurrState == 0x100);
}

/**
 * Offset/Address/Size: 0x5D0 | 0x801623F0 | size: 0x18
 */
bool IsDuringAutoreplay()
{
    return (nlTaskManager::m_pInstance->m_CurrState == 0x10);
}

/**
 * Offset/Address/Size: 0x598 | 0x801623B8 | size: 0x38
 */
bool IsBowserAround()
{
    return (BasicStadium::GetCurrentStadium()->mpNPCManager->mpBowser->meBowserState != BOWSER_STATE_HIDDEN);
}

/**
 * Offset/Address/Size: 0x580 | 0x801623A0 | size: 0x18
 */
bool IsShotInProgress()
{
    return (g_pBall->m_tShotTimer.m_uPackedTime != 0);
}

/**
 * Offset/Address/Size: 0x11C | 0x80161F3C | size: 0x464
 */
void InitializeTimeRegions()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80161E20 | size: 0x11C
 */
void DestroyTimeRegions()
{
}

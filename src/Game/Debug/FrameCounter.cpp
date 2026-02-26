#include "Game/Debug/FrameCounter.h"
#include "Game/Debug/TimeRegions.h"

#include "NL/nlDebugFile.h"
#include "NL/nlMemory.h"
#include "NL/nlPrint.h"
#include "NL/nlTicker.h"

int FrameCounter::NUM_FRAMES_TO_AVERAGE_OVER = 0x1E;

// /**
//  * Offset/Address/Size: 0x0 | 0x801FE0D4 | size: 0x68
//  */
// void nlWalkList<ListEntry<TimeRegion*>, ListContainerBase<TimeRegion*, NewAdapter<ListEntry<TimeRegion*> > > >(ListEntry<TimeRegion*>*, ListContainerBase<TimeRegion*, NewAdapter<ListEntry<TimeRegion*> > >*, void (ListContainerBase<TimeRegion*, NewAdapter<ListEntry<TimeRegion*> > >::*)(ListEntry<TimeRegion*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x801FE048 | size: 0x8C
//  */
// void nlListContainer<TimeRegion*>::~nlListContainer()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801FDF8C | size: 0x24
//  */
// void ListContainerBase<TimeRegion*, NewAdapter<ListEntry<TimeRegion*> > >::DeleteEntry(ListEntry<TimeRegion*>*)
// {
// }

/**
 * Offset/Address/Size: 0x1374 | 0x801FDF10 | size: 0x7C
 */
FrameCounter::FrameCounter(const char* firstName, const char* secondName)
{
    m_FirstName = firstName;
    m_SecondName = secondName;

    unk30 = 0;
    unk28 = 0;
    unk34 = 0;
    m_ContinuousFrameHistoryIndex = 0;

    m_CurrTimer[0] = 0.0f;
    m_CurrTimer[1] = 0.0f;

    m_CurrTimerNum = -1;

    memset(m_FrameHistory, 0, 0xA00);
    memset(m_ContinuousFrameHistory, 0, 0x640);
}

/**
 * Offset/Address/Size: 0x12F8 | 0x801FDE94 | size: 0x7C
 */
void FrameCounter::StartTimer(int timerNum)
{
    u32 currentTick = nlGetTicker();

    if (m_CurrTimerNum != -1)
    {
        m_CurrTimer[m_CurrTimerNum] += nlGetTickerDifference(m_StartTick, currentTick);
    }

    m_StartTick = currentTick;
    m_CurrTimerNum = timerNum;
}

/**
 * Offset/Address/Size: 0x1078 | 0x801FDC14 | size: 0x280
 */
void FrameCounter::FinishTiming()
{
}

/**
 * Offset/Address/Size: 0xED8 | 0x801FDA74 | size: 0x1A0
 */
void FrameCounter::WriteFrameRateStatsToFile(const char* fileName)
{
    char buf[128];
    void* file = nlOpenFileDebug("framerate_stats.txt", false, true);
    nlWriteLineDebug(file, fileName, false);
    nlWriteLineDebug(file, "========================================", false);
    nlWriteLineDebug(file, "Region                          AvgTime     Percentage", false);
    nlWriteLineDebug(file, "------                          -------     ----------", false);
    nlWriteLineDebug(file, "==========================================", false);

    ListEntry<TimeRegion*>* entry = TimeRegion::sTimeRegionList.m_Head;
    while (entry != NULL)
    {
        TimeRegion* region = entry->data;
        float ratio = (float)region->m_unk10 / (float)region->m_unk14;
        float avgTime = region->m_fThreshold / (float)region->m_unk14;
        float pct = 100.0f * (1.0f - ratio);

        nlSNPrintf(buf, 128, "  %-30s  %8.2f  %8.2f%%\n", region->m_unk14, region->m_pName, pct, avgTime);
        nlWriteLineDebug(file, buf, false);

        entry = entry->next;
    }

    nlCloseFileDebug(file);
}

/**
 * Offset/Address/Size: 0xC5C | 0x801FD7F8 | size: 0x27C
 */
void DrawCircle(nlVector3, float, float, nlColour)
{
}

/**
 * Offset/Address/Size: 0x904 | 0x801FD4A0 | size: 0x358
 */
void DrawSmile(nlVector3, float, float, nlColour, float)
{
}

/**
 * Offset/Address/Size: 0x588 | 0x801FD124 | size: 0x37C
 */
void DrawBrow(const nlVector3&, const nlVector3&, float, float, float)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801FCB9C | size: 0x588
 */
void FrameCounter::DisplayFrameSmiler()
{
}

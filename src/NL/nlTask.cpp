#include "NL/nlTask.h"
#include "NL/nlMemory.h"
#include "NL/nlTicker.h"
#include "NL/nlDLRing.h"

#define assert(condition) ((condition) ? ((void)0) : ((void)0))

u8 g_StackWatermarkFiller = 0x78;
float g_fTaskTimeUpperBound = 0.1f;

nlTaskManager* nlTaskManager::m_pInstance = nullptr;
u8 g_DoStackWatermarkTests;
float g_fTaskTimeLowerBound;

/**
 * Offset/Address/Size: 0x0 | 0x801D28FC | size: 0xC
 */
void nlTaskManager::SetTimeDilation(float timeDilation)
{
    m_pInstance->m_timeDilation = timeDilation;
}

/**
 * Offset/Address/Size: 0xC | 0x801D2908 | size: 0xC
 */
void nlTaskManager::SetNextState(unsigned int nextState)
{
    m_pInstance->m_nextState = nextState;
}

/**
 * Offset/Address/Size: 0x18 | 0x801D2914 | size: 0x150
 */
void nlTaskManager::RunAllTasks()
{
    f32 tickerDifference;
    f32 deltaTime;
    f32 clampedDeltaTime;
    nlTask* currentTask;
    nlTask* taskIterator;
    s32 currentTicker;

    currentTask = nlDLRingGetStart<nlTask>(m_pInstance->m_taskRingHead);
    if (currentTask != NULL)
    {
        if ((u32)m_pInstance->m_CurrState != (u32)m_pInstance->m_nextState)
        {
        loop_2:
            currentTask->StateTransition(m_pInstance->m_CurrState, m_pInstance->m_nextState);
            if (nlDLRingIsEnd<nlTask>(m_pInstance->m_taskRingHead, currentTask) == 0)
            {
                currentTask = currentTask->m_next;
                goto loop_2;
            }
            m_pInstance->m_taskCount = (u32)m_pInstance->m_CurrState;
            m_pInstance->m_CurrState = (u32)m_pInstance->m_nextState;
        }

        taskIterator = nlDLRingGetStart<nlTask>(m_pInstance->m_taskRingHead);
    loop_6:
        currentTicker = nlGetTicker();
        tickerDifference = nlGetTickerDifference(taskIterator->m_unk_0x14, currentTicker);
        taskIterator->m_unk_0x14 = currentTicker;
        if (taskIterator->m_unk_0x10 & m_pInstance->m_CurrState)
        {
            clampedDeltaTime = tickerDifference / 1000.f;
            if (clampedDeltaTime < g_fTaskTimeLowerBound)
            {
                clampedDeltaTime = g_fTaskTimeLowerBound;
            }
            else if (clampedDeltaTime > g_fTaskTimeUpperBound)
            {
                clampedDeltaTime = g_fTaskTimeUpperBound;
            }
            deltaTime = clampedDeltaTime * m_pInstance->m_timeDilation;
            m_pInstance->m_unk_0x14 = deltaTime;
            taskIterator->Run(deltaTime);
        }
        if (taskIterator != m_pInstance->m_taskRingHead)
        {
            taskIterator = taskIterator->m_next;
            goto loop_6;
        }
    }
}

/**
 * Offset/Address/Size: 0x168 | 0x801D2A64 | size: 0xC4
 */
void nlTaskManager::AddTask(nlTask* arg0, unsigned int arg1, unsigned int arg2)
{
    arg0->m_unk_0x0C = arg1;
    arg0->m_unk_0x10 = arg2;
    arg0->m_unk_0x14 = nlGetTicker();

    if (m_pInstance->m_taskRingHead == nullptr)
    {
        nlDLRingAddStart<nlTask>(&m_pInstance->m_taskRingHead, arg0);
        return;
    }

    // Find the appropriate position to insert the task based on priority
    nlTask* currentTask = nlDLRingGetStart<nlTask>(m_pInstance->m_taskRingHead);
    while (currentTask != nullptr)
    {
        if (currentTask->m_unk_0x0C >= arg1)
        {
            currentTask = currentTask->m_prev;
            break;
        }
        else if (!nlDLRingIsEnd<nlTask>(m_pInstance->m_taskRingHead, currentTask))
        {
            currentTask = currentTask->m_next;
        }
        else
        {
            break;
        }
    }

    nlDLRingInsert<nlTask>(&m_pInstance->m_taskRingHead, currentTask, arg0);
}

/**
 * Offset/Address/Size: 0x22C | 0x801D2B28 | size: 0x74
 */
void nlTaskManager::Startup(unsigned int arg0)
{
    void* pData = nlMalloc(0x1C, 8, 0);
    pData = (pData) ? pData : pData; // just to produce "cmplwi r3, 0x0"
    m_pInstance = (nlTaskManager*)pData;
    m_pInstance->m_taskCount = arg0;
    m_pInstance->m_CurrState = arg0; // m_previousState ?
    m_pInstance->m_nextState = arg0;
    m_pInstance->m_taskRingHead = nullptr; // Initialize task ring head to null
    m_pInstance->m_timeDilation = 1.0f;
    m_pInstance->m_flags = 0;
}

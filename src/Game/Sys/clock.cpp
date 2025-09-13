#include "clock.h"
#include "NL/nlTask.h"

Clock* ClockManager::m_inactiveList = NULL;
Clock* ClockManager::m_activeList = NULL;
Clock* ClockManager::m_pendingActiveList = NULL;
bool ClockManager::m_bUpdatingClocks = false;

/**
 * Offset/Address/Size: 0x3D8 | 0x80212D90 | size: 0x4
 */
void ClockManager::Initialize()
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0x238 | 0x80212BF0 | size: 0x1A0
 */
void ClockManager::Update(float arg8)
{
    ClockCallback temp_r12;
    ClockCallback temp_r12_2;

    Clock* var_r31;
    Clock* temp_r30;

    if (m_activeList != NULL)
    {
        m_bUpdatingClocks = true;
        var_r31 = m_activeList->m_next;

    loop_2:
        temp_r30 = var_r31->m_next;
        if (((s32)var_r31->m_unk_0x18 == 3) || !(var_r31->m_unk_0x14 & nlTaskManager::m_pInstance->m_CurrState))
        {
            if (var_r31 != m_activeList)
            {
                var_r31 = temp_r30;
                goto loop_2;
            }
        }
        else
        {
            var_r31->m_unk_0x08 = (f32)((arg8 * var_r31->m_unk_0x04) + var_r31->m_unk_0x08);
            if (var_r31->m_unk_0x04 >= 0.f)
            {
                if (var_r31->m_unk_0x08 >= var_r31->m_unk_0x0C)
                {
                    var_r31->m_unk_0x18 = 2;
                    var_r31->m_unk_0x08 = (f32)var_r31->m_unk_0x0C;
                    temp_r12 = var_r31->m_callback;
                    if (temp_r12 != NULL)
                    {
                        temp_r12(var_r31->m_unk_0x1C, var_r31->m_unk_0x20);
                    }
                    nlDLRingRemove<Clock>(&m_activeList, var_r31);
                    nlDLRingAddEnd<Clock>(&m_inactiveList, var_r31);
                }
            }
            else
            {
                if (var_r31->m_unk_0x08 <= var_r31->m_unk_0x0C)
                {
                    var_r31->m_unk_0x18 = 2;
                    var_r31->m_unk_0x08 = (f32)var_r31->m_unk_0x0C;
                    temp_r12_2 = var_r31->m_callback;
                    if (temp_r12_2 != NULL)
                    {
                        temp_r12_2(var_r31->m_unk_0x1C, var_r31->m_unk_0x20);
                    }
                    nlDLRingRemove<Clock>(&m_activeList, var_r31);
                    nlDLRingAddEnd<Clock>(&m_inactiveList, var_r31);
                }
            }

            if ((var_r31 != m_activeList) && (m_activeList != NULL))
            {
                var_r31 = temp_r30;
                goto loop_2;
            }
        }
        m_bUpdatingClocks = 0;
        nlDLRingAppendRing<Clock>(&m_activeList, m_pendingActiveList);
        m_pendingActiveList = 0;
    }
}

/**
 * Offset/Address/Size: 0x1D8 | 0x80212B90 | size: 0x60
 */
Clock::Clock(float param_1, float param_2, float param_3, unsigned long param_4, ClockCallback callback)
{
    m_unk_0x04 = param_3;
    m_unk_0x08 = param_1;
    m_unk_0x0C = param_2;
    m_unk_0x18 = 0;
    m_callback = callback;
    m_unk_0x14 = param_4;
    nlDLRingAddEnd<Clock>(&ClockManager::m_inactiveList, this);
}

/**
 * Offset/Address/Size: 0x14C | 0x80212B04 | size: 0x8C
 */
Clock::~Clock()
{
    if ((nlDLRingRemoveSafely<Clock>(&ClockManager::m_activeList, this) == 0)
        && (nlDLRingRemoveSafely<Clock>(&ClockManager::m_pendingActiveList, this) == 0))
    {
        nlDLRingRemoveSafely<Clock>(&ClockManager::m_inactiveList, this);
    }
}

/**
 * Offset/Address/Size: 0xD8 | 0x80212A90 | size: 0x74
 */
void Clock::Reset(float param_1, float param_2, float param_3)
{
    m_unk_0x04 = param_3;
    m_unk_0x08 = param_1;
    m_unk_0x0C = param_2;

    if (m_unk_0x18 == 1)
    {
        if (nlDLRingRemoveSafely<Clock>(&ClockManager::m_activeList, this) == 0)
        {
            nlDLRingRemoveSafely<Clock>(&ClockManager::m_pendingActiveList, this);
        }
        nlDLRingAddEnd<Clock>(&ClockManager::m_inactiveList, this);
    }
    m_unk_0x18 = 0;
}

/**
 * Offset/Address/Size: 0x68 | 0x80212A20 | size: 0x70
 */
void Clock::Start()
{
    if (m_unk_0x18 != 1)
    {
        nlDLRingRemove<Clock>(&ClockManager::m_inactiveList, this);
        if (ClockManager::m_bUpdatingClocks != 0)
        {
            nlDLRingAddEnd<Clock>(&ClockManager::m_pendingActiveList, this);
        }
        else
        {
            nlDLRingAddEnd<Clock>(&ClockManager::m_activeList, this);
        }
    }
    m_unk_0x18 = 1;
}

/**
 * Offset/Address/Size: 0x0 | 0x802129B8 | size: 0x68
 */
void Clock::Stop()
{
    if (m_unk_0x18 == 1)
    {
        if (nlDLRingRemoveSafely<Clock>(&ClockManager::m_activeList, this) == 0)
        {
            nlDLRingRemoveSafely<Clock>(&ClockManager::m_pendingActiveList, this);
        }
        nlDLRingAddEnd<Clock>(&ClockManager::m_inactiveList, this);
    }
    m_unk_0x18 = 0;
}

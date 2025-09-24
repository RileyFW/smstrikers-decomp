#include "Game/Sys/eventman.h"

#include "NL/nlString.h"
#include "NL/nlDLRing.h"
#include "NL/nlMemory.h"

EventManager* g_pEventManager = 0;

/**
 * Offset/Address/Size: 0x488 | 0x801FAE08 | size: 0x94
 */
EventManager::~EventManager()
{
    if (m_pool)
    {
        delete (u32*)m_pool;
    }

    if (m_dest)
    {
        delete[] m_dest;
        m_dest = 0;
    }

    if (m_handlers)
    {
        nlDeleteDLRing(&m_handlers);
    }
}

/**
 * Offset/Address/Size: 0x370 | 0x801FACF0 | size: 0x118
 */
void EventManager::Create(unsigned long count, unsigned long size)
{
    EventManager* m = (EventManager*)nlMalloc(sizeof(EventManager), 8, false);
    if (m)
    {
        m->m_dispatching = 0;
        m->m_handlers = 0;
        m->m_free = 0;
        m->m_keep = 0;
        m->m_queue = 0;
        m->m_deferred = 0;
        m->m_dest = 0;
        m->m_pool = 0;
        m->m_count = count; // +0x20
        m->m_size = size;   // +0x24

        // Allocate pool: count * size
        u32 total = m->m_count * m->m_size;
        m->m_pool = nlMalloc(total, 8, false);

        nlPrintf("Event Manager: Allocating %d events of size %d. Total = %d bytes\n", m->m_count, m->m_size, total); // @342

        for (u32 i = 0; i < m->m_count; ++i)
        {
            char* base = (char*)m->m_pool + i * m->m_size;
            Event* e = (Event*)base;
            e->m_next = 0;
            e->m_prev = 0;
            e->m_nReferenceCount = 0;
            // EventData vptr is set by constructing the subobject; we only need it to be a valid base
            // The original TU writes the vptr slot; letting the compiler emit that via default ctor:
            new (&e->m_data) EventData();
            nlDLRingAddEnd(&m->m_free, e);
        }

        // Finish default destination setup
        m->SetupDestArray();
    }
    g_pEventManager = m;
}

/**
 * Offset/Address/Size: 0x30C | 0x801FAC8C | size: 0x64
 */
#pragma push
#pragma optimization_level 1
#pragma optimize_for_size on
EventHandler* EventManager::AddEventHandler(EventCallback callback, void* arg1, unsigned long arg2)
{
    EventHandler* temp_r3 = (EventHandler*)nlMalloc(0x14, 8, 0);
    temp_r3->callback = callback;
    temp_r3->mask = arg2;
    temp_r3->unkC = arg1;
    nlDLRingAddEnd<EventHandler>(&this->m_handlers, temp_r3);
    return temp_r3;
}
#pragma pop

/**
 * Offset/Address/Size: 0x2D4 | 0x801FAC54 | size: 0x38
 */
void EventManager::RemoveEventHandler(EventHandler* h)
{
    nlDLRingRemove<EventHandler>(&m_handlers, h);
    delete h;
}

/**
 * Offset/Address/Size: 0x1C4 | 0x801FAB44 | size: 0x110
 */
void EventManager::AllocateDestArray(unsigned long count, unsigned long maskDefault)
{
    m_dest = (u32*)nlMalloc(count * sizeof(u32), 8, false);
    for (u32 i = 0; i < count; ++i)
    {
        m_dest[i] = maskDefault;
    }
}

/**
 * Offset/Address/Size: 0xF4 | 0x801FAA74 | size: 0xD0
 */
Event* EventManager::CreateValidEvent(unsigned long eventID, unsigned long uSize)
{
    if (uSize > m_size)
    {
        nlPrintf("Event Manager: Size mismatch on event creation (%d vs %d)!\n", uSize, m_size); // @326
        return NULL;
    }

    Event* e;
    if (!m_free)
    {
        nlPrintf("Event Manager: There are no more free events in the free event list!\n"); // @293
        e = NULL;
    }
    else
    {
        e = nlDLRingRemoveStart(&m_free);
        if (m_dispatching)
        {
            nlDLRingAddEnd(&m_deferred, e);
        }
        else
        {
            nlDLRingAddEnd(&m_queue, e);
        }
    }

    if (!e)
    {
        return NULL;
    }

    e->m_uEventID = eventID; // stw at +0x08

    return e;
}

/**
 * Offset/Address/Size: 0x0 | 0x801FA980 | size: 0xF4
 */
void EventManager::DispatchEvents()
{
    m_dispatching = 1; // stb 1 at +0
    while (m_queue != 0)
    {
        Event* e = nlDLRingRemoveStart(&m_queue); // free->queue ring
        if (m_handlers != 0)
        {
            EventHandler* it = nlDLRingGetStart(m_handlers);
            EventHandler* end = m_handlers;
            do
            {
                u32 mask = m_dest[e->m_uEventID]; // dest[type]
                if ((it->mask & mask) != 0)
                {
                    void (*fn)(Event*, void*) = it->callback;
                    void* ud = it->unkC;
                    (*fn)(e, ud); // bctrl
                }

                if (it == end)
                    break;

                it = it->m_next;
            } while (1);
        }
        if (e->m_nReferenceCount != 0)
        {
            nlDLRingAddEnd(&m_keep, e);
        }
        else
        {
            nlDLRingAddEnd(&m_free, e);
        }
    }

    m_dispatching = 0;
    m_queue = m_deferred;
    m_deferred = NULL;
}

#ifndef _EVENTMAN_H_
#define _EVENTMAN_H_

#include "types.h"

class EventHandler;
class EventManager;

struct EventData
{
    // public:
    // EventData() { }
    // virtual ~EventData() { }
    virtual u32 GetID() { return -1; }
};

class Event
{
public:
    /* 0x00 */ Event* m_next;
    /* 0x04 */ Event* m_prev;
    /* 0x08 */ u32 m_uEventID;
    /* 0x0C */ s32 m_nReferenceCount;
    /* 0x10 */ EventData m_data;

    Event()
        : m_next(NULL)
        , m_prev(NULL)
        , m_nReferenceCount(0)
    {
    }
};

typedef void (*EventCallback)(Event*, void*);

// class EventHandler /* size >= 0x2C */
// {
// public:
//     /* 0x00 */ EventHandler* m_next;
//     /* 0x04 */ EventHandler* m_prev;
//     /* 0x08 */ EventCallback callback;
//     /* 0x0C */ void* param;
//     /* 0x10 */ u32 mask;
//     /* 0x14 */ s32 unk14;
//     /* 0x18 */ s32 unk18;
//     /* 0x1C */ Event* m_event;
//     /* 0x20 */ EventManager* m_manager;
//     /* 0x24 */ u32 unk24;
// };

class EventHandler
{
public:
    inline void set(EventCallback pEventHandlerFunc, unsigned long uDestinationMask, void* pParam)
    {
        m_pCBFunction = pEventHandlerFunc;
        m_uDestinationMask = uDestinationMask;
        m_pCBParam = pParam;
    }

    /* 0x00 */ EventHandler* m_next;
    /* 0x04 */ EventHandler* m_prev;
    /* 0x08 */ void (*m_pCBFunction)(class Event*, void*);
    /* 0x0C */ void* m_pCBParam;
    /* 0x10 */ unsigned long m_uDestinationMask;
}; // total size: 0x14

class EventManager
{
public:
    static void Create(unsigned long, unsigned long);
    void SetupDestArray();
    EventHandler* AddEventHandler(EventCallback, void*, unsigned long);
    void RemoveEventHandler(EventHandler*);
    void AllocateDestArray(unsigned long, unsigned long);
    Event* CreateValidEvent(unsigned long eventID, unsigned long uSize);
    void DispatchEvents();

    /* 0x00 */ bool m_dispatching;
    /* 0x04 */ EventHandler* m_handlers;
    /* 0x08 */ Event* m_free;
    /* 0x0C */ Event* m_keep;
    /* 0x10 */ Event* m_queue;
    /* 0x14 */ Event* m_deferred;
    /* 0x18 */ u32* m_dest;
    /* 0x1C */ void* m_pool;
    /* 0x20 */ u32 m_count;
    /* 0x24 */ u32 m_size;

    virtual ~EventManager();
};

extern EventManager* g_pEventManager;

#endif // _EVENTMAN_H_

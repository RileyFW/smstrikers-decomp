#include "Game/eventman.h"

/**
 * Offset/Address/Size: 0x0 | 0x801FA980 | size: 0xF4
 */
void EventManager::DispatchEvents()
{
}

/**
 * Offset/Address/Size: 0xF4 | 0x801FAA74 | size: 0xD0
 */
void EventManager::CreateValidEvent(unsigned long, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x1C4 | 0x801FAB44 | size: 0x110
 */
void EventManager::AllocateDestArray(unsigned long, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x2D4 | 0x801FAC54 | size: 0x38
 */
void EventManager::RemoveEventHandler(EventHandler*)
{
}

/**
 * Offset/Address/Size: 0x30C | 0x801FAC8C | size: 0x64
 */
void EventManager::AddEventHandler(void (*)(Event*, void*), void*, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x370 | 0x801FACF0 | size: 0x118
 */
void EventManager::Create(unsigned long, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x488 | 0x801FAE08 | size: 0x94
 */
EventManager::~EventManager()
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x801FAE9C | size: 0x20
//  */
// void nlDeleteDLRing<EventHandler>(EventHandler**)
// {
// }

// /**
//  * Offset/Address/Size: 0x20 | 0x801FAEBC | size: 0x38
//  */
// void nlDLRingRemoveStart<Event>(Event**)
// {
// }

// /**
//  * Offset/Address/Size: 0x58 | 0x801FAEF4 | size: 0x18
//  */
// void nlDLRingGetStart<EventHandler>(EventHandler*)
// {
// }

// /**
//  * Offset/Address/Size: 0x70 | 0x801FAF0C | size: 0x44
//  */
// void nlDLRingRemove<EventHandler>(EventHandler**, EventHandler*)
// {
// }

// /**
//  * Offset/Address/Size: 0xB4 | 0x801FAF50 | size: 0x44
//  */
// void nlDLRingRemove<Event>(Event**, Event*)
// {
// }

// /**
//  * Offset/Address/Size: 0xF8 | 0x801FAF94 | size: 0x3C
//  */
// void nlDLRingAddEnd<EventHandler>(EventHandler**, EventHandler*)
// {
// }

// /**
//  * Offset/Address/Size: 0x134 | 0x801FAFD0 | size: 0x3C
//  */
// void nlDLRingAddEnd<Event>(Event**, Event*)
// {
// }

// /**
//  * Offset/Address/Size: 0x170 | 0x801FB00C | size: 0x38
//  */
// void nlDLRingAddStart<Event>(Event**, Event*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1A8 | 0x801FB044 | size: 0x38
//  */
// void nlDLRingAddStart<EventHandler>(EventHandler**, EventHandler*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801FB07C | size: 0x70
//  */
// void nlDeleteRing<EventHandler>(EventHandler**)
// {
// }

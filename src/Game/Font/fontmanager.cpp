#include "Game/Font/fontmanager.h"
#include "NL/nlString.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x80209CC8 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<nlFont*>, DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>>(DLListEntry<nlFont*>*, DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>*, void (DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>::*)(DLListEntry<nlFont*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xB0 | 0x80209C90 | size: 0x38
//  */
// void nlDLRingAddStart<DLListEntry<nlFont*>>(DLListEntry<nlFont*>**, DLListEntry<nlFont*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x74 | 0x80209C54 | size: 0x3C
//  */
// void nlDLRingAddEnd<DLListEntry<nlFont*>>(DLListEntry<nlFont*>**, DLListEntry<nlFont*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x5C | 0x80209C3C | size: 0x18
//  */
// void nlDLRingGetStart<DLListEntry<nlFont*>>(DLListEntry<nlFont*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x80209C1C | size: 0x20
//  */
// void nlDLRingIsEnd<DLListEntry<nlFont*>>(DLListEntry<nlFont*>*, DLListEntry<nlFont*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80209BE0 | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<nlFont*>, DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>>(DLListEntry<nlFont*>*, DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>*, void (DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>::*)(DLListEntry<nlFont*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80209BD0 | size: 0x10
//  */
// void DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>::DeleteEntry(DLListEntry<nlFont*>*)
// {
// }

/**
 * Offset/Address/Size: 0x4CC | 0x80209B60 | size: 0x70
 */
FontManager::FontManager()
{
    // SlotPoolBase::BaseAddNewBlock(&m_fonts.m_Allocator, 0xC);
}

/**
 * Offset/Address/Size: 0x374 | 0x80209A08 | size: 0x158
 */
FontManager::~FontManager()
{
}

/**
 * Offset/Address/Size: 0x2A8 | 0x8020993C | size: 0xCC
 */
nlFont* FontManager::GetFontByHashID(unsigned long uHashID)
{
    DLListEntry<nlFont*>* head;
    DLListEntry<nlFont*>* entry = nlDLRingGetStart(m_fonts.m_Head);
    head = m_fonts.m_Head;

    while (entry != NULL)
    {
        if (uHashID == entry->m_data->m_Metrics.FontName)
        {
            return entry->m_data;
        }

        if (nlDLRingIsEnd(head, entry) || entry == NULL)
        {
            entry = NULL;
        }
        else
        {
            entry = entry->m_next;
        }
    }

    nlPrintf("GetFontByHashID: Hash not found: %d\n", uHashID);

    DLListEntry<nlFont*>* start = nlDLRingGetStart(m_fonts.m_Head);
    if (start == NULL)
    {
        return NULL;
    }
    return start->m_data;
}

/**
 * Offset/Address/Size: 0x0 | 0x80209694 | size: 0x2A8
 */
void FontManager::LoadFont(const char*, const char*, const char*)
{
}

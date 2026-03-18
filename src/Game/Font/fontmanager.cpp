#include "Game/Font/fontmanager.h"
#include "NL/nlBundleFile.h"
#include "NL/nlMemory.h"
#include "NL/nlString.h"
#include "NL/gl/glTexture.h"
#include "NL/nlBundleFile.h"

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

/**
 * Offset/Address/Size: 0x0 | 0x80209BE0 | size: 0x3C
 * TODO: 96.00% match - prologue scheduling mismatch remains.
 * Target orders `lwz r7, 0(r5)` before saving LR; current MWCC output saves LR first.
 */
template <>
void nlWalkDLRing<DLListEntry<nlFont*>, DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*> > > >(
    DLListEntry<nlFont*>* head,
    DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*> > >* callback,
    void (DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*> > >::*callbackFunc)(DLListEntry<nlFont*>*))
{
    void (DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*> > >::*func)(DLListEntry<nlFont*>*) = callbackFunc;
    nlWalkRing(head, callback, func);
}

// /**
//  * Offset/Address/Size: 0x0 | 0x80209BD0 | size: 0x10
//  */
// void DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>::DeleteEntry(DLListEntry<nlFont*>*)
// {
// }

template <>
nlDLListSlotPool<nlFont*>::nlDLListSlotPool()
{
    this->m_Head = NULL;
    this->m_Allocator.m_Initial = 8;
    SlotPoolBase::BaseAddNewBlock((SlotPoolBase*)&this->m_Allocator, sizeof(DLListEntry<nlFont*>));
    this->m_Allocator.m_Delta = 0;
}

/**
 * Offset/Address/Size: 0x4CC | 0x80209B60 | size: 0x70
 * TODO: 96.25% match - remaining mismatch is r30/r31 nonvolatile register
 * allocation in the inlined m_fonts slot-pool constructor path.
 */
FontManager::FontManager()
{
}

/**
 * Offset/Address/Size: 0x374 | 0x80209A08 | size: 0x158
 * TODO: 97.97% match - auto-generated m_fonts destructor path still lowers to
 * nlWalkRing with @106/@165 callback constants instead of target nlWalkDLRing
 * calls that reuse @198.
 */
FontManager::~FontManager()
{
    DLListEntry<nlFont*>* head;
    DLListEntry<nlFont*>* current = nlDLRingGetStart(m_fonts.m_Head);
    head = m_fonts.m_Head;

    while (current != NULL)
    {
        delete current->m_data;

        if (nlDLRingIsEnd(head, current) || current == NULL)
        {
            current = NULL;
        }
        else
        {
            current = current->m_next;
        }
    }

    typedef DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*> > > FontListBase;
    typedef void (*WalkFn)(DLListEntry<nlFont*>*, FontListBase*, void (FontListBase::*)(DLListEntry<nlFont*>*));

    void (FontListBase::*func)(DLListEntry<nlFont*>*) = &FontListBase::DeleteEntry;
    WalkFn walk = &nlWalkDLRing<DLListEntry<nlFont*>, FontListBase>;
    walk(m_fonts.m_Head, &m_fonts, func);
    m_fonts.m_Head = NULL;
}

/**
 * Offset/Address/Size: 0x2A8 | 0x8020993C | size: 0xCC
 */
nlFont* FontManager::GetFontByHashID(unsigned long hashID)
{
    DLListEntry<nlFont*>* head;
    DLListEntry<nlFont*>* entry = nlDLRingGetStart(m_fonts.m_Head);
    head = m_fonts.m_Head;

    while (entry != NULL)
    {
        nlFont* font = entry->m_data;
        if (hashID == font->m_Metrics.FontName)
        {
            return font;
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

    nlPrintf("FontManager: Warning, failed to find font 0x%08x\n", hashID);

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
bool FontManager::LoadFont(const char* bundlePath, const char* fontName, const char* fontFileName)
{
    BundleFile bundleFile;
    char nameBuffer[0xFF];
    nlFont* font = NULL;

    nlStrNCpy(nameBuffer, fontFileName, 0xFF);
    nlToLower(nameBuffer);

    bundleFile.Open(bundlePath);

    unsigned long fontHash = nlStringHash(fontName);

    BundleFileDirectoryEntry fontEntry;
    if (!bundleFile.GetFileInfo(fontHash, &fontEntry, true))
    {
        return false;
    }

    char* data = (char*)nlMalloc(fontEntry.m_length, 0x20, true);
    bundleFile.ReadFile(fontHash, data, fontEntry.m_length);

    font = new (nlMalloc(sizeof(nlFont), 0x8, false)) nlFont();

    unsigned long nameHash = nlStringHash(nameBuffer);
    font->Load(fontName, data, nameHash);

    delete[] data;

    // Allocate a slot from the font pool
    if (m_fonts.m_Allocator.m_FreeList == NULL)
    {
        SlotPoolBase::BaseAddNewBlock(&m_fonts.m_Allocator, sizeof(DLListEntry<nlFont*>));
    }

    DLListEntry<nlFont*>* slot = NULL;
    if (m_fonts.m_Allocator.m_FreeList != NULL)
    {
        slot = (DLListEntry<nlFont*>*)m_fonts.m_Allocator.m_FreeList;
        m_fonts.m_Allocator.m_FreeList = m_fonts.m_Allocator.m_FreeList->m_next;
    }

    if (slot != NULL)
    {
        slot->m_next = NULL;
        slot->m_prev = NULL;
        slot->m_data = font;
    }

    nlDLRingAddEnd(&m_fonts.m_Head, slot);

    // Load textures for each page
    for (unsigned long i = 0; i < font->m_PageCount; i++)
    {
        unsigned long textureHash = font->m_TextureHandles[i];

        BundleFileDirectoryEntry dirEntry;
        bundleFile.GetFileInfo(textureHash, &dirEntry, true);

        BundleFileDirectoryEntry texEntry;
        if (bundleFile.GetFileInfo(textureHash, &texEntry, true))
        {
            char* texData = (char*)nlMalloc(texEntry.m_length, 0x20, true);
            bundleFile.ReadFile(textureHash, texData, texEntry.m_length);
            glTextureAdd(textureHash, texData, texEntry.m_length);
            delete[] texData;
        }

        if (font->m_TextureType == SplitFX)
        {
            unsigned long effectHash = font->m_EffectTextureHandles[i];

            bundleFile.GetFileInfo(effectHash, &dirEntry, true);

            BundleFileDirectoryEntry effectEntry;
            if (bundleFile.GetFileInfo(effectHash, &effectEntry, true))
            {
                char* effectData = (char*)nlMalloc(effectEntry.m_length, 0x20, true);
                bundleFile.ReadFile(effectHash, effectData, effectEntry.m_length);
                glTextureAdd(effectHash, effectData, effectEntry.m_length);
                delete[] effectData;
            }
        }
    }

    bundleFile.Close();
    return true;
}

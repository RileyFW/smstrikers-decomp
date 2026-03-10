#include "Game/AnimInventory.h"

#include "NL/nlString.h"
#include "NL/nlMemory.h"
#include "NL/nlFileGC.h"

SAnimContainer* g_pDefaultSAnimInventory = nullptr;

/**
 * Offset/Address/Size: 0x438 | 0x800073B4 | size: 0xA0
 */
cAnimInventory::cAnimInventory(const AnimProperties* props, int count)
{
    m_count = count;
    m_cont = 0;
    m_anims = 0;
    m_props = props;

    SAnimContainer* cont = (SAnimContainer*)nlMalloc(0x1C, 8, 0);
    if (cont)
    {
        cont->animHead = 0;
        cont->animTail = 0;
        cont->fileHead = 0;
        cont->fileTail = 0;
        cont->animCount = 0;
    }
    m_cont = cont;

    if (g_pDefaultSAnimInventory == 0)
        g_pDefaultSAnimInventory = m_cont;

    m_anims = (cSAnim**)nlMalloc((unsigned long)(m_count << 2), 8, 0);
}

/**
 * Offset/Address/Size: 0x29C | 0x80007218 | size: 0x19C
 */
cAnimInventory::~cAnimInventory()
{
    SAnimContainer* c = m_cont;
    if (c)
    {
        // 1) Destroy each cSAnim
        ListEntry<cSAnim*>* it = c->animHead;
        while (it)
        {
            cSAnim* a = it->data;
            if (a)
            {
                a->Destroy();
            }
            it = it->next;
        }

        // 2) Free all anim list entries (walk and delete each entry)
        c->animHead = 0;
        c->animTail = 0;

        // 3) Pop all file list entries; free entry, then free char*
        ListEntry<char*>* popped;
        do
        {
            nlListRemoveStart(&c->fileHead, &popped);
            if (popped)
            {
                char* filename = popped->data;
                delete popped;   // free entry
                delete filename; // free char* that came from loader
            }
        } while (c->fileHead != 0);
        c->animCount = 0;

        // 4) Ensure file list head/tail nulled (mirrors second walk)
        c->fileHead = 0;
        c->fileTail = 0;

        // 5) Delete the container itself
        delete c;
    }

    if (m_anims)
    {
        delete[] m_anims;
    }

    g_pDefaultSAnimInventory = (SAnimContainer*)0;
}

/**
 * Offset/Address/Size: 0x88 | 0x80007004 | size: 0x214
 * TODO: 86.4% match in scratch (wRAb2) - this/path register assignment and loop
 * induction register allocation differ in both animation lookup loops.
 */
void cAnimInventory::AddAnimBundle(const char* path)
{
    int len;
    char* pMem = (char*)nlLoadEntireFileToVirtualMemory(path, &len, 0x10000, 0, AllocateStart);
    SAnimContainer* inv = m_cont;

    ListEntry<char*>* pFileEntry = (ListEntry<char*>*)nlMalloc(8, 8, 0);
    if (pFileEntry != 0)
    {
        pFileEntry->next = 0;
        pFileEntry->data = pMem;
    }
    nlListAddStart<ListEntry<char*> >(&inv->fileHead, pFileEntry, &inv->fileTail);

    char* end = pMem + len;
    while (pMem != end)
    {
        if ((((nlChunk*)pMem)->m_ID & 0xFFFFFF00) == 0x80017000)
        {
            cSAnim* pAnim = cSAnim::Initialize((nlChunk*)pMem);
            ListEntry<cSAnim*>* pAnimEntry = (ListEntry<cSAnim*>*)nlMalloc(8, 8, 0);
            if (pAnimEntry != 0)
            {
                pAnimEntry->next = 0;
                pAnimEntry->data = pAnim;
            }
            nlListAddStart<ListEntry<cSAnim*> >(&inv->animHead, pAnimEntry, &inv->animTail);
            inv->animCount++;
        }
        else
        {
            nlPrintf("Warning: inventory encountered an unknown chunk type\n");
        }

        pMem += ((nlChunk*)pMem)->m_Size + 8;
    }

    int i;
    int propOffset = 0;
    for (i = 0; i < m_count; i++)
    {
        unsigned int hash = nlStringHash(*(const char**)((char*)m_props + propOffset + 4));
        ListEntry<cSAnim*>* pList = m_cont->animHead;
        cSAnim* pFound = 0;

        while (pList != 0)
        {
            cSAnim* pEntryAnim = pList->data;
            if (hash == pEntryAnim->m_uHashID)
            {
                pFound = pEntryAnim;
                break;
            }
            pList = pList->next;
        }

        m_anims[i] = pFound;
        if (m_anims[i] == 0)
        {
            nlPrintf("Warning! Could not find \"%s\" in bundle \"%s\"\n", *(const char**)((char*)m_props + propOffset + 4), path);
            hash = nlStringHash(*(const char**)((char*)m_props + propOffset + 4));
            pList = g_pDefaultSAnimInventory->animHead;
            pFound = 0;
            while (pList != 0)
            {
                cSAnim* pEntryAnim = pList->data;
                if (hash == pEntryAnim->m_uHashID)
                {
                    pFound = pEntryAnim;
                    break;
                }
                pList = pList->next;
            }

            m_anims[i] = pFound;
            if (m_anims[i] == 0)
            {
                m_anims[i] = m_anims[0];
            }
        }
        propOffset += sizeof(AnimProperties);
    }
}

/**
 * Offset/Address/Size: 0x78 | 0x80006FF4 | size: 0x10
 */
cSAnim* cAnimInventory::GetAnim(int i)
{
    return m_anims[i];
}

/**
 * Offset/Address/Size: 0x64 | 0x80006FE0 | size: 0x14
 */
ePlayMode cAnimInventory::GetPlayMode(int i)
{
    return m_props[i].playMode;
}

/**
 * Offset/Address/Size: 0x50 | 0x80006FCC | size: 0x14
 */
float cAnimInventory::GetBlendTime(int i)
{
    return m_props[i].blendTime;
}

/**
 * Offset/Address/Size: 0x3C | 0x80006FB8 | size: 0x14
 */
bool cAnimInventory::GetMirrored(int i)
{
    return m_props[i].mirrored;
}

/**
 * Offset/Address/Size: 0x28 | 0x80006FA4 | size: 0x14
 */
int cAnimInventory::GetBallRotationMode(int i)
{
    return m_props[i].ballRotMode;
}

/**
 * Offset/Address/Size: 0x14 | 0x80006F90 | size: 0x14
 */
int cAnimInventory::GetEndPhase(int i)
{
    return m_props[i].endPhase;
}

/**
 * Offset/Address/Size: 0x0 | 0x80006F7C | size: 0x14
 */
u8 cAnimInventory::GetMatchCharacterSpeed(int i)
{
    return m_props[i].matchCharSpd;
}

// /**
//  * Offset/Address/Size: 0x0 | 0x80007454 | size: 0x24
//  */
// void ListContainerBase<cSAnim*, NewAdapter<ListEntry<cSAnim*>>>::DeleteEntry(ListEntry<cSAnim*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x24 | 0x80007478 | size: 0x24
//  */
// void ListContainerBase<char*, NewAdapter<ListEntry<char*>>>::DeleteEntry(ListEntry<char*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8000749C | size: 0x54
//  */
// void nlPrintf(const char*, ...)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800074F0 | size: 0x68
//  */
// void nlWalkList<ListEntry<char*>, ListContainerBase<char*, NewAdapter<ListEntry<char*>>>>(ListEntry<char*>*, ListContainerBase<char*,
// NewAdapter<ListEntry<char*>>>*, void (ListContainerBase<char*, NewAdapter<ListEntry<char*>>>::*)(ListEntry<char*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x68 | 0x80007558 | size: 0x68
//  */
// void nlWalkList<ListEntry<cSAnim*>, ListContainerBase<cSAnim*, NewAdapter<ListEntry<cSAnim*>>>>(ListEntry<cSAnim*>*,
// ListContainerBase<cSAnim*, NewAdapter<ListEntry<cSAnim*>>>*, void (ListContainerBase<cSAnim*,
// NewAdapter<ListEntry<cSAnim*>>>::*)(ListEntry<cSAnim*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xD0 | 0x800075C0 | size: 0x44
//  */
// void nlListRemoveStart<ListEntry<char*>>(ListEntry<char*>**, ListEntry<char*>**)
// {
// }

// /**
//  * Offset/Address/Size: 0x114 | 0x80007604 | size: 0x28
//  */
// void nlListAddStart<ListEntry<cSAnim*>>(ListEntry<cSAnim*>**, ListEntry<cSAnim*>*, ListEntry<cSAnim*>**)
// {
// }

// /**
//  * Offset/Address/Size: 0x13C | 0x8000762C | size: 0x28
//  */
// void nlListAddStart<ListEntry<char*>>(ListEntry<char*>**, ListEntry<char*>*, ListEntry<char*>**)
// {
// }

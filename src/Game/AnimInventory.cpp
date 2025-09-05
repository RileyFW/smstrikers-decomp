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
 */
void cAnimInventory::AddAnimBundle(const char* path)
{
    int fileSize = 0;
    void* base = nlLoadEntireFileToVirtualMemory(path, &fileSize, 1, 0, eAllocType_0);
    char* p = (char*)base;
    char* end = p + fileSize;

    // Remember the loaded block in the container’s file list
    {
        ListEntry<char*>* e = (ListEntry<char*>*)nlMalloc(8, 8, 0);
        if (e)
        {
            e->next = 0;
            e->data = (char*)base;
        }
        nlListAddStart(&m_cont->fileHead, e, &m_cont->fileTail); // :contentReference[oaicite:16]{index=16}
    }

    // Walk chunks
    while (p != end)
    {
        u32 id = *(u32*)p;
        u32 masked = id & 0xFFFFFF00;
        if (((masked + 0x7FFF0000u) & 0xFFFF0000u) == 0x70000000u) // chunk family check.  :contentReference[oaicite:17]{index=17}
        {
            // cSAnim::Initialize(nlChunk*)
            cSAnim* a = cSAnim::Initialize((nlChunk*)p);

            // push into anim list
            ListEntry<cSAnim*>* e = (ListEntry<cSAnim*>*)nlMalloc(8, 8, 0);
            if (e)
            {
                e->next = 0;
                e->data = a;
            }
            nlListAddStart(&m_cont->animHead, e, &m_cont->animTail); // :contentReference[oaicite:18]{index=18}
            m_cont->animCount++;
        }
        else
        {
            nlPrintf("Warning: inventory encountered an unknown chunk type\n"); // @392.  :contentReference[oaicite:19]{index=19}
        }

        // advance by chunk->size + header (header size is 8)
        u32 chunkSize = *(u32*)(p + 4);
        p += (int)chunkSize + 8;
    }

    // Resolve each desired animation name to a cSAnim*
    int i;
    int ofs = 0;
    int dst = 0;
    for (i = 0; i < m_count; ++i)
    {
        const char* name = *(const char**)((char*)m_props + ofs + 4); // +4 = name.  :contentReference[oaicite:20]{index=20}
        u32 h = nlStringHash(name);

        // search in this container
        ListEntry<cSAnim*>* it = m_cont->animHead;
        cSAnim* found = 0;
        while (it)
        {
            cSAnim* a = it->data;
            // a->mHash at +4 (compared in asm)
            if (*(u32*)((char*)a + 4) == h)
            {
                found = a;
                break;
            }
            it = it->next;
        }
        m_anims[dst >> 2] = found;

        // not found? warn and try default container
        if (m_anims[dst >> 2] == 0)
        {
            nlPrintf("Warning! Could not find \"%s\" in bundle \"%s\"\n", name, path); // @393.  :contentReference[oaicite:21]{index=21}

            SAnimContainer* defc = g_pDefaultSAnimInventory;
            it = defc ? defc->animHead : 0;
            found = 0;
            while (it)
            {
                cSAnim* a = it->data;
                if (*(u32*)((char*)a + 4) == h)
                {
                    found = a;
                    break;
                }
                it = it->next;
            }
            m_anims[dst >> 2] = found;

            // still not found? fall back to first entry
            if (m_anims[dst >> 2] == 0)
                m_anims[dst >> 2] = m_anims[0];
        }

        ofs += 0x20; // next property
        dst += 4;    // next anim pointer slot
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
int cAnimInventory::GetPlayMode(int i)
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

#include "Game/SAnim/AnimRetargeter.h"

/**
 * Offset/Address/Size: 0x0 | 0x801EFF90 | size: 0x48
 * TODO: 88.9% match - prolog instruction scheduling: target has mr r7,r5 / lwz r4,0x44(r4)
 *   but compiler emits lwz r4,0x44(r4) / li r7,0. Likely -inline deferred context difference.
 */
AnimRetarget* AnimRetargetList::GetAnimRetargetWithSignature(const cSAnim* anim)
{
    AnimRetarget* result = NULL;
    const unsigned long signature = anim->m_nHierarchySignature;
    AnimRetarget* p;
    long offset = 0;

    for (long i = m_NumAnimRetargets; i > 0; i--)
    {
        p = (AnimRetarget*)((char*)m_pAnimRetarget + offset);
        if (signature == p->m_TargetHierarchySignature)
        {
            result = p;
            break;
        }
        offset += sizeof(AnimRetarget);
    }

    return result;
}

/**
 * Offset/Address/Size: 0x48 | 0x801EFFD8 | size: 0x10C
 * TODO: 91.9% match - register allocation mismatch around aligned chunk pointer
 * computation in second/loop chunk-data blocks (r3/r4/r5/r6 swaps; extra store/branch).
 */
void AnimRetargetList::Initialize(nlChunk*)
{
    AnimRetargetList* data;
    nlChunk* chunk = (nlChunk*)&m_NumAnimRetargets;
    u32 align = chunk->m_ID & 0x7F000000;

    if (((-align | align) >> 31) != 0)
    {
        u32 mask = 1 << (align >> 24);
        u32 ptr = (u32)chunk + mask;
        ptr += 7;
        ptr &= ~(mask - 1);
        data = (AnimRetargetList*)ptr;
    }
    else
    {
        data = (AnimRetargetList*)((u8*)chunk + 8);
    }

    nlChunk* nextChunk = (nlChunk*)((u8*)chunk + chunk->m_Size + 0x10);
    align = nextChunk->m_ID & 0x7F000000;

    AnimRetarget* pAnimRetarget;

    if (((-align | align) >> 31) != 0)
    {
        u32 mask = 1 << (align >> 24);
        u32 ptr = (u32)nextChunk + mask;
        ptr += 7;
        ptr &= ~(mask - 1);
        pAnimRetarget = (AnimRetarget*)ptr;
    }
    else
    {
        pAnimRetarget = (AnimRetarget*)((u8*)nextChunk + 8);
    }
    data->m_pAnimRetarget = pAnimRetarget;

    s32 i = 0;
    s32 off = 0;

    while (i < data->m_NumAnimRetargets)
    {
        nlChunk* mapChunk = (nlChunk*)((u8*)nextChunk + nextChunk->m_Size + 8);
        nextChunk = mapChunk;
        align = mapChunk->m_ID & 0x7F000000;

        signed short* nextMap;

        if (((-align | align) >> 31) != 0)
        {
            u32 mask = 1 << (align >> 24);
            u32 ptr = (u32)mapChunk + mask;
            ptr += 7;
            ptr &= ~(mask - 1);
            nextMap = (signed short*)ptr;
        }
        else
        {
            nextMap = (signed short*)((u8*)mapChunk + 8);
        }

        *(signed short**)((u8*)data->m_pAnimRetarget + off + 8) = nextMap;
        off += 0xC;
        i++;
    }
}

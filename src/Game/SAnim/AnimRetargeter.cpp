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
 * TODO: 84.2% match - work in progress..
 */
void AnimRetargetList::Initialize(nlChunk* chunk)
{
    nlChunk* chunkPtr = (nlChunk*)&m_NumAnimRetargets;
    u32 id = chunkPtr->m_ID;
    u32 align = id & 0x7F000000;
    AnimRetargetList* data;

    if (((-align | align) >> 31) != 0)
    {
        u32 alignVal = 1 << (align >> 24);
        data = (AnimRetargetList*)(((u32)chunkPtr + alignVal + 7) & ~(alignVal - 1));
    }
    else
    {
        data = (AnimRetargetList*)((u32)chunkPtr + 8);
    }

    nlChunk* nextChunk = (nlChunk*)((char*)chunkPtr + chunkPtr->m_Size + 0x10);
    u32 nextId = nextChunk->m_ID;
    u32 nextAlign = nextId & 0x7F000000;
    AnimRetarget* mapData;

    if (((-nextAlign | nextAlign) >> 31) != 0)
    {
        u32 alignVal = 1 << (nextAlign >> 24);
        mapData = (AnimRetarget*)(((u32)nextChunk + alignVal + 7) & ~(alignVal - 1));
    }
    else
    {
        mapData = (AnimRetarget*)((u32)nextChunk + 8);
    }

    data->m_pAnimRetarget = mapData;

    s32 i = 0;
    s32 offset = 0;

    while (i < data->m_NumAnimRetargets)
    {
        nlChunk* mapChunk = (nlChunk*)((char*)nextChunk + nextChunk->m_Size + 8);
        u32 mapId = mapChunk->m_ID;
        u32 mapAlign = mapId & 0x7F000000;
        signed short* nextMap;

        nextChunk = mapChunk;

        if (((-mapAlign | mapAlign) >> 31) != 0)
        {
            u32 alignVal = 1 << (mapAlign >> 24);
            nextMap = (signed short*)(((u32)mapChunk + alignVal + 7) & ~(alignVal - 1));
        }
        else
        {
            nextMap = (signed short*)((u32)mapChunk + 8);
        }

        AnimRetarget* retargets = data->m_pAnimRetarget;
        *(signed short**)((char*)retargets + offset + 8) = nextMap;
        offset += 0xC;
        i++;
    }
}

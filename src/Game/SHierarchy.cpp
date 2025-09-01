#include "Game/SHierarchy.h"
#include "types.h"

/**
 * Offset/Address/Size: 0x0 | 0x801EDFEC | size: 0x18
 */
bool cSHierarchy::PreserveBoneLength(int nodeIndex) const
{
    return m_boneLengthFlags[nodeIndex] ? true : false;
}

/**
 * Offset/Address/Size: 0x18 | 0x801EE004 | size: 0x10
 */
nlVector3* cSHierarchy::GetTranslationOffset(int nodeIndex) const
{
    return &m_translationOffsets[nodeIndex];
}

/**
 * Offset/Address/Size: 0x28 | 0x801EE014 | size: 0x10
 */
s32 cSHierarchy::GetParent(int nodeIndex) const
{
    return *((s32*)this->m_parentIndices + nodeIndex);
}

/**
 * Offset/Address/Size: 0x38 | 0x801EE024 | size: 0x10
 */
s32 cSHierarchy::GetPushPop(int nodeIndex) const
{
    return *((s32*)this->m_pushPopFlags + nodeIndex);
}

/**
 * Offset/Address/Size: 0x48 | 0x801EE034 | size: 0x10
 */
s32 cSHierarchy::GetMirroredNode(int nodeIndex) const
{
    return *((s32*)this->m_mirroredNodeIndices + nodeIndex);
}

/**
 * Offset/Address/Size: 0x58 | 0x801EE044 | size: 0x10
 */
s32 cSHierarchy::GetNumChildren(int nodeIndex) const
{
    return m_childCounts[nodeIndex];
}

/**
 * Offset/Address/Size: 0x68 | 0x801EE054 | size: 0x10
 */
u32 cSHierarchy::GetNodeID(int nodeIndex) const
{
    return this->m_nodeIDs[nodeIndex];
}

/**
 * Offset/Address/Size: 0x78 | 0x801EE064 | size: 0x40
 */
s32 cSHierarchy::GetNodeIndexByID(unsigned int nodeID) const
{
    s32 totalNodes;
    s32 searchCounter;
    s32 currentIndex;
    u32* nodeIDArray;

    totalNodes = this->m_nodeCount;
    currentIndex = 0;
    nodeIDArray = this->m_nodeIDs;
    searchCounter = totalNodes;
    if (totalNodes > 0)
    {
    loop_1:
        if (nodeID == *nodeIDArray)
        {
            return currentIndex;
        }
        nodeIDArray += 4;
        currentIndex += 1;
        searchCounter -= 1;
        if (searchCounter == 0)
        {
            /* Duplicate return node #4. Try simplifying control flow for better match */
            return -1;
        }
        goto loop_1;
    }
    return -1;
}

/**
 * Offset/Address/Size: 0xB8 | 0x801EE0A4 | size: 0x18
 */
s32 cSHierarchy::GetChild(int parentIndex, int childIndex) const
{
    FORCE_DONT_INLINE;
    return *((s32*)((s32**)this->m_childArrays)[parentIndex] + childIndex);
}

/**
 * Offset/Address/Size: 0xD0 | 0x801EE0BC | size: 0x284
 */
void cSHierarchy::BuildPushPopFlags(int nodeIndex, int currentDepth, int& stackDepth)
{
    s32 nodeOffset;
    s32 childCount;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 newStackDepth;
    s32 childNodeIndex;
    s32 grandchildIndex;
    s32 grandchildStackDepth;
    s32 grandchildNodeIndex;
    s32 grandchildChildCount;
    s32 greatGrandchildStackDepth;
    s32 greatGrandchildChildCount;
    s32 greatGrandchildIndex;
    s32 greatGrandchildNodeIndex;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 previousStackDepth;
    s32 previousStackDepth_2;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r6;
    s32 temp_r6_2;
    s32 childArrayOffset;
    s32 childLoopCounter;
    s32 grandchildArrayOffset;
    s32 grandchildLoopCounter;
    s32 greatGrandchildLoopCounter;

    temp_r6 = stackDepth;
    if (currentDepth != temp_r6)
    {
        ((s32*)this->m_pushPopFlags)[nodeIndex - 1] = currentDepth - temp_r6;
        stackDepth = currentDepth;
    }
    temp_r0 = nodeIndex * 4;
    nodeOffset = temp_r0;
    temp_r0_2 = ((s32*)this->m_childCounts)[nodeIndex];
    childCount = temp_r0_2;
    if (temp_r0_2 != 0)
    {
        childLoopCounter = 0;
        childArrayOffset = 0;
        ((s32*)this->m_pushPopFlags)[nodeIndex] = 1;
        stackDepth += 1;
        newStackDepth = stackDepth;
    loop_29:
        if (childLoopCounter < childCount)
        {
            temp_r5 = stackDepth;
            temp_r6_2 = ((s32*)((s32**)this->m_childArrays)[nodeIndex])[childLoopCounter];
            if (newStackDepth != temp_r5)
            {
                ((s32*)this->m_pushPopFlags)[temp_r6_2 - 1] = newStackDepth - temp_r5;
                stackDepth = newStackDepth;
            }
            childNodeIndex = temp_r6_2 * 4;
            grandchildChildCount = ((s32*)this->m_childCounts)[temp_r6_2];
            if (grandchildChildCount != 0)
            {
                grandchildLoopCounter = 0;
                ((s32*)this->m_pushPopFlags)[temp_r6_2] = 1;
                grandchildArrayOffset = 0;
                stackDepth += 1;
                greatGrandchildStackDepth = stackDepth;
            loop_25:
                if (grandchildLoopCounter < grandchildChildCount)
                {
                    temp_r5_2 = stackDepth;
                    grandchildNodeIndex = ((s32*)((s32**)this->m_childArrays)[temp_r6_2])[grandchildLoopCounter];
                    if (greatGrandchildStackDepth != temp_r5_2)
                    {
                        ((s32*)this->m_pushPopFlags)[grandchildNodeIndex - 1] = greatGrandchildStackDepth - temp_r5_2;
                        stackDepth = greatGrandchildStackDepth;
                    }
                    temp_r4 = grandchildNodeIndex * 4;
                    greatGrandchildChildCount = ((s32*)this->m_childCounts)[grandchildNodeIndex];
                    if (greatGrandchildChildCount != 0)
                    {
                        greatGrandchildLoopCounter = 0;
                        ((s32*)this->m_pushPopFlags)[grandchildNodeIndex] = 1;
                        stackDepth += 1;
                        greatGrandchildIndex = stackDepth;
                    loop_21:
                        if (greatGrandchildLoopCounter < greatGrandchildChildCount)
                        {
                            temp_r0_3 = stackDepth;
                            greatGrandchildNodeIndex = GetChild(grandchildNodeIndex, greatGrandchildLoopCounter);
                            if (greatGrandchildIndex != temp_r0_3)
                            {
                                ((s32*)this->m_pushPopFlags)[greatGrandchildNodeIndex - 1] = greatGrandchildIndex - temp_r0_3;
                                stackDepth = greatGrandchildIndex;
                            }
                            temp_r4_2 = greatGrandchildNodeIndex * 4;
                            s32 greatGreatGrandchildChildCount = ((s32*)this->m_childCounts)[greatGrandchildNodeIndex];
                            if (greatGreatGrandchildChildCount != 0)
                            {
                                s32 greatGreatGrandchildLoopCounter = 0;
                                ((s32*)this->m_pushPopFlags)[greatGrandchildNodeIndex] = 1;
                                stackDepth += 1;
                                s32 greatGreatGrandchildStackDepth = stackDepth;
                            loop_17:
                                if (greatGreatGrandchildLoopCounter < greatGreatGrandchildChildCount)
                                {
                                    BuildPushPopFlags(GetChild(greatGrandchildNodeIndex, greatGreatGrandchildLoopCounter),
                                        greatGreatGrandchildStackDepth, stackDepth);
                                    greatGreatGrandchildLoopCounter += 1;
                                    goto loop_17;
                                }
                            }
                            else
                            {
                                ((s32*)this->m_pushPopFlags)[greatGrandchildNodeIndex] = 0;
                            }
                            greatGrandchildLoopCounter += 1;
                            goto loop_21;
                        }
                    }
                    else
                    {
                        ((s32*)this->m_pushPopFlags)[grandchildNodeIndex] = 0;
                    }
                    grandchildArrayOffset += 4;
                    grandchildLoopCounter += 1;
                    goto loop_25;
                }
            }
            else
            {
                ((s32*)this->m_pushPopFlags)[temp_r6_2] = 0;
            }
            childArrayOffset += 4;
            childLoopCounter += 1;
            goto loop_29;
        }
        return;
    }
    ((s32*)this->m_pushPopFlags)[nodeIndex] = 0;
}

/**
 * Offset/Address/Size: 0x354 | 0x801EE340 | size: 0x3E0
 */
cSHierarchy* cSHierarchy::Initialize(nlChunk* chunkData)
{
    s32 stackDepth;
    void* chunkPtr;
    void* chunkPtr_6;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r3_10;
    s32 temp_r3_11;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 temp_r3_6;
    s32 temp_r3_7;
    s32 temp_r3_8;
    s32 temp_r3_9;
    s32 temp_r4;
    s32 temp_r4_10;
    s32 temp_r4_11;
    s32 temp_r4_2;
    s32 temp_r4_3;
    s32 temp_r4_4;
    s32 temp_r4_5;
    s32 temp_r4_6;
    s32 temp_r4_7;
    s32 temp_r4_8;
    s32 temp_r4_9;
    s32 alignedOffset;
    s32 alignedOffset_10;
    s32 alignedOffset_11;
    s32 alignedOffset_2;
    s32 alignedOffset_3;
    s32 alignedOffset_4;
    s32 alignedOffset_5;
    s32 alignedOffset_6;
    s32 alignedOffset_7;
    s32 alignedOffset_8;
    s32 alignedOffset_9;
    s32 nodeIndex;
    s32 childArrayOffset;
    s32 nodeCounter;
    void* finalChunkPtr;
    void* chunkPtr_2;
    void* chunkPtr_3;
    void* chunkPtr_4;
    void* chunkPtr_5;
    void* nextChunkPtr;
    void* nextChunkPtr_2;
    void* nextChunkPtr_3;
    void* nextChunkPtr_4;

    chunkPtr = (void*)&this->m_nodeCount;
    temp_r3 = this->m_nodeCount & 0x7F000000;
    if (((-temp_r3 | temp_r3) >> 0x1F) != 0)
    {
        temp_r4 = 1 << (temp_r3 >> 0x18);
        alignedOffset = (s32)((char*)chunkPtr + temp_r4 + 7) & ~(temp_r4 - 1);
    }
    else
    {
        alignedOffset = (s32)((char*)chunkPtr + 8);
    }
    nextChunkPtr = (void*)((char*)chunkPtr + (*(s32*)((char*)chunkPtr + 4) + 8));
    temp_r3_2 = *(s32*)nextChunkPtr & 0x7F000000;
    if (((-temp_r3_2 | temp_r3_2) >> 0x1F) != 0)
    {
        temp_r4_2 = 1 << (temp_r3_2 >> 0x18);
        alignedOffset_2 = (s32)((char*)nextChunkPtr + temp_r4_2 + 7) & ~(temp_r4_2 - 1);
    }
    else
    {
        alignedOffset_2 = (s32)((char*)nextChunkPtr + 8);
    }
    ((cSHierarchy*)alignedOffset)->m_hierarchyMetadata = (void*)alignedOffset_2;
    chunkPtr_2 = (void*)((char*)nextChunkPtr + (*(s32*)((char*)nextChunkPtr + 4) + 8));
    temp_r3_3 = *(s32*)chunkPtr_2 & 0x7F000000;
    if (((-temp_r3_3 | temp_r3_3) >> 0x1F) != 0)
    {
        temp_r4_3 = 1 << (temp_r3_3 >> 0x18);
        alignedOffset_3 = (s32)((char*)chunkPtr_2 + temp_r4_3 + 7) & ~(temp_r4_3 - 1);
    }
    else
    {
        alignedOffset_3 = (s32)((char*)chunkPtr_2 + 8);
    }
    ((cSHierarchy*)alignedOffset)->m_nodeIDs = (u32*)alignedOffset_3;
    nextChunkPtr_2 = (void*)((char*)chunkPtr_2 + (*(s32*)((char*)chunkPtr_2 + 4) + 8));
    temp_r3_4 = *(s32*)nextChunkPtr_2 & 0x7F000000;
    if (((-temp_r3_4 | temp_r3_4) >> 0x1F) != 0)
    {
        temp_r4_4 = 1 << (temp_r3_4 >> 0x18);
        alignedOffset_4 = (s32)((char*)nextChunkPtr_2 + temp_r4_4 + 7) & ~(temp_r4_4 - 1);
    }
    else
    {
        alignedOffset_4 = (s32)((char*)nextChunkPtr_2 + 8);
    }
    ((cSHierarchy*)alignedOffset)->m_parentIndices = (void*)alignedOffset_4;
    chunkPtr_3 = (void*)((char*)nextChunkPtr_2 + (*(s32*)((char*)nextChunkPtr_2 + 4) + 8));
    temp_r3_5 = *(s32*)chunkPtr_3 & 0x7F000000;
    if (((-temp_r3_5 | temp_r3_5) >> 0x1F) != 0)
    {
        temp_r4_5 = 1 << (temp_r3_5 >> 0x18);
        alignedOffset_5 = (s32)((char*)chunkPtr_3 + temp_r4_5 + 7) & ~(temp_r4_5 - 1);
    }
    else
    {
        alignedOffset_5 = (s32)((char*)chunkPtr_3 + 8);
    }
    ((cSHierarchy*)alignedOffset)->m_childCounts = (s32*)alignedOffset_5;
    nextChunkPtr_3 = (void*)((char*)chunkPtr_3 + (*(s32*)((char*)chunkPtr_3 + 4) + 8));
    temp_r3_6 = *(s32*)nextChunkPtr_3 & 0x7F000000;
    if (((-temp_r3_6 | temp_r3_6) >> 0x1F) != 0)
    {
        temp_r4_6 = 1 << (temp_r3_6 >> 0x18);
        alignedOffset_6 = (s32)((char*)nextChunkPtr_3 + temp_r4_6 + 7) & ~(temp_r4_6 - 1);
    }
    else
    {
        alignedOffset_6 = (s32)((char*)nextChunkPtr_3 + 8);
    }
    ((cSHierarchy*)alignedOffset)->m_childArrays = (void*)alignedOffset_6;
    chunkPtr_4 = (void*)((char*)nextChunkPtr_3 + (*(s32*)((char*)nextChunkPtr_3 + 4) + 8));
    temp_r3_7 = *(s32*)chunkPtr_4 & 0x7F000000;
    if (((-temp_r3_7 | temp_r3_7) >> 0x1F) != 0)
    {
        temp_r4_7 = 1 << (temp_r3_7 >> 0x18);
        alignedOffset_7 = (s32)((char*)chunkPtr_4 + temp_r4_7 + 7) & ~(temp_r4_7 - 1);
    }
    else
    {
        alignedOffset_7 = (s32)((char*)chunkPtr_4 + 8);
    }
    ((cSHierarchy*)alignedOffset)->m_pushPopFlags = (void*)alignedOffset_7;
    finalChunkPtr = (void*)((char*)chunkPtr_4 + (*(s32*)((char*)chunkPtr_4 + 4) + 8));
    temp_r3_8 = *(s32*)finalChunkPtr & 0x7F000000;
    if (((-temp_r3_8 | temp_r3_8) >> 0x1F) != 0)
    {
        temp_r4_8 = 1 << (temp_r3_8 >> 0x18);
        alignedOffset_8 = (s32)((char*)finalChunkPtr + temp_r4_8 + 7) & ~(temp_r4_8 - 1);
    }
    else
    {
        alignedOffset_8 = (s32)((char*)finalChunkPtr + 8);
    }
    nodeIndex = 0;
    childArrayOffset = alignedOffset_8;
    nodeCounter = 0;
loop_29:
    if (nodeCounter < ((cSHierarchy*)alignedOffset)->m_nodeCount)
    {
        if (*((s32*)((cSHierarchy*)alignedOffset)->m_childCounts + nodeIndex) > 0)
        {
            *((s32*)((cSHierarchy*)alignedOffset)->m_childArrays + nodeIndex) = childArrayOffset;
        }
        else
        {
            *((s32*)((cSHierarchy*)alignedOffset)->m_childArrays + nodeIndex) = 0;
        }
        nodeCounter += 1;
        temp_r0 = *((s32*)((cSHierarchy*)alignedOffset)->m_childCounts + nodeIndex);
        nodeIndex += 4;
        childArrayOffset += temp_r0 * 4;
        goto loop_29;
    }
    stackDepth = 0;
    int stackDepth_ref = stackDepth;
    BuildPushPopFlags(0, 0, stackDepth_ref);
    chunkPtr_5 = (void*)((char*)finalChunkPtr + (*(s32*)((char*)finalChunkPtr + 4) + 8));
    temp_r3_9 = *(s32*)chunkPtr_5 & 0x7F000000;
    if (((-temp_r3_9 | temp_r3_9) >> 0x1F) != 0)
    {
        temp_r4_9 = 1 << (temp_r3_9 >> 0x18);
        alignedOffset_9 = (s32)((char*)chunkPtr_5 + temp_r4_9 + 7) & ~(temp_r4_9 - 1);
    }
    else
    {
        alignedOffset_9 = (s32)((char*)chunkPtr_5 + 8);
    }
    ((cSHierarchy*)alignedOffset)->m_mirroredNodeIndices = (void*)alignedOffset_9;
    nextChunkPtr_4 = (void*)((char*)finalChunkPtr + (*(s32*)((char*)finalChunkPtr + 4) + 8));
    temp_r3_10 = *(s32*)nextChunkPtr_4 & 0x7F000000;
    if (((-temp_r3_10 | temp_r3_10) >> 0x1F) != 0)
    {
        temp_r4_10 = 1 << (temp_r3_10 >> 0x18);
        alignedOffset_10 = (s32)((char*)nextChunkPtr_4 + temp_r4_10 + 7) & ~(temp_r4_10 - 1);
    }
    else
    {
        alignedOffset_10 = (s32)((char*)nextChunkPtr_4 + 8);
    }
    ((cSHierarchy*)alignedOffset)->m_translationOffsets = (nlVector3*)alignedOffset_10;
    chunkPtr_6 = (void*)((char*)nextChunkPtr_4 + (*(s32*)((char*)nextChunkPtr_4 + 4) + 8));
    temp_r3_11 = *(s32*)chunkPtr_6 & 0x7F000000;
    if (((-temp_r3_11 | temp_r3_11) >> 0x1F) != 0)
    {
        temp_r4_11 = 1 << (temp_r3_11 >> 0x18);
        alignedOffset_11 = (s32)((char*)chunkPtr_6 + temp_r4_11 + 7) & ~(temp_r4_11 - 1);
    }
    else
    {
        alignedOffset_11 = (s32)((char*)chunkPtr_6 + 8);
    }
    ((cSHierarchy*)alignedOffset)->m_boneLengthFlags = (bool*)alignedOffset_11;
    return (cSHierarchy*)alignedOffset;
}

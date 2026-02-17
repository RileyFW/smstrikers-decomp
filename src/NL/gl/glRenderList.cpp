#include "NL/gl/glRenderList.h"
#include "NL/nlSlotPool.h"

/**
 * Offset/Address/Size: 0x0 | 0x801D92C0 | size: 0x36C
 */
void GLRenderList::AttachModel(const glModel*, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x36C | 0x801D962C | size: 0xD4
 */
void gl_ViewAttachPacket(eGLView view, unsigned long layer, const glModelPacket* pPacket)
{
    GLRenderList* pList = gl_ViewGetRenderList(view);
    const glModelPacket* pKey = pPacket;

    if ((s32)pList->m_unk_0x00 < 0x1A && glRenderBuffer.m_bEnabled && glRenderBuffer.m_bExclusive && !glRenderBuffer.m_bSending)
    {
        return;
    }

    GLTexturePacketTree* pTree = pList->texPacketTree[layer];
    const unsigned int& one = 1;
    AVLTreeNode* existingNode;
    pTree->AddAVLNode((AVLTreeNode**)&pTree->m_Root, &pKey, (void*)&one, &existingNode, pTree->m_NumElements);

    unsigned int* pCount;
    if (existingNode == NULL)
    {
        pTree->m_NumElements++;
        pCount = NULL;
    }
    else
    {
        pCount = &((AVLTreeEntry<const glModelPacket*, unsigned int>*)existingNode)->value;
    }

    if (pCount != NULL)
    {
        (*pCount)++;
    }
}

/**
 * Offset/Address/Size: 0x440 | 0x801D9700 | size: 0x290
 */
void GLRenderList::Iterate(eGLView, void (*)(eGLView, unsigned long, const glModelPacket*))
{
}

/**
 * Offset/Address/Size: 0x6D0 | 0x801D9990 | size: 0x28
 */
void PacketCallbackManager::ListCallback(const glModelPacket** pPacketPtr)
{
    DoCallback(*pPacketPtr, 1);
}

/**
 * Offset/Address/Size: 0x6F8 | 0x801D99B8 | size: 0x28
 */
void PacketCallbackManager::DepthCallback(const DepthPacketPair& key, unsigned int* count)
{
    DoCallback(key.packet, *count);
}

/**
 * Offset/Address/Size: 0x720 | 0x801D99E0 | size: 0x28
 */
void PacketCallbackManager::TexCallback(const glModelPacket* const& key, unsigned int* count)
{
    DoCallback(key, *count);
}

/**
 * Offset/Address/Size: 0x748 | 0x801D9A08 | size: 0x298
 */
void PacketCallbackManager::DoCallback(const glModelPacket*, unsigned int)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x9E0 | 0x801D9CA0 | size: 0x108
 * TODO: 90.2% match - MWCC loop unrolling uses static offsets instead of
 * per-iteration addi r3,r3,4 pointer bumps seen in target
 */
bool GLRenderList::IsEmpty() const
{
    if (m_unk_0x04 == GLVSort_Texture)
    {
        for (unsigned int layer = 0; layer < 7u; layer++)
        {
            if (texPacketTree[layer]->m_Root != NULL)
            {
                return false;
            }
        }
        return true;
    }
    if (m_unk_0x04 == GLVSort_TransformedDepth || m_unk_0x04 == GLVSort_TransformedMatrixDepth)
    {
        return depthPacketTree->m_Root == NULL;
    }
    return packetList->m_Head == NULL;
}

/**
 * Offset/Address/Size: 0xAE8 | 0x801D9DA8 | size: 0x80
 */
void GLRenderList::Compact()
{
    Clear();

    for (int i = 0; i < 7; i++)
    {
        u32* ptr = (u32*)((u8*)this + 0x0C + i * 4);
        SlotPoolBase::BaseFreeBlocks((SlotPoolBase*)(*ptr + 4), 0x14);
    }

    u32 poolAddr2 = *(u32*)((u8*)this + 0x28);
    SlotPoolBase::BaseFreeBlocks((SlotPoolBase*)(poolAddr2 + 4), 0x18);

    u32 poolAddr3 = *(u32*)((u8*)this + 0x2C);
    SlotPoolBase::BaseFreeBlocks((SlotPoolBase*)poolAddr3, 0x0C);
}

/**
 * Offset/Address/Size: 0xB68 | 0x801D9E28 | size: 0xA0
 */
typedef DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*> > > GLPacketListBase;

void GLRenderList::Clear()
{
    GLPacketListBase* pList;
    int i;
    for (i = 0; i < 7; i++)
    {
        texPacketTree[i]->Clear();
    }
    depthPacketTree->Clear();

    pList = packetList;
    nlWalkDLRing(pList->m_Head, pList, &GLPacketListBase::DeleteEntry);
    pList->m_Head = NULL;
    uDepthInsertNumber = 0;
}

/**
 * Offset/Address/Size: 0xC08 | 0x801D9EC8 | size: 0x1B0
 */
GLRenderList::GLRenderList()
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x801DA078 | size: 0x34
//  */
// void WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>::Callback(DLListEntry<const glModelPacket*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801DA0AC | size: 0x10
//  */
// void AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::DeleteEntry(AVLTreeEntry<const glModelPacket*, unsigned int>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x10 | 0x801DA0BC | size: 0x10
//  */
// void AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::DeleteEntry(AVLTreeEntry<DepthPacketPair, unsigned int>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x20 | 0x801DA0CC | size: 0x44
//  */
// void AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::Walk<PacketCallbackManager>(PacketCallbackManager*, void (PacketCallbackManager::*)(const DepthPacketPair&, unsigned int*))
// {
// }

// /**
//  * Offset/Address/Size: 0x64 | 0x801DA110 | size: 0x2CC
//  */
// void AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::InorderWalk<PacketCallbackManager>(AVLTreeEntry<DepthPacketPair, unsigned int>*, PacketCallbackManager*, void (PacketCallbackManager::*)(const DepthPacketPair&, unsigned int*))
// {
// }

// /**
//  * Offset/Address/Size: 0x330 | 0x801DA3DC | size: 0x8
//  */
// void AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x338 | 0x801DA3E4 | size: 0x44
//  */
// void AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::Walk<PacketCallbackManager>(PacketCallbackManager*, void (PacketCallbackManager::*)(const glModelPacket* const&, unsigned int*))
// {
// }

// /**
//  * Offset/Address/Size: 0x37C | 0x801DA428 | size: 0x2CC
//  */
// void AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::InorderWalk<PacketCallbackManager>(AVLTreeEntry<const glModelPacket*, unsigned int>*, PacketCallbackManager*, void (PacketCallbackManager::*)(const glModelPacket* const&, unsigned int*))
// {
// }

// /**
//  * Offset/Address/Size: 0x648 | 0x801DA6F4 | size: 0x8
//  */
// void AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x650 | 0x801DA6FC | size: 0x58
//  */
// void AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0x6A8 | 0x801DA754 | size: 0x64
//  */
// void AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::DestroyTree(void (AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::*)(AVLTreeEntry<DepthPacketPair, unsigned int>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x70C | 0x801DA7B8 | size: 0x758
//  */
// void AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::PostorderTraversal(AVLTreeEntry<DepthPacketPair, unsigned int>*, void (AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::*)(AVLTreeEntry<DepthPacketPair, unsigned int>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xE64 | 0x801DAF10 | size: 0x58
//  */
// void AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0xEBC | 0x801DAF68 | size: 0x64
//  */
// void AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::DestroyTree(void (AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::*)(AVLTreeEntry<const glModelPacket*, unsigned int>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xF20 | 0x801DAFCC | size: 0x758
//  */
// void AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::PostorderTraversal(AVLTreeEntry<const glModelPacket*, unsigned int>*, void (AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::*)(AVLTreeEntry<const glModelPacket*, unsigned int>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x1678 | 0x801DB724 | size: 0x50
//  */
// void AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x16C8 | 0x801DB774 | size: 0x50
//  */
// void AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1718 | 0x801DB7C4 | size: 0xBC
//  */
// void AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x17D4 | 0x801DB880 | size: 0xBC
//  */
// void AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1890 | 0x801DB93C | size: 0xA0
//  */
// void AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1930 | 0x801DB9DC | size: 0xA8
//  */
// void AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801DBA84 | size: 0x10
//  */
// void DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>::DeleteEntry(DLListEntry<const glModelPacket*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801DBA94 | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<const glModelPacket*>, WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>>(DLListEntry<const glModelPacket*>*, WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>*, void (WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>::*)(DLListEntry<const glModelPacket*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x801DBAD0 | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<const glModelPacket*>, DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>>(DLListEntry<const glModelPacket*>*, DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>*, void (DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>::*)(DLListEntry<const glModelPacket*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x78 | 0x801DBB0C | size: 0x3C
//  */
// void nlDLRingAddEnd<DLListEntry<const glModelPacket*>>(DLListEntry<const glModelPacket*>**, DLListEntry<const glModelPacket*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xB4 | 0x801DBB48 | size: 0x38
//  */
// void nlDLRingAddStart<DLListEntry<const glModelPacket*>>(DLListEntry<const glModelPacket*>**, DLListEntry<const glModelPacket*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801DBB80 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<const glModelPacket*>, DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>>(DLListEntry<const glModelPacket*>*, DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>*, void (DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>::*)(DLListEntry<const glModelPacket*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x60 | 0x801DBBE0 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<const glModelPacket*>, WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>>(DLListEntry<const glModelPacket*>*, WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>*, void (WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>::*)(DLListEntry<const glModelPacket*>*))
// {
// }

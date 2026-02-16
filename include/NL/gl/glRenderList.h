#ifndef _GLRENDERLIST_H_
#define _GLRENDERLIST_H_

// void gl_ViewAttachPacket(eGLView, unsigned long, const glModelPacket*);
// void nlDLRingAddEnd<DLListEntry<const glModelPacket*>>(DLListEntry<const glModelPacket*>**, DLListEntry<const glModelPacket*>*);
// void nlDLRingAddStart<DLListEntry<const glModelPacket*>>(DLListEntry<const glModelPacket*>**, DLListEntry<const glModelPacket*>*);

#include "NL/gl/glView.h"
#include "NL/nlAVLTreeSlotPool.h"
#include "NL/nlDLListSlotPool.h"
#include "Game/GL/GLRenderBuffer.h"

class glModel;
class TextureTreeCompare;

struct DepthPacketPair
{
    /* 0x0 */ unsigned long sortKey;
    /* 0x4 */ const glModelPacket* packet;
}; // total size: 0x8
class DepthTreeCompare;

typedef nlAVLTreeSlotPool<const glModelPacket*, unsigned int, TextureTreeCompare> GLTexturePacketTree;
typedef nlAVLTreeSlotPool<DepthPacketPair, unsigned int, DepthTreeCompare> GLDepthPacketTree;

typedef nlDLListSlotPool<const glModelPacket*> GLPacketList;

extern GLRenderBuffer glRenderBuffer;

class GLRenderList // size: 0x30
{
public:
    void AttachModel(const glModel*, unsigned long);
    void Iterate(eGLView, void (*)(eGLView, unsigned long, const glModelPacket*));
    bool IsEmpty() const;
    void Compact();
    void Clear();

    GLRenderList();

    /* 0x00 */ u32 m_unk_0x00;
    /* 0x04 */ eGLViewSort m_unk_0x04;
    /* 0x08 */ unsigned long uDepthInsertNumber;
    /* 0x0C */ GLTexturePacketTree* texPacketTree[7];
    /* 0x28 */ GLDepthPacketTree* depthPacketTree;
    /* 0x2C */ GLPacketList* packetList;
};

class PacketCallbackManager
{
public:
    void ListCallback(const glModelPacket**);
    void DepthCallback(const DepthPacketPair&, unsigned int*);
    void TexCallback(const glModelPacket* const&, unsigned int*);
    void DoCallback(const glModelPacket*, unsigned int);
};

// class WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>
// {
// public:
//     void Callback(DLListEntry<const glModelPacket*>*);
// };

// class AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>
// {
// public:
//     void DeleteEntry(AVLTreeEntry<const glModelPacket*, unsigned int>*);
//     void Walk<PacketCallbackManager>(PacketCallbackManager*, void (PacketCallbackManager::*)(const glModelPacket* const&, unsigned int*));
//     void InorderWalk<PacketCallbackManager>(AVLTreeEntry<const glModelPacket*, unsigned int>*, PacketCallbackManager*, void (PacketCallbackManager::*)(const glModelPacket* const&, unsigned int*));
//     void CastUp(AVLTreeNode*) const;
//     void Clear();
//     void DestroyTree(void (AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::*)(AVLTreeEntry<const glModelPacket*, unsigned int>*));
//     void PostorderTraversal(AVLTreeEntry<const glModelPacket*, unsigned int>*, void (AVLTreeBase<const glModelPacket*, unsigned int, BasicSlotPool<AVLTreeEntry<const glModelPacket*, unsigned int>>, TextureTreeCompare>::*)(AVLTreeEntry<const glModelPacket*, unsigned int>*));
//     void CompareNodes(AVLTreeNode*, AVLTreeNode*);
//     void CompareKey(void*, AVLTreeNode*);
//     void AllocateEntry(void*, void*);
// };

// class AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>
// {
// public:
//     void DeleteEntry(AVLTreeEntry<DepthPacketPair, unsigned int>*);
//     void Walk<PacketCallbackManager>(PacketCallbackManager*, void (PacketCallbackManager::*)(const DepthPacketPair&, unsigned int*));
//     void InorderWalk<PacketCallbackManager>(AVLTreeEntry<DepthPacketPair, unsigned int>*, PacketCallbackManager*, void (PacketCallbackManager::*)(const DepthPacketPair&, unsigned int*));
//     void CastUp(AVLTreeNode*) const;
//     void Clear();
//     void DestroyTree(void (AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::*)(AVLTreeEntry<DepthPacketPair, unsigned int>*));
//     void PostorderTraversal(AVLTreeEntry<DepthPacketPair, unsigned int>*, void (AVLTreeBase<DepthPacketPair, unsigned int, BasicSlotPool<AVLTreeEntry<DepthPacketPair, unsigned int>>, DepthTreeCompare>::*)(AVLTreeEntry<DepthPacketPair, unsigned int>*));
//     void CompareNodes(AVLTreeNode*, AVLTreeNode*);
//     void CompareKey(void*, AVLTreeNode*);
//     void AllocateEntry(void*, void*);
// };

// class DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>
// {
// public:
//     void DeleteEntry(DLListEntry<const glModelPacket*>*);
// };

// class nlWalkDLRing<DLListEntry<const glModelPacket*>, WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>>(DLListEntry<const glModelPacket*>*, WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>*, void (WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>
// {
// public:
//     void *)(DLListEntry<const glModelPacket*>*));
// };

// class nlWalkDLRing<DLListEntry<const glModelPacket*>, DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>>(DLListEntry<const glModelPacket*>*, DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>*, void (DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>
// {
// public:
//     void *)(DLListEntry<const glModelPacket*>*));
// };

// class nlWalkRing<DLListEntry<const glModelPacket*>, DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>>(DLListEntry<const glModelPacket*>*, DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>*, void (DLListContainerBase<const glModelPacket*, BasicSlotPool<DLListEntry<const glModelPacket*>>>
// {
// public:
//     void *)(DLListEntry<const glModelPacket*>*));
// };

// class nlWalkRing<DLListEntry<const glModelPacket*>, WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>>(DLListEntry<const glModelPacket*>*, WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>*, void (WalkHelper<const glModelPacket*, DLListEntry<const glModelPacket*>, PacketCallbackManager>
// {
// public:
//     void *)(DLListEntry<const glModelPacket*>*));
// };

#endif // _GLRENDERLIST_H_

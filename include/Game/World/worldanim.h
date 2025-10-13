#ifndef _WORLDANIM_H_
#define _WORLDANIM_H_

#include "NL/nlList.h"
#include "Game/Render/SkinAnimatedNPC.h"

template <typename T>
class cInventory
{
public:
    /* 0x0 */ nlListContainer<T> m_lItemList;
    /* 0xC */ nlListContainer<T> m_lMemList;
    /* 0x18 */ int m_nItemCount;
}; // total size: 0x1C

class AnimationSet
{
public:
    /* 0x0 */ cInventory<cSHierarchy> m_animInventory;
}; // total size: 0x1C

class WorldAnimController
{
public:
    void SetAnimation(const char* szAnimationName, ePlayMode playMode);
    void SetAnimationTime(float fTime);
    void GetAnimationTime();
    void GetAnimationDuration();

public:
    /* 0x4, */ class cPoseAccumulator* m_pPoseAccumulator;
    /* 0x8, */ class cPN_SAnimController* m_pPoseTree;
    /* 0xC, */ float m_fSpeed;
    /* 0x10 */ class AnimationSet* m_pAnimationSet;
    /* 0x14 */ bool m_bIsGanged;
}; // total size: 0x18

class WorldAnimManager
{
public:
    WorldAnimManager();
    ~WorldAnimManager();
};

// class nlAVLTree<unsigned long, AnimationSet*, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void ~nlAVLTree();
// };

// class AVLTreeBase<unsigned long, AnimationSet*, NewAdapter<AVLTreeEntry<unsigned long, AnimationSet*>>, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void DeleteEntry(AVLTreeEntry<unsigned long, AnimationSet*>*);
//     void AllocateEntry(void*, void*);
//     void CompareKey(void*, AVLTreeNode*);
//     void CompareNodes(AVLTreeNode*, AVLTreeNode*);
//     void CastUp(AVLTreeNode*) const;
//     void PostorderTraversal(AVLTreeEntry<unsigned long, AnimationSet*>*, void (AVLTreeBase<unsigned long, AnimationSet*, NewAdapter<AVLTreeEntry<unsigned long, AnimationSet*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, AnimationSet*>*));
//     void DestroyTree(void (AVLTreeBase<unsigned long, AnimationSet*, NewAdapter<AVLTreeEntry<unsigned long, AnimationSet*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, AnimationSet*>*));
//     void Clear();
//     void ~AVLTreeBase();
// };

#endif // _WORLDANIM_H_

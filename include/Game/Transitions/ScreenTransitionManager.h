#ifndef _SCREENTRANSITIONMANAGER_H_
#define _SCREENTRANSITIONMANAGER_H_

#include "NL/gl/glView.h"
#include "NL/nlSingleton.h"
#include "NL/nlVector.h"
#include "NL/nlAVLTree.h"

class ScreenTransition
{
public:
    /* 0x08 */ virtual ~ScreenTransition() { };
    /* 0x0C */ virtual void Update(float) = 0;
    /* 0x10 */ virtual void Render(eGLView) = 0;
    /* 0x14 */ virtual bool IsFinished() = 0;
    /* 0x18 */ virtual float Time() const = 0;
    /* 0x1C */ virtual void CutTime() const { };
    /* 0x20 */ virtual void Reset() = 0;
    /* 0x24 */ virtual void Cancel() = 0;
    /* 0x28 */ virtual float GetTransitionLength() = 0;
    /* 0x2C */ virtual void DoSanityCheck() { };
};

class ScreenTransitionCallback
{
public:
    virtual inline void TransitionFinished();
    virtual inline void TransitionProgressed(float);
    virtual inline void Cut();
    virtual inline void SequenceSwitch();
};

class ScreenTransitionManager : public nlSingleton<ScreenTransitionManager>
{
public:
    ScreenTransitionManager();
    virtual ~ScreenTransitionManager();
    void Render(float);
    void CancelAllTransitions();
    void DeleteAllTransitions();
    void AddTransitionToMap(char*, ScreenTransition*);
    void EnableRandomTransition(const char*);
    void SelectRandomTransition(const char*);
    void GetSelectedTransitionCutTime() const;
    void EnableSelectedTransition();
    void AddTransitions(char* loadedData, unsigned long fileSize);

    /* 0x04 */ ScreenTransition* m_pActiveTransition;
    /* 0x08 */ nlAVLTree<unsigned long, ScreenTransition*, DefaultKeyCompare<unsigned long> > m_TransitionMap;

    /* 0x1C */ eGLView m_eView;
    /* 0x20 */ ScreenTransitionCallback* m_pCallback;
    /* 0x24 */ ScreenTransition* m_SelectedTransition;
    /* 0x28 */ float m_fCurrentTime;
    /* 0x2C */ float m_fCurrentLength;
    /* 0x30 */ Vector m_Transitions;
    /* 0x3C */ bool m_Cut;
}; // total size: 0x40

// class nlAVLTree<unsigned long, ScreenTransition*, DefaultKeyCompare<unsigned long> >
// {
// public:
//     void ~nlAVLTree();
// };

// class BasicString < char, Detail
// {
// public:
//     void TempStringAllocator > ::BasicString();
// };

// class Vector < BasicString < char, Detail
// {
// public:
//     void TempStringAllocator >, DefaultAllocator > ::reserve(int);
//     void TempStringAllocator >, DefaultAllocator > ::insert(BasicString<char, Detail::TempStringAllocator>*, const BasicString<char, Detail::TempStringAllocator>*, const BasicString<char, Detail::TempStringAllocator>*);
//     void TempStringAllocator >, DefaultAllocator > ::push_back(const BasicString<char, Detail::TempStringAllocator>&);
// };

// class AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >
// {
// public:
//     void DeleteEntry(AVLTreeEntry<unsigned long, ScreenTransition*>*);
//     void AllocateEntry(void*, void*);
//     void CompareKey(void*, AVLTreeNode*);
//     void CompareNodes(AVLTreeNode*, AVLTreeNode*);
//     void DeleteValue(AVLTreeEntry<unsigned long, ScreenTransition*>*);
//     void Clear();
//     void ~AVLTreeBase();
//     void CastUp(AVLTreeNode*) const;
//     void PostorderTraversal(AVLTreeEntry<unsigned long, ScreenTransition*>*, void (AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::*)(AVLTreeEntry<unsigned long, ScreenTransition*>*));
//     void DestroyTree(void (AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::*)(AVLTreeEntry<unsigned long, ScreenTransition*>*));
//     void DeleteValues();
// };

// class NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >
// {
// public:
//     void Delete(AVLTreeEntry<unsigned long, ScreenTransition*>*);
// };

#endif // _SCREENTRANSITIONMANAGER_H_

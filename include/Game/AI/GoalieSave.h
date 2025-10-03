#ifndef _GOALIESAVE_H_
#define _GOALIESAVE_H_

void InsertSorted(nlDLListContainer<MyMiniData*>&, MyMiniData*);
void nlListAddStart<ListEntry<SaveData*>>(ListEntry<SaveData*>**, ListEntry<SaveData*>*, ListEntry<SaveData*>**);
void nlDLRingIsStart<DLListEntry<MyMiniData*>>(DLListEntry<MyMiniData*>*, DLListEntry<MyMiniData*>*);
void nlDLRingIsEnd<DLListEntry<MyMiniData*>>(DLListEntry<MyMiniData*>*, DLListEntry<MyMiniData*>*);
void nlDLRingGetStart<DLListEntry<MyMiniData*>>(DLListEntry<MyMiniData*>*);
void nlDLRingAddEnd<DLListEntry<MyMiniData*>>(DLListEntry<MyMiniData*>**, DLListEntry<MyMiniData*>*);
void nlDLRingAddStart<DLListEntry<MyMiniData*>>(DLListEntry<MyMiniData*>**, DLListEntry<MyMiniData*>*);
void nlDLRingInsert<DLListEntry<MyMiniData*>>(DLListEntry<MyMiniData*>**, DLListEntry<MyMiniData*>*, DLListEntry<MyMiniData*>*);
void 0x8028D298..0x8028D29C | size: 0x4;

class GoalieSave
{
public:
    void ClearData();
    void InitData(Goalie*);
    void FindBestSave(SaveBlendInfo&, const nlVector3&, float, bool, unsigned int, bool);
    void FindBestInList(SaveBlendInfo&, nlListContainer<SaveData*>&, const nlVector3&, float, unsigned int, bool);
    void GetClosestBlendedPos(SaveBlendInfo&, const nlVector3&, SaveData*);
    void GetMissChipSaveData(bool, bool);
    void GetRandomSTSMissData(bool);
    void GetSTSSpinMissData(bool);
    void GetRandomSTSSaveData();
    void TriggerCallback(float, float, unsigned long, float, void*);
    void AddAreaToGrid(SaveData*);
    void AddSegmentToGrid(SaveData*, SaveData*);
    void AddChainToGrid(SaveData*, bool);
    void AddToGrid(SaveData*);
};


class AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>
{
public:
    void AllocateEntry(void*, void*);
    void CompareKey(void*, AVLTreeNode*);
    void CompareNodes(AVLTreeNode*, AVLTreeNode*);
    void ~AVLTreeBase();
    void CastUp(AVLTreeNode*) const;
    void PostorderTraversal(AVLTreeEntry<int, SaveData*>*, void (AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>::*)(AVLTreeEntry<int, SaveData*>*));
    void DestroyTree(void (AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>::*)(AVLTreeEntry<int, SaveData*>*));
    void Clear();
    void DeleteEntry(AVLTreeEntry<int, SaveData*>*);
};


class DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>
{
public:
    void DeleteEntry(DLListEntry<MyMiniData*>*);
};


class ListContainerBase<SaveData*, NewAdapter<ListEntry<SaveData*>>>
{
public:
    void DeleteEntry(ListEntry<SaveData*>*);
};


class nlListContainer<SaveData*>
{
public:
    void nlListContainer();
    void ~nlListContainer();
};


class nlAVLTree<int, SaveData*, DefaultKeyCompare<int>>
{
public:
    void ~nlAVLTree();
};


class nlWalkList<ListEntry<SaveData*>, ListContainerBase<SaveData*, NewAdapter<ListEntry<SaveData*>>>>(ListEntry<SaveData*>*, ListContainerBase<SaveData*, NewAdapter<ListEntry<SaveData*>>>*, void (ListContainerBase<SaveData*, NewAdapter<ListEntry<SaveData*>>>
{
public:
    void *)(ListEntry<SaveData*>*));
};


class nlWalkDLRing<DLListEntry<MyMiniData*>, DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>>(DLListEntry<MyMiniData*>*, DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>*, void (DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>
{
public:
    void *)(DLListEntry<MyMiniData*>*));
};


class nlWalkRing<DLListEntry<MyMiniData*>, DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>>(DLListEntry<MyMiniData*>*, DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>*, void (DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>
{
public:
    void *)(DLListEntry<MyMiniData*>*));
};

#endif // _GOALIESAVE_H_
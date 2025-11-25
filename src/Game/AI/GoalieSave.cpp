#include "Game/AI/GoalieSave.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x80056D60 | size: 0xA4
//  */
// void 0x8028D298..0x8028D29C | size: 0x4
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80056D00 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<MyMiniData*>, DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>>(DLListEntry<MyMiniData*>*, DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>*, void (DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>::*)(DLListEntry<MyMiniData*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x10C | 0x80056CD4 | size: 0x2C
//  */
// void nlDLRingInsert<DLListEntry<MyMiniData*>>(DLListEntry<MyMiniData*>**, DLListEntry<MyMiniData*>*, DLListEntry<MyMiniData*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xD4 | 0x80056C9C | size: 0x38
//  */
// void nlDLRingAddStart<DLListEntry<MyMiniData*>>(DLListEntry<MyMiniData*>**, DLListEntry<MyMiniData*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x98 | 0x80056C60 | size: 0x3C
//  */
// void nlDLRingAddEnd<DLListEntry<MyMiniData*>>(DLListEntry<MyMiniData*>**, DLListEntry<MyMiniData*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x80 | 0x80056C48 | size: 0x18
//  */
// void nlDLRingGetStart<DLListEntry<MyMiniData*>>(DLListEntry<MyMiniData*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x60 | 0x80056C28 | size: 0x20
//  */
// void nlDLRingIsEnd<DLListEntry<MyMiniData*>>(DLListEntry<MyMiniData*>*, DLListEntry<MyMiniData*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x80056C04 | size: 0x24
//  */
// void nlDLRingIsStart<DLListEntry<MyMiniData*>>(DLListEntry<MyMiniData*>*, DLListEntry<MyMiniData*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80056BC8 | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<MyMiniData*>, DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>>(DLListEntry<MyMiniData*>*, DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>*, void (DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>::*)(DLListEntry<MyMiniData*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x68 | 0x80056BA0 | size: 0x28
//  */
// void nlListAddStart<ListEntry<SaveData*>>(ListEntry<SaveData*>**, ListEntry<SaveData*>*, ListEntry<SaveData*>**)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80056B38 | size: 0x68
//  */
// void nlWalkList<ListEntry<SaveData*>, ListContainerBase<SaveData*, NewAdapter<ListEntry<SaveData*>>>>(ListEntry<SaveData*>*, ListContainerBase<SaveData*, NewAdapter<ListEntry<SaveData*>>>*, void (ListContainerBase<SaveData*, NewAdapter<ListEntry<SaveData*>>>::*)(ListEntry<SaveData*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x118 | 0x80056AD8 | size: 0x60
//  */
// void nlAVLTree<int, SaveData*, DefaultKeyCompare<int>>::~nlAVLTree()
// {
// }

// /**
//  * Offset/Address/Size: 0x108 | 0x80056AC8 | size: 0x10
//  */
// void nlListContainer<SaveData*>::nlListContainer()
// {
// }

// /**
//  * Offset/Address/Size: 0x5C | 0x80056A1C | size: 0xAC
//  */
// void nlListContainer<SaveData*>::~nlListContainer()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800569C0 | size: 0x24
//  */
// void ListContainerBase<SaveData*, NewAdapter<ListEntry<SaveData*>>>::DeleteEntry(ListEntry<SaveData*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8005699C | size: 0x24
//  */
// void DLListContainerBase<MyMiniData*, NewAdapter<DLListEntry<MyMiniData*>>>::DeleteEntry(DLListEntry<MyMiniData*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x8F4 | 0x80056938 | size: 0x64
//  */
// void AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x8C8 | 0x8005690C | size: 0x2C
//  */
// void AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x89C | 0x800568E0 | size: 0x2C
//  */
// void AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x840 | 0x80056884 | size: 0x5C
//  */
// void AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>::~AVLTreeBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x838 | 0x8005687C | size: 0x8
//  */
// void AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0xE0 | 0x80056124 | size: 0x758
//  */
// void AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>::PostorderTraversal(AVLTreeEntry<int, SaveData*>*, void (AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>::*)(AVLTreeEntry<int, SaveData*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x7C | 0x800560C0 | size: 0x64
//  */
// void AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>::DestroyTree(void (AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>::*)(AVLTreeEntry<int, SaveData*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x24 | 0x80056068 | size: 0x58
//  */
// void AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80056044 | size: 0x24
//  */
// void AVLTreeBase<int, SaveData*, NewAdapter<AVLTreeEntry<int, SaveData*>>, DefaultKeyCompare<int>>::DeleteEntry(AVLTreeEntry<int, SaveData*>*)
// {
// }

/**
 * Offset/Address/Size: 0x2B44 | 0x80055F64 | size: 0xE0
 */
void GoalieSave::ClearData()
{
}

/**
 * Offset/Address/Size: 0x23F4 | 0x80055814 | size: 0x750
 */
void GoalieSave::InitData(Goalie*)
{
}

// /**
//  * Offset/Address/Size: 0x227C | 0x8005569C | size: 0x178
//  */
// void InsertSorted(nlDLListContainer<MyMiniData*>&, MyMiniData*)
// {
// }

/**
 * Offset/Address/Size: 0x1FC0 | 0x800553E0 | size: 0x2BC
 */

SaveData* GoalieSave::FindBestSave(SaveBlendInfo& blendInfo, const nlVector3& v3LocalPos, float fTime, bool bDoNearSearch, unsigned int uSaveType, bool bFromTakeoff)
{
    return NULL;
}

/**
 * Offset/Address/Size: 0x1A1C | 0x80054E3C | size: 0x5A4
 */
void GoalieSave::FindBestInList(SaveBlendInfo&, nlListContainer<SaveData*>&, const nlVector3&, float, unsigned int, bool)
{
}

/**
 * Offset/Address/Size: 0xF90 | 0x800543B0 | size: 0xA8C
 */
void GoalieSave::GetClosestBlendedPos(SaveBlendInfo&, const nlVector3&, SaveData*)
{
}

/**
 * Offset/Address/Size: 0xF4C | 0x8005436C | size: 0x44
 */
SaveData* GoalieSave::GetMissChipSaveData(bool, bool)
{
    return NULL;
}

/**
 * Offset/Address/Size: 0xEBC | 0x800542DC | size: 0x90
 */
SaveData* GoalieSave::GetRandomSTSMissData(bool)
{
    return NULL;
}

/**
 * Offset/Address/Size: 0xE98 | 0x800542B8 | size: 0x24
 */
SaveData* GoalieSave::GetSTSSpinMissData(bool)
{
    return NULL;
}

/**
 * Offset/Address/Size: 0xE24 | 0x80054244 | size: 0x74
 */
SaveData* GoalieSave::GetRandomSTSSaveData()
{
    return NULL;
}

/**
 * Offset/Address/Size: 0xDCC | 0x800541EC | size: 0x58
 */
void GoalieSave::TriggerCallback(float, float, unsigned long, float, void*)
{
}

/**
 * Offset/Address/Size: 0x780 | 0x80053BA0 | size: 0x64C
 */
void GoalieSave::AddAreaToGrid(SaveData*)
{
}

/**
 * Offset/Address/Size: 0x390 | 0x800537B0 | size: 0x3F0
 */
void GoalieSave::AddSegmentToGrid(SaveData*, SaveData*)
{
}

/**
 * Offset/Address/Size: 0x20C | 0x8005362C | size: 0x184
 */
void GoalieSave::AddChainToGrid(SaveData*, bool)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80053420 | size: 0x20C
 */
void GoalieSave::AddToGrid(SaveData*)
{
}

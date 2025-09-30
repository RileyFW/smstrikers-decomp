#include "Game/Transitions/ScreenTransitionManager.h"

/**
 * Offset/Address/Size: 0x0 | 0x80206908 | size: 0x24
 */
void NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >::Delete(AVLTreeEntry<unsigned long, ScreenTransition*>*)
{
}

/**
 * Offset/Address/Size: 0x9EC | 0x802068E4 | size: 0x24
 */
void AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::DeleteEntry(AVLTreeEntry<unsigned long, ScreenTransition*>*)
{
}

/**
 * Offset/Address/Size: 0x988 | 0x80206880 | size: 0x64
 */
void AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::AllocateEntry(void*, void*)
{
}

/**
 * Offset/Address/Size: 0x95C | 0x80206854 | size: 0x2C
 */
void AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::CompareKey(void*, AVLTreeNode*)
{
}

/**
 * Offset/Address/Size: 0x930 | 0x80206828 | size: 0x2C
 */
void AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::CompareNodes(AVLTreeNode*, AVLTreeNode*)
{
}

/**
 * Offset/Address/Size: 0x8D0 | 0x802067C8 | size: 0x60
 */
void AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::DeleteValue(AVLTreeEntry<unsigned long, ScreenTransition*>*)
{
}

/**
 * Offset/Address/Size: 0x878 | 0x80206770 | size: 0x58
 */
void AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::Clear()
{
}

/**
 * Offset/Address/Size: 0x81C | 0x80206714 | size: 0x5C
 */
void AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::~AVLTreeBase()
{
}

/**
 * Offset/Address/Size: 0x814 | 0x8020670C | size: 0x8
 */
void AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::CastUp(AVLTreeNode*) const
{
}

/**
 * Offset/Address/Size: 0xBC | 0x80205FB4 | size: 0x758
 */
void AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::PostorderTraversal(AVLTreeEntry<unsigned long, ScreenTransition*>*, void (AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::*)(AVLTreeEntry<unsigned long, ScreenTransition*>*))
{
}

/**
 * Offset/Address/Size: 0x58 | 0x80205F50 | size: 0x64
 */
void AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::DestroyTree(void (AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::*)(AVLTreeEntry<unsigned long, ScreenTransition*>*))
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80205EF8 | size: 0x58
 */
void AVLTreeBase<unsigned long, ScreenTransition*, NewAdapter<AVLTreeEntry<unsigned long, ScreenTransition*> >, DefaultKeyCompare<unsigned long> >::DeleteValues()
{
}

/**
 * Offset/Address/Size: 0x1C0 | 0x80205D3C | size: 0x1BC
 */
void Vector<BasicString<char, Detail::TempStringAllocator>, DefaultAllocator>::reserve(int)
{
}

/**
 * Offset/Address/Size: 0x38 | 0x80205BB4 | size: 0x188
 */
void Vector<BasicString<char, Detail::TempStringAllocator>, DefaultAllocator>::insert(BasicString<char, Detail::TempStringAllocator>*, const BasicString<char, Detail::TempStringAllocator>*, const BasicString<char, Detail::TempStringAllocator>*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80205B7C | size: 0x38
 */
void Vector<BasicString<char, Detail::TempStringAllocator>, DefaultAllocator>::push_back(const BasicString<char, Detail::TempStringAllocator>&)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80205B70 | size: 0xC
 */
void BasicString<char, Detail::TempStringAllocator>::BasicString()
{
}

/**
 * Offset/Address/Size: 0x9DC | 0x80205ACC | size: 0xA4
 */
ScreenTransitionManager::ScreenTransitionManager()
{
}

/**
 * Offset/Address/Size: 0x97C | 0x80205A6C | size: 0x60
 */
void nlAVLTree<unsigned long, ScreenTransition*, DefaultKeyCompare<unsigned long> >::~nlAVLTree()
{
}

/**
 * Offset/Address/Size: 0x8FC | 0x802059EC | size: 0x80
 */
ScreenTransitionManager::~ScreenTransitionManager()
{
}

/**
 * Offset/Address/Size: 0x7F4 | 0x802058E4 | size: 0x108
 */
void ScreenTransitionManager::Render(float)
{
}

/**
 * Offset/Address/Size: 0x78C | 0x8020587C | size: 0x68
 */
void ScreenTransitionManager::CancelAllTransitions()
{
}

/**
 * Offset/Address/Size: 0x71C | 0x8020580C | size: 0x70
 */
void ScreenTransitionManager::DeleteAllTransitions()
{
}

/**
 * Offset/Address/Size: 0x5A4 | 0x80205694 | size: 0x178
 */
void ScreenTransitionManager::AddTransitionToMap(char*, ScreenTransition*)
{
}

/**
 * Offset/Address/Size: 0x504 | 0x802055F4 | size: 0xA0
 */
void ScreenTransitionManager::EnableRandomTransition(const char*)
{
}

/**
 * Offset/Address/Size: 0x33C | 0x8020542C | size: 0x1C8
 */
void ScreenTransitionManager::SelectRandomTransition(const char*)
{
}

/**
 * Offset/Address/Size: 0x2FC | 0x802053EC | size: 0x40
 */
void ScreenTransitionManager::GetSelectedTransitionCutTime() const
{
}

/**
 * Offset/Address/Size: 0x260 | 0x80205350 | size: 0x9C
 */
void ScreenTransitionManager::EnableSelectedTransition()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x802050F0 | size: 0x260
 */
void ScreenTransitionManager::AddTransitions(char*, unsigned long)
{
}

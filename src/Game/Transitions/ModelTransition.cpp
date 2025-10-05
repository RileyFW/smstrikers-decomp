#include "Game/Transitions/ModelTransition.h"

#include "NL/nlMath.h"

// /**
//  * Offset/Address/Size: 0xA04 | 0x80204CA0 | size: 0x24
//  */
// void AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore> >, DefaultKeyCompare<unsigned long> >::DeleteEntry(AVLTreeEntry<unsigned long, TransitionModelStore>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x998 | 0x80204C34 | size: 0x6C
//  */
// void AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore> >, DefaultKeyCompare<unsigned long> >::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x96C | 0x80204C08 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore> >, DefaultKeyCompare<unsigned long> >::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x940 | 0x80204BDC | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore> >, DefaultKeyCompare<unsigned long> >::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x938 | 0x80204BD4 | size: 0x8
//  */
// void AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore> >, DefaultKeyCompare<unsigned long> >::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x1E0 | 0x8020447C | size: 0x758
//  */
// void AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore> >, DefaultKeyCompare<unsigned long> >::PostorderTraversal(AVLTreeEntry<unsigned long, TransitionModelStore>*, void (AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore> >, DefaultKeyCompare<unsigned long> >::*)(AVLTreeEntry<unsigned long, TransitionModelStore>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x17C | 0x80204418 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore> >, DefaultKeyCompare<unsigned long> >::DestroyTree(void (AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore> >, DefaultKeyCompare<unsigned long> >::*)(AVLTreeEntry<unsigned long, TransitionModelStore>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x124 | 0x802043C0 | size: 0x58
//  */
// void AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore> >, DefaultKeyCompare<unsigned long> >::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0xC8 | 0x80204364 | size: 0x5C
//  */
// void AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore> >, DefaultKeyCompare<unsigned long> >::~AVLTreeBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x68 | 0x80204304 | size: 0x60
//  */
// void nlAVLTree<unsigned long, TransitionModelStore, DefaultKeyCompare<unsigned long> >::~nlAVLTree()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80204294 | size: 0x8
//  */
// void nlMatrix4::GetTranslation() const
// {
// }

// /**
//  * Offset/Address/Size: 0x50 | 0x80204290 | size: 0x4
//  */
// void ScreenTransition::DoSanityCheck()
// {
// }

// /**
//  * Offset/Address/Size: 0x8 | 0x80204248 | size: 0x48
//  */
// ScreenTransition::~ScreenTransition()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80204240 | size: 0x8
//  */
// void ScreenTransition::CutTime() const
// {
// }

/**
 * Offset/Address/Size: 0x1E60 | 0x80203F24 | size: 0x31C
 */
void GetNumLeafNodesInHierarchy(cSHierarchy&, int, int)
{
}

/**
 * Offset/Address/Size: 0x1BCC | 0x80203C90 | size: 0x294
 */
void ShuffleIntoOutline(Vector<nlVector3, DefaultAllocator>&)
{
}

/**
 * Offset/Address/Size: 0x188C | 0x80203950 | size: 0x340
 */
void UpdateEffectsFromLeafNodes(cPoseAccumulator&, EmissionController**, cSHierarchy&, int, int)
{
}

/**
 * Offset/Address/Size: 0x17E0 | 0x802038A4 | size: 0xAC
 */
ModeledScreenTransition::ModeledScreenTransition()
{
}

/**
 * Offset/Address/Size: 0x15C8 | 0x8020368C | size: 0x218
 */
ModeledScreenTransition::~ModeledScreenTransition()
{
}

/**
 * Offset/Address/Size: 0x15C4 | 0x80203688 | size: 0x4
 */
void ModeledScreenTransition::DoSanityCheck()
{
}

/**
 * Offset/Address/Size: 0x1520 | 0x802035E4 | size: 0xA4
 */
void ModeledScreenTransition::Update(float)
{
}

/**
 * Offset/Address/Size: 0x13EC | 0x802034B0 | size: 0x134
 */
void ModeledScreenTransition::Render(eGLView)
{
}

/**
 * Offset/Address/Size: 0x918 | 0x802029DC | size: 0xAD4
 */
void ModeledScreenTransition::RenderOutline() const
{
}

/**
 * Offset/Address/Size: 0x8DC | 0x802029A0 | size: 0x3C
 */
bool ModeledScreenTransition::IsFinished()
{
    return false;
}

/**
 * Offset/Address/Size: 0x8C0 | 0x80202984 | size: 0x1C
 */
float ModeledScreenTransition::Time() const
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x76C | 0x80202830 | size: 0x154
 */
void ModeledScreenTransition::Reset()
{
}

/**
 * Offset/Address/Size: 0x70C | 0x802027D0 | size: 0x60
 */
void ModeledScreenTransition::Cancel()
{
}

/**
 * Offset/Address/Size: 0x44 | 0x80202108 | size: 0x6C8
 */
ModeledScreenTransition* ModeledScreenTransition::LoadFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x802020C4 | size: 0x44
 */
float ModeledScreenTransition::GetTransitionLength()
{
    return 0.0f;
}

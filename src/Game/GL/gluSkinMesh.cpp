#include "Game/GL/gluSkinMesh.h"

// /**
//  * Offset/Address/Size: 0x38 | 0x801B64C0 | size: 0x18
//  */
// void nlRingGetStart<BoneMapList>(BoneMapList*)
// {
// }

// /**
//  * Offset/Address/Size: 0x20 | 0x801B64A8 | size: 0x18
//  */
// void nlRingGetStart<SkinPairList>(SkinPairList*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801B6488 | size: 0x20
//  */
// void nlRingIsEnd<SkinPairList>(SkinPairList*, SkinPairList*)
// {
// }

// /**
//  * Offset/Address/Size: 0x310 | 0x801B6480 | size: 0x8
//  */
// void AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned
// long>>::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x44 | 0x801B61B4 | size: 0x2CC
//  */
// void AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned
// long>>::InorderWalk<TempMatrixCopier>(AVLTreeEntry<unsigned long, unsigned long>*, TempMatrixCopier*, void (TempMatrixCopier::*)(const
// unsigned long&, unsigned long*))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801B6170 | size: 0x44
//  */
// void AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned
// long>>::Walk<TempMatrixCopier>(TempMatrixCopier*, void (TempMatrixCopier::*)(const unsigned long&, unsigned long*))
// {
// }

/**
 * Offset/Address/Size: 0x550 | 0x801B6094 | size: 0xDC
 */
void ShaderSkinMesh::StitchModel()
{
}

/**
 * Offset/Address/Size: 0x4F0 | 0x801B6034 | size: 0x60
 */
void TempMatrixCopier::CopyMatrix(const unsigned long& boneId, unsigned long* outValue)
{
    SkinMatrix& matrix = (SkinMatrix&)m_Mesh->GetPoseMatrix(boneId);
    matrix.Get(m_TempMatrices[*outValue]);
}

/**
 * Offset/Address/Size: 0x0 | 0x801B5B44 | size: 0x4F0
 */
void ShaderSkinMesh::AttachSkinData(unsigned long, const nlMatrix4*)
{
}

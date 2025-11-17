#ifndef _GLUSKINMESH_H_
#define _GLUSKINMESH_H_

#include "Game/GL/ShaderSkinMesh.h"

class TempMatrixCopier
{
public:
    void CopyMatrix(const unsigned long&, unsigned long*);

    /* 0x00 */ nlMatrix4* m_TempMatrices;
    /* 0x04 */ ShaderSkinMesh* m_Mesh;
}; // total size: 0x8

// class AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void CastUp(AVLTreeNode*) const;
//     void InorderWalk<TempMatrixCopier>(AVLTreeEntry<unsigned long, unsigned long>*, TempMatrixCopier*, void (TempMatrixCopier::*)(const
//     unsigned long&, unsigned long*)); void Walk<TempMatrixCopier>(TempMatrixCopier*, void (TempMatrixCopier::*)(const unsigned long&,
//     unsigned long*));
// };

#endif // _GLUSKINMESH_H_

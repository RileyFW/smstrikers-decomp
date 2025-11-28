#ifndef _GLXLOADMODEL_H_
#define _GLXLOADMODEL_H_

#include "NL/nlMath.h"
#include "NL/gl/glView.h"

class nlChunk;
class glModel;
class BoneMapList;

void glplatEndLoadModel(void*, unsigned long, unsigned long*);
void glplatBeginLoadModel(const char*, void (*)(void*, unsigned long, void*), void*);
glModel* glplatLoadModel(const char* filename, unsigned long* pNumModels);
void glxLoadModelFromMemory(char*, int, unsigned long*, bool);
void glx_MakeSkinMesh(nlChunk*, glModel*);
void glSetIgnoreDuplicateModels(bool);
// void nlRingAddEnd<BoneMapList>(BoneMapList**, BoneMapList*);
// void nlRingAddStart<BoneMapList>(BoneMapList**, BoneMapList*);

// class nlAVLTree<unsigned long, unsigned long, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void ~nlAVLTree();
// };

// class AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void DeleteEntry(AVLTreeEntry<unsigned long, unsigned long>*);
//     void ~AVLTreeBase();
//     void Clear();
//     void DestroyTree(void (AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, unsigned long>*));
//     void PostorderTraversal(AVLTreeEntry<unsigned long, unsigned long>*, void (AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, unsigned long>*));
//     void AllocateEntry(void*, void*);
//     void CompareKey(void*, AVLTreeNode*);
//     void CompareNodes(AVLTreeNode*, AVLTreeNode*);
// };

#endif // _GLXLOADMODEL_H_

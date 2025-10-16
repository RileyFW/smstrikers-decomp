#ifndef _SHADERSKINMESH_H_
#define _SHADERSKINMESH_H_

void nlDeleteRing<SkinPairList>(SkinPairList**);
void nlRingAddEnd<SkinPairList>(SkinPairList**, SkinPairList*);
void nlRingAddStart<SkinPairList>(SkinPairList**, SkinPairList*);
void nlDeleteRing<BoneMapList>(BoneMapList**);

class ShaderSkinMesh
{
public:
    ShaderSkinMesh();
    ~ShaderSkinMesh();
    void SetMorphIDs(const unsigned long*);
    void ConnectToPose(cPoseAccumulator*);
    void SetBoneMatrix(unsigned long, const nlMatrix4*);
    void GetPoseMatrix(unsigned long);
    void GetPoseMatrices(GLSkinMeshMatrix*);
    void SetPoseMatrices(int, GLSkinMeshMatrix*);
    void PrepareToRender(unsigned long, const nlMatrix4*);
    void AppendSkinPairList(int, const SkinPair*);
    void SetSoftwareVertices(int, const SkinVertex*);
    void AppendStitchingInfo(int, int, int, const unsigned char*);
    void MakeUserData(nlAVLTree<unsigned long, unsigned long, DefaultKeyCompare<unsigned long>>*);
    void Pose(cPoseAccumulator*);
    void SetMorphNumDeltas(const unsigned long*);
    void SetMorphDeltas(int, const MorphDelta*);
};


class UserDataBuilder
{
public:
    void AddEntry(const unsigned long&, unsigned long*);
};


class nlAVLTree<unsigned long, SkinMatrix, DefaultKeyCompare<unsigned long>>
{
public:
    void ~nlAVLTree();
};


class AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned long>>
{
public:
    void InorderWalk<UserDataBuilder>(AVLTreeEntry<unsigned long, unsigned long>*, UserDataBuilder*, void (UserDataBuilder::*)(const unsigned long&, unsigned long*));
    void Walk<UserDataBuilder>(UserDataBuilder*, void (UserDataBuilder::*)(const unsigned long&, unsigned long*));
};


class AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix>>, DefaultKeyCompare<unsigned long>>
{
public:
    void DeleteEntry(AVLTreeEntry<unsigned long, SkinMatrix>*);
    void AllocateEntry(void*, void*);
    void CompareKey(void*, AVLTreeNode*);
    void CompareNodes(AVLTreeNode*, AVLTreeNode*);
    void CastUp(AVLTreeNode*) const;
    void PostorderTraversal(AVLTreeEntry<unsigned long, SkinMatrix>*, void (AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, SkinMatrix>*));
    void DestroyTree(void (AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, SkinMatrix>*));
    void Clear();
    void ~AVLTreeBase();
};


class BoneMapList
{
public:
    ~BoneMapList();
};

#endif // _SHADERSKINMESH_H_
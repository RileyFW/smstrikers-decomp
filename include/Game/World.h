#ifndef _WORLD_H_
#define _WORLD_H_

#include "NL/nlMath.h"

// void DoTranslucency(DrawableObject*);
// void nlListAddStart<ListEntry<LightObject*>>(ListEntry<LightObject*>**, ListEntry<LightObject*>*, ListEntry<LightObject*>**);
// void nlDLRingIsEnd<DLListEntry<WorldAnimController*>>(DLListEntry<WorldAnimController*>*, DLListEntry<WorldAnimController*>*);
// void nlDLRingGetStart<DLListEntry<WorldAnimController*>>(DLListEntry<WorldAnimController*>*);
// void nlStrChr<char>(const char*, char);
// void 0x8028D34C..0x8028D350 | size: 0x4;

class DrawableObject;
class DrawableModel;
class nlChunk;
class glModelPacket;
class glModel;
class WorldObjectData;
class Event;

class World
{
public:
    static u32 m_uCurrentFrameCount;

    virtual ~World();
    World(const char*);

    virtual void GetTerrainType(const nlVector3&) const = 0;
    virtual void HandleObjectCreation(WorldObjectData*);
    virtual void Render(); // 0x14
    virtual void Update(float); // 0x18
    virtual void UpdateInReplay(float); // 0x1C
    virtual void FixedUpdate(float); // 0x20
    virtual void HandleEvent(Event*, void*); // 0x24 
    virtual void CreateHelperObjFromChunk(nlChunk*); // 0x28
    virtual void DoLoad() = 0; // 0x2C
    virtual void DoInitialize() = 0; // 0x30

    int CompareNameToGenericName(const char*, const char*);
    void GetHashIdForGenericName(const char*) const;
    void GetShadowLight(const nlVector3&, float);
    void AddDrawableObject(unsigned long, DrawableObject*);
    void FindHelperObject(unsigned long);
    void FindDrawableObject(unsigned long);
    void HandleCameraSwitch();
    void IsSphereInFrustum(const nlMatrix4&, float);
    void ExtractFrustumPlanes();
    void GetCustomSpecularData(glModelPacket*, bool);
    void CreateLightUserData();
    void LoadObjectData(const char*);
    void AddToHyperSTSDrawables(unsigned long, DrawableModel*);
    void LoadGeometry(glModel*, unsigned long, bool, bool, unsigned long*, int*, bool);
    void LoadGeometry(const char*, bool, bool, unsigned long*, int*);
    void Load(bool);

    /* 0x04 */ u8 m_padding_0x04[0x18];
    /* 0x1C */ u8 m_unk_0x1C;
    /* 0x1D */ u8 m_padding_0x1D[0x30];
    /* 0x4C */ void *m_unk_0x4C;
};


// class nlAVLTree<unsigned long, LightObject*, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void ~nlAVLTree();
// };


// class AVLTreeBase<unsigned long, DrawableObject*, NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void DeleteEntry(AVLTreeEntry<unsigned long, DrawableObject*>*);
//     void ~AVLTreeBase();
//     void Clear();
//     void DestroyTree(void (AVLTreeBase<unsigned long, DrawableObject*, NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, DrawableObject*>*));
//     void PostorderTraversal(AVLTreeEntry<unsigned long, DrawableObject*>*, void (AVLTreeBase<unsigned long, DrawableObject*, NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, DrawableObject*>*));
//     void CastUp(AVLTreeNode*) const;
//     void CompareNodes(AVLTreeNode*, AVLTreeNode*);
//     void CompareKey(void*, AVLTreeNode*);
//     void AllocateEntry(void*, void*);
// };


// class AVLTreeBase<unsigned long, LightObject*, NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void ~AVLTreeBase();
//     void Clear();
//     void DestroyTree(void (AVLTreeBase<unsigned long, LightObject*, NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, LightObject*>*));
//     void PostorderTraversal(AVLTreeEntry<unsigned long, LightObject*>*, void (AVLTreeBase<unsigned long, LightObject*, NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, LightObject*>*));
//     void CastUp(AVLTreeNode*) const;
//     void CompareNodes(AVLTreeNode*, AVLTreeNode*);
//     void CompareKey(void*, AVLTreeNode*);
//     void AllocateEntry(void*, void*);
//     void DeleteEntry(AVLTreeEntry<unsigned long, LightObject*>*);
// };


// class nlAVLTree<unsigned long, DrawableObject*, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void ~nlAVLTree();
// };


// class nlAVLTree<unsigned long, HelperObject*, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void ~nlAVLTree();
// };


// class AVLTreeBase<unsigned long, HelperObject*, NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void ~AVLTreeBase();
//     void Clear();
//     void DestroyTree(void (AVLTreeBase<unsigned long, HelperObject*, NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, HelperObject*>*));
//     void PostorderTraversal(AVLTreeEntry<unsigned long, HelperObject*>*, void (AVLTreeBase<unsigned long, HelperObject*, NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, HelperObject*>*));
//     void CastUp(AVLTreeNode*) const;
//     void CompareNodes(AVLTreeNode*, AVLTreeNode*);
//     void CompareKey(void*, AVLTreeNode*);
//     void AllocateEntry(void*, void*);
//     void DeleteEntry(AVLTreeEntry<unsigned long, HelperObject*>*);
// };


// class ListContainerBase<LightObject*, NewAdapter<ListEntry<LightObject*>>>
// {
// public:
//     void DeleteEntry(ListEntry<LightObject*>*);
// };


// class DLListContainerBase<WorldAnimController*, NewAdapter<DLListEntry<WorldAnimController*>>>
// {
// public:
//     void DeleteEntry(DLListEntry<WorldAnimController*>*);
// };


// class nlWalkList<ListEntry<LightObject*>, ListContainerBase<LightObject*, NewAdapter<ListEntry<LightObject*>>>>(ListEntry<LightObject*>*, ListContainerBase<LightObject*, NewAdapter<ListEntry<LightObject*>>>*, void (ListContainerBase<LightObject*, NewAdapter<ListEntry<LightObject*>>>
// {
// public:
//     void *)(ListEntry<LightObject*>*));
// };


// class nlWalkDLRing<DLListEntry<WorldAnimController*>, DLListContainerBase<WorldAnimController*, NewAdapter<DLListEntry<WorldAnimController*>>>>(DLListEntry<WorldAnimController*>*, DLListContainerBase<WorldAnimController*, NewAdapter<DLListEntry<WorldAnimController*>>>*, void (DLListContainerBase<WorldAnimController*, NewAdapter<DLListEntry<WorldAnimController*>>>
// {
// public:
//     void *)(DLListEntry<WorldAnimController*>*));
// };


// class nlWalkRing<DLListEntry<WorldAnimController*>, DLListContainerBase<WorldAnimController*, NewAdapter<DLListEntry<WorldAnimController*>>>>(DLListEntry<WorldAnimController*>*, DLListContainerBase<WorldAnimController*, NewAdapter<DLListEntry<WorldAnimController*>>>*, void (DLListContainerBase<WorldAnimController*, NewAdapter<DLListEntry<WorldAnimController*>>>
// {
// public:
//     void *)(DLListEntry<WorldAnimController*>*));
// };

#endif // _WORLD_H_

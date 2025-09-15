#ifndef _WORLD_H_
#define _WORLD_H_

#include "NL/nlMath.h"

// void DoTranslucency(DrawableObject*);
// void nlListAddStart<ListEntry<LightObject*>>(ListEntry<LightObject*>**, ListEntry<LightObject*>*, ListEntry<LightObject*>**);
// void nlDLRingIsEnd<DLListEntry<WorldAnimController*>>(DLListEntry<WorldAnimController*>*, DLListEntry<WorldAnimController*>*);
// void nlDLRingGetStart<DLListEntry<WorldAnimController*>>(DLListEntry<WorldAnimController*>*);
// void nlStrChr<char>(const char*, char);
// void 0x8028D34C..0x8028D350 | size: 0x4;

enum eTerrain
{
    T_Grass = 0,
    T_BlueGrass = 1,
    T_Concrete = 2,
    T_BlueConcrete = 3,
    T_Wood = 4,
    T_Metal = 5,
    T_Rubber = 6,
    T_Num = 7,
};

class WorldAnimManager;
class DrawableObject;
class DrawableModel;
class nlChunk;
class glModelPacket;
class glModel;
class WorldObjectData;
class Event;
class CharacterPhysicsData;
class LightObject;

class World
{
public:
    static u32 m_uCurrentFrameCount;
    static bool sbIsHyperShootToScoreRenderingEnabled;

    World(const char*);
    /* 0x04 */ virtual ~World();

    /* 0x08 */ virtual eTerrain GetTerrainType(const nlVector3&) const = 0;
    /* 0x10 */ virtual void HandleObjectCreation(WorldObjectData*);
    /* 0x14 */ virtual void Render();
    /* 0x18 */ virtual void Update(float);
    /* 0x1C */ virtual void UpdateInReplay(float);
    /* 0x20 */ virtual void FixedUpdate(float);
    /* 0x24 */ virtual void HandleEvent(Event*, void*);
    /* 0x28 */ virtual void CreateHelperObjFromChunk(nlChunk*);
    /* 0x2C */ virtual bool DoLoad() = 0;
    /* 0x30 */ virtual void DoInitialize() = 0;

    int CompareNameToGenericName(const char*, const char*);
    void GetHashIdForGenericName(const char*) const;
    void GetShadowLight(const nlVector3&, float);
    void AddDrawableObject(unsigned long, DrawableObject*);
    void FindHelperObject(unsigned long);
    DrawableObject* FindDrawableObject(unsigned long);
    void HandleCameraSwitch();
    void IsSphereInFrustum(const nlMatrix4&, float);
    void ExtractFrustumPlanes();
    void GetCustomSpecularData(glModelPacket*, bool);
    void CreateLightUserData();
    bool LoadObjectData(const char*);
    void AddToHyperSTSDrawables(unsigned long, DrawableModel*);
    bool LoadGeometry(glModel*, unsigned long, bool, bool, unsigned long*, int*, bool);
    bool LoadGeometry(const char*, bool, bool, unsigned long*, int*);
    void Load(bool);

    /* 0x004 */ WorldAnimManager* m_pWorldAnimManager;
    /* 0x008 */ s32 m_lightMap;
    // /* 0x008 */ class nlAVLTree m_lightMap;
    /* 0x00C */ u8 pad_0x08[0x10];
    /* 0x01C */ bool m_Locked;
    /* 0x020 */ struct glModel* m_pModels;
    /* 0x024 */ unsigned long m_uNumModels;
    // /* 0x028 */ nlDLListContainer m_animControllerList;
    /* 0x028 */ u8 pad_0x28[0x8];
    /* 0x030 */ void* m_pLightData;
    /* 0x034 */ void* m_pPlayerNISLightData;
    /* 0x038 */ void* m_pIntensityPerm;
    /* 0x03C */ void* m_pIntensityData;
    /* 0x040 */ void* m_pSTSIntensity;
    /* 0x044 */ void* m_pSpecularData;
    // /* 0x048 */ nlAVLTree m_drawableMap;
    /* 0x048 */ u8 pad_0x48[0x14];
    // /* 0x05C */ nlAVLTree m_hyperSTSDrawableMap;
    /* 0x05C */ u8 pad_0x5C[0x14];
    // /* 0x070 */ nlAVLTree m_helperMap;
    /* 0x070 */ u8 pad_0x70[0x14];
    /* 0x084 */ nlVector4 m_frustumPlane[5];
    /* 0x0D4 */ char m_WorldNamePrefix[64];
    /* 0x114 */ int m_WorldNameLength;
    /* 0x118 */ unsigned long m_WorldLightRamp;
    /* 0x11C */ unsigned long m_ObjectLightRamp;
    /* 0x120 */ unsigned long m_PlayerLightRamp_;
    // /* 0x124 */ unsigned long m_STSLightRamp;
    // /* 0x128 */ unsigned long m_PlayerNISLightRamp;

    /* 0x124 */ u32 m_LightRampTexA;
    /* 0x128 */ u32 m_LightRampTexB;
    /* 0x12C */ u32 m_PlayerLightRampTex;
    /* 0x130 */ u32 m_GlobalLightRampSTSTex;

    // DWARF seems wrong here

    // /* 0x12C */ CharacterPhysicsData* m_pPhysicsData;
    // /* 0x130 */ const LightObject* m_pShadowLight;
}; // total size: 0x134

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

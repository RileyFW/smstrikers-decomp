#include "Game/Physics/Physics.h"

#include "NL/nlMemory.h"
#include "Game/Ball.h"
#include "Game/Inventory.h"
#include "Game/Physics/CollisionSpace.h"
#include "Game/Physics/LoadablePhysicsMesh.h"
#include "Game/Physics/PhysicsNet.h"
#include "ode/NLGAdditions.h"

extern PhysicsWorld* g_PhysicsWorld;
extern nlListContainer<PhysicsObject*> g_NetPhysicsObjects;
extern nlListContainer<PhysicsObject*> g_StaticPhysicsPrimitives;
extern CollisionSpace* g_CollisionSpace;
extern PhysicsMesh* g_TerrainMesh;
static PhysicsRoundedCorner* corners[4];
static cInventory<LoadablePhysicsMesh*> s_PhysicsMeshes;
static bool sbDisableCollisionDetection;
static bool sbNonMovingAABBsInitialized;

void dClearCachedData();

extern "C"
{
    typedef void* dAllocFunction(unsigned long);
    typedef void* dReallocFunction(void*, unsigned long, unsigned long);
    typedef void dFreeFunction(void*, unsigned long);

    void dSetAllocHandler(dAllocFunction* fn);
    void dSetReallocHandler(dReallocFunction* fn);
    void dSetFreeHandler(dFreeFunction* fn);
}

class SimpleCollisionSpace : public CollisionSpace
{
public:
    SimpleCollisionSpace(PhysicsWorld*);
};

class PhysicsGroundPlane : public PhysicsObject
{
public:
    PhysicsGroundPlane(CollisionSpace*);
    virtual int GetObjectType() const { return 0; }
};

class PhysicsWall : public PhysicsObject
{
public:
    PhysicsWall(CollisionSpace*, float, float, float);
    virtual int GetObjectType() const { return 0; }
};

struct sSideLinePlane
{
    nlVector2 vNormal;
    float fDistance;
};

struct sCornerSegment
{
    nlVector2 vCenter;
    unsigned short thetaStart;
    unsigned short thetaEnd;
    float fRadius;
};

class cField
{
public:
    static sSideLinePlane mSidelines[4];
    static sCornerSegment mCorners[4];
};

class BasicStadium
{
public:
    static BasicStadium* GetCurrentStadium();

    unsigned char _pad0[0x134];
    CharacterPhysicsData* m_pCharacterPhysicsData;
    unsigned char _pad138[0x30];
    char m_szBaseName[0x20];
};

extern "C" void ConstructStaticPhysicsPrimitives__13PhysicsLoaderFP20CharacterPhysicsData(
    PhysicsLoader*,
    CharacterPhysicsData*);
extern "C" PhysicsWorld* __ct__12PhysicsWorldFv(PhysicsWorld*);
extern "C" SimpleCollisionSpace* __ct__20SimpleCollisionSpaceFP12PhysicsWorld(SimpleCollisionSpace*, PhysicsWorld*);
extern "C" PhysicsGroundPlane* __ct__18PhysicsGroundPlaneFP14CollisionSpace(PhysicsGroundPlane*, CollisionSpace*);
extern "C" PhysicsWall* __ct__11PhysicsWallFP14CollisionSpacefff(PhysicsWall*, CollisionSpace*, float, float, float);
extern "C" PhysicsRoundedCorner* __ct__20PhysicsRoundedCornerFP14CollisionSpaceRC9nlVector2fbb(
    PhysicsRoundedCorner*,
    CollisionSpace*,
    const nlVector2&,
    float,
    bool,
    bool);

/**
 * Offset/Address/Size: 0x0 | 0x80132B10 | size: 0x14C
 */
void PhysicsUpdate(PhysicsWorld* pWorld, float fDeltaT)
{
    if (!sbDisableCollisionDetection)
    {
        pWorld->Collide();
    }

    if (pWorld == g_PhysicsWorld && !sbDisableCollisionDetection)
    {
        int ballFlags = dGeomGetGFlags(g_pBall->m_pPhysicsBall->m_geomID);

        if (!sbNonMovingAABBsInitialized)
        {
            ListEntry<PhysicsObject*>* entry = g_NetPhysicsObjects.m_Head;
            while (entry != NULL)
            {
                dGeomComputeAABB(entry->data->m_geomID);
                entry = entry->next;
            }
            sbNonMovingAABBsInitialized = true;
        }
        else
        {
            ListEntry<PhysicsObject*>* entry = g_NetPhysicsObjects.m_Head;
            while (entry != NULL)
            {
                dGeomMarkAABBAsValid(entry->data->m_geomID);
                entry = entry->next;
            }
        }

        PhysicsAIBall* pPhysicsBall = g_pBall->m_pPhysicsBall;
        if (pPhysicsBall->m_unk_0x58)
        {
            dGeomComputeAABB(pPhysicsBall->m_geomID);
            g_PhysicsWorld->DoCollisions(pPhysicsBall, g_NetPhysicsObjects);
        }

        dGeomSetGFlags(g_pBall->m_pPhysicsBall->m_geomID, ballFlags);
    }

    pWorld->PreUpdate();
    pWorld->Update(fDeltaT, true);
    pWorld->PostUpdate();
}

/**
 * Offset/Address/Size: 0x14C | 0x80132C5C | size: 0x244
 * TODO: 92.7% match - r29/r30 register swap throughout, stack offsets off by 4 bytes,
 *       nlWalkList member function pointer constants differ. Likely -inline deferred related.
 */
void PhysicsLoader::DestroyPhysics()
{
    PhysicsNet::StaticDestroy();

    for (int i = 0; i < 4; i++)
    {
        delete corners[i];
    }

    ListEntry<PhysicsObject*>* entry = g_StaticPhysicsPrimitives.m_Head;
    while (entry != NULL)
    {
        delete entry->data;
        entry = entry->next;
    }

    typedef ListContainerBase<PhysicsObject*, NewAdapter<ListEntry<PhysicsObject*> > > PhysListBase;
    nlWalkList(g_StaticPhysicsPrimitives.m_Head, (PhysListBase*)&g_StaticPhysicsPrimitives, &PhysListBase::DeleteEntry);
    g_StaticPhysicsPrimitives.m_Head = NULL;
    g_StaticPhysicsPrimitives.m_Tail = NULL;

    nlWalkList(g_NetPhysicsObjects.m_Head, (PhysListBase*)&g_NetPhysicsObjects, &PhysListBase::DeleteEntry);
    g_NetPhysicsObjects.m_Head = NULL;
    g_NetPhysicsObjects.m_Tail = NULL;

    ListEntry<LoadablePhysicsMesh*>* meshEntry = s_PhysicsMeshes.m_lItemList.m_Head;
    while (meshEntry != NULL)
    {
        meshEntry->data->Destroy();
        meshEntry = meshEntry->next;
    }

    typedef ListContainerBase<LoadablePhysicsMesh*, NewAdapter<ListEntry<LoadablePhysicsMesh*> > > MeshListBase;
    nlWalkList(s_PhysicsMeshes.m_lItemList.m_Head, (MeshListBase*)&s_PhysicsMeshes.m_lItemList, &MeshListBase::DeleteEntry);
    s_PhysicsMeshes.m_lItemList.m_Head = NULL;
    s_PhysicsMeshes.m_lItemList.m_Tail = NULL;

    while (s_PhysicsMeshes.m_lMemList.m_Head != NULL)
    {
        ListEntry<LoadablePhysicsMesh*>* removed = nlListRemoveStart(&s_PhysicsMeshes.m_lMemList.m_Head, &s_PhysicsMeshes.m_lMemList.m_Tail);
        LoadablePhysicsMesh* mesh = removed->data;
        ::operator delete(removed);
        ::operator delete(mesh);
    }

    s_PhysicsMeshes.m_nItemCount = 0;
    g_TerrainMesh = NULL;

    if (g_CollisionSpace != NULL)
    {
        delete g_CollisionSpace;
    }
    g_CollisionSpace = NULL;

    delete g_PhysicsWorld;
    g_PhysicsWorld = NULL;

    dClearCachedData();
}

/**
 * Offset/Address/Size: 0x390 | 0x80132EA0 | size: 0x60
 */
PhysicsRoundedCorner::~PhysicsRoundedCorner()
{
}

/**
 * Offset/Address/Size: 0x3F0 | 0x80132F00 | size: 0x338
 */
void PhysicsLoader::ConstructStaticPhysicsPrimitives(CharacterPhysicsData*)
{
}

/**
 * Offset/Address/Size: 0x728 | 0x80133238 | size: 0x2C0
 * TODO: 94.0% match - stack frame is 0x120 instead of 0x130, register allocation starts at r26
 *       instead of r24. Target uses add base+offset loop pattern, current uses pointer advancement.
 *       MWCC register allocator difference with -inline deferred.
 */
bool PhysicsLoader::StartLoad(LoadingManager*)
{
    PhysicsLoader* pThis = this;
    ListEntry<PhysicsObject*>** pHead;
    ListEntry<PhysicsObject*>** pTail;
    int i;
    int j;
    unsigned long uPositiveNetMeshID;
    unsigned long uNegativeNetMeshID;
    char szTemp[0x100];

    dSetAllocHandler(ODEAlloc);
    dSetReallocHandler(ODERealloc);
    dSetFreeHandler(ODEFree);

    PhysicsWorld* pWorld = (PhysicsWorld*)nlMalloc(0x10, 8, false);
    if (pWorld != NULL)
    {
        pWorld = __ct__12PhysicsWorldFv(pWorld);
    }
    g_PhysicsWorld = pWorld;

    SimpleCollisionSpace* pSpace = (SimpleCollisionSpace*)nlMalloc(0x10, 8, false);
    if (pSpace != NULL)
    {
        pSpace = __ct__20SimpleCollisionSpaceFP12PhysicsWorld(pSpace, g_PhysicsWorld);
    }
    g_CollisionSpace = pSpace;

    g_PhysicsWorld->SetCFM(0.00001f);
    g_PhysicsWorld->SetERP(0.2f);

    PhysicsGroundPlane* pGroundPlane = (PhysicsGroundPlane*)nlMalloc(0x2C, 8, false);
    if (pGroundPlane != NULL)
    {
        pGroundPlane = __ct__18PhysicsGroundPlaneFP14CollisionSpace(pGroundPlane, g_CollisionSpace);
    }

    ListEntry<PhysicsObject*>* pEntry = (ListEntry<PhysicsObject*>*)nlMalloc(8, 8, false);
    if (pEntry != NULL)
    {
        pEntry->next = NULL;
        pEntry->data = pGroundPlane;
    }

    pHead = &g_StaticPhysicsPrimitives.m_Head;
    pTail = &g_StaticPhysicsPrimitives.m_Tail;
    nlListAddEnd(pHead, pTail, pEntry);

    for (i = 0; i < 4; i++)
    {
        PhysicsWall* pWall = (PhysicsWall*)nlMalloc(0x2C, 8, false);
        if (pWall != NULL)
        {
            pWall = __ct__11PhysicsWallFP14CollisionSpacefff(pWall,
                g_CollisionSpace,
                cField::mSidelines[i].vNormal.f.x,
                cField::mSidelines[i].vNormal.f.y,
                cField::mSidelines[i].fDistance);
        }

        pEntry = (ListEntry<PhysicsObject*>*)nlMalloc(8, 8, false);
        if (pEntry != NULL)
        {
            pEntry->next = NULL;
            pEntry->data = pWall;
        }

        nlListAddEnd(pHead, pTail, pEntry);
    }

    for (j = 0; j < 4; j++)
    {
        PhysicsRoundedCorner* pCorner = (PhysicsRoundedCorner*)nlMalloc(0x2C, 8, false);
        if (pCorner != NULL)
        {
            pCorner = __ct__20PhysicsRoundedCornerFP14CollisionSpaceRC9nlVector2fbb(pCorner,
                g_CollisionSpace,
                cField::mCorners[j].vCenter,
                cField::mCorners[j].fRadius,
                cField::mCorners[j].vCenter.f.x > 0.0f,
                cField::mCorners[j].vCenter.f.y > 0.0f);
        }
        corners[j] = pCorner;
    }

    PhysicsNet::StaticInit(g_CollisionSpace);

    if (NetMesh::s_bAnimatedNetMeshEnabled)
    {
        const char* pBaseName = BasicStadium::GetCurrentStadium()->m_szBaseName;

        nlStrNCat<char>(szTemp, pBaseName, "/NetMesh", 0x100);
        uPositiveNetMeshID = nlStringLowerHash(szTemp);

        nlStrNCat<char>(szTemp, pBaseName, "/NetMesh01", 0x100);
        uNegativeNetMeshID = nlStringLowerHash(szTemp);

        PhysicsNet::spPhysNetPositiveX->mpNetMesh->Initialize(uPositiveNetMeshID);
        PhysicsNet::spPhysNetNegativeX->mpNetMesh->Initialize(uNegativeNetMeshID);
    }

    ConstructStaticPhysicsPrimitives__13PhysicsLoaderFP20CharacterPhysicsData(
        pThis,
        BasicStadium::GetCurrentStadium()->m_pCharacterPhysicsData);

    return true;
}

/**
 * Offset/Address/Size: 0x9E8 | 0x801334F8 | size: 0x20
 */
void ODEFree(void* ptr, unsigned long size)
{
    nlFree(ptr);
}

/**
 * Offset/Address/Size: 0xA08 | 0x80133518 | size: 0x70
 */
void* ODERealloc(void* oldPtr, unsigned long oldSize, unsigned long newSize)
{
    void* newPtr = nlMalloc(newSize, 8, false);
    if (oldSize != 0)
    {
        memcpy(newPtr, oldPtr, oldSize);
    }
    nlFree(oldPtr);
    return newPtr;
}

/**
 * Offset/Address/Size: 0xA78 | 0x80133588 | size: 0x28
 */
void* ODEAlloc(unsigned long size)
{
    return nlMalloc(size, 8, false);
}

// /**
//  * Offset/Address/Size: 0x0 | 0x801335B0 | size: 0x8
//  */
// void PhysicsRoundedCorner::GetObjectType() const
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x801335B8 | size: 0x68
 */
// void nlWalkList<ListEntry<LoadablePhysicsMesh*>, ListContainerBase<LoadablePhysicsMesh*,
// NewAdapter<ListEntry<LoadablePhysicsMesh*>>>>(ListEntry<LoadablePhysicsMesh*>*, ListContainerBase<LoadablePhysicsMesh*,
// NewAdapter<ListEntry<LoadablePhysicsMesh*>>>*, void (ListContainerBase<LoadablePhysicsMesh*,
// NewAdapter<ListEntry<LoadablePhysicsMesh*>>>::*)(ListEntry<LoadablePhysicsMesh*>*))
// {
// }

/**
 * Offset/Address/Size: 0x68 | 0x80133620 | size: 0x68
 */
// void nlWalkList<ListEntry<PhysicsObject*>, ListContainerBase<PhysicsObject*,
// NewAdapter<ListEntry<PhysicsObject*>>>>(ListEntry<PhysicsObject*>*, ListContainerBase<PhysicsObject*,
// NewAdapter<ListEntry<PhysicsObject*>>>*, void (ListContainerBase<PhysicsObject*,
// NewAdapter<ListEntry<PhysicsObject*>>>::*)(ListEntry<PhysicsObject*>*))
// {
// }

/**
 * Offset/Address/Size: 0xD0 | 0x80133688 | size: 0x2C
 */
// void nlListAddEnd<ListEntry<PhysicsObject*>>(ListEntry<PhysicsObject*>**, ListEntry<PhysicsObject*>**, ListEntry<PhysicsObject*>*)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x801336B4 | size: 0x24
 */
// void ListContainerBase<PhysicsObject*, NewAdapter<ListEntry<PhysicsObject*>>>::DeleteEntry(ListEntry<PhysicsObject*>*)
// {
// }

/**
 * Offset/Address/Size: 0x24 | 0x801336D8 | size: 0x24
 */
// void ListContainerBase<LoadablePhysicsMesh*, NewAdapter<ListEntry<LoadablePhysicsMesh*>>>::DeleteEntry(ListEntry<LoadablePhysicsMesh*>*)
// {
// }

/**
 * Offset/Address/Size: 0xF4 | 0x801337A8 | size: 0xAC
 */
// void nlListContainer<PhysicsObject*>::~nlListContainer()
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x80133854 | size: 0x1E0
 */
// void cInventory<LoadablePhysicsMesh>::~cInventory()
// {
// }

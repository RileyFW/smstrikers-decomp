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
 */
void PhysicsLoader::StartLoad(LoadingManager*)
{
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

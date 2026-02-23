#include "Game/Render/SidelineExplodable.h"
#include "Game/Render/AnimatedModelExplodable.h"
#include "Game/Render/StaticModelExplodable.h"
#include "NL/nlMath.h"
#include "NL/nlString.h"
#include "types.h"

float ExplosionFragment::sfFadeOutTime = 1.0f;

ExplosionFragment** SidelineExplodableManager::sFragmentLookupTable = NULL;

/**
 * Offset/Address/Size: 0x8 | 0x8016974C | size: 0x38
 */
ExplosionFragment::ExplosionFragment()
{
    mpPhysicsObject = NULL;
    mDrawableFragmentID = 0xFFFF;
    mbIsActive = false;
    mbInfiniteLifespan = false;
    mbIsStationary = false;
    mStationaryTransform = NULL;
    mpSmokeEmissionController = NULL;
}

// /**
//  * Offset/Address/Size: 0x0 | 0x80169744 | size: 0x8
//  */
// void SidelineExplosionPhysicsObject::GetObjectType() const
// {
// }

// /**
//  * Offset/Address/Size: 0x2388 | 0x801696E8 | size: 0x5C
//  */
// void Function1<void, EmissionController&>::FunctorImpl<BindExp2<void, void (*)(EmissionController&, ExplosionFragment*), Placeholder<0>, ExplosionFragment*> >::~FunctorImpl()
// {
// }

/**
 * Offset/Address/Size: 0x2188 | 0x801694E8 | size: 0x200
 */
ExplosionFragment::~ExplosionFragment()
{
}

/**
 * Offset/Address/Size: 0x2134 | 0x80169494 | size: 0x54
 */
void UpdateEmissionControllerPosition(EmissionController& ec, ExplosionFragment* pFragment)
{
    const nlVector3* pPos;
    if (pFragment->mpPhysicsObject != NULL)
    {
        pPos = &pFragment->mpPhysicsObject->GetPosition();
    }
    else
    {
        pPos = (const nlVector3*)&(pFragment->mStationaryTransform->f.m41);
    }
    ec.SetPosition(*pPos);
}

/**
 * Offset/Address/Size: 0x2128 | 0x80169488 | size: 0xC
 */
void EmissionControllerFinished(EmissionController&, ExplosionFragment* p0)
{
    p0->mpSmokeEmissionController = NULL;
}

/**
 * Offset/Address/Size: 0x20EC | 0x8016944C | size: 0x3C
 */
nlVector3& ExplosionFragment::GetPosition() const
{
    if (mpPhysicsObject != NULL)
    {
        return mpPhysicsObject->GetPosition();
    }
    return *(nlVector3*)&mStationaryTransform->m[3];
}

/**
 * Offset/Address/Size: 0x2048 | 0x801693A8 | size: 0xA4
 */
void ExplosionFragment::GetRotation(nlMatrix4* dest) const
{
    if (mpPhysicsObject != NULL)
    {
        mpPhysicsObject->GetRotation(dest);
        return;
    }

    nlMatrix4* src = mStationaryTransform;

    // Copy 3x3 rotation with 4th column as zeros
    ((f32*)dest)[0] = ((f32*)src)[0];
    ((f32*)dest)[1] = ((f32*)src)[1];
    ((f32*)dest)[2] = ((f32*)src)[2];
    ((f32*)dest)[3] = 0.0f;

    ((f32*)dest)[4] = ((f32*)src)[4];
    ((f32*)dest)[5] = ((f32*)src)[5];
    ((f32*)dest)[6] = ((f32*)src)[6];
    ((f32*)dest)[7] = 0.0f;

    ((f32*)dest)[8] = ((f32*)src)[8];
    ((f32*)dest)[9] = ((f32*)src)[9];
    ((f32*)dest)[10] = ((f32*)src)[10];
    ((f32*)dest)[11] = 0.0f;

    // 4th row is 0, 0, 0, 1
    ((f32*)dest)[12] = 0.0f;
    ((f32*)dest)[13] = 0.0f;
    ((f32*)dest)[14] = 0.0f;
    ((f32*)dest)[15] = 1.0f;
}

/**
 * Offset/Address/Size: 0x200C | 0x8016936C | size: 0x3C
 */
SidelineExplodable::SidelineExplodable()
{
    mExplosionFragments.mData = NULL;
    mExplosionFragments.mSize = 0;
    mExplosionFragments.mCapacity = 0;
    mNumActiveFragments = 0;
    mbAngleRangeInitialized = false;
    mbIsMainModelVisible = true;
    mfExplodeTime = 0.0f;
    mpAssociatedEffect = NULL;
}

/**
 * Offset/Address/Size: 0x1D74 | 0x801690D4 | size: 0x298
 */
SidelineExplodable::~SidelineExplodable()
{
}

/**
 * Offset/Address/Size: 0x1CC4 | 0x80169024 | size: 0xB0
 */
extern "C" void Allocate__18SidelineExplodableFv(SidelineExplodable*);

void SidelineExplodable::Initialize(int numFragmentModels)
{
    mNumFragmentModels = numFragmentModels;
    Allocate__18SidelineExplodableFv(this);

    SidelineExplodableNode* node = NULL;

    if (SidelineExplodableNode::sSidelineExplodableNodeSlotPool.m_FreeList == NULL)
    {
        SlotPoolBase::BaseAddNewBlock(&SidelineExplodableNode::sSidelineExplodableNodeSlotPool, 8);
    }

    SlotPoolEntry* entry = SidelineExplodableNode::sSidelineExplodableNodeSlotPool.m_FreeList;
    if (entry != NULL)
    {
        node = (SidelineExplodableNode*)entry;
        SidelineExplodableNode::sSidelineExplodableNodeSlotPool.m_FreeList = (SlotPoolEntry*)entry->m_next;
    }

    if (node != NULL)
    {
        node->mpExplodable = NULL;
        node->next = NULL;
    }

    node->mpExplodable = this;
    node->next = NULL;
    nlListAddEnd<SidelineExplodableNode>(&SidelineExplodableManager::sSidelineExplodableList.m_pStart,
        &SidelineExplodableManager::sSidelineExplodableList.m_pEnd,
        node);
}

/**
 * Offset/Address/Size: 0x1C9C | 0x80168FFC | size: 0x28
 */
void SidelineExplodable::Allocate()
{
    mExplosionFragments.resize(mNumFragmentModels);
}

/**
 * Offset/Address/Size: 0x19A0 | 0x80168D00 | size: 0x2FC
 */
void SidelineExplodable::Update(float)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x1710 | 0x80168A70 | size: 0x290
 */
void SidelineExplodable::DestroyAllActiveFragments(bool)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0xE84 | 0x801681E4 | size: 0x88C
 */
void SidelineExplodable::Explode()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0xC08 | 0x80167F68 | size: 0x27C
 */
void SidelineExplodable::FindExplosionAngleRange(unsigned short& min, unsigned short& max) const
{
}

/**
 * Offset/Address/Size: 0xC04 | 0x80167F64 | size: 0x4
 */
void SidelineExplodableTextureLoadCallback(unsigned long)
{
}

/**
 * Offset/Address/Size: 0x9EC | 0x80167D4C | size: 0x218
 */
void ExplodableCategoryData::LoadGeometry()
{
}

/**
 * Offset/Address/Size: 0x938 | 0x80167C98 | size: 0xB4
 */
void SidelineExplodableManager::CleanUp()
{
    AnimatedModelExplodable::CleanUp();
    StaticModelExplodable::CleanUp();

    if (sbIsInitialized)
    {
        DrawableFragmentHandleNode** pTail = &sUnusedDrawableFragments.m_pEnd;
        SlotPoolBase* pPool = &DrawableFragmentHandleNode::sDrawableFragmentHandleNodePool;
        DrawableFragmentHandleNode* node;

        while ((node = sUnusedDrawableFragments.m_pStart) != NULL)
        {
            nlListRemoveStart<DrawableFragmentHandleNode>(&sUnusedDrawableFragments.m_pStart, pTail);
            ((SlotPoolEntry*)node)->m_next = pPool->m_FreeList;
            pPool->m_FreeList = (SlotPoolEntry*)node;
        }

        operator delete[](sFragmentLookupTable);
        sFragmentLookupTable = NULL;
        sbIsInitialized = false;
    }

    SlotPoolBase::BaseFreeBlocks(&SidelineExplodableNode::sSidelineExplodableNodeSlotPool, 8);
    SlotPoolBase::BaseFreeBlocks(&DrawableFragmentHandleNode::sDrawableFragmentHandleNodePool, 8);
}

/**
 * Offset/Address/Size: 0x810 | 0x80167B70 | size: 0x128
 */
void SidelineExplodableManager::Update(float fDeltaT)
{
    if (!sbIsInitialized)
    {
        sbIsInitialized = true;
        sFragmentLookupTable = (ExplosionFragment**)nlMalloc(0x50, 8, false);

        SlotPool<DrawableFragmentHandleNode>& pool = DrawableFragmentHandleNode::sDrawableFragmentHandleNodePool;
        u16 i;
        DrawableFragmentHandleNode* node;
        DrawableFragmentHandleNode** tail = &sUnusedDrawableFragments.m_pEnd;

        for (i = 0; i < 20; i++)
        {
            node = NULL;

            if (pool.m_FreeList == NULL)
            {
                SlotPoolBase::BaseAddNewBlock(&DrawableFragmentHandleNode::sDrawableFragmentHandleNodePool, 8);
            }

            SlotPoolEntry* entry = pool.m_FreeList;
            if (entry != NULL)
            {
                node = (DrawableFragmentHandleNode*)entry;
                pool.m_FreeList = (SlotPoolEntry*)entry->m_next;
            }

            if (node != NULL)
            {
                node->mID = 0;
                node->next = NULL;
            }

            node->mID = i;
            nlListAddEnd<DrawableFragmentHandleNode>(&sUnusedDrawableFragments.m_pStart, tail, node);
            sFragmentLookupTable[i] = NULL;
        }
    }

    SidelineExplodableNode* node = sSidelineExplodableList.m_pStart;
    while (node != NULL)
    {
        node->mpExplodable->SidelineExplodable::Update(fDeltaT);
        node = node->next;
    }
}

/**
 * Offset/Address/Size: 0x7EC | 0x80167B4C | size: 0x24
 */
int SidelineExplodableManager::GetNumExplodables()
{
    return nlListCountElements<SidelineExplodableNode>(sSidelineExplodableList.m_pStart);
}

/**
 * Offset/Address/Size: 0x7C4 | 0x80167B24 | size: 0x28
 */
void SidelineExplodableManager::GetVisibilityOfExplodableModels(bool* visibility, int numExplodables)
{
    SidelineExplodableNode* node;

    bool* visibilityPtr = visibility;
    node = sSidelineExplodableList.m_pStart;
    while (node != NULL)
    {
        *visibilityPtr = node->mpExplodable->mbIsMainModelVisible;
        visibilityPtr += 1;
        node = node->next;
    }
}

/**
 * Offset/Address/Size: 0x744 | 0x80167AA4 | size: 0x80
 */
void SidelineExplodableManager::SetVisibilityOfUnexplodedModels(bool* visibility, int numExplodables)
{
    SidelineExplodableNode* node = sSidelineExplodableList.m_pStart;
    int i = 0;

    while (node != NULL)
    {
        node->mpExplodable->DestroyAllActiveFragments(visibility[i]);
        if (node->mpExplodable->mpAssociatedEffect != NULL)
        {
            node->mpExplodable->mpAssociatedEffect->m_bDisabled = !visibility[i];
        }
        i++;
        node = node->next;
    }
}

/**
 * Offset/Address/Size: 0x650 | 0x801679B0 | size: 0xF4
 * TODO: 99.51% match - loop body still has f0/f1 register assignment swap on m42/m41/m43 loads
 */
void SidelineExplodableManager::TriggerExplosions(const nlVector3& pos, float explosionRadius)
{
    SidelineExplodableNode* node = sSidelineExplodableList.m_pStart;
    float divisor = 25.0f;
    float posX;
    float posY;
    float posZ;
    float triggerRadius = 1.2f * explosionRadius;
    posZ = pos.f.z;
    posY = pos.f.y;
    posX = pos.f.x;

    while (node != NULL)
    {
        SidelineExplodable* pExplodable = node->mpExplodable;
        const nlMatrix4& worldMtx = pExplodable->GetWorldMatrix();
        float dy = worldMtx.f.m43 - posZ;
        float dx = worldMtx.f.m41 - posX;
        float dz = worldMtx.f.m42 - posY;
        float dist = nlSqrt(dy * dy + (dx * dx + dz * dz), true);
        if (dist < triggerRadius)
        {
            pExplodable->mfExplodeTime = dist / divisor;
        }
        node = node->next;
    }
}

/**
 * Offset/Address/Size: 0x600 | 0x80167960 | size: 0x50
 */
void SidelineExplodableManager::DestroyAllActiveFragments(bool renewExplodables)
{
    SidelineExplodableNode* node = sSidelineExplodableList.m_pStart;
    while (node != NULL)
    {
        node->mpExplodable->DestroyAllActiveFragments(renewExplodables);
        node = node->next;
    }
}

/**
 * Offset/Address/Size: 0x588 | 0x801678E8 | size: 0x78
 */
void SidelineExplodableManager::RemoveSidelineExplodable(SidelineExplodable* pSidelineExplodable)
{
    SidelineExplodableNode* node = sSidelineExplodableList.m_pStart;
    while (node != NULL)
    {
        SidelineExplodableNode* nextnode = node->next;
        if (node->mpExplodable == pSidelineExplodable)
        {
            nlListRemoveElement<SidelineExplodableNode>(&sSidelineExplodableList.m_pStart, node, &sSidelineExplodableList.m_pEnd);
            ((SlotPoolEntry*)node)->m_next = SidelineExplodableNode::sSidelineExplodableNodeSlotPool.m_FreeList;
            SidelineExplodableNode::sSidelineExplodableNodeSlotPool.m_FreeList = (SlotPoolEntry*)node;
        }
        node = nextnode;
    }
}

/**
 * Offset/Address/Size: 0x568 | 0x801678C8 | size: 0x20
 */
ExplosionFragment* SidelineExplodableManager::GetFragmentFromHandle(unsigned short handle)
{
    if (sFragmentLookupTable == NULL)
    {
        return 0;
    }
    // return *(sFragmentLookupTable__25SidelineExplodableManager.unk0 + ((this * 4) & 0x3FFFC));
    return sFragmentLookupTable[handle];
}

// /**
//  * Offset/Address/Size: 0x508 | 0x80167868 | size: 0x60
//  */
// PhysicsBox::~PhysicsBox()
// {
// }

/**
 * Offset/Address/Size: 0x358 | 0x801676B8 | size: 0x1B0
 */
ContactType SidelineExplosionPhysicsObject::Contact(PhysicsObject* other, dContact* contact, int what, PhysicsObject* otherObject)
{
    return NO_CONTACT;
}

/**
 * Offset/Address/Size: 0x338 | 0x80167698 | size: 0x20
 */
bool SidelineExplosionPhysicsObject::SetContactInfo(dContact* contact, PhysicsObject* other, bool first)
{
    contact->surface.mu = 75.0f;
    contact->surface.mode = 0x14;
    contact->surface.soft_cfm = 0.0001f;
    return true;
}

/**
 * Offset/Address/Size: 0x1D4 | 0x80167534 | size: 0x164
 */
void SidelineExplosionPhysicsObject::PostUpdate()
{
}

/**
 * Offset/Address/Size: 0xA0 | 0x80167400 | size: 0x134
 */
void SidelineExplodableManager::AssociateEffectWithNearbyFloatingCamera(EmissionController* pEmissionController)
{
    const nlVector3& position = pEmissionController->GetPosition();
    float bestDist = 1e10f;
    SidelineExplodableNode* node = sSidelineExplodableList.m_pStart;
    SidelineExplodable* closest = NULL;
    const char* floatingCamName = "Cam_\0\0\0\0";

    while (node != NULL)
    {
        const nlMatrix4& mat = node->mpExplodable->GetWorldMatrix();
        nlVector3 diff;
        nlVec3Sub(diff, mat.GetTranslation(), position);
        float dist = diff.GetLengthSq3D();
        if (closest == NULL || dist < bestDist)
        {
            closest = node->mpExplodable;
            bestDist = dist;
        }
        node = node->next;
    }

    const nlMatrix4& closestMat = closest->GetWorldMatrix();
    float cdy = closestMat.m[3][1] - position.f.y;
    float cdx = closestMat.m[3][0] - position.f.x;
    float closestDist = cdx * cdx + cdy * cdy;
    if (closestDist < 10000.0f)
    {
        ExplodableCategoryData& catData = closest->GetCategoryData();
        if (nlStrNCmp<char>(catData.mBaseModelName, floatingCamName, 4) == 0)
        {
            closest->mpAssociatedEffect = pEmissionController;
        }
    }
}

/**
 * Offset/Address/Size: 0x70 | 0x801673D0 | size: 0x30
 * TODO: 97.9% match - r4/r5 register swap for mpExplodable/mpAssociatedEffect temps.
 * Likely -inline deferred context-dependent register allocation difference.
 */
void SidelineExplodableManager::UnAssociateEffectWithNearbyFloatingCamera(EmissionController* pEmissionController)
{
    SidelineExplodableNode* node = sSidelineExplodableList.m_pStart;
    while (node != NULL)
    {
        if (node->mpExplodable->mpAssociatedEffect == pEmissionController)
        {
            node->mpExplodable->mpAssociatedEffect = 0;
        }
        node = node->next;
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x80167360 | size: 0x70
 */
SidelineExplosionPhysicsObject::~SidelineExplosionPhysicsObject()
{
}

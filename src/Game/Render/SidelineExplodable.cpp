#include "Game/Render/SidelineExplodable.h"
#include "NL/nlMath.h"
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
void UpdateEmissionControllerPosition(EmissionController&, ExplosionFragment*)
{
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
void ExplosionFragment::GetRotation(nlMatrix4*) const
{
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
void SidelineExplodable::Initialize(int)
{
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
}

/**
 * Offset/Address/Size: 0x810 | 0x80167B70 | size: 0x128
 */
void SidelineExplodableManager::Update(float)
{
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
 */
void SidelineExplodableManager::TriggerExplosions(const nlVector3& pos, float explosionRadius)
{
    SidelineExplodableNode* node = sSidelineExplodableList.m_pStart;
    while (node != NULL)
    {
        nlVector3 temp_r3_2 = node->mpExplodable->mExplosionFragments.mData[0].GetPosition();
        float x = temp_r3_2.f.x - pos.f.x;
        float y = temp_r3_2.f.y - pos.f.y;
        float z = temp_r3_2.f.z - pos.f.z;
        float triggerDist = nlSqrt((x * x) + ((y * y) + (z * z)), true);
        if (triggerDist < (1.2f * explosionRadius))
        {
            node->mpExplodable->mfExplodeTime = triggerDist / 25.0f;
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
        if (node->mpExplodable == pSidelineExplodable)
        {
            nlListRemoveElement<SidelineExplodableNode>(&sSidelineExplodableList.m_pStart, node, &sSidelineExplodableList.m_pEnd);
            node->mpExplodable = (SidelineExplodable*)sSidelineExplodableNodeSlotPool.m_FreeList->m_next;
            sSidelineExplodableNodeSlotPool.m_FreeList = (SlotPoolEntry*)node;
        }
        node = node->next;
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
void SidelineExplodableManager::AssociateEffectWithNearbyFloatingCamera(EmissionController*)
{
}

/**
 * Offset/Address/Size: 0x70 | 0x801673D0 | size: 0x30
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

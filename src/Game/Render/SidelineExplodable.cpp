#include "Game/Render/SidelineExplodable.h"

ExplosionFragment** SidelineExplodableManager::sFragmentLookupTable = NULL;

// /**
//  * Offset/Address/Size: 0x0 | 0x8016A0C0 | size: 0x64
//  */
// void SlotPool<SidelineExplodableNode>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8016A0A8 | size: 0x18
//  */
// void Bind<void, void (*)(EmissionController&, ExplosionFragment*), Placeholder<0>, ExplosionFragment*>(void (*)(EmissionController&, ExplosionFragment*), const Placeholder<0>&, ExplosionFragment* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x100 | 0x8016A07C | size: 0x2C
//  */
// void nlListAddEnd<DrawableFragmentHandleNode>(DrawableFragmentHandleNode**, DrawableFragmentHandleNode**, DrawableFragmentHandleNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x8016A038 | size: 0x44
//  */
// void nlListRemoveStart<DrawableFragmentHandleNode>(DrawableFragmentHandleNode**, DrawableFragmentHandleNode**)
// {
// }

// /**
//  * Offset/Address/Size: 0x20 | 0x80169F9C | size: 0x9C
//  */
// void nlListRemoveElement<SidelineExplodableNode>(SidelineExplodableNode**, SidelineExplodableNode*, SidelineExplodableNode**)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80169F7C | size: 0x20
//  */
// void nlListCountElements<SidelineExplodableNode>(SidelineExplodableNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80169F6C | size: 0x8
//  */
// void CollisionExplosionFragmentPlayerData::GetID()
// {
// }

// /**
//  * Offset/Address/Size: 0x36C | 0x80169CC0 | size: 0x2AC
//  */
// void Vector<ExplosionFragment, DefaultAllocator>::Vector(int, const char*)
// {
// }

// /**
//  * Offset/Address/Size: 0x27C | 0x80169BD0 | size: 0xF0
//  */
// void Vector<ExplosionFragment, DefaultAllocator>::reserve(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80169954 | size: 0x27C
//  */
// void Vector<ExplosionFragment, DefaultAllocator>::resize(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x16C | 0x801698F0 | size: 0x64
//  */
// void SlotPool<DrawableFragmentHandleNode>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x70 | 0x801697F4 | size: 0x34
//  */
// void Function1<void, EmissionController&>::FunctorImpl<BindExp2<void, void (*)(EmissionController&, ExplosionFragment*), Placeholder<0>, ExplosionFragment*> >::operator()(EmissionController&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80169784 | size: 0x70
//  */
// void Function1<void, EmissionController&>::FunctorImpl<BindExp2<void, void (*)(EmissionController&, ExplosionFragment*), Placeholder<0>, ExplosionFragment*> >::Clone() const
// {
// }

/**
 * Offset/Address/Size: 0x8 | 0x8016974C | size: 0x38
 */
ExplosionFragment::ExplosionFragment()
{
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
void EmissionControllerFinished(EmissionController&, ExplosionFragment*)
{
}

/**
 * Offset/Address/Size: 0x20EC | 0x8016944C | size: 0x3C
 */
void ExplosionFragment::GetPosition() const
{
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
}

/**
 * Offset/Address/Size: 0x19A0 | 0x80168D00 | size: 0x2FC
 */
void SidelineExplodable::Update(float)
{
}

/**
 * Offset/Address/Size: 0x1710 | 0x80168A70 | size: 0x290
 */
void SidelineExplodable::DestroyAllActiveFragments(bool)
{
}

/**
 * Offset/Address/Size: 0xE84 | 0x801681E4 | size: 0x88C
 */
void SidelineExplodable::Explode()
{
}

/**
 * Offset/Address/Size: 0xC08 | 0x80167F68 | size: 0x27C
 */
void SidelineExplodable::FindExplosionAngleRange(unsigned short&, unsigned short&) const
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
void SidelineExplodableManager::GetNumExplodables()
{
}

/**
 * Offset/Address/Size: 0x7C4 | 0x80167B24 | size: 0x28
 */
void SidelineExplodableManager::GetVisibilityOfExplodableModels(bool*, int)
{
}

/**
 * Offset/Address/Size: 0x744 | 0x80167AA4 | size: 0x80
 */
void SidelineExplodableManager::SetVisibilityOfUnexplodedModels(bool*, int)
{
}

/**
 * Offset/Address/Size: 0x650 | 0x801679B0 | size: 0xF4
 */
void SidelineExplodableManager::TriggerExplosions(const nlVector3&, float)
{
}

/**
 * Offset/Address/Size: 0x600 | 0x80167960 | size: 0x50
 */
void SidelineExplodableManager::DestroyAllActiveFragments(bool)
{
}

/**
 * Offset/Address/Size: 0x588 | 0x801678E8 | size: 0x78
 */
void SidelineExplodableManager::RemoveSidelineExplodable(SidelineExplodable*)
{
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
int SidelineExplosionPhysicsObject::Contact(PhysicsObject* other, dContact* contact, int what, PhysicsObject* otherObject)
{
    return 0;
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
void SidelineExplodableManager::UnAssociateEffectWithNearbyFloatingCamera(EmissionController*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80167360 | size: 0x70
 */
SidelineExplosionPhysicsObject::~SidelineExplosionPhysicsObject()
{
}

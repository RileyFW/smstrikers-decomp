#include "Game/AI/Powerups.h"

// /**
//  * Offset/Address/Size: 0x190 | 0x80061D50 | size: 0x64
//  */
// void SlotPool<FreezeShell>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x12C | 0x80061CEC | size: 0x64
//  */
// void SlotPool<GreenShell>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0xC8 | 0x80061C88 | size: 0x64
//  */
// void SlotPool<SpinyShell>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x64 | 0x80061C24 | size: 0x64
//  */
// void SlotPool<RedShell>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80061BC0 | size: 0x64
//  */
// void SlotPool<Banana>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x374 | 0x80061B5C | size: 0x64
//  */
// void SlotPool<Bobomb>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x114 | 0x80060A74 | size: 0xD74
//  */
// void FormatImpl<BasicString<char, Detail::TempStringAllocator>>::operator%<int>(const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80060960 | size: 0x114
//  */
// void Format<BasicString<char, Detail::TempStringAllocator>, int>(const BasicString<char, Detail::TempStringAllocator>&, const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x8 | 0x80060958 | size: 0x8
//  */
// void PowerupHitPlayerEventData::GetID()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80060950 | size: 0x8
//  */
// void PowerupUsedEventData::GetID()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80060948 | size: 0x8
//  */
// void DrawableObject::Clone() const
// {
// }

/**
 * Offset/Address/Size: 0x5EBC | 0x800607A8 | size: 0x1A0
 */
cFielder* FindPowerupTarget(cFielder*, Bowser*)
{
    return NULL;
}

/**
 * Offset/Address/Size: 0x5998 | 0x80060284 | size: 0x524
 */
void PowerupThrowPosition(int, eThrowStyle, PowerupBase*, PowerupBase*)
{
}

/**
 * Offset/Address/Size: 0x4F00 | 0x8005F7EC | size: 0xA98
 */
void PowerupCreateAndThrow(cFielder*, ePowerUpType, int, Bowser*)
{
}

/**
 * Offset/Address/Size: 0x4EB4 | 0x8005F7A0 | size: 0x4C
 */
void FindPowerUp(unsigned long)
{
}

// /**
//  * Offset/Address/Size: 0x4C00 | 0x8005F4EC | size: 0x2B4
//  */
// void PowerupModelPool::Initialize(int, unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x4B68 | 0x8005F454 | size: 0x98
 */
void InitializePowerups()
{
}

/**
 * Offset/Address/Size: 0x4AEC | 0x8005F3D8 | size: 0x7C
 */
void CompactPowerups()
{
}

/**
 * Offset/Address/Size: 0x465C | 0x8005EF48 | size: 0x490
 */
PowerupBase::PowerupBase(cFielder*, ePowerUpType, float, ePowerupSize, bool, int)
{
}

/**
 * Offset/Address/Size: 0x4540 | 0x8005EE2C | size: 0x11C
 */
PowerupBase::~PowerupBase()
{
}

/**
 * Offset/Address/Size: 0x451C | 0x8005EE08 | size: 0x24
 */
void PowerupBase::GetRadius() const
{
}

/**
 * Offset/Address/Size: 0x4404 | 0x8005ECF0 | size: 0x118
 */
void PowerupBase::Update(float)
{
}

/**
 * Offset/Address/Size: 0x3DFC | 0x8005E6E8 | size: 0x608
 */
void PowerupBase::AwardPowerup(cTeam*)
{
}

/**
 * Offset/Address/Size: 0x38B4 | 0x8005E1A0 | size: 0x548
 */
void PowerupBase::CollisionCallback(PhysicsObject*, PhysicsObject*, const nlVector3&, void*)
{
}

/**
 * Offset/Address/Size: 0x3374 | 0x8005DC60 | size: 0x540
 */
void PowerupBase::ThrowAt(cFielder*, Bowser*)
{
}

/**
 * Offset/Address/Size: 0x28DC | 0x8005D1C8 | size: 0xA98
 */
void PowerupBase::Destroy(bool)
{
}

/**
 * Offset/Address/Size: 0x27C0 | 0x8005D0AC | size: 0x11C
 */
void PowerupBase::PreThrow(cFielder*, Bowser*)
{
}

/**
 * Offset/Address/Size: 0x24CC | 0x8005CDB8 | size: 0x2F4
 */
void PowerupBase::UpdateTransform()
{
}

/**
 * Offset/Address/Size: 0x2360 | 0x8005CC4C | size: 0x16C
 */
void PowerupBase::Init(cFielder*, Bowser*)
{
}

// /**
//  * Offset/Address/Size: 0x22F0 | 0x8005CBDC | size: 0x70
//  */
// PhysicsShell::~PhysicsShell()
// {
// }

/**
 * Offset/Address/Size: 0x2050 | 0x8005C93C | size: 0x2A0
 */
void PowerupBase::PlayPowerupSound(ePowerUpType, PowerupBase::PowerupSound, const nlVector3&, float)
{
}

/**
 * Offset/Address/Size: 0x1E00 | 0x8005C6EC | size: 0x250
 */
void PowerupBase::PlayPowerupSound(ePowerUpType, PowerupBase::PowerupSound, PhysicsObject*, float)
{
}

/**
 * Offset/Address/Size: 0x1DD0 | 0x8005C6BC | size: 0x30
 */
void PowerupBase::StopPowerupInEffectSound(SFXEmitter*)
{
}

/**
 * Offset/Address/Size: 0x1C98 | 0x8005C584 | size: 0x138
 */
GreenShell::~GreenShell()
{
}

/**
 * Offset/Address/Size: 0x1A80 | 0x8005C36C | size: 0x218
 */
void GreenShell::Update(float)
{
}

/**
 * Offset/Address/Size: 0x19AC | 0x8005C298 | size: 0xD4
 */
void GreenShell::Destroy(bool)
{
}

/**
 * Offset/Address/Size: 0x1874 | 0x8005C160 | size: 0x138
 */
RedShell::~RedShell()
{
}

/**
 * Offset/Address/Size: 0x1628 | 0x8005BF14 | size: 0x24C
 */
void RedShell::Update(float)
{
}

/**
 * Offset/Address/Size: 0x1554 | 0x8005BE40 | size: 0xD4
 */
void RedShell::Destroy(bool)
{
}

/**
 * Offset/Address/Size: 0x13C8 | 0x8005BCB4 | size: 0x18C
 */
void RedShell::SeekTarget()
{
}

/**
 * Offset/Address/Size: 0x1290 | 0x8005BB7C | size: 0x138
 */
Banana::~Banana()
{
}

/**
 * Offset/Address/Size: 0x1130 | 0x8005BA1C | size: 0x160
 */
void Banana::Update(float)
{
}

/**
 * Offset/Address/Size: 0x105C | 0x8005B948 | size: 0xD4
 */
void Banana::Destroy(bool)
{
}

/**
 * Offset/Address/Size: 0xF24 | 0x8005B810 | size: 0x138
 */
SpinyShell::~SpinyShell()
{
}

/**
 * Offset/Address/Size: 0xD0C | 0x8005B5F8 | size: 0x218
 */
void SpinyShell::Update(float)
{
}

/**
 * Offset/Address/Size: 0xC38 | 0x8005B524 | size: 0xD4
 */
void SpinyShell::Destroy(bool)
{
}

/**
 * Offset/Address/Size: 0xB00 | 0x8005B3EC | size: 0x138
 */
FreezeShell::~FreezeShell()
{
}

/**
 * Offset/Address/Size: 0x8E8 | 0x8005B1D4 | size: 0x218
 */
void FreezeShell::Update(float)
{
}

/**
 * Offset/Address/Size: 0x814 | 0x8005B100 | size: 0xD4
 */
void FreezeShell::Destroy(bool)
{
}

/**
 * Offset/Address/Size: 0x6DC | 0x8005AFC8 | size: 0x138
 */
Bobomb::~Bobomb()
{
}

/**
 * Offset/Address/Size: 0x428 | 0x8005AD14 | size: 0x2B4
 */
void Bobomb::Update(float)
{
}

/**
 * Offset/Address/Size: 0x80 | 0x8005A96C | size: 0x3A8
 */
void Bobomb::ThrowAt(cFielder*, Bowser*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8005A8EC | size: 0x80
 */
void Bobomb::Destroy(bool)
{
}

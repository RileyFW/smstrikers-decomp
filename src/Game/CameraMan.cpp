#include "Game/CameraMan.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x801A8634 | size: 0x88
//  */
// void nlDeleteRing<cBaseCamera>(cBaseCamera**)
// {
// }

// /**
//  * Offset/Address/Size: 0x1F8 | 0x801A85FC | size: 0x38
//  */
// void nlDLRingAddStart<cBaseCamera>(cBaseCamera**, cBaseCamera*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1BC | 0x801A85C0 | size: 0x3C
//  */
// void nlDLRingAddEnd<cBaseCamera>(cBaseCamera**, cBaseCamera*)
// {
// }

// /**
//  * Offset/Address/Size: 0x178 | 0x801A857C | size: 0x44
//  */
// void nlDLRingRemove<cBaseCamera>(cBaseCamera**, cBaseCamera*)
// {
// }

// /**
//  * Offset/Address/Size: 0x138 | 0x801A853C | size: 0x40
//  */
// void nlDLRingValidateContainsElement<cBaseCamera>(cBaseCamera*, const cBaseCamera*)
// {
// }

// /**
//  * Offset/Address/Size: 0x9C | 0x801A84A0 | size: 0x9C
//  */
// void nlDLRingRemoveSafely<cBaseCamera>(cBaseCamera**, const cBaseCamera*)
// {
// }

// /**
//  * Offset/Address/Size: 0x8C | 0x801A8490 | size: 0x10
//  */
// void nlDLRingGetEnd<cBaseCamera>(cBaseCamera*)
// {
// }

// /**
//  * Offset/Address/Size: 0x54 | 0x801A8458 | size: 0x38
//  */
// void nlDLRingRemoveStart<cBaseCamera>(cBaseCamera**)
// {
// }

// /**
//  * Offset/Address/Size: 0x20 | 0x801A8424 | size: 0x34
//  */
// void nlDLRingRemoveEnd<cBaseCamera>(cBaseCamera**)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801A8404 | size: 0x20
//  */
// void nlDeleteDLRing<cBaseCamera>(cBaseCamera**)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801A83F4 | size: 0x10
//  */
// void 0x801A8404..0x801A8634 | size : 0x230
// {
// }

/**
 * Offset/Address/Size: 0x1D04 | 0x801A838C | size: 0x68
 */
void FireCameraRumbleFilter(float, float)
{
}

/**
 * Offset/Address/Size: 0x1768 | 0x801A7DF0 | size: 0x59C
 */
void cCameraManager::Startup()
{
}

/**
 * Offset/Address/Size: 0x1730 | 0x801A7DB8 | size: 0x38
 */
void cCameraManager::Shutdown()
{
}

/**
 * Offset/Address/Size: 0x10CC | 0x801A7754 | size: 0x664
 */
void cCameraManager::Update(float)
{
}

/**
 * Offset/Address/Size: 0xD78 | 0x801A7400 | size: 0x354
 */
void cCameraManager::UpdateGameCameraType()
{
}

/**
 * Offset/Address/Size: 0xD50 | 0x801A73D8 | size: 0x28
 */
void cCameraManager::HasCamera(cBaseCamera*)
{
}

/**
 * Offset/Address/Size: 0xC58 | 0x801A72E0 | size: 0xF8
 */
void cCameraManager::PushCamera(cBaseCamera*)
{
}

/**
 * Offset/Address/Size: 0xBA8 | 0x801A7230 | size: 0xB0
 */
void cCameraManager::Remove(const cBaseCamera&)
{
}

/**
 * Offset/Address/Size: 0xA94 | 0x801A711C | size: 0x114
 */
void cCameraManager::Remove(eCameraType, bool)
{
}

/**
 * Offset/Address/Size: 0x7F8 | 0x801A6E80 | size: 0x29C
 */
void cCameraManager::PushCameraWithTransition(cBaseCamera*, float, eCameraTransition, void (*)(eCameraMessage))
{
}

/**
 * Offset/Address/Size: 0x590 | 0x801A6C18 | size: 0x268
 */
void cCameraManager::PopCameraWithTransition(float, eCameraTransition, void (*)(eCameraMessage))
{
}

/**
 * Offset/Address/Size: 0x200 | 0x801A6888 | size: 0x390
 */
void cCameraManager::IsObjectOccludingField(const DrawableObject*)
{
}

/**
 * Offset/Address/Size: 0x1A4 | 0x801A682C | size: 0x5C
 */
void cCameraManager::GetDistanceFromCameraToObject(const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x174 | 0x801A67FC | size: 0x30
 */
void cCameraManager::GetViewVector(nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x150 | 0x801A67D8 | size: 0x24
 */
void cCameraManager::GetUpVector(nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x1C | 0x801A66A4 | size: 0x134
 */
void cCameraManager::SetWorldUpVectorTilt(float, float)
{
}

/**
 * Offset/Address/Size: 0xC | 0x801A6694 | size: 0x10
 */
void cCameraManager::PushWorldUpVector()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801A6688 | size: 0xC
 */
void cCameraManager::PopWorldUpVector()
{
}

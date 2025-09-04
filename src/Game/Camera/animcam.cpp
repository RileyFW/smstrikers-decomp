#include "animcam.h"

/**
 * Offset/Address/Size: 0x160 | 0x801A5EE4 | size: 0x1C
 */
void 0x8028D358..0x8028D35C | size: 0x4
{
}

/**
 * Offset/Address/Size: 0x138 | 0x801A5EBC | size: 0x28
 */
void nlListAddStart<cCameraData>(cCameraData**, cCameraData*, cCameraData**)
{
}

/**
 * Offset/Address/Size: 0x9C | 0x801A5E20 | size: 0x9C
 */
void nlListRemoveElement<cCameraData>(cCameraData**, cCameraData*, cCameraData**)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801A5D84 | size: 0x9C
 */
void nlDeleteList<cCameraData>(cCameraData**)
{
}

/**
 * Offset/Address/Size: 0x20 | 0x801A5D7C | size: 0x8
 */
void cAnimCamera::GetViewMatrix() const
{
}

/**
 * Offset/Address/Size: 0x18 | 0x801A5D74 | size: 0x8
 */
void cAnimCamera::GetFOV() const
{
}

/**
 * Offset/Address/Size: 0x10 | 0x801A5D6C | size: 0x8
 */
void cAnimCamera::GetCameraPosition() const
{
}

/**
 * Offset/Address/Size: 0x8 | 0x801A5D64 | size: 0x8
 */
void cAnimCamera::GetTargetPosition() const
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801A5D5C | size: 0x8
 */
void cAnimCamera::GetType()
{
}

/**
 * Offset/Address/Size: 0x113C | 0x801A5D30 | size: 0x2C
 */
void EnableDofDebug()
{
}

/**
 * Offset/Address/Size: 0xCA4 | 0x801A5898 | size: 0x498
 */
void LoadAnimCameraData(nlChunk*, nlChunk*, cCameraData*, bool)
{
}

/**
 * Offset/Address/Size: 0xBF8 | 0x801A57EC | size: 0xAC
 */
void cAnimCamera::LoadCameraAnimation(nlChunk*, nlChunk*, const char*, bool)
{
}

/**
 * Offset/Address/Size: 0xB14 | 0x801A5708 | size: 0xE4
 */
void cAnimCamera::LoadCameraAnimation(const char*, const char*, bool)
{
}

/**
 * Offset/Address/Size: 0xAE8 | 0x801A56DC | size: 0x2C
 */
void cAnimCamera::FreeCameraAnimations()
{
}

/**
 * Offset/Address/Size: 0xA54 | 0x801A5648 | size: 0x94
 */
cAnimCamera::cAnimCamera()
{
}

/**
 * Offset/Address/Size: 0x9F8 | 0x801A55EC | size: 0x5C
 */
cAnimCamera::~cAnimCamera()
{
}

/**
 * Offset/Address/Size: 0x41C | 0x801A5010 | size: 0x5DC
 */
void cAnimCamera::BuildAnimViewMatrix(nlMatrix4&)
{
}

/**
 * Offset/Address/Size: 0x410 | 0x801A5004 | size: 0xC
 */
void cAnimCamera::UnselectCameraAnimation()
{
}

/**
 * Offset/Address/Size: 0x39C | 0x801A4F90 | size: 0x74
 */
void cAnimCamera::SelectCameraAnimation(const char*)
{
}

/**
 * Offset/Address/Size: 0x34C | 0x801A4F40 | size: 0x50
 */
void cAnimCamera::CameraAnimationExists(const char*) const
{
}

/**
 * Offset/Address/Size: 0x2AC | 0x801A4EA0 | size: 0xA0
 */
void cAnimCamera::FreeCameraAnimation(const char*)
{
}

/**
 * Offset/Address/Size: 0x150 | 0x801A4D44 | size: 0x15C
 */
void cAnimCamera::Update(float)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801A4BF4 | size: 0x150
 */
void cAnimCamera::ManualUpdate(float)
{
}

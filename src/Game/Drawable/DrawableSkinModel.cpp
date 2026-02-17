#include "Game/Drawable/DrawableSkinModel.h"
#include "Game/World/worldanim.h"

/**
 * Offset/Address/Size: 0x0 | 0x80122D5C | size: 0x60
 */
DrawableSkinModel::~DrawableSkinModel()
{
}

/**
 * Offset/Address/Size: 0x60 | 0x80122DBC | size: 0x170
 */
void DrawableSkinModel::Draw()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80122F2C | size: 0x24
 */
void DrawableSkinModel::SetAnimation(const char* szAnimationName, unsigned long playMode)
{
    m_pAnimController->SetAnimation(szAnimationName, (ePlayMode)playMode);
}

/**
 * Offset/Address/Size: 0x24 | 0x80122F50 | size: 0xC
 */
void DrawableSkinModel::SetAnimationSpeed(float)
{
}

/**
 * Offset/Address/Size: 0x30 | 0x80122F5C | size: 0x24
 */
void DrawableSkinModel::GetAnimationTime()
{
}

/**
 * Offset/Address/Size: 0x54 | 0x80122F80 | size: 0x24
 */
void DrawableSkinModel::SetAnimationTime(float)
{
}

/**
 * Offset/Address/Size: 0x78 | 0x80122FA4 | size: 0x24
 */
void DrawableSkinModel::GetAnimationDuration()
{
}

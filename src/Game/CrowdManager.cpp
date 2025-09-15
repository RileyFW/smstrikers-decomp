#include "Game/CrowdManager.h"

// /**
//  * Offset/Address/Size: 0x54 | 0x80164954 | size: 0x50
//  */
// void Replayable<1, SaveFrame, int>(SaveFrame&, int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80164900 | size: 0x54
//  */
// void Replayable<1, LoadFrame, int>(LoadFrame&, int&)
// {
// }

/**
 * Offset/Address/Size: 0x978 | 0x801647F4 | size: 0x10C
 */
void CrowdManager::Initialize()
{
}

/**
 * Offset/Address/Size: 0x974 | 0x801647F0 | size: 0x4
 */
void CrowdManager::Uninitialize()
{
}

/**
 * Offset/Address/Size: 0x938 | 0x801647B4 | size: 0x3C
 */
void CrowdManager::SetStadium(const char*)
{
}

/**
 * Offset/Address/Size: 0x918 | 0x80164794 | size: 0x20
 */
void CrowdManager::GetTextureHandle(unsigned long) const
{
}

/**
 * Offset/Address/Size: 0x79C | 0x80164618 | size: 0x17C
 */
void CrowdManager::Replay(LoadFrame&)
{
}

/**
 * Offset/Address/Size: 0x76C | 0x801645E8 | size: 0x30
 */
void CrowdManager::Replay(SaveFrame&)
{
}

/**
 * Offset/Address/Size: 0x70C | 0x80164588 | size: 0x60
 */
void CrowdBundleLoad_cb(void*, unsigned long, void*)
{
}

/**
 * Offset/Address/Size: 0x5A0 | 0x8016441C | size: 0x16C
 */
void CrowdManager::SetState(eCrowdState, bool)
{
}

/**
 * Offset/Address/Size: 0x480 | 0x801642FC | size: 0x120
 */
void CrowdManager::Update(float)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80163E7C | size: 0x480
 */
void CrowdManager::EventHandler(Event*)
{
}

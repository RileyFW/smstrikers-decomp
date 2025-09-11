#include "Game/ReplayManager.h"

// /**
//  * Offset/Address/Size: 0x3B4 | 0x80112CC4 | size: 0x10
//  */
// void 0x8028D2B8..0x8028D2BC | size: 0x4
// {
// }

// /**
//  * Offset/Address/Size: 0x388 | 0x80112C98 | size: 0x2C
//  */
// void Replayable<0, LoadFrame, RenderSnapshot>(LoadFrame&, RenderSnapshot&)
// {
// }

// /**
//  * Offset/Address/Size: 0x35C | 0x80112C6C | size: 0x2C
//  */
// void Replayable<0, SaveFrame, RenderSnapshot>(SaveFrame&, RenderSnapshot&)
// {
// }

// /**
//  * Offset/Address/Size: 0x1A4 | 0x80112AB4 | size: 0x1B8
//  */
// void Replay::Play<RenderSnapshot>(float, RenderSnapshot&, RenderSnapshot&, float*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x8011294C | size: 0x168
//  */
// void Replay::Record<RenderSnapshot>(float, RenderSnapshot&, unsigned int)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80112910 | size: 0x3C
//  */
// void Blend<RenderSnapshot>(const float*, const RenderSnapshot&, const RenderSnapshot&, RenderSnapshot&)
// {
// }

// /**
//  * Offset/Address/Size: 0x50 | 0x8011290C | size: 0x4
//  */
// void cBaseCamera::Reactivate()
// {
// }

// /**
//  * Offset/Address/Size: 0x48 | 0x80112904 | size: 0x8
//  */
// void cBaseCamera::GetFOV() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801128BC | size: 0x48
//  */
// cBaseCamera::~cBaseCamera()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80112838 | size: 0x84
//  */
// RenderSnapshot::RenderSnapshot()
// {
// }

// /**
//  * Offset/Address/Size: 0x5C | 0x801127BC | size: 0x7C
//  */
// RenderSnapshot::~RenderSnapshot()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80112760 | size: 0x5C
//  */
// cFollowCamera::~cFollowCamera()
// {
// }

/**
 * Offset/Address/Size: 0x964 | 0x801126D4 | size: 0x8C
 */
ReplayManager::~ReplayManager()
{
}

/**
 * Offset/Address/Size: 0x89C | 0x8011260C | size: 0xC8
 */
ReplayManager* ReplayManager::Instance()
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x828 | 0x80112598 | size: 0x74
 */
void ReplayManager::Initialize()
{
}

/**
 * Offset/Address/Size: 0x7DC | 0x8011254C | size: 0x4C
 */
void ReplayManager::InitializeSnapshots()
{
}

/**
 * Offset/Address/Size: 0x760 | 0x801124D0 | size: 0x7C
 */
void ReplayManager::Uninitialize()
{
}

/**
 * Offset/Address/Size: 0x6E0 | 0x80112450 | size: 0x80
 */
void ReplayManager::GrabSnapshot()
{
}

/**
 * Offset/Address/Size: 0x6B4 | 0x80112424 | size: 0x2C
 */
void ReplayManager::GetMutableRenderSnapshot()
{
}

/**
 * Offset/Address/Size: 0x5C4 | 0x80112334 | size: 0xF0
 */
void ReplayManager::Flush()
{
}

/**
 * Offset/Address/Size: 0x514 | 0x80112284 | size: 0xB0
 */
void ReplayManager::ResetSnapshots()
{
}

/**
 * Offset/Address/Size: 0x4C0 | 0x80112230 | size: 0x54
 */
void ReplayManager::PrepareForRecording()
{
}

/**
 * Offset/Address/Size: 0x454 | 0x801121C4 | size: 0x6C
 */
void ReplayManager::SetCurrentTime(float)
{
}

/**
 * Offset/Address/Size: 0x3C0 | 0x80112130 | size: 0x94
 */
void ReplayManager::EventHandler(Event*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80111D70 | size: 0x3C0
 */
void ReplayManager::RenderSnapshotAt(float)
{
}

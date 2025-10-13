#include "pnSAnimController.h"

/**
 * Offset/Address/Size: 0x0 | 0x801EB598 | size: 0x8
 */
void cSAnim::GetCallbackList() const
{
}

/**
 * Offset/Address/Size: 0x8 | 0x801EB588 | size: 0x10
 */
void cPN_SAnimController::SetTime(float)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801EB580 | size: 0x8
 */
void cPN_SAnimController::GetType()
{
}

/**
 * Offset/Address/Size: 0xEC0 | 0x801EB51C | size: 0x64
 */
void SlotPool<cPN_SAnimController>::~SlotPool()
{
}

/**
 * Offset/Address/Size: 0xDC0 | 0x801EB41C | size: 0x98
 */
cPN_SAnimController::cPN_SAnimController(cSAnim*, const AnimRetarget*, ePlayMode, void (*)(unsigned int, cPN_SAnimController*), unsigned int, bool)
{
}

/**
 * Offset/Address/Size: 0xAF0 | 0x801EB14C | size: 0x2D0
 */
void cPN_SAnimController::Update(float)
{
}

/**
 * Offset/Address/Size: 0x7E8 | 0x801EAE44 | size: 0x308
 */
void cPN_SAnimController::UpdateSynchronized(float)
{
}

/**
 * Offset/Address/Size: 0x760 | 0x801EADBC | size: 0x88
 */
void cPN_SAnimController::Evaluate(float, cPoseAccumulator*) const
{
}

/**
 * Offset/Address/Size: 0x5DC | 0x801EAC38 | size: 0x184
 */
void cPN_SAnimController::Evaluate(int, float, cPoseAccumulator*) const
{
}

/**
 * Offset/Address/Size: 0x35C | 0x801EA9B8 | size: 0x280
 */
void cPN_SAnimController::BlendRootTrans(nlVector3*, float, float*)
{
}

/**
 * Offset/Address/Size: 0x1F4 | 0x801EA850 | size: 0x168
 */
void cPN_SAnimController::BlendRootRot(unsigned short*, float, float*)
{
}

/**
 * Offset/Address/Size: 0x114 | 0x801EA770 | size: 0xE0
 */
void cPN_SAnimController::ProcessCallbacks()
{
}

/**
 * Offset/Address/Size: 0xB0 | 0x801EA70C | size: 0x64
 */
void cPN_SAnimController::TestTrigger(float) const
{
}

/**
 * Offset/Address/Size: 0x20 | 0x801EA67C | size: 0x90
 */
void cPN_SAnimController::TestFrameTrigger(float)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801EA65C | size: 0x20
 */
void cPN_SAnimController::RemapNode(int) const
{
}

#include "Game/SAnim/pnSingleAxisBlender.h"

/**
 * Offset/Address/Size: 0x0 | 0x801EF4C0 | size: 0x6C
 */
cPN_SingleAxisBlender::~cPN_SingleAxisBlender()
{
}

/**
 * Offset/Address/Size: 0x5DC | 0x801EF320 | size: 0xD4
 */
cPN_SingleAxisBlender::cPN_SingleAxisBlender(int, void (*)(unsigned int, cPN_SingleAxisBlender*), unsigned int, float)
{
}

/**
 * Offset/Address/Size: 0x518 | 0x801EF25C | size: 0xC4
 */
cPoseNode* cPN_SingleAxisBlender::Update(float)
{
    return this;
}

/**
 * Offset/Address/Size: 0x3CC | 0x801EF110 | size: 0x14C
 */
void cPN_SingleAxisBlender::Evaluate(int, float, cPoseAccumulator*) const
{
}

/**
 * Offset/Address/Size: 0x298 | 0x801EEFDC | size: 0x134
 */
void cPN_SingleAxisBlender::Evaluate(float, cPoseAccumulator*) const
{
}

/**
 * Offset/Address/Size: 0x14C | 0x801EEE90 | size: 0x14C
 */
void cPN_SingleAxisBlender::BlendRootTrans(nlVector3*, float, float*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801EED44 | size: 0x14C
 */
void cPN_SingleAxisBlender::BlendRootRot(unsigned short*, float, float*)
{
}

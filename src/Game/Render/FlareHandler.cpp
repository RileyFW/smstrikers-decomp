#include "Game/Render/FlareHandler.h"

/**
 * Offset/Address/Size: 0x818 | 0x8016A93C | size: 0x4
 */
void FlareHandler::Initialize()
{
}

/**
 * Offset/Address/Size: 0x7B8 | 0x8016A8DC | size: 0x60
 */
void FlareHandler::Cleanup()
{
}

/**
 * Offset/Address/Size: 0x6C4 | 0x8016A7E8 | size: 0xF4
 */
void FlareHandler::AddHalo(const nlMatrix4&)
{
}

/**
 * Offset/Address/Size: 0x5D0 | 0x8016A6F4 | size: 0xF4
 */
void FlareHandler::AddGlow(const nlMatrix4&)
{
}

/**
 * Offset/Address/Size: 0x290 | 0x8016A3B4 | size: 0x340
 */
void FlareHandler::AddFace(const FlareStruct*, GLMeshWriter*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8016A124 | size: 0x290
 */
void FlareHandler::Render()
{
}

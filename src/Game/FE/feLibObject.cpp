#include "Game/FE/feLibObject.h"

/**
 * Offset/Address/Size: 0x0 | 0x80209D28 | size: 0x8
 */
const feVector3& FELibObject::GetScale() const
{
    return m_attributes.v3Scale;
}

/**
 * Offset/Address/Size: 0x8 | 0x80209D30 | size: 0x8
 */
const feVector3& FELibObject::GetRotation() const
{
    return m_attributes.v3Rotation;
}

/**
 * Offset/Address/Size: 0x10 | 0x80209D38 | size: 0x8
 */
const feVector3& FELibObject::GetPosition() const
{
    return m_attributes.v3Position;
}

/**
 * Offset/Address/Size: 0x18 | 0x80209D40 | size: 0x8
 */
const nlColour& FELibObject::GetColour() const
{
    return m_attributes.colour;
}

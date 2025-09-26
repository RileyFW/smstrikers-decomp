#include "Game/GL/gluMeshWriter.h"

/**
 * Offset/Address/Size: 0x0 | 0x801B5918 | size: 0x28
 */
void GLMeshWriter::Texcoord(short, short)
{
}

/**
 * Offset/Address/Size: 0x28 | 0x801B5940 | size: 0x5C
 */
void GLMeshWriter::Texcoord(const nlVector2&)
{
}

/**
 * Offset/Address/Size: 0x84 | 0x801B599C | size: 0x118
 */
void GLMeshWriter::Normal(const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x19C | 0x801B5AB4 | size: 0x90
 */
bool GLMeshWriter::End()
{
    return false;
}

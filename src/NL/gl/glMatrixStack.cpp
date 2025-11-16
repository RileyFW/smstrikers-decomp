#include "NL/gl/glMatrixStack.h"
#include "NL/nlMemory.h"

/**
 * Offset/Address/Size: 0x0 | 0x801D8C00 | size: 0x84
 */
void GLMatrixStack::GetTop(nlMatrix4& result)
{
    result = top;
}

/**
 * Offset/Address/Size: 0x84 | 0x801D8C84 | size: 0xA4
 */
void GLMatrixStack::PopMatrix()
{
    top = stack[--stackDepth];
    bDirtyInverse = 1;
}

/**
 * Offset/Address/Size: 0x128 | 0x801D8D28 | size: 0xA4
 */
void GLMatrixStack::PushMatrix()
{
    stack[stackDepth++] = top;
    bDirtyInverse = 1;
}

/**
 * Offset/Address/Size: 0x1CC | 0x801D8DCC | size: 0xB8
 */
void GLMatrixStack::MultMatrix(const nlMatrix4& m)
{
    nlMatrix4 tmp = top;
    nlMultMatrices(top, m, tmp);
    bDirtyInverse = 1;
}

/**
 * Offset/Address/Size: 0x284 | 0x801D8E84 | size: 0x3C
 */
void GLMatrixStack::LoadIdentity()
{
    top.SetIdentity();
    inverse.SetIdentity();
    bDirtyInverse = 0;
}

/**
 * Offset/Address/Size: 0x2C0 | 0x801D8EC0 | size: 0x54
 */
GLMatrixStack::~GLMatrixStack()
{
    delete[] stack;
}

/**
 * Offset/Address/Size: 0x314 | 0x801D8F14 | size: 0xA8
 */
GLMatrixStack::GLMatrixStack(int stackSize)
{
    maxStackDepth = stackSize;
    stackDepth = 0;
    stack = (nlMatrix4*)nlMalloc(stackSize << 6, 8, 0);
    for (int i = 0; i < stackSize; i++)
    {
        stack[i].SetIdentity();
    }
    top.SetIdentity();
    inverse.SetIdentity();
    bDirtyInverse = 0;
}

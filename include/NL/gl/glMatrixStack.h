#ifndef _GLMATRIXSTACK_H_
#define _GLMATRIXSTACK_H_

#include "NL/nlMath.h"

class GLMatrixStack
{
public:
    void GetTop(nlMatrix4&);
    void PopMatrix();
    void PushMatrix();
    void MultMatrix(const nlMatrix4&);
    void LoadIdentity();
    ~GLMatrixStack();
    GLMatrixStack(int);

    /* 0x00 */ nlMatrix4 top;
    /* 0x40 */ nlMatrix4 inverse;
    /* 0x80 */ nlMatrix4* stack;
    /* 0x84 */ bool bDirtyInverse;
    /* 0x88 */ u32 maxStackDepth;
    /* 0x8C */ u32 stackDepth;
}; // total size: 0x90

#endif // _GLMATRIXSTACK_H_

#ifndef _GLDRAW2_H_
#define _GLDRAW2_H_

#include "types.h"

#include "NL/nlColour.h"
#include "NL/gl/glView.h"

class glPoly2
{
public:
    bool Attach(eGLView, int, unsigned long*, unsigned long);
    void FullCoverage(const nlColour&, float);
    void SetupRectangle(float, float, float, float, float);
    void SetupRotatedRectangle(float, float, float, float, float, float);
    void SetColour(const nlColour& col);

    /* 0x00 */ nlVector2 m_pos[4];
    /* 0x20 */ nlVector2 m_uv[4];
    /* 0x40 */ nlColour m_colour[4];
    /* 0x50 */ float depth;

    // /* 0x40 */ unsigned long c0;
    // /* 0x44 */ unsigned long c1;
    // /* 0x48 */ unsigned long c2;
    // /* 0x4C */ unsigned long c3;
};

bool glAttachPoly2(eGLView, unsigned long, glPoly2*, unsigned long*, const void*);

#endif // _GLDRAW2_H_

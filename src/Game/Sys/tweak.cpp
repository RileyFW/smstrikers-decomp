#include "tweak.h"

#include "NL/gl/glFont.h"
#include "NL/gl/glState.h"
#include "NL/gl/glDraw2.h"

/**
 * Offset/Address/Size: 0x0 | 0x801FB0EC | size: 0x1A4
 */
void DrawTextRectangle(int view, float vx0, float vy0, float vx1, float vy1, float depth, const nlColour& colour, bool expand8)
{
    float yb, xr;
    float sx0 = 0.0f, sy0 = 0.0f;
    float sx1 = 0.0f, sy1 = 0.0f;
    glFontVirtualPosToScreenCoordPos(vx0, vy0, sx0, sy0);
    glFontVirtualPosToScreenCoordPos(vx1, vy1, sx1, sy1);

    if (expand8)
    {
        sx0 -= 8.0f;
        sy0 -= 8.0f;
        sx1 += 8.0f;
        sy1 += 8.0f;
    }

    float w = sx1 - sx0;
    float h = sy1 - sy0;

    glSetDefaultState(false);

    if ((u8)colour.a != 0xFF)
    {
        glSetRasterState(GLS_AlphaBlend, 1U);
        glSetRasterState(GLS_AlphaTest, 1U);
        glSetRasterState(GLS_AlphaTestRef, 0U);
        glSetCurrentRasterState(glHandleizeRasterState());
    }

    glPoly2 poly;
    xr = sx0 + w;
    yb = sy0 + h;

    poly.x0 = sx0;
    poly.y0 = sy0; // TL
    poly.x1 = sx0;
    poly.y1 = yb; // BL
    poly.x2 = xr;
    poly.y2 = yb; // BR
    poly.x3 = xr;
    poly.y3 = sy0; // TR

    poly.c3 = *((unsigned long*)&colour);
    poly.c2 = *((unsigned long*)&colour);
    poly.c1 = *((unsigned long*)&colour);
    poly.c0 = *((unsigned long*)&colour);

    poly.depth = depth;

    poly.Attach((eGLView)view, 0, 0, -1U);
}

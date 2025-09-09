#include "NL/gl/glFont.h"
#include "NL/gl/glState.h"
#include "NL/nlPrint.h"
#include "NL/nlString.h"
#include "NL/glx/glxFont.h"

#include "NL/gl/glDraw2.h"

#include "font_data.h"

glPoly2* g_poly = NULL;
void* handle = NULL;
bool bInsideBegin = false;
bool bEnabled = false;
bool bDrop = false;
bool bVirtualCoords = false;

/**
 * Offset/Address/Size: 0x0 | 0x801D8398 | size: 0xE8
 */
bool glFontPrintf(eGLView view, int x, int y, const nlColour& col, const char* format, ...)
{
    char string[0x80];
    va_list args;

    if (bEnabled == false)
    {
        return false;
    }

    va_start(args, format);
    nlVSNPrintf(string, 0x80, format, args);
    va_end(args);

    return glFontPrint(view, x, y, col, string);
}

/**
 * Offset/Address/Size: 0xE8 | 0x801D8480 | size: 0xF4
 */
bool glFontPrintf(eGLView view, int x, int y, const char* format, ...)
{
    char string[0x80];
    va_list args;

    if (bEnabled == false)
    {
        return false;
    }

    va_start(args, format);
    nlVSNPrintf(string, 0x80, format, args);
    va_end(args);

    nlColour col;
    col.c[0] = 255;
    col.c[1] = 255;
    col.c[2] = 255;
    col.c[3] = 255;

    return glFontPrint(view, x, y, col, string);
}

/**
 * Offset/Address/Size: 0x1DC | 0x801D8574 | size: 0x3EC
 */
bool glFontPrint(eGLView view, int x, int y, const nlColour& col, const char* text)
{
    if (nlStrLen(text) == 0)
    {
        return false;
    }

    if (bEnabled == false)
    {
        return false;
    }

    int pos_x = x;
    int pos_y = y;
    if ((u8)bVirtualCoords != 0)
    {
        pos_x = (pos_x * 0xA) + 0x28;
        pos_y = (pos_y * 0xB) + 0x20;
    }

    int str_len = nlStrLen(text);

    // todo

    glAttachPoly2(view, str_len, g_poly, 0, 0);
    return false;
}

/**
 * Offset/Address/Size: 0x5C8 | 0x801D8960 | size: 0x18
 */
void glFontEnd()
{
    if (bEnabled != false)
    {
        bInsideBegin = false;
    }
}

/**
 * Offset/Address/Size: 0x5E0 | 0x801D8978 | size: 0x7C
 */
void glFontBegin(bool drop)
{
    if (bEnabled != false)
    {
        glSetDefaultState(0);
        glSetCurrentTexture((unsigned long)handle, eGLTextureType_0);
        glSetRasterState(GLS_AlphaTest, 1);
        glSetCurrentRasterState(glHandleizeRasterState());
        glSetTextureState(eGLTextureState_6, 1);
        glSetCurrentTextureState(glHandleizeTextureState());
        bDrop = drop;
        bInsideBegin = true;
    }
}

/**
 * Offset/Address/Size: 0x65C | 0x801D89F4 | size: 0x24
 */
void glFontVirtualPosToScreenCoordPos(float x, float y, float& outX, float& outY)
{
    outX = (10.0f * x) + 40.0f;
    outY = (11.0f * y) + 32.0f;
}

/**
 * Offset/Address/Size: 0x680 | 0x801D8A18 | size: 0x5C
 */
void gl_FontStartup()
{
    handle = (void*)glGetTexture("font/fixed8x8");
    glplatCreateFont(0x40, 0x80, _fontData, (unsigned long)handle);
    bInsideBegin = 0;
    bEnabled = 1;
    bDrop = 0;
    bVirtualCoords = 1;
}

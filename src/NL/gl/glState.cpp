#include "NL/gl/gl.h"
#include "NL/gl/glState.h"

typedef struct PackedTextureInfo
{
    u32 start_bit; // packed_texture[s].0
    u32 count;     // packed_texture[s].4
} PackedTextureInfo;

extern PackedTextureInfo packed_texture[]; // 8 bytes per entry

/**
 * Offset/Address/Size: 0x0 | 0x801DBC44 | size: 0x184
 */
void glSetDefaultState(bool)
{
}

/**
 * Offset/Address/Size: 0x184 | 0x801DBDC8 | size: 0xC
 */
void glUnHandleizeTextureState(unsigned long long)
{
}

/**
 * Offset/Address/Size: 0x190 | 0x801DBDD4 | size: 0xC
 */
unsigned long long glHandleizeTextureState()
{
    return 0;
}

/**
 * Offset/Address/Size: 0x19C | 0x801DBDE0 | size: 0x8
 */
void glUnHandleizeRasterState(unsigned long)
{
}

/**
 * Offset/Address/Size: 0x1A4 | 0x801DBDE8 | size: 0x8
 */
unsigned long glHandleizeRasterState()
{
    return 0;
}

/**
 * Offset/Address/Size: 0x1AC | 0x801DBDF0 | size: 0x14
 */
void glSetTextureStateDefaults()
{
}

/**
 * Offset/Address/Size: 0x1C0 | 0x801DBE04 | size: 0xC
 */
void glSetRasterStateDefaults()
{
}

/**
 * Offset/Address/Size: 0x1CC | 0x801DBE10 | size: 0x12C
 */
void glSetTextureState(unsigned long long&, eGLTextureState, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x2F8 | 0x801DBF3C | size: 0x118
 */
void glSetTextureState(eGLTextureState, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x410 | 0x801DC054 | size: 0x9C
 */
void glGetTextureState(unsigned long long, eGLTextureState)
{
}

/**
 * Offset/Address/Size: 0x4AC | 0x801DC0F0 | size: 0x9C
 */
void glGetTextureState(eGLTextureState)
{
}

/**
 * Offset/Address/Size: 0x548 | 0x801DC18C | size: 0xBC
 */
void glSetRasterState(unsigned long&, eGLState, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x604 | 0x801DC248 | size: 0xB4
 */
void glSetRasterState(eGLState, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x6B8 | 0x801DC2FC | size: 0x58
 */
void glGetRasterState(unsigned long, eGLState)
{
}

/**
 * Offset/Address/Size: 0x710 | 0x801DC354 | size: 0x5C
 */
void glGetRasterState(eGLState)
{
}

/**
 * Offset/Address/Size: 0x76C | 0x801DC3B0 | size: 0x30
 */
u32 glGetTexture(const char* textureName)
{
    if (textureName == 0)
        return 0xFFFFFFFF;

    return glHash(textureName);
}

/**
 * Offset/Address/Size: 0x79C | 0x801DC3E0 | size: 0x30
 */
u32 glGetProgram(const char*)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x7CC | 0x801DC410 | size: 0x18
 */
u32 glSetCurrentMatrix(unsigned long)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x7E4 | 0x801DC428 | size: 0x20
 */
void glSetCurrentTextureState(unsigned long long state)
{
}

/**
 * Offset/Address/Size: 0x804 | 0x801DC448 | size: 0x14
 */
void glGetCurrentTextureState()
{
}

/**
 * Offset/Address/Size: 0x818 | 0x801DC45C | size: 0x18
 */
void glSetCurrentRasterState(unsigned long)
{
}

/**
 * Offset/Address/Size: 0x830 | 0x801DC474 | size: 0x10
 */
void glGetCurrentRasterState()
{
}

/**
 * Offset/Address/Size: 0x840 | 0x801DC484 | size: 0x18
 */
u32 glSetCurrentProgram(unsigned long)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x858 | 0x801DC49C | size: 0x50
 */
void glSetCurrentTexture(unsigned long, eGLTextureType)
{
}

/**
 * Offset/Address/Size: 0x8A8 | 0x801DC4EC | size: 0x30
 */
void glStateRestore(const glStateBundle&)
{
}

/**
 * Offset/Address/Size: 0x8D8 | 0x801DC51C | size: 0x2C
 */
void glStateSave(glStateBundle&)
{
}

/**
 * Offset/Address/Size: 0x904 | 0x801DC548 | size: 0xC
 */
glStateBundle* gl_GetCurrentStateBundle()
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x910 | 0x801DC554 | size: 0x1E78
 */
void gl_StateStartup()
{
}

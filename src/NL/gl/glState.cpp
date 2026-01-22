#include "NL/gl/gl.h"

#include "NL/gl/glState.h"
#include "NL/nlMemory.h"

typedef struct PackedTextureInfo
{
    u32 start_bit; // packed_texture[s].0
    u32 count;     // packed_texture[s].4
} PackedTextureInfo;

extern PackedTextureInfo packed_texture[]; // 8 bytes per entry

static glStateBundle _bundle;

static unsigned long defaultRasterState = 0;
static glRasterState _state;

static unsigned long long defaultTextureState = 0;
static glTextureState _textureState;

static gl_StateBitfield packed_raster[GLS_Num];

/**
 * Offset/Address/Size: 0x0 | 0x801DBC44 | size: 0x184
 */
void glSetDefaultState(bool)
{
}

/**
 * Offset/Address/Size: 0x184 | 0x801DBDC8 | size: 0xC
 */
void glUnHandleizeTextureState(unsigned long long state)
{
    _textureState.m_State = state;
}

/**
 * Offset/Address/Size: 0x190 | 0x801DBDD4 | size: 0xC
 */
unsigned long long glHandleizeTextureState()
{
    return _textureState.m_State;
}

/**
 * Offset/Address/Size: 0x19C | 0x801DBDE0 | size: 0x8
 */
void glUnHandleizeRasterState(unsigned long state)
{
    _state.m_State = state;
}

/**
 * Offset/Address/Size: 0x1A4 | 0x801DBDE8 | size: 0x8
 */
unsigned long glHandleizeRasterState()
{
    return _state.m_State;
}

/**
 * Offset/Address/Size: 0x1AC | 0x801DBDF0 | size: 0x14
 */
void glSetTextureStateDefaults()
{
    _textureState.m_State = defaultTextureState;
}

/**
 * Offset/Address/Size: 0x1C0 | 0x801DBE04 | size: 0xC
 */
void glSetRasterStateDefaults()
{
    _state.m_State = defaultRasterState;
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
unsigned long glGetTextureState(unsigned long long, eGLTextureState)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x4AC | 0x801DC0F0 | size: 0x9C
 */
unsigned long glGetTextureState(eGLTextureState)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x548 | 0x801DC18C | size: 0xBC
 */
u32 glSetRasterState(unsigned long&, eGLState, unsigned long)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x604 | 0x801DC248 | size: 0xB4
 */
u32 glSetRasterState(eGLState, unsigned long)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x6B8 | 0x801DC2FC | size: 0x58
 */
u32 glGetRasterState(unsigned long raster, eGLState state)
{
    unsigned long out = 0;
    for (s32 cnt = 0; cnt < packed_raster[state].numBits; cnt++)
    {
        if (raster & (1u << (unsigned int)(packed_raster[state].startBit + cnt)))
        {
            out |= (1u << (unsigned int)cnt);
        }
    }
    return out;
}

/**
 * Offset/Address/Size: 0x710 | 0x801DC354 | size: 0x5C
 */
u32 glGetRasterState(eGLState state)
{
    u32 out = 0;
    for (s32 cnt = 0; cnt < packed_raster[state].numBits; cnt++)
    {
        if (_state.m_State & (1u << (unsigned int)(packed_raster[state].startBit + cnt)))
        {
            out |= (1u << (unsigned int)cnt);
        }
    }
    return out;
}

/**
 * Offset/Address/Size: 0x76C | 0x801DC3B0 | size: 0x30
 */
u32 glGetTexture(const char* textureName)
{
    if (textureName == 0)
        return -1;

    return glHash(textureName);
}

/**
 * Offset/Address/Size: 0x79C | 0x801DC3E0 | size: 0x30
 */
u32 glGetProgram(const char* programName)
{
    if (programName == NULL)
    {
        return -1;
    }
    return glHash(programName);
}

/**
 * Offset/Address/Size: 0x7CC | 0x801DC410 | size: 0x18
 */
u32 glSetCurrentMatrix(unsigned long matrix)
{
    u32 temp_r0 = _bundle.matrix;
    _bundle.matrix = matrix;
    return temp_r0;
}

/**
 * Offset/Address/Size: 0x7E4 | 0x801DC428 | size: 0x20
 */
u64 glSetCurrentTextureState(unsigned long long state)
{
    unsigned long long temp_r0 = _bundle.texturestate;
    _bundle.texturestate = state;
    return temp_r0;
}

/**
 * Offset/Address/Size: 0x804 | 0x801DC448 | size: 0x14
 */
u64 glGetCurrentTextureState()
{
    return _bundle.texturestate;
}

/**
 * Offset/Address/Size: 0x818 | 0x801DC45C | size: 0x18
 */
u32 glSetCurrentRasterState(unsigned long raster)
{
    u32 temp_r0 = _bundle.raster;
    _bundle.raster = raster;
    return temp_r0;
}

/**
 * Offset/Address/Size: 0x830 | 0x801DC474 | size: 0x10
 */
u32 glGetCurrentRasterState()
{
    return _bundle.raster;
}

/**
 * Offset/Address/Size: 0x840 | 0x801DC484 | size: 0x18
 */
u32 glSetCurrentProgram(unsigned long program)
{
    u32 temp_r0 = _bundle.program;
    _bundle.program = program;
    return temp_r0;
}

/**
 * Offset/Address/Size: 0x858 | 0x801DC49C | size: 0x50
 */
u32 glSetCurrentTexture(unsigned long texture, eGLTextureType type)
{
    u32 prev = _bundle.texture[(unsigned int)type];

    unsigned int bit = 1u << (unsigned int)type;
    if (texture == 0xFFFFFFFFu)
    {
        _bundle.texconfig = _bundle.texconfig & ~bit;
    }
    else
    {
        _bundle.texconfig = _bundle.texconfig | bit;
    }

    _bundle.texture[(unsigned int)type] = texture;
    return prev;
}

/**
 * Offset/Address/Size: 0x8A8 | 0x801DC4EC | size: 0x30
 */
void glStateRestore(const glStateBundle& state)
{
    memcpy(&_bundle, &state, sizeof(glStateBundle));
}

/**
 * Offset/Address/Size: 0x8D8 | 0x801DC51C | size: 0x2C
 */
void glStateSave(glStateBundle& state)
{
    memcpy(&state, &_bundle, sizeof(glStateBundle));
}

/**
 * Offset/Address/Size: 0x904 | 0x801DC548 | size: 0xC
 */
glStateBundle* gl_GetCurrentStateBundle()
{
    return &_bundle;
}

/**
 * Offset/Address/Size: 0x910 | 0x801DC554 | size: 0x1E78
 */
void gl_StateStartup()
{
}

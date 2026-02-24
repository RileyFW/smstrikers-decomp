#include "NL/gl/gl.h"

#include "NL/gl/glState.h"
#include "NL/gl/glMatrix.h"
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
 * TODO: 99.43% match - remaining register allocation differences in the final
 * _bundle setup block (r4/r5/r6 around bundle base, invalid, and 0xF0 mask).
 */
void glSetDefaultState(bool setRasterDefaults)
{
    _state.m_State = defaultRasterState;
    _textureState.m_State = defaultTextureState;

    if (setRasterDefaults)
    {
        s32 startBit = packed_raster[0].startBit;
        s32 numBits = packed_raster[0].numBits;
        s32 i;

        for (i = numBits; i > 0; i--)
        {
        }

        for (i = 0; i < numBits; i++)
        {
            if ((1u << i) & 1u)
            {
                _state.m_State = _state.m_State | (1u << startBit);
            }
            else
            {
                _state.m_State = _state.m_State & ~(1u << startBit);
            }
            startBit++;
        }

        {
            s32 startBit2 = packed_raster[1].startBit;
            s32 numBits2 = packed_raster[1].numBits;

            for (i = numBits2; i > 0; i--)
            {
            }

            for (i = 0; i < numBits2; i++)
            {
                if ((1u << i) & 1u)
                {
                    _state.m_State = _state.m_State | (1u << startBit2);
                }
                else
                {
                    _state.m_State = _state.m_State & ~(1u << startBit2);
                }
                startBit2++;
            }
        }
    }

    _bundle.raster = _state.m_State;
    _bundle.texturestate = _textureState.m_State;
    _bundle.program = (u32)-1;
    _bundle.matrix = glGetIdentityMatrix();

    {
        volatile glStateBundle* p = &_bundle;
        u32 invalid = (u32)-1;
        u8 texconfig = p->texconfig;
        u8 mF8 = texconfig & 0xF8;
        u8 mF0 = texconfig & 0xF0;

        p->texconfig = texconfig & 0xFE;
        p->texconfig = texconfig & 0xFC;
        p->texconfig = mF8;
        p->texconfig = mF0;
        p->texconfig = (u8)(mF0 & 0xE0);

        p->texture[0] = invalid;
        p->texture[1] = invalid;
        p->texture[2] = invalid;
        p->texture[3] = invalid;
        p->texture[4] = invalid;

        p->texconfig = (u8)(mF0 & 0xC0);
        p->texture[5] = invalid;
    }
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
 * TODO: 75.6% match - MWCC register allocator merges both halves of u64 cmp
 * (initialized to 0) into single register (r23) instead of separate r20/r21,
 * shifting all callee-saved register assignments by 1. All instructions match
 * structurally (only register number diffs).
 */
unsigned long glSetTextureState(unsigned long long& texture, eGLTextureState state, unsigned long value)
{
    unsigned long out = 0;
    PackedTextureInfo* pInfo = &packed_texture[state];
    PackedTextureInfo* pCount = (PackedTextureInfo*)((u8*)pInfo + 4);
    s32 cnt = (s32)out;
    unsigned long long cmp = (unsigned long long)out;
    unsigned long one = 1;
    unsigned long long tex = texture;
    s32 numBits = pInfo->count;

    for (; cnt < numBits; cnt++)
    {
        unsigned long long mask = 1ULL << (cnt + pInfo->start_bit);
        if ((tex & mask) != cmp)
        {
            out |= (one << cnt);
        }
    }

    for (cnt = 0; cnt < (s32)pCount->start_bit; cnt++)
    {
        if (value & (1 << cnt))
        {
            unsigned long long mask = 1ULL << (cnt + pInfo->start_bit);
            unsigned long lo = ((unsigned long*)&texture)[1];
            unsigned long hi = ((unsigned long*)&texture)[0];
            ((unsigned long*)&texture)[1] = lo | (unsigned long)mask;
            ((unsigned long*)&texture)[0] = hi | (unsigned long)(mask >> 32);
        }
        else
        {
            unsigned long lo = ((unsigned long*)&texture)[1];
            u32 startBit = pInfo->start_bit;
            unsigned long hi = ((unsigned long*)&texture)[0];
            unsigned long mask32 = 1UL << (cnt + startBit);
            unsigned long notMask = ~mask32;
            ((unsigned long*)&texture)[1] = lo & notMask;
            ((unsigned long*)&texture)[0] = hi & (unsigned long)((s32)notMask >> 31);
        }
    }

    return out;
}

static inline unsigned long SetTextureStateImpl(unsigned long long* pState, eGLTextureState state, unsigned long value)
{
    PackedTextureInfo* pInfo = &packed_texture[state];
    unsigned long long tex = *pState;
    unsigned long out = 0;
    s32 cnt = (s32)out;
    unsigned long long cmp = (unsigned long long)out;
    unsigned long one = 1;
    s32 numBits = pInfo->count;

    for (; cnt < numBits; cnt++)
    {
        unsigned long long mask = 1ULL << (cnt + pInfo->start_bit);
        if ((tex & mask) != cmp)
        {
            out |= (one << cnt);
        }
    }

    numBits = pInfo->count;
    cnt = 0;
    for (; cnt < numBits; cnt++)
    {
        unsigned long hi;
        unsigned long lo;
        if (value & (1 << cnt))
        {
            unsigned long long mask = 1ULL << (cnt + pInfo->start_bit);
            hi = (unsigned long)(*pState >> 32) | (unsigned long)(mask >> 32);
            lo = (unsigned long)*pState | (unsigned long)mask;
        }
        else
        {
            u32 startBit = pInfo->start_bit;
            unsigned long mask32 = 1UL << (cnt + startBit);
            unsigned long notMask = ~mask32;
            lo = (unsigned long)*pState & notMask;
            hi = (unsigned long)(*pState >> 32) & (unsigned long)((s32)notMask >> 31);
        }
        *pState = ((unsigned long long)lo) | ((unsigned long long)hi << 32);
    }

    return out;
}

/**
 * Offset/Address/Size: 0x2F8 | 0x801DBF3C | size: 0x118
 * TODO: 98.9% match - r30/r31 register swap for out vs texHi due to MWCC u64
 * register allocation interleaving. All instructions match, only register diffs.
 */
unsigned long glSetTextureState(eGLTextureState state, unsigned long value)
{
    return SetTextureStateImpl(&_textureState.m_State, state, value);
}

/**
 * Offset/Address/Size: 0x410 | 0x801DC054 | size: 0x9C
 * TODO: 84.2% match - MWCC merges u64 cmp (0) halves into single register (r30)
 * instead of two (r29:r30), shifting all callee-saved register assignments by 1.
 * All instructions match structurally (only register number diffs).
 */
unsigned long glGetTextureState(unsigned long long texture, eGLTextureState texturestate)
{
    PackedTextureInfo* pInfo = &packed_texture[texturestate];
    unsigned long out = 0;
    s32 cnt = (s32)out;
    unsigned long long cmp = (unsigned long long)out;
    unsigned long one = 1;
    s32 numBits = pInfo->count;

    for (; cnt < numBits; cnt++)
    {
        unsigned long long mask = 1ULL << (cnt + pInfo->start_bit);
        if ((texture & mask) != cmp)
        {
            out |= (one << cnt);
        }
    }

    return out;
}

static inline unsigned long GetTextureStateImpl(unsigned long long* pTexture, eGLTextureState texturestate)
{
    PackedTextureInfo* pInfo = &packed_texture[texturestate];
    s32 numBits = pInfo->count;
    unsigned long long texture = *pTexture;
    s32 cnt = 0;
    unsigned long out = 0;
    cnt = (s32)out;
    unsigned long one = 1;
    unsigned long long cmp = (unsigned long long)out;

    for (; cnt < numBits; cnt++)
    {
        unsigned long long mask = 1ULL << (cnt + pInfo->start_bit);
        if ((texture & mask) != cmp)
        {
            out |= (one << cnt);
        }
    }

    return out;
}

/**
 * Offset/Address/Size: 0x4AC | 0x801DC0F0 | size: 0x9C
 */
unsigned long glGetTextureState(eGLTextureState texturestate)
{
    return GetTextureStateImpl(&_textureState.m_State, texturestate);
}

static inline unsigned long glExtractRasterBits(unsigned long raster, gl_StateBitfield* p, s32* pn)
{
    unsigned long out = 0;
    for (s32 i = 0; i < *pn; i++)
    {
        if (raster & (1u << (i + p->startBit)))
        {
            out |= (1u << i);
        }
    }
    return out;
}

/**
 * Offset/Address/Size: 0x548 | 0x801DC18C | size: 0xBC
 */
u32 glSetRasterState(unsigned long& raster, eGLState state, unsigned long value)
{
    gl_StateBitfield* p = &packed_raster[state];
    s32* pn = &p->numBits;
    unsigned long out = glExtractRasterBits(raster, p, pn);

    for (s32 i = 0; i < *pn; i++)
    {
        if (value & (1u << i))
        {
            raster |= (1u << (i + p->startBit));
        }
        else
        {
            raster &= ~(1u << (i + p->startBit));
        }
    }

    return out;
}

/**
 * Offset/Address/Size: 0x604 | 0x801DC248 | size: 0xB4
 * TODO: 79.4% match - register allocation differences (r7/r3 for out, r9/r8 for numBits)
 */
u32 glSetRasterState(eGLState state, unsigned long value)
{
    u32 out = 0;
    u32 currentState = _state.m_State;
    s32 cnt = (s32)out;

    for (; cnt < packed_raster[state].numBits; cnt++)
    {
        if (currentState & (1 << (packed_raster[state].startBit + cnt)))
        {
            out |= (1 << cnt);
        }
    }

    for (cnt = 0; cnt < packed_raster[state].numBits; cnt++)
    {
        if (value & (1 << cnt))
        {
            _state.m_State = _state.m_State | (1 << (packed_raster[state].startBit + cnt));
        }
        else
        {
            _state.m_State = _state.m_State & ~(1 << (packed_raster[state].startBit + cnt));
        }
    }

    return out;
}

/**
 * Offset/Address/Size: 0x6B8 | 0x801DC2FC | size: 0x58
 */
u32 glGetRasterState(unsigned long raster, eGLState state)
{
    gl_StateBitfield* p = &packed_raster[state];
    s32* pn = &p->numBits;
    return glExtractRasterBits(raster, p, pn);
}

/**
 * Offset/Address/Size: 0x710 | 0x801DC354 | size: 0x5C
 */
u32 glGetRasterState(eGLState state)
{
    gl_StateBitfield* p = &packed_raster[state];
    s32* pn = &p->numBits;
    return glExtractRasterBits(_state.m_State, p, pn);
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

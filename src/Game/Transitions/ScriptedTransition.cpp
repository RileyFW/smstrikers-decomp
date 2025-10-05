#include "Game/Transitions/ScriptedTransition.h"

#include "stdlib.h"
#include "strtold.h"

inline float parseFloat(const char* str, float defaultValue = 0.0f)
{
    if (str != nullptr)
    {
        return atof(str);
    }
    return defaultValue;
}

namespace TransitionModifiers
{

/**
 * Offset/Address/Size: 0x1988 | 0x802082B4 | size: 0x8C
 */
void ScaleModel::ApplyModifier(glPoly2& poly, float time)
{
    float x = ((1.0f - time) * m_v2StartScale.f.x) + (time * m_v2EndScale.f.x);
    float y = ((1.0f - time) * m_v2StartScale.f.y) + (time * m_v2EndScale.f.y);

    poly.m_pos[0].f.x *= x;
    poly.m_pos[0].f.y *= y;
    poly.m_pos[1].f.x *= x;
    poly.m_pos[1].f.y *= y;
    poly.m_pos[2].f.x *= x;
    poly.m_pos[2].f.y *= y;
    poly.m_pos[3].f.x *= x;
    poly.m_pos[3].f.y *= y;
}

/**
 * Offset/Address/Size: 0x18CC | 0x802081F8 | size: 0xBC
 */
void ScaleModel::InitializeFromParser(SimpleParser* parser)
{
    m_v2StartScale.f.x = atof(parser->NextTokenOnLine(true));
    m_v2StartScale.f.y = atof(parser->NextTokenOnLine(true));
    f32 val = m_v2StartScale.f.x;
    char* token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        val = atof(token);
    }
    m_v2EndScale.f.x = val;

    val = m_v2StartScale.f.y;
    token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        val = atof(token);
    }
    m_v2EndScale.f.y = val;
}

/**
 * Offset/Address/Size: 0x1870 | 0x8020819C | size: 0x5C
 */
ScaleModel::~ScaleModel()
{
}

/**
 * Offset/Address/Size: 0x17B0 | 0x802080DC | size: 0xC0
 */
void ColourBlend::ApplyModifier(glPoly2& poly, float time)
{
    nlColour col;
    s32 temp_r6;
    u32 temp_r3;

    temp_r3 = 255.0f * time;
    temp_r6 = 0xFF - temp_r3;

    col.c[0] = ((temp_r6 * m_cStartColour.c[0]) + (temp_r3 * m_cEndColour.c[0])) >> 8;
    col.c[1] = ((temp_r6 * m_cStartColour.c[1]) + (temp_r3 * m_cEndColour.c[1])) >> 8;
    col.c[2] = ((temp_r6 * m_cStartColour.c[2]) + (temp_r3 * m_cEndColour.c[2])) >> 8;
    col.c[3] = ((temp_r6 * m_cStartColour.c[3]) + (temp_r3 * m_cEndColour.c[3])) >> 8;
    poly.SetColour(col);
}

/**
 * Offset/Address/Size: 0x1694 | 0x80207FC0 | size: 0x11C
 */
void ColourBlend::InitializeFromParser(SimpleParser* parser)
{
    m_cStartColour.c[0] = atoi(parser->NextTokenOnLine(true));
    m_cStartColour.c[1] = atoi(parser->NextTokenOnLine(true));
    m_cStartColour.c[2] = atoi(parser->NextTokenOnLine(true));
    m_cStartColour.c[3] = atoi(parser->NextTokenOnLine(true));

    unsigned char val = m_cStartColour.c[0];
    char* token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        val = atoi(token);
    }
    m_cEndColour.c[0] = val;

    val = m_cStartColour.c[1];
    token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        val = atoi(token);
    }
    m_cEndColour.c[1] = val;

    val = m_cStartColour.c[2];
    token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        val = atoi(token);
    }
    m_cEndColour.c[2] = val;

    val = m_cStartColour.c[3];
    token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        val = atoi(token);
    }
    m_cEndColour.c[3] = val;
}

/**
 * Offset/Address/Size: 0x1638 | 0x80207F64 | size: 0x5C
 */
ColourBlend::~ColourBlend()
{
}

/**
 * Offset/Address/Size: 0x15AC | 0x80207ED8 | size: 0x8C
 */
void ScaleTexture::ApplyModifier(glPoly2& poly, float time)
{
    float x = ((1.0f - time) * m_v2StartShift.f.x) + (time * m_v2EndShift.f.x);
    float y = ((1.0f - time) * m_v2StartShift.f.y) + (time * m_v2EndShift.f.y);

    poly.m_uv[0].f.x *= x;
    poly.m_uv[0].f.y *= y;
    poly.m_uv[1].f.x *= x;
    poly.m_uv[1].f.y *= y;
    poly.m_uv[2].f.x *= x;
    poly.m_uv[2].f.y *= y;
    poly.m_uv[3].f.x *= x;
    poly.m_uv[3].f.y *= y;
}

/**
 * Offset/Address/Size: 0x14F0 | 0x80207E1C | size: 0xBC
 */
void ScaleTexture::InitializeFromParser(SimpleParser* parser)
{
    m_v2StartShift.f.x = atof(parser->NextTokenOnLine(true));
    m_v2StartShift.f.y = atof(parser->NextTokenOnLine(true));
    f32 val = m_v2StartShift.f.x;
    char* token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        val = atof(token);
    }
    m_v2EndShift.f.x = val;

    val = m_v2StartShift.f.y;
    token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        val = atof(token);
    }
    m_v2EndShift.f.y = val;
}

/**
 * Offset/Address/Size: 0x1494 | 0x80207DC0 | size: 0x5C
 */
ScaleTexture::~ScaleTexture()
{
}

/**
 * Offset/Address/Size: 0x1408 | 0x80207D34 | size: 0x8C
 */
void TranslateModel::ApplyModifier(glPoly2& poly, float time)
{
    float x = ((1.0f - time) * m_v2StartShift.f.x) + (time * m_v2EndShift.f.x);
    float y = ((1.0f - time) * m_v2StartShift.f.y) + (time * m_v2EndShift.f.y);

    poly.m_pos[0].f.x += x;
    poly.m_pos[0].f.y += y;
    poly.m_pos[1].f.x += x;
    poly.m_pos[1].f.y += y;
    poly.m_pos[2].f.x += x;
    poly.m_pos[2].f.y += y;
    poly.m_pos[3].f.x += x;
    poly.m_pos[3].f.y += y;
}

/**
 * Offset/Address/Size: 0x134C | 0x80207C78 | size: 0xBC
 */
void TranslateModel::InitializeFromParser(SimpleParser* parser)
{
    m_v2StartShift.f.x = atof(parser->NextTokenOnLine(true));
    m_v2StartShift.f.y = atof(parser->NextTokenOnLine(true));
    f32 val = m_v2StartShift.f.x;
    char* token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        val = atof(token);
    }
    m_v2EndShift.f.x = val;

    val = m_v2StartShift.f.y;
    token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        val = atof(token);
    }
    m_v2EndShift.f.y = val;
}

/**
 * Offset/Address/Size: 0x12F0 | 0x80207C1C | size: 0x5C
 */
TranslateModel::~TranslateModel()
{
}

/**
 * Offset/Address/Size: 0x1264 | 0x80207B90 | size: 0x8C
 */
void TranslateTexture::ApplyModifier(glPoly2& poly, float time)
{
    float x = ((1.0f - time) * m_v2StartShift.f.x) + (time * m_v2EndShift.f.x);
    float y = ((1.0f - time) * m_v2StartShift.f.y) + (time * m_v2EndShift.f.y);

    poly.m_uv[0].f.x += x;
    poly.m_uv[0].f.y += y;
    poly.m_uv[1].f.x += x;
    poly.m_uv[1].f.y += y;
    poly.m_uv[2].f.x += x;
    poly.m_uv[2].f.y += y;
    poly.m_uv[3].f.x += x;
    poly.m_uv[3].f.y += y;
}

/**
 * Offset/Address/Size: 0x11A8 | 0x80207AD4 | size: 0xBC
 */
void TranslateTexture::InitializeFromParser(SimpleParser* parser)
{
    m_v2StartShift.f.x = atof(parser->NextTokenOnLine(true));
    m_v2StartShift.f.y = atof(parser->NextTokenOnLine(true));
    f32 val = m_v2StartShift.f.x;
    char* token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        val = atof(token);
    }
    m_v2EndShift.f.x = val;

    val = m_v2StartShift.f.y;
    token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        val = atof(token);
    }
    m_v2EndShift.f.y = val;
}

/**
 * Offset/Address/Size: 0x114C | 0x80207A78 | size: 0x5C
 */
TranslateTexture::~TranslateTexture()
{
}

/**
 * Offset/Address/Size: 0x1064 | 0x80207990 | size: 0xE8
 */
void RotateModel::ApplyModifier(glPoly2& poly, float time)
{
    nlMatrix4 m4;
    nlMatrix3 m3;
    nlQuaternion quat;

    nlMakeQuat(quat, m_v3Axis, (3.1415927f * ((m_angleStart * (1.0f - time)) + (time * m_angleEnd))) / 180.0f);
    nlQuatToMatrix(m4, quat);

    m3.m[0] = m4.f.m11;
    m3.m[1] = m4.f.m12;
    m3.m[3] = m4.f.m21;
    m3.m[4] = m4.f.m22;
    m3.m[7] = 0.0f;
    m3.m[6] = 0.0f;
    m3.m[5] = 0.0f;
    m3.m[2] = 0.0f;
    m3.m[8] = 1.0f;

    for (int i = 0; i < 4; i++)
    {
        nlVector2 temp;
        nlMultVectorMatrix(temp, poly.m_pos[i], m3);
        poly.m_pos[i] = temp;
    }
}

/**
 * Offset/Address/Size: 0xF9C | 0x802078C8 | size: 0xC8
 */
void RotateModel::InitializeFromParser(SimpleParser* parser)
{
    f32 angleEnd;

    m_v3Axis.f.x = atof(parser->NextTokenOnLine(true));
    m_v3Axis.f.y = atof(parser->NextTokenOnLine(true));
    m_v3Axis.f.z = atof(parser->NextTokenOnLine(true));
    m_angleStart = atof(parser->NextTokenOnLine(true));

    angleEnd = m_angleStart;
    char* token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        angleEnd = atof(token);
    }
    m_angleEnd = angleEnd;
}

/**
 * Offset/Address/Size: 0xF40 | 0x8020786C | size: 0x5C
 */
RotateModel::~RotateModel()
{
}

/**
 * Offset/Address/Size: 0xE58 | 0x80207784 | size: 0xE8
 */
void RotateTexture::ApplyModifier(glPoly2& poly, float time)
{
    nlMatrix4 m4;
    nlMatrix3 m3;
    nlQuaternion quat;

    nlMakeQuat(quat, m_v3Axis, (3.1415927f * ((m_angleStart * (1.0f - time)) + (time * m_angleEnd))) / 180.0f);
    nlQuatToMatrix(m4, quat);

    m3.m[0] = m4.f.m11;
    m3.m[1] = m4.f.m12;
    m3.m[3] = m4.f.m21;
    m3.m[4] = m4.f.m22;
    m3.m[7] = 0.0f;
    m3.m[6] = 0.0f;
    m3.m[5] = 0.0f;
    m3.m[2] = 0.0f;
    m3.m[8] = 1.0f;

    for (int i = 0; i < 4; i++)
    {
        nlVector2 temp;
        nlMultVectorMatrix(temp, poly.m_pos[i], m3);
        poly.m_pos[i] = temp;
    }
}

/**
 * Offset/Address/Size: 0xD90 | 0x802076BC | size: 0xC8
 */
void RotateTexture::InitializeFromParser(SimpleParser* parser)
{
    f32 angleEnd;

    m_v3Axis.f.x = atof(parser->NextTokenOnLine(true));
    m_v3Axis.f.y = atof(parser->NextTokenOnLine(true));
    m_v3Axis.f.z = atof(parser->NextTokenOnLine(true));
    m_angleStart = atof(parser->NextTokenOnLine(true));

    angleEnd = m_angleStart;
    char* token = parser->NextTokenOnLine(true);
    if (token != nullptr)
    {
        angleEnd = atof(token);
    }
    m_angleEnd = angleEnd;
}

/**
 * Offset/Address/Size: 0xD34 | 0x80207660 | size: 0x5C
 */
RotateTexture::~RotateTexture()
{
}

/**
 * Offset/Address/Size: 0xCE8 | 0x80207614 | size: 0x4C
 */
void ScreenBlur::Cleanup()
{
    glViewSetFilter(GLV_ScreenBlur, GLFilter_None);
    glViewSetFilterSource(GLV_ScreenBlur, GLTG_Main);
    glViewSetFilter(GLV_ScreenBlur2, GLFilter_None);
    glViewSetFilterSource(GLV_ScreenBlur2, GLTG_GlowConv);
}

/**
 * Offset/Address/Size: 0xCE4 | 0x80207610 | size: 0x4
 */
void ScreenBlur::ApplyModifier(glPoly2&, float)
{
}

/**
 * Offset/Address/Size: 0xC60 | 0x8020758C | size: 0x84
 */
void ScreenBlur::InitializeFromParser(SimpleParser* parser)
{
    m_fStartBlend = parseFloat(parser->NextTokenOnLine(true));
    m_fEndBlend = parseFloat(parser->NextTokenOnLine(true));
}

/**
 * Offset/Address/Size: 0xC04 | 0x80207530 | size: 0x5C
 */
ScreenBlur::~ScreenBlur()
{
}

/**
 * Offset/Address/Size: 0xBC8 | 0x802074F4 | size: 0x3C
 */
void ScreenGrab::Cleanup()
{
    glViewSetFilter(GLV_Particles, GLFilter_None);
    m_bDoGrab = true;
}

/**
 * Offset/Address/Size: 0xB64 | 0x80207490 | size: 0x64
 */
void ScreenGrab::ApplyModifier(glPoly2& poly, float time)
{
    if (m_bDoGrab)
    {
        glViewSetFilter(GLV_ScreenGrab, GLFilter_Blt);
        glViewSetFilterSource(GLV_ScreenGrab, GLTG_Main);
        m_bDoGrab = false;
    }
    else
    {
        glViewSetFilter(GLV_ScreenGrab, GLFilter_None);
    }
}

/**
 * Offset/Address/Size: 0xB60 | 0x8020748C | size: 0x4
 */
void ScreenGrab::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0xB04 | 0x80207430 | size: 0x5C
 */
ScreenGrab::~ScreenGrab()
{
}

/**
 * Offset/Address/Size: 0xA74 | 0x802073A0 | size: 0x90
 */
void ToScreenCoordinates::ApplyModifier(glPoly2& poly, float time)
{
    for (int i = 0; i < 4; i++)
    {
        nlVector2 temp;
        nlMultVectorMatrix(temp, poly.m_pos[i], m_m3Position);
        poly.m_pos[i] = temp;

        nlMultVectorMatrix(temp, poly.m_uv[i], m_m3UV);
        poly.m_uv[i] = temp;
    }
}

/**
 * Offset/Address/Size: 0xA70 | 0x8020739C | size: 0x4
 */
void ToScreenCoordinates::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0xA14 | 0x80207340 | size: 0x5C
 */
ToScreenCoordinates::~ToScreenCoordinates()
{
}

} // namespace TransitionModifiers

/**
 * Offset/Address/Size: 0x9A0 | 0x802072CC | size: 0x74
 */
ScriptedScreenTransition::ScriptedScreenTransition()
{
    m_pModifiers = nullptr;
    m_nModifiers = 0;
    m_fLength = 0.0f;
    m_fCurrentTime = 0.0f;
    m_nTexture = glHash("global/white");
    m_eTimeLine = TIME_LINEAR;
}

/**
 * Offset/Address/Size: 0x8D0 | 0x802071FC | size: 0xD0
 */
ScriptedScreenTransition::~ScriptedScreenTransition()
{
    if (m_pModifiers != nullptr)
    {
        for (int i = 0; i < m_nModifiers; i++)
        {
            delete m_pModifiers[i];
            m_pModifiers[i] = nullptr;
        }

        delete[] m_pModifiers;
        m_pModifiers = nullptr;
    }
}

/**
 * Offset/Address/Size: 0x8C0 | 0x802071EC | size: 0x10
 */
void ScriptedScreenTransition::Update(float dt)
{
    m_fCurrentTime += dt;
}

/**
 * Offset/Address/Size: 0x708 | 0x80207034 | size: 0x1B8
 */
void ScriptedScreenTransition::Render(eGLView)
{
}

/**
 * Offset/Address/Size: 0x698 | 0x80206FC4 | size: 0x70
 */
void ScriptedScreenTransition::Cancel()
{
}

/**
 * Offset/Address/Size: 0x3B8 | 0x80206CE4 | size: 0x2E0
 */
void ScriptedScreenTransition::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8020692C | size: 0x3B8
 */
void ScriptedScreenTransition::GetModifierFromName(char*)
{
}

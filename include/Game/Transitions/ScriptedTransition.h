#ifndef _SCRIPTEDTRANSITION_H_
#define _SCRIPTEDTRANSITION_H_

#include "NL/nlMath.h"
#include "NL/gl/glDraw2.h"

#include "Game/Sys/simpleparser.h"
#include "Game/Transitions/ScreenTransitionManager.h"

#include "NL/gl/glStruct.h"

enum eTimeLine
{
    TIME_LINEAR = 0,
    TIME_ACCEL = 1,
    TIME_DECEL = 2,
    NUM_TIME_LINES = 3,
};

class TransitionModifierInterface
{
public:
    TransitionModifierInterface() { };
    virtual ~TransitionModifierInterface() { };
    virtual void InitializeFromParser(SimpleParser*) = 0;
    virtual void ApplyModifier(glPoly2&, float) = 0;
    virtual void Cleanup() { };
};

class ScriptedScreenTransition : public ScreenTransition
{
public:
    ScriptedScreenTransition();
    virtual ~ScriptedScreenTransition();
    virtual bool IsFinished() { return m_fCurrentTime > m_fLength; };
    virtual void Reset() { m_fCurrentTime = 0.0f; };
    virtual float Time() const { return m_fCurrentTime / m_fLength; };
    virtual float GetTransitionLength() { return m_fLength; };
    virtual void Update(float);
    virtual void Render(eGLView);
    virtual void Cancel();

    void InitializeFromParser(SimpleParser*);
    TransitionModifierInterface* GetModifierFromName(char*);

    /* 0x04 */ TransitionModifierInterface** m_pModifiers; // offset 0x4, size 0x4
    /* 0x08 */ int m_nModifiers;                           // offset 0x8, size 0x4
    /* 0x0C */ float m_fLength;                            // offset 0xC, size 0x4
    /* 0x10 */ float m_fCurrentTime;                       // offset 0x10, size 0x4
    /* 0x14 */ u32 m_nTexture;                             // offset 0x14, size 0x4
    /* 0x18 */ eTimeLine m_eTimeLine;                      // offset 0x18, size 0x4
}; // total size: 0x1C

namespace TransitionModifiers
{

class ScaleModel : public TransitionModifierInterface
{
public:
    ScaleModel()
    {
        m_v2StartScale.f.x = 1.0f;
        m_v2StartScale.f.y = 1.0f;
        m_v2EndScale.f.x = 1.0f;
        m_v2EndScale.f.y = 1.0f;
    }
    virtual ~ScaleModel();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x4 */ nlVector2 m_v2StartScale;
    /* 0xC */ nlVector2 m_v2EndScale;
}; // total size: 0x14

class ColourBlend : public TransitionModifierInterface
{
public:
    ColourBlend()
    {
        nlColourSet(m_cStartColour, 0xFF, 0xFF, 0xFF, 0xFF);
        nlColourSet(m_cEndColour, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    virtual ~ColourBlend();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x4 */ nlColour m_cStartColour;
    /* 0x8 */ nlColour m_cEndColour;
}; // total size: 0xC

class ScaleTexture : public TransitionModifierInterface
{
public:
    ScaleTexture()
    {
        m_v2StartShift.f.x = 1.0f;
        m_v2StartShift.f.y = 1.0f;
        m_v2EndShift.f.x = 1.0f;
        m_v2EndShift.f.y = 1.0f;
    }
    virtual ~ScaleTexture();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x4 */ nlVector2 m_v2StartShift;
    /* 0xC */ nlVector2 m_v2EndShift;
}; // total size: 0x14

class TranslateModel : public TransitionModifierInterface
{
public:
    TranslateModel()
    {
        m_v2StartShift.f.x = 0.0f;
        m_v2StartShift.f.y = 0.0f;
        m_v2EndShift.f.x = 0.0f;
        m_v2EndShift.f.y = 0.0f;
    }
    virtual ~TranslateModel();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x4 */ nlVector2 m_v2StartShift;
    /* 0xC */ nlVector2 m_v2EndShift;
}; // total size: 0x14

class TranslateTexture : public TransitionModifierInterface
{
public:
    TranslateTexture()
    {
        m_v2StartShift.f.x = 0.0f;
        m_v2StartShift.f.y = 0.0f;
        m_v2EndShift.f.x = 0.0f;
        m_v2EndShift.f.y = 0.0f;
    }
    virtual ~TranslateTexture();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x04 */ nlVector2 m_v2StartShift;
    /* 0x0C */ nlVector2 m_v2EndShift;
}; // total size: 0x14

class RotateModel : public TransitionModifierInterface
{
public:
    RotateModel()
    {
        m_angleStart = 0.0f;
        m_angleEnd = 0.0f;
        m_v3Axis.f.x = 0.0f;
        m_v3Axis.f.y = 0.0f;
        m_v3Axis.f.z = 1.0f;
    }
    virtual ~RotateModel();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x04 */ nlVector3 m_v3Axis;
    /* 0x10 */ float m_angleStart;
    /* 0x14 */ float m_angleEnd;
}; // total size: 0x18

class RotateTexture : public TransitionModifierInterface
{
public:
    RotateTexture()
    {
        m_angleStart = 0.0f;
        m_angleEnd = 0.0f;
        m_v3Axis.f.x = 0.0f;
        m_v3Axis.f.y = 0.0f;
        m_v3Axis.f.z = 1.0f;
    }
    virtual ~RotateTexture();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x04 */ nlVector3 m_v3Axis;
    /* 0x10 */ float m_angleStart;
    /* 0x14 */ float m_angleEnd;
}; // total size: 0x18

class ScreenBlur : public TransitionModifierInterface
{
public:
    ScreenBlur()
    {
        m_fStartBlend = 1.0f;
        m_fEndBlend = 1.0f;
    }
    virtual ~ScreenBlur();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);
    virtual void Cleanup();

    /* 0x4 */ float m_fStartBlend;
    /* 0x8 */ float m_fEndBlend;
}; // total size: 0xC

class ScreenGrab : public TransitionModifierInterface
{
public:
    ScreenGrab()
    {
        m_bDoGrab = true;
        m_nTexture = glHash("target/backbuffer");
    }
    virtual ~ScreenGrab();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);
    virtual void Cleanup();

    /* 0x4 */ bool m_bDoGrab;
    /* 0x8 */ u32 m_nTexture;
}; // total size: 0xC

class ToScreenCoordinates : public TransitionModifierInterface
{
public:
    ToScreenCoordinates()
    {
        float temp_f30 = 0.5f * glGetOrthographicWidth();
        float temp_f31 = 0.5f * glGetOrthographicHeight();
        float temp_f1 = -glGetScreenInfo()->PixelCentre;

        m_m3Position.SetIdentity();
        m_m3UV.SetIdentity();

        m_m3Position.f.m11 = temp_f30;
        m_m3Position.f.m22 = temp_f31;
        m_m3Position.f.m31 = temp_f30 - temp_f1;
        m_m3Position.f.m32 = temp_f31 - temp_f1;

        m_m3UV.f.m32 = 0.5f;
        m_m3UV.f.m31 = 0.5f;
        m_m3UV.f.m22 = 0.5f;
        m_m3UV.f.m11 = 0.5f;
    };

    virtual ~ToScreenCoordinates();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x04 */ nlMatrix3 m_m3Position;
    /* 0x28 */ nlMatrix3 m_m3UV;
}; // total size: 0x4C

}; // namespace TransitionModifiers

#endif // _SCRIPTEDTRANSITION_H_

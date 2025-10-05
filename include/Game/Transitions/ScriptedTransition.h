#ifndef _SCRIPTEDTRANSITION_H_
#define _SCRIPTEDTRANSITION_H_

#include "NL/nlMath.h"
#include "NL/gl/glDraw2.h"

#include "Game/Sys/simpleparser.h"
#include "Game/Transitions/ScreenTransitionManager.h"

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
    void GetModifierFromName(char*);

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
    virtual ~ScaleModel();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x4 */ nlVector2 m_v2StartScale;
    /* 0xC */ nlVector2 m_v2EndScale;
}; // total size: 0x14

class ColourBlend : public TransitionModifierInterface
{
public:
    virtual ~ColourBlend();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x4 */ nlColour m_cStartColour;
    /* 0x8 */ nlColour m_cEndColour;
}; // total size: 0xC

class ScaleTexture : public TransitionModifierInterface
{
public:
    virtual ~ScaleTexture();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x4 */ nlVector2 m_v2StartShift;
    /* 0xC */ nlVector2 m_v2EndShift;
}; // total size: 0x14

class TranslateModel : public TransitionModifierInterface
{
public:
    virtual ~TranslateModel();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x4 */ nlVector2 m_v2StartShift;
    /* 0xC */ nlVector2 m_v2EndShift;
}; // total size: 0x14

class TranslateTexture : public TransitionModifierInterface
{
public:
    virtual ~TranslateTexture();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x04 */ nlVector2 m_v2StartShift;
    /* 0x0C */ nlVector2 m_v2EndShift;
}; // total size: 0x14

class RotateModel : public TransitionModifierInterface
{
public:
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
    virtual ~ScreenGrab();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);
    virtual void Cleanup();

    /* 0x4 */ bool m_bDoGrab;
    /* 0x8 */ u32 m_nTexture;
}; // total size: 0xC

class ToScreenCoordinates : public TransitionModifierInterface
{
    virtual ~ToScreenCoordinates();
    virtual void ApplyModifier(glPoly2&, float);
    virtual void InitializeFromParser(SimpleParser*);

    /* 0x04 */ nlMatrix3 m_m3Position;
    /* 0x28 */ nlMatrix3 m_m3UV;
}; // total size: 0x4C

}; // namespace TransitionModifiers

#endif // _SCRIPTEDTRANSITION_H_

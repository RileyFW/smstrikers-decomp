#ifndef _SCRIPTEDTRANSITION_H_
#define _SCRIPTEDTRANSITION_H_


class ScriptedScreenTransition
{
public:
    void GetTransitionLength();
    void Time() const;
    void Reset();
    void IsFinished();
    ScriptedScreenTransition();
    ~ScriptedScreenTransition();
    void Update(float);
    void Render(eGLView);
    void Cancel();
    void InitializeFromParser(SimpleParser*);
    void GetModifierFromName(char*);
};


class TransitionModifiers
{
public:
    void ScaleModel::ApplyModifier(glPoly2&, float);
    void ScaleModel::InitializeFromParser(SimpleParser*);
    void ScaleModel::~ScaleModel();
    void ColourBlend::ApplyModifier(glPoly2&, float);
    void ColourBlend::InitializeFromParser(SimpleParser*);
    void ColourBlend::~ColourBlend();
    void ScaleTexture::ApplyModifier(glPoly2&, float);
    void ScaleTexture::InitializeFromParser(SimpleParser*);
    void ScaleTexture::~ScaleTexture();
    void TranslateModel::ApplyModifier(glPoly2&, float);
    void TranslateModel::InitializeFromParser(SimpleParser*);
    void TranslateModel::~TranslateModel();
    void TranslateTexture::ApplyModifier(glPoly2&, float);
    void TranslateTexture::InitializeFromParser(SimpleParser*);
    void TranslateTexture::~TranslateTexture();
    void RotateModel::ApplyModifier(glPoly2&, float);
    void RotateModel::InitializeFromParser(SimpleParser*);
    void RotateModel::~RotateModel();
    void RotateTexture::ApplyModifier(glPoly2&, float);
    void RotateTexture::InitializeFromParser(SimpleParser*);
    void RotateTexture::~RotateTexture();
    void ScreenBlur::Cleanup();
    void ScreenBlur::ApplyModifier(glPoly2&, float);
    void ScreenBlur::InitializeFromParser(SimpleParser*);
    void ScreenBlur::~ScreenBlur();
    void ScreenGrab::Cleanup();
    void ScreenGrab::ApplyModifier(glPoly2&, float);
    void ScreenGrab::InitializeFromParser(SimpleParser*);
    void ScreenGrab::~ScreenGrab();
    void ToScreenCoordinates::ApplyModifier(glPoly2&, float);
    void ToScreenCoordinates::InitializeFromParser(SimpleParser*);
    void ToScreenCoordinates::~ToScreenCoordinates();
};


class TransitionModifierInterface
{
public:
    void Cleanup();
    ~TransitionModifierInterface();
};

#endif // _SCRIPTEDTRANSITION_H_
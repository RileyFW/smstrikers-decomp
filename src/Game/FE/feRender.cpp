#include "Game/FE/feRender.h"
#include "Game/FE/tlInstance.h"
#include "Game/FE/tlTextInstance.h"
#include "Game/FE/feScene.h"
#include "Game/FE/fePackage.h"
#include "Game/FE/fePresentation.h"
#include "NL/gl/glMatrixStack.h"
#include "NL/nlMemory.h"
#include "NL/nlColour.h"
#include "NL/platvmath.h"
#include "NL/gl/gl.h"

GLMatrixStack* FERender::m_pMatrixStack = nullptr;
FEScene* FERender::m_pRenderScene = nullptr;

static nlFloatColour s_currentAssetColour;

/**
 * Offset/Address/Size: 0x0 | 0x8020A288 | size: 0x3BC
 */
void FERender::RenderImageInstance(const TLImageInstance*)
{
}

inline void ConvertFloatColourToColour(nlColour& out, const nlFloatColour& in)
{
    out.c[0] = in.c[0] * 255.0f;
    out.c[1] = in.c[1] * 255.0f;
    out.c[2] = in.c[2] * 255.0f;
    out.c[3] = in.c[3] * 255.0f;
}

inline void ConvertFloatColourToColour_(nlColour& out, const float r, const float g, const float b, const float a)
{
    out.c[0] = r;
    out.c[1] = g;
    out.c[2] = b;
    out.c[3] = a;
}

/**
 * Offset/Address/Size: 0x3BC | 0x8020A644 | size: 0xD0
 */
void FERender::RenderTextInstance(TLTextInstance* textInstance)
{
    nlMatrix4 combinedMatrix;

    m_pMatrixStack->GetTop(combinedMatrix);

    nlMultMatrices(combinedMatrix, combinedMatrix, m_pRenderScene->m_matView);

    textInstance->m_DrawInfo.pMatrix = &combinedMatrix;

    nlColour colour;
    ConvertColour(colour, s_currentAssetColour);
    // ConvertFloatColourToColour(colour, s_currentAssetColour);
    // ConvertFloatColourToColour_(colour, s_currentAssetColour.c[0] * 255.0f, s_currentAssetColour.c[1] * 255.0f, s_currentAssetColour.c[2] * 255.0f, s_currentAssetColour.c[3] * 255.0f);

    textInstance->Render((eGLView)(m_pRenderScene->m_uRenderView), colour);
}

/**
 * Offset/Address/Size: 0x48C | 0x8020A714 | size: 0x64
 */
void FERender::RenderScene(FEScene* scene)
{
    if (scene == nullptr)
    {
        return;
    }

    m_pRenderScene = scene;
    m_pMatrixStack->LoadIdentity();

    s_currentAssetColour.c[0] = 1.0f;
    s_currentAssetColour.c[1] = 1.0f;
    s_currentAssetColour.c[2] = 1.0f;
    s_currentAssetColour.c[3] = 1.0f;

    FEPresentation* presentation = scene->m_pFEPackage->GetPresentation();
    RenderPresentation(presentation);

    m_pRenderScene = nullptr;
}

/**
 * Offset/Address/Size: 0x4F0 | 0x8020A778 | size: 0x38
 */
void FERender::RenderPresentation(const FEPresentation* presentation)
{
    if (presentation == nullptr)
    {
        return;
    }

    if (presentation->m_slides == nullptr)
    {
        return;
    }

    RenderSlide(presentation->m_currentSlide);
}

/**
 * Offset/Address/Size: 0x528 | 0x8020A7B0 | size: 0x42C
 */
void FERender::RenderComponentInstance(TLComponentInstance*)
{
}

/**
 * Offset/Address/Size: 0x978 | 0x8020AC00 | size: 0x418
 */
void FERender::RenderSlide(const TLSlide*)
{
}

/**
 * Offset/Address/Size: 0xD90 | 0x8020B018 | size: 0x7A8
 */
void FERender::RenderTimeLineAsset(TLInstance*, float)
{
}

/**
 * Offset/Address/Size: 0x1538 | 0x8020B7C0 | size: 0x24
 */
void FERender::PopTransformMatrix()
{
    m_pMatrixStack->PopMatrix();
}

/**
 * Offset/Address/Size: 0x155C | 0x8020B7E4 | size: 0xF4
 */
void FERender::PushTransformMatrix(const TLInstance* instance)
{
    nlMatrix4 combinedMatrix; // r1+0x88
    nlMatrix4 scaleMatrix;    // r1+0x48
    nlMatrix4 rotationMatrix; // r1+0x08

    nlMakeRotationMatrixEulerAngles(rotationMatrix, instance->GetRotation().f.x, instance->GetRotation().f.y, instance->GetRotation().f.z);
    nlMakeScaleMatrix(scaleMatrix, instance->GetScale().f.x, instance->GetScale().f.y, instance->GetScale().f.z);
    nlMultMatrices(combinedMatrix, scaleMatrix, rotationMatrix);

    const feVector3& tlPosition = instance->GetPosition();
    combinedMatrix.SetRow4_(4, tlPosition.f.x, tlPosition.f.y, tlPosition.f.z * -1.0f, 1.0f);

    m_pMatrixStack->PushMatrix();
    m_pMatrixStack->MultMatrix(combinedMatrix);
}

/**
 * Offset/Address/Size: 0x1650 | 0x8020B8D8 | size: 0x50
 */
void FERender::Initialize()
{
    if (m_pMatrixStack == nullptr)
    {
        m_pMatrixStack = new (nlMalloc(sizeof(GLMatrixStack), 8, false)) GLMatrixStack(16);
    }
}

/**
 * Offset/Address/Size: 0x16A0 | 0x8020B928 | size: 0x38
 */
void FERender::Cleanup()
{
    if (m_pMatrixStack != nullptr)
    {
        delete m_pMatrixStack;
        m_pMatrixStack = nullptr;
    }
}

/**
 * Offset/Address/Size: 0x16D8 | 0x8020B960 | size: 0xB4
 */
void FERender::CalculateCurrentAssetColour(const TLInstance* instance)
{
    nlFloatColour* curAssetColour = &s_currentAssetColour;
    for (u32 i = 0; i < 4; i++)
    {
        curAssetColour->c[i] = (instance->GetColour().c[i] * curAssetColour->c[i]) / 255.0f;
    }
}

// {
//     const nlColour& colour = instance->GetColour();

//     for (int i = 0; i < 4; i++)
//     {
//         float component = (float)colour.c[i];
//         s_currentAssetColour.c[i] = (s_currentAssetColour.c[i] * component) / 255.0f;
//     }
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020BA14 | size: 0x8
//  */
// void TLInstance::GetType() const
// {
// }

// /**
//  * Offset/Address/Size: 0x8 | 0x8020BA1C | size: 0x8
//  */
// void TLInstance::IsVisible() const
// {
// }

// /**
//  * Offset/Address/Size: 0x10 | 0x8020BA24 | size: 0x8
//  */
// void TLInstance::GetLibRefObject() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020BA2C | size: 0x8
//  */
// void TLComponent::GetActiveSlide()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020BA34 | size: 0x8
//  */
// void FEScene::GetRenderView() const
// {
// }

// /**
//  * Offset/Address/Size: 0x8 | 0x8020BA3C | size: 0x8
//  */
// void FEScene::GetCameraMatrix() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020BA44 | size: 0x70
//  */
// void ConvertColour(nlColour&, const nlFloatColour&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020BAB4 | size: 0x8
//  */
// void TLTextInstance::SetMatrix(nlMatrix4*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020BABC | size: 0x24
//  */
// void nlMatrix4::SetTranslation(const nlVector3&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020BAE0 | size: 0x1C
//  */
// void feVector3::GetNLVector3(nlVector3&) const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020BAFC | size: 0x8
//  */
// void TLSlide::GetCurrentTime() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020BB04 | size: 0x3C
//  */
// void 0x8028D570..0x8028D574 | size: 0x4
// {
// }

#include "Game/Drawable/DrawableBall.h"
#include "Game/Drawable/DrawableCharacter.h"
#include "Game/RenderSnapshot.h"
#include "Game/Ball.h"
#include "Game/CharacterTemplate.h"
#include "NL/gl/glModel.h"
#include "NL/gl/glState.h"
#include "NL/gl/glUserData.h"

extern float g_fBallBlur;

/**
 * Offset/Address/Size: 0x0 | 0x8011DD50 | size: 0x80
 */
void DrawableBall::EvaluateFrom(DrawableCharacter& character)
{
    mPosition = character.GetBallPosition();
    mOrientation = character.GetBallOrientation();
}

/**
 * Offset/Address/Size: 0x80 | 0x8011DDD0 | size: 0x140
 */
void DrawableBall::Blend(const float*, const DrawableBall&, const DrawableBall&)
{
}

/**
 * Offset/Address/Size: 0x1C0 | 0x8011DF10 | size: 0x47C
 */
void DrawableBall::Render() const
{
}

/**
 * Offset/Address/Size: 0x63C | 0x8011E38C | size: 0xB4
 */
glModel* BallLightingCB(glModel* pModel, eGLView& view, unsigned long& uLayer)
{
    glModelPacket* pPacket;

    static u32 WhiteTexture = glGetTexture("global/white");

    pPacket = pModel->packets;
    while (pPacket < &pModel->packets[pModel->numPackets])
    {
        pPacket->state.texture[0] = WhiteTexture;
        glSetRasterState(pPacket->state.raster, GLS_AlphaBlend, 4);
        pPacket++;
    }

    uLayer += 2;
    return pModel;
}

/**
 * Offset/Address/Size: 0x6F0 | 0x8011E440 | size: 0x10C
 */
glModel* BallBlurCB(glModel* pModel, eGLView& view, unsigned long& uLayer)
{
    glModelPacket* pPacket;
    if (g_fBallBlur == 0.0f)
    {
        return nullptr;
    }

    void* pUserDataHandle = glUserAlloc(GLUD_ConstantColour, 4, false);
    u8* pColorData = (u8*)glUserGetData(pUserDataHandle);

    const float alphaFloat = 255.0f * g_fBallBlur;

    pColorData[0] = 0xC8;
    pColorData[1] = 0xC8;
    pColorData[2] = 0xC8;
    pColorData[3] = (u8)(int)alphaFloat;

    pPacket = pModel->packets;
    while (pPacket < &pModel->packets[pModel->numPackets])
    {
        if (g_fBallBlur != 1.0f)
        {
            glSetRasterState(pPacket->state.raster, GLS_AlphaBlend, 1);
            glSetRasterState(pPacket->state.raster, GLS_DepthWrite, 0);
            glUserAttach(pUserDataHandle, pPacket, false);
        }
        pPacket++;
    }

    return pModel;
}

/**
 * Offset/Address/Size: 0x7FC | 0x8011E54C | size: 0xCC
 */
void DrawableBall::Grab()
{
    mOrientation = g_pBall->m_qOrientation;
    mPosition = g_pBall->m_v3Position;
    mVelocity = g_pBall->m_v3Velocity;
    mOwnerIndex = GetCharacterIndex(g_pBall->m_pOwner);
    mPrevOwnerIndex = GetCharacterIndex(g_pBall->m_pPrevOwner);
    mPassTargetIndex = GetCharacterIndex(g_pBall->m_pPassTarget);
    mLastTouchIndex = GetCharacterIndex(g_pBall->m_pLastTouch);
    mVisible = true;
}

/**
 * Offset/Address/Size: 0x8C8 | 0x8011E618 | size: 0x24
 */
DrawableCharacter* DrawableBall::IndexToPlayer(int index) const
{
    if (index == -1)
    {
        return nullptr;
    }
    return &mRenderSnapshot->mCharacters[index];
}

/**
 * Offset/Address/Size: 0x0 | 0x8011E63C | size: 0x138
 */
template <>
void DrawableBall::Replay<LoadFrame>(LoadFrame& frame)
{
}

/**
 * Offset/Address/Size: 0x138 | 0x8011E774 | size: 0x138
 */
template <>
void DrawableBall::Replay<SaveFrame>(SaveFrame& frame)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8011E8AC | size: 0x50
 */
// void Replayable<1, SaveFrame, char>(SaveFrame&, char&)
// {
// }

/**
 * Offset/Address/Size: 0x50 | 0x8011E8FC | size: 0x54
 */
// void Replayable<1, LoadFrame, char>(LoadFrame&, char&)
// {
// }

/**
 * Offset/Address/Size: 0xA4 | 0x8011E950 | size: 0x98
 */
// void Replayable<1, SaveFrame, FloatCompressor<-127, 127, 7>>(SaveFrame&, const FloatCompressor<-127, 127, 7>&)
// {
// }

/**
 * Offset/Address/Size: 0x13C | 0x8011E9E8 | size: 0x98
 */
// void Replayable<1, SaveFrame, FloatCompressor<-1, 1, 13>>(SaveFrame&, const FloatCompressor<-1, 1, 13>&)
// {
// }

/**
 * Offset/Address/Size: 0x1D4 | 0x8011EA80 | size: 0x98
 */
// void Replayable<1, SaveFrame, FloatCompressor<-127, 127, 5>>(SaveFrame&, const FloatCompressor<-127, 127, 5>&)
// {
// }

/**
 * Offset/Address/Size: 0x26C | 0x8011EB18 | size: 0x74
 */
// void Replayable<1, LoadFrame, FloatCompressor<-127, 127, 7>>(LoadFrame&, const FloatCompressor<-127, 127, 7>&)
// {
// }

/**
 * Offset/Address/Size: 0x2E0 | 0x8011EB8C | size: 0x74
 */
// void Replayable<1, LoadFrame, FloatCompressor<-1, 1, 13>>(LoadFrame&, const FloatCompressor<-1, 1, 13>&)
// {
// }

/**
 * Offset/Address/Size: 0x354 | 0x8011EC00 | size: 0x74
 */
// void Replayable<1, LoadFrame, FloatCompressor<-127, 127, 5>>(LoadFrame&, const FloatCompressor<-127, 127, 5>&)
// {
// }

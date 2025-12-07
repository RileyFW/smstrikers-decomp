#include "Game/Drawable/DrawableCharacter.h"
#include "Game/Character.h"
#include "Game/Player.h"
#include "Game/AI/HeadTrack.h"

cCharacter* DrawableCharacter::spRenderOnlyThisCharacter = nullptr;
bool DrawableCharacter::sbRenderOpposingGoalieToo = false;

/**
 * Offset/Address/Size: 0x2C0 | 0x8011C5EC | size: 0x178
 */
template <>
void DrawableCharacter::Replay<SaveFrame>(SaveFrame& frame)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8011C32C | size: 0x2C0
 */
template <>
void DrawableCharacter::Replay<LoadFrame>(LoadFrame& frame)
{
}

/**
 * Offset/Address/Size: 0x2D50 | 0x8011BC00 | size: 0x4C
 */
DrawableCharacter::DrawableCharacter()
{
    mVisible = true;

    mPoseTree = nullptr;
    mPoseAccumulator = nullptr;
    mEffectsTexturing = nullptr;
    mCharacter = nullptr;
    mBowser = nullptr;

    mPosition.f.x = 0.0f;
    mPosition.f.y = 0.0f;
    mPosition.f.z = 0.0f;
    mBip01Position.f.x = 0.0f;
    mBip01Position.f.y = 0.0f;
    mBip01Position.f.z = 0.0f;
    mHeadPosition.f.x = 0.0f;
    mHeadPosition.f.y = 0.0f;
    mHeadPosition.f.z = 0.0f;
}

/**
 * Offset/Address/Size: 0x2C6C | 0x8011BB1C | size: 0xE4
 */
DrawableCharacter::~DrawableCharacter()
{
}

/**
 * Offset/Address/Size: 0x2BA4 | 0x8011BA54 | size: 0xC8
 */
void DrawableCharacter::Free()
{
}

/**
 * Offset/Address/Size: 0x2B98 | 0x8011BA48 | size: 0xC
 */
cPN_SAnimController& DrawableCharacter::GetAnimController() const
{
    return *mCharacter->m_pCurrentAnimController;
}

/**
 * Offset/Address/Size: 0x2A1C | 0x8011B8CC | size: 0x17C
 */
void DrawableCharacter::Grab(cCharacter&)
{
}

/**
 * Offset/Address/Size: 0x29F0 | 0x8011B8A0 | size: 0x2C
 */
void DrawableCharacterHeadTrackCallback(unsigned int ctx, unsigned int, cPoseAccumulator* poseAccumulator, unsigned int headNodeIndex, int unused)
{
    DrawableCharacter* pDrawableCharacter = (DrawableCharacter*)ctx;
    CalcHeadTrackMatrix(pDrawableCharacter->mHeadSpin, pDrawableCharacter->mHeadTilt, poseAccumulator, headNodeIndex);
}

/**
 * Offset/Address/Size: 0x290C | 0x8011B7BC | size: 0xE4
 */
void DrawableCharacter::DrawableBowserHeadTrackCallback(unsigned int, unsigned int, cPoseAccumulator*, unsigned int, int)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x27F4 | 0x8011B6A4 | size: 0x118
 */
void DrawableCharacter::BuildNodeMatrices()
{
}

/**
 * Offset/Address/Size: 0x26C4 | 0x8011B574 | size: 0x130
 */
void DrawableCharacter::Render(cCharacter&) const
{
}

/**
 * Offset/Address/Size: 0x22EC | 0x8011B19C | size: 0x3D8
 */
void FindBoundingSphereAccurate(nlVector3*, float*, int, const nlVector3*)
{
}

/**
 * Offset/Address/Size: 0x1AE4 | 0x8011A994 | size: 0x808
 */
void DrawableCharacter::SendToGl(const cCharacter&) const
{
}

// /**
//  * Offset/Address/Size: 0xA6C | 0x8011991C | size: 0x1078
//  */
// void cPoseAccumulator::operator=(const cPoseAccumulator&)
// {
// }

/**
 * Offset/Address/Size: 0x924 | 0x801197D4 | size: 0x148
 */
void DrawableCharacter::Grab(SkinAnimatedMovableNPC& character)
{
    mCharacter = nullptr;

    if (character.GetSkinAnimatedNPC_Type() == SkinAnimatedNPC_BOWSER)
    {
        mBowser = (Bowser*)&character;
    }

    mPosition = character.mv3Position;

    nlMatrix4& nodeMatrix = character.mpPoseAccumulator->GetNodeMatrix(0);
    mHeight = nodeMatrix.f.m43;

    mVelocity.f.x = 0.0f;
    mVelocity.f.y = 0.0f;
    mVelocity.f.z = 0.0f;

    mFacingDirection = character.maFacingDirection;

    float headSpin = character.GetHeadSpin();
    mHeadSpin = (unsigned short)(int)headSpin;

    float headTilt = character.GetHeadTilt();
    mHeadTilt = (unsigned short)(int)headTilt;

    mPoseTree = character.mpPoseTree;
    mVisible = character.mbIsVisible;
    mDirt = false;

    if (mPoseAccumulator == nullptr)
    {
        mPoseAccumulator = (cPoseAccumulator*)new (nlMalloc(0x58, 8, false)) cPoseAccumulator(*character.mpPoseAccumulator);
    }
    else
    {
        // *mPoseAccumulator = *character.mpPoseAccumulator;
    }

    mEffectsTexturing = nullptr;
}

/**
 * Offset/Address/Size: 0x87C | 0x8011972C | size: 0xA8
 */
void DrawableCharacter::Render(SkinAnimatedMovableNPC& character) const
{
    if (!mVisible)
    {
        return;
    }

    nlMatrix4 rotMatrix;
    float angle = 0.0000958738f * (float)mFacingDirection;
    nlMakeRotationMatrixZ(rotMatrix, angle);

    rotMatrix.SetRow_(3, mPosition);

    character.mbIsVisible = mVisible;
    character.RenderFromReplay(*mPoseAccumulator, &rotMatrix);
}

/**
 * Offset/Address/Size: 0x2B8 | 0x80119168 | size: 0x5C4
 */
void DrawableCharacter::Blend(const float*, const DrawableCharacter&, const DrawableCharacter&)
{
}

/**
 * Offset/Address/Size: 0xD8 | 0x80118F88 | size: 0x1E0
 */
void DrawableCharacter::EvaluateFrom(const cPoseNode& poseNode, const nlVector3& position, unsigned short facingDirection)
{
    mPosition = position;

    mVelocity.f.x = 0.0f;
    mVelocity.f.y = 0.0f;
    mVelocity.f.z = 0.0f;

    mFacingDirection = facingDirection;
    mHeadSpin = 0;
    mHeadTilt = 0;
    mHeight = 0.0f;

    mPoseAccumulator->InitAccumulators();

    poseNode.Evaluate(1.0f, mPoseAccumulator);

    mEffectsTexturing = fxGetTexturing(eFXTex_Nothing);

    nlMatrix4 rotMatrix;
    float angle = 0.0000958738f * (float)mFacingDirection;
    nlMakeRotationMatrixZ(rotMatrix, angle);
    rotMatrix.SetRow_(3, mPosition);

    if (mCharacter != nullptr)
    {
        mPoseAccumulator->SetBuildNodeMatrixCallback(mCharacter->m_nHeadJointIndex, DrawableCharacterHeadTrackCallback, (unsigned int)this, 0);
    }
    else
    {
        if (mBowser != nullptr)
        {
            mPoseAccumulator->SetBuildNodeMatrixCallback(mBowser->mnHeadJointIndex, DrawableBowserHeadTrackCallback, (unsigned int)this, 0);
        }
    }

    mPoseAccumulator->BuildNodeMatrices(rotMatrix);

    if (mCharacter != nullptr)
    {
        mPoseAccumulator->SetBuildNodeMatrixCallback(
            mCharacter->m_nHeadJointIndex,
            nullptr,
            0,
            0);
    }
    else if (mBowser != nullptr)
    {
        mPoseAccumulator->SetBuildNodeMatrixCallback(
            mBowser->mnHeadJointIndex,
            nullptr,
            0,
            0);
    }

    nlMatrix4& bip01Matrix = mPoseAccumulator->GetNodeMatrix(mCharacter->m_nBip01JointIndex_0xA4);
    mBip01Position = bip01Matrix.GetTranslation();

    nlMatrix4& headMatrix = mPoseAccumulator->GetNodeMatrix(mCharacter->m_nHeadJointIndex);
    mHeadPosition = headMatrix.GetTranslation();
}

/**
 * Offset/Address/Size: 0x88 | 0x80118F38 | size: 0x50
 */
nlVector3 DrawableCharacter::GetBallPosition() const
{
    cPlayer* pPlayer = (cPlayer*)mCharacter;
    nlMatrix4& matrix = mPoseAccumulator->GetNodeMatrix(pPlayer->m_nBallJointIndex);
    return matrix.GetTranslation();
}

/**
 * Offset/Address/Size: 0x24 | 0x80118ED4 | size: 0x64
 */
nlQuaternion DrawableCharacter::GetBallOrientation() const
{
    nlQuaternion quat;
    nlMatrixToQuat(quat, mPoseAccumulator->GetNodeMatrix(((cPlayer*)mCharacter)->m_nBallJointIndex));
    return quat;
}

/**
 * Offset/Address/Size: 0x18 | 0x80118EC8 | size: 0xC
 */
void DrawableCharacter::RenderOnlyOneCharacter(const cCharacter& character, bool renderOpposingGoalieToo)
{
    spRenderOnlyThisCharacter = (cCharacter*)&character;
    sbRenderOpposingGoalieToo = renderOpposingGoalieToo;
}

/**
 * Offset/Address/Size: 0x8 | 0x80118EB8 | size: 0x10
 */
void DrawableCharacter::RenderAllCharacters()
{
    spRenderOnlyThisCharacter = nullptr;
    sbRenderOpposingGoalieToo = false;
}

/**
 * Offset/Address/Size: 0x0 | 0x80118EB0 | size: 0x8
 */
cCharacter* DrawableCharacter::OnlyRenderingOneCharacter()
{
    return spRenderOnlyThisCharacter;
}

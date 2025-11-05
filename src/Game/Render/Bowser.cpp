#include "Game/Render/Bowser.h"
#include "Game/AI/HeadTrack.h"
#include "Game/AI/Powerups.h"
#include "Game/AI/Fielder.h"
#include "Game/Ball.h"
#include "Game/Sys/eventman.h"
#include "Game/ReplayManager.h"
#include "NL/nlString.h"
#include "Game/PoseAccumulator.h"
#include "Game/Camera/CameraMan.h"
#include "Game/Game.h"
#include "Game/Audio/AudioLoader.h"
// #include "Game/SoundProps/bowsergensoundproperties.h"
#include "math.h"

SoundPropAccessor* gpBOWSERSoundPropAccessor;

float Bowser::mfYAxisTilt = 0.0f;

/**
 * Offset/Address/Size: 0x4BBC | 0x8015D930 | size: 0x2C
 */
void AnimSoundCallback(unsigned int eventID)
{
    g_pEventManager->CreateValidEvent(eventID, 0x14);
}

/**
 * Offset/Address/Size: 0x4638 | 0x8015D3AC | size: 0x584
 */
Bowser::Bowser(cSHierarchy& pHierarchy, int nModelID, PhysicsNPC& mpPhysObj, cInventory<cSAnim>* pInventorySAnim)
    : SkinAnimatedMovableNPC(pHierarchy, nModelID, mpPhysObj)
{
}

/**
 * Offset/Address/Size: 0x44F0 | 0x8015D264 | size: 0x148
 */
Bowser::~Bowser()
{
}

/**
 * Offset/Address/Size: 0x325C | 0x8015BFD0 | size: 0x1294
 */
void Bowser::Update(float)
{
}

/**
 * Offset/Address/Size: 0x3054 | 0x8015BDC8 | size: 0x208
 */
void Bowser::CollisionCallback(PhysicsObject*, PhysicsObject*, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x2B64 | 0x8015B8D8 | size: 0x4F0
 */
void Bowser::ActionInit()
{
}

/**
 * Offset/Address/Size: 0x28A4 | 0x8015B618 | size: 0x2C0
 */
void Bowser::ActionThrow()
{
}

/**
 * Offset/Address/Size: 0x26DC | 0x8015B450 | size: 0x1C8
 */
void Bowser::ActionRoll()
{
}

/**
 * Offset/Address/Size: 0x24B4 | 0x8015B228 | size: 0x228
 */
void Bowser::ActionStomp()
{
}

/**
 * Offset/Address/Size: 0x2314 | 0x8015B088 | size: 0x1A0
 */
void Bowser::ActionDescend(float)
{
}

/**
 * Offset/Address/Size: 0x2080 | 0x8015ADF4 | size: 0x294
 */
void Bowser::ActionFall()
{
}

/**
 * Offset/Address/Size: 0x1CE4 | 0x8015AA58 | size: 0x39C
 */
void Bowser::ActionJump()
{
}

/**
 * Offset/Address/Size: 0x1A90 | 0x8015A804 | size: 0x254
 */
void Bowser::ActionHide()
{
}

/**
 * Offset/Address/Size: 0x177C | 0x8015A4F0 | size: 0x314
 */
void Bowser::ActionReset()
{
}

/**
 * Offset/Address/Size: 0x1534 | 0x8015A2A8 | size: 0x248
 */
void Bowser::ActionLeave()
{
}

/**
 * Offset/Address/Size: 0x1384 | 0x8015A0F8 | size: 0x1B0
 */
void Bowser::Move(float)
{
}

/**
 * Offset/Address/Size: 0x1114 | 0x80159E88 | size: 0x270
 */
void Bowser::ActionIdle()
{
}

/**
 * Offset/Address/Size: 0x1044 | 0x80159DB8 | size: 0xD0
 */
void Bowser::SetTiltParameters(float fYAxisTilt)
{
    mfYAxisTilt = fYAxisTilt;
    cCameraManager::SetWorldUpVectorTilt(0.0f, fYAxisTilt);

    if ((g_pBall != NULL) && (g_pBall->m_pPhysicsBall != NULL))
    {
        if ((float)fabs(fYAxisTilt) > 0.01f)
        {
            nlVector3 tiltForce = { 0.0f, 0.0f, 0.0f };
            tiltForce.f.x = -fYAxisTilt * g_pGame->m_pGameTweaks->unk338;

            g_pBall->m_pPhysicsBall->m_v3TiltForce = tiltForce;
            g_pBall->m_pPhysicsBall->m_bUseTiltForce = true;
            return;
        }
        g_pBall->m_pPhysicsBall->m_bUseTiltForce = false;
    }
}

/**
 * Offset/Address/Size: 0x954 | 0x801596C8 | size: 0x6F0
 */
void Bowser::CheckForAbort()
{
}

/**
 * Offset/Address/Size: 0x888 | 0x801595FC | size: 0xCC
 */
void Bowser::UpdateFireEmitter(EmissionController& controller)
{
    if (ReplayManager::Instance()->mRender != nullptr)
    {
        RenderSnapshot* pRenderSnapshot = ReplayManager::Instance()->mRender;
        cPoseAccumulator* pPoseAccumulator = pRenderSnapshot->mBowser.mPoseAccumulator;

        controller.SetPosition(pRenderSnapshot->mBowser.mPosition);
        controller.SetVelocity(pRenderSnapshot->mBowser.mVelocity);
        controller.SetPoseAccumulator(*pPoseAccumulator);

        static unsigned int HeadJointID = nlStringHash("bip01 head");

        nlMatrix4& headMatrix = pPoseAccumulator->GetNodeMatrixByHashID(HeadJointID);
        nlVector3 direction;
        // = headMatrix.GetTranslation();
        nlVec3Set(direction, headMatrix.f.m21, headMatrix.f.m22, headMatrix.f.m23);
        // direction.f.x = headMatrix.f.m21; // row 1, column 0
        // direction.f.y = headMatrix.f.m22; // row 1, column 1
        // direction.f.z = headMatrix.f.m23; // row 1, column 2
        controller.SetDirection(direction);
    }
}

/**
 * Offset/Address/Size: 0x810 | 0x80159584 | size: 0x78
 */
void Bowser::UpdateBowserLandEmitter(EmissionController& controller)
{
    if (ReplayManager::Instance()->mRender != nullptr)
    {
        RenderSnapshot* pRenderSnapshot = ReplayManager::Instance()->mRender;
        cPoseAccumulator* pPoseAccumulator = pRenderSnapshot->mBowser.mPoseAccumulator;

        controller.SetPosition(pRenderSnapshot->mBowser.mPosition);
        controller.SetVelocity(pRenderSnapshot->mBowser.mVelocity);
        controller.SetPoseAccumulator(*pPoseAccumulator);
    }
}

/**
 * Offset/Address/Size: 0x7A4 | 0x80159518 | size: 0x6C
 */
void Bowser::FindTarget()
{
    if (g_pBall->GetOwnerFielder() != NULL && !g_pBall->GetOwnerFielder()->IsInvincible())
    {
        mpTarget = g_pBall->GetOwnerFielder(); // at 0x0EC
    }
    else
    {
        mpTarget = FindPowerupTarget((cFielder*)NULL, this);
    }
}

/**
 * Offset/Address/Size: 0x334 | 0x801590A8 | size: 0x470
 */
void Bowser::SetupBaseSFX()
{
    if (!AudioLoader::IsInited())
    {
        return;
    }

    m_pCharacterSFX->Init();
    m_pCharacterSFX->mGroup = 8;
    m_pCharacterSFX->mpPhysObj = (PhysicsObject*)mpPhysObj;
    m_pCharacterSFX->SetSFX(gpBOWSERSoundPropAccessor);
    AudioLoader::SetupBowserStadiumSoundTable(this);

    // temp_r3_3 = this->unkD4;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_3, 8.2f / temp_r3_3->unk8, 0x5A, AnimSoundCallback);
    // temp_r3_4 = this->unkD4;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_4, 18.3f / temp_r3_4->unk8, 0x5F, AnimSoundCallback);
    // temp_r3_5 = this->unkD4;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_5, 18.3f / temp_r3_5->unk8, 0x5F, AnimSoundCallback);
    // temp_r3_6 = this->unkD4;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_6, 25.0f / temp_r3_6->unk8, 0x60, AnimSoundCallback);
    // temp_r3_7 = this->unkDC;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_7, 3.0f / temp_r3_7->unk8, 0x5F, AnimSoundCallback);
    // temp_r3_8 = this->unkDC;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_8, 25.5f / temp_r3_8->unk8, 0x5F, AnimSoundCallback);
    // temp_r3_9 = this->unkD8;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_9, 8.0f / temp_r3_9->unk8, 0x5B, AnimSoundCallback);
    // temp_r3_10 = this->unkD8;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_10, 16.0f / temp_r3_10->unk8, 0x5C, AnimSoundCallback);
    // temp_r3_11 = this->unkE4;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_11, 13.0f / temp_r3_11->unk8, 0x60, AnimSoundCallback);
    // temp_r3_12 = this->unkE8;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_12, 3.0f / temp_r3_12->unk8, 0x5B, AnimSoundCallback);
    // temp_r3_13 = this->unkE8;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_13, 13.0f / temp_r3_13->unk8, 0x5D, AnimSoundCallback);
    // temp_r3_14 = this->unkE8;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_14, 22.7f / temp_r3_14->unk8, 0x5F, AnimSoundCallback);
    // temp_r3_15 = this->unkE8;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_15, 22.7f / temp_r3_15->unk8, 0x5F, AnimSoundCallback);
    // temp_r3_16 = this->unkE8;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_16, 32.0f / temp_r3_16->unk8, 0x5F, AnimSoundCallback);
    // temp_r3_17 = this->unkE8;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_17, 32.8f / temp_r3_17->unk8, 0x5F, AnimSoundCallback);
    // temp_r3_18 = this->unkE0;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_18, 15.7f / temp_r3_18->unk8, 0x5F, AnimSoundCallback);
    // temp_r3_19 = this->unkE0;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_19, 20.0f / temp_r3_19->unk8, 0x63, AnimSoundCallback);
    // temp_r3_20 = this->unkE0;
    // CreateCallback__6cSAnimFfUiPFUi_v(temp_r3_20, 39.0f / temp_r3_20->unk8, 0x5F, AnimSoundCallback);

    // float numKeys = (float)mpAnim[1]->m_nNumKeys;
    // mpAnim[1]->CreateCallback(90.0f / numKeys, 0x5A, AnimSoundCallback);
    // mpAnim[1]->CreateCallback(95.0f / numKeys, 0x5F, AnimSoundCallback);
    // mpAnim[1]->CreateCallback(95.0f / numKeys, 0x5F, AnimSoundCallback);
    // mpAnim[1]->CreateCallback(96.0f / numKeys, 0x60, AnimSoundCallback);

    // numKeys = (float)mpAnim[3]->m_nNumKeys;
    // mpAnim[3]->CreateCallback(30.0f / numKeys, 0x5F, AnimSoundCallback);
    // mpAnim[3]->CreateCallback(96.0f / numKeys, 0x5F, AnimSoundCallback);

    // numKeys = (float)mpAnim[2]->m_nNumKeys;
    // mpAnim[2]->CreateCallback(91.0f / numKeys, 0x5B, AnimSoundCallback);
    // mpAnim[2]->CreateCallback(92.0f / numKeys, 0x5C, AnimSoundCallback);

    // numKeys = (float)mpAnim[5]->m_nNumKeys;
    // mpAnim[5]->CreateCallback(100.0f / numKeys, 0x60, AnimSoundCallback);

    // numKeys = (float)mpAnim[6]->m_nNumKeys;
    // mpAnim[6]->CreateCallback(30.0f / numKeys, 0x5B, AnimSoundCallback);
    // mpAnim[6]->CreateCallback(100.0f / numKeys, 0x5D, AnimSoundCallback);
    // mpAnim[6]->CreateCallback(104.0f / numKeys, 0x5F, AnimSoundCallback);
    // mpAnim[6]->CreateCallback(104.0f / numKeys, 0x5F, AnimSoundCallback);
    // mpAnim[6]->CreateCallback(108.0f / numKeys, 0x5F, AnimSoundCallback);
    // mpAnim[6]->CreateCallback(108.0f / numKeys, 0x5F, AnimSoundCallback);

    // numKeys = (float)mpAnim[4]->m_nNumKeys;
    // mpAnim[4]->CreateCallback(95.0f / numKeys, 0x5F, AnimSoundCallback);
    // mpAnim[4]->CreateCallback(99.0f / numKeys, 0x63, AnimSoundCallback);
    // mpAnim[4]->CreateCallback(100.0f / numKeys, 0x5F, AnimSoundCallback);
}

/**
 * Offset/Address/Size: 0x290 | 0x80159004 | size: 0xA4
 */
void Bowser::PlaySFX(Audio::eCharSFX type, PosUpdateMethod posUpdateMethod, float fDelay, bool bIs3D)
{
    Audio::SoundAttributes attrs;
    attrs.Init();
    attrs.SetSoundType(type, bIs3D);
    attrs.mf_DelayTime = fDelay;
    attrs.posUpdateMethod = posUpdateMethod;

    if (posUpdateMethod == VECTORS)
    {
        attrs.UseStationaryPosVector(mv3Position);
    }

    m_pCharacterSFX->Play(attrs);
}

/**
 * Offset/Address/Size: 0x9C | 0x80158E10 | size: 0x1F4
 */
void Bowser::CheckFootSteps()
{
}

/**
 * Offset/Address/Size: 0x60 | 0x80158DD4 | size: 0x3C
 */
float Bowser::GetHeadSpin() const
{
    return (float)(unsigned short)(int)this->mpHeadTrack->m_fHeadSpin;
}

/**
 * Offset/Address/Size: 0x24 | 0x80158D98 | size: 0x3C
 */
float Bowser::GetHeadTilt() const
{
    return (float)(unsigned short)(int)this->mpHeadTrack->m_fHeadTilt;
}

/**
 * Offset/Address/Size: 0x0 | 0x80158D74 | size: 0x24
 */
void Bowser::DrawShadow(const cPoseAccumulator& poseAccumulator, const nlMatrix4& matrix)
{
    SkinAnimatedNPC::DrawShadow(mpLastModel, matrix);
}

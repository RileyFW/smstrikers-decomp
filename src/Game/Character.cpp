#include "Game/Character.h"
#include "Game/CharacterTemplate.h"
#include "Game/Effects/EmissionManager.h"

#include "NL/nlString.h"

#include "NL/gl/glState.h"
#include "NL/gl/glTexture.h"

#include "Game/Team.h"
#include "Game/AI/Fielder.h"
#include "Game/AnimInventory.h"
#include "Game/SAnim/pnBlender.h"
#include "Game/SAnim/AnimRetargeter.h"
#include "NL/nlSlotPool.h"

#include "Game/Ball.h"
#include "Game/Sys/audio.h"
#include "types.h"

static f32 CANT_COLLIDE = *(f32*)__float_max;

static const nlVector3 v3Zero = { 0.0f, 0.0f, 0.0f };
static const char szMushroomBlurTextureBase[23] = "global/mushroomstreak_";
static const char szMushroomBlurTexture[22] = "global/mushroomstreak";

extern unsigned int nlDefaultSeed;
static bool sbElectricFenceDebug = false;

eCharacterModelType cCharacter::m_ModelType = CharModel_Rigid;

nlVector3 g_v3PrevJointPosition = { 0.0f, 0.0f, 0.0f };

/**
 * Offset/Address/Size: 0x0 | 0x8000DF4C | size: 0x88
 */
void cCharacter::AddRandomDirt()
{
    m_MinDirt += nlRandomf(0.05f, &nlDefaultSeed);
    if (m_MinDirt > 0.2f)
    {
        m_MinDirt = 0.2f;
    }

    m_Dirt += 0.5f + nlRandomf(0.39999998f, &nlDefaultSeed);
    if (m_Dirt > 1.0f)
    {
        m_Dirt = 1.0f;
    }
}

/**
 * Offset/Address/Size: 0x88 | 0x8000DFD4 | size: 0x74
 */
void cCharacter::SetElectrocutionTextureEnabled(bool arg0)
{
    if ((m_bIsUsingElectrocutionTexture == false) && (arg0 != false))
    {
        m_pEffectsTexturing = fxGetTexturing((eEffectsTextureType)4);
    }

    if ((m_bIsUsingElectrocutionTexture != false) && (arg0 == false))
    {
        m_pEffectsTexturing = 0;
    }

    m_bIsUsingElectrocutionTexture = arg0;
}

/**
 * Offset/Address/Size: 0xFC | 0x8000E048 | size: 0x30
 */
void cCharacter::PerformBlinking(GLSkinMesh* skinMesh, glModel* model) const
{
    Blinker* temp_r3 = m_pBlinker;
    if (temp_r3 != NULL)
    {
        temp_r3->Blink(model);
    }
}

/**
 * Offset/Address/Size: 0x12C | 0x8000E078 | size: 0x2C
 */
void cCharacter::UpdateBlinking(float fDeltaT)
{
    Blinker* temp_r3 = m_pBlinker;
    if (temp_r3 != NULL)
    {
        temp_r3->Update(fDeltaT);
    }
}

/**
 * Offset/Address/Size: 0x158 | 0x8000E0A4 | size: 0x80
 */
void cCharacter::PlayRandomCharDialogue(unsigned long dialogueType, PosUpdateMethod posUpdateMethod, float f1, float f2)
{
    if (Audio::IsInited())
    {
        m_pCharacterSFX->PlayRandomCharDialogue((CharDialogueType)dialogueType, posUpdateMethod, f1, f2, true);
    }
}

/**
 * Offset/Address/Size: 0x1D8 | 0x8000E124 | size: 0xD0
 */
int cCharacter::Play3DSFX(Audio::eCharSFX sfxType, PosUpdateMethod posUpdateMethod, float fMaxVol)
{
    if (!Audio::IsInited())
    {
        return -1;
    }

    Audio::SoundAttributes attributes;
    attributes.Init();

    attributes.me_ClassType = 1; // CHAR
    attributes.mu_Type = sfxType;
    attributes.mb_Is3D = true;
    attributes.mf_Volume = fMaxVol;
    attributes.mf_Attenuate = 1.0f;
    attributes.posUpdateMethod = posUpdateMethod;

    if (posUpdateMethod == VECTORS)
    {
        attributes.UseStationaryPosVector(m_v3Position);
    }

    return (Audio::IsInited() ? m_pCharacterSFX->Play(attributes) : -1);
}

/**
 * Offset/Address/Size: 0x2A8 | 0x8000E1F4 | size: 0x3C
 */
void cCharacter::StopPlayingAllTrackedSFX()
{
    if (Audio::IsInited())
    {
        m_pCharacterSFX->StopPlayingAllTrackedSFX();
    }
}

/**
 * Offset/Address/Size: 0x2E4 | 0x8000E230 | size: 0x50
 */
void cCharacter::StopSFX(Audio::eCharSFX sfxType)
{
    if (Audio::IsInited())
    {
        m_pCharacterSFX->Stop(sfxType, cGameSFX::SFX_STOP_FIRST);
    }
}

/**
 * Offset/Address/Size: 0x334 | 0x8000E280 | size: 0x60
 */
// void cCharacter::PlaySFX(Audio::SoundAttributes&)
int cCharacter::PlaySFX(Audio::SoundAttributes& attributes)
{
    if (Audio::IsInited())
    {
        return m_pCharacterSFX->Play(attributes);
    }
    return -1;
}

/**
 * Offset/Address/Size: 0x394 | 0x8000E2E0 | size: 0x78
 */
void cCharacter::SetSFX(SoundPropAccessor* pSoundPropAccessor)
{
    if (Audio::IsInited())
    {
        m_pCharacterSFX->Init();
        m_pCharacterSFX->mpPhysObj = m_pPhysicsCharacter;
        m_pCharacterSFX->SetSFX(pSoundPropAccessor);
    }
}

/**
 * Offset/Address/Size: 0x40C | 0x8000E358 | size: 0x650
 */
void cCharacter::UpdateMovementState(float)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0xA5C | 0x8000E9A8 | size: 0x34
 */
bool cCharacter::IsPlayingEffect(const EffectsGroup* effectGroup) const
{
    u32 characterIndex = GetCharacterIndex(this);
    return EmissionManager::IsPlaying(characterIndex, effectGroup);
}

/**
 * Offset/Address/Size: 0xA90 | 0x8000E9DC | size: 0x34
 */
void cCharacter::EndEffect(const EffectsGroup* effectGroup)
{
    u32 characterIndex = GetCharacterIndex(this);
    EmissionManager::Kill(characterIndex, effectGroup);
}

/**
 * Offset/Address/Size: 0xAC4 | 0x8000EA10 | size: 0x34
 */
void cCharacter::KillEffect(const EffectsGroup* effectGroup)
{
    u32 characterIndex = GetCharacterIndex(this);
    EmissionManager::Destroy(characterIndex, effectGroup);
}

/**
 * Offset/Address/Size: 0xAF8 | 0x8000EA44 | size: 0x1FC
 */
void cCharacter::Update(float fDeltaT)
{
    m_pPoseTree = m_pPoseTree->Update(fDeltaT);
    UpdateMovementState(fDeltaT);

    if (m_bIsUsingElectrocutionTexture)
    {
        if (!EmissionManager::IsPlaying(GetCharacterIndex(this), fxGetGroup("electric_fence_character")))
        {
            if (m_bIsUsingElectrocutionTexture)
            {
                m_pEffectsTexturing = nullptr;
            }
            m_bIsUsingElectrocutionTexture = false;
        }
    }

    m_Dirt = -((0.013333334f * fDeltaT) - m_Dirt);
    if (m_Dirt < m_MinDirt)
    {
        m_Dirt = m_MinDirt;
    }

    if (m_pBlurHandler != nullptr)
    {
        bool bIsZero = (v3Zero.f.x == g_v3PrevJointPosition.f.x && v3Zero.f.y == g_v3PrevJointPosition.f.y && v3Zero.f.z == g_v3PrevJointPosition.f.z);

        if (bIsZero)
        {
            g_v3PrevJointPosition = m_v3Position;
        }

        nlVector3 jointPosition;
        nlVector3 forwardVector;

        if (m_eClassType == FIELDER)
        {
            cSHierarchy* hierarchy = m_pPoseAccumulator->m_BaseSHierarchy;
            const nlMatrix4& nodeMatrix = m_pPoseAccumulator->GetNodeMatrix(hierarchy->GetNodeIndexByID(nlStringLowerHash("bip01 spine1")));
            jointPosition = *(nlVector3*)&nodeMatrix.m[3][0];

            nlVec3Set(forwardVector, m_v3Position.f.x - m_v3PrevPosition.f.x, m_v3Position.f.y - m_v3PrevPosition.f.y, m_v3Position.f.z - m_v3PrevPosition.f.z);
        }
        // what happens here, if m_eClassType != FIELDER? ...

        g_v3PrevJointPosition = jointPosition;
        m_pBlurHandler->AddViewOrientedPoint(jointPosition, forwardVector);
    }
}

/**
 * Offset/Address/Size: 0xCF4 | 0x8000EC40 | size: 0x84
 */
bool cCharacter::ShouldStartCrossBlend(int animID)
{
    float time;
    float threshold = 0.5f * m_pAnimInventory->GetBlendTime(animID);

    time = m_pCurrentAnimController->m_fTime;
    time = 1.0f - time;

    float remaining = time * ((float)(m_pCurrentAnimController->m_pSAnim->m_nNumKeys) / 30.0f);

    return (remaining <= threshold);
}

/**
 * Offset/Address/Size: 0xD78 | 0x8000ECC4 | size: 0x40
 */
void cCharacter::SetVelocity(const nlVector3& velocity)
{
    m_v3Velocity = velocity;
    m_pPhysicsCharacter->SetCharacterVelocityXY(m_v3Velocity);
}

/**
 * Offset/Address/Size: 0xDB8 | 0x8000ED04 | size: 0x58
 */
void cCharacter::SetPosition(const nlVector3& position)
{
    m_v3Position = position;
    m_v3PrevPosition = m_v3Position;
    m_pPhysicsCharacter->SetCharacterPositionXY(m_v3Position);
}

/**
 * Offset/Address/Size: 0xE10 | 0x8000ED5C | size: 0x30
 */
void cCharacter::SetFacingDirection(unsigned short dir)
{
    m_aPrevFacingDirection = m_aActualFacingDirection;
    m_aActualFacingDirection = dir;
    m_pPhysicsCharacter->SetFacingDirection(dir);
}

/**
 * Offset/Address/Size: 0xE40 | 0x8000ED8C | size: 0x148
 */
void cCharacter::SetAnimState(int animID, bool useBlendTime, float fNonDefaultBlendTime, bool bRestartCyclic, bool bForceMirrorSwap)
{
    float finalBlendTime;
    cPN_SAnimController* newController;
    cPN_Blender* blender;
    cPoseNode* oldController;

    if (useBlendTime)
    {
        finalBlendTime = m_pAnimInventory->GetBlendTime(animID);
    }
    else
    {
        finalBlendTime = fNonDefaultBlendTime;
    }

    newController = NewAnimController(animID, bRestartCyclic, bForceMirrorSwap, nullptr, 0);
    oldController = m_pAILayer[0];

    if (oldController != nullptr && finalBlendTime != 0.0f)
    {
        blender = new (AllocateBlender()) cPN_Blender(oldController, newController, finalBlendTime);
    }
    else
    {
        delete oldController;
        blender = nullptr;
    }

    m_pAILayer[0] = blender;
    m_pCurrentAnimController = newController;

    SetAnimID(animID);
}

/**
 * Offset/Address/Size: 0xF88 | 0x8000EED4 | size: 0x8
 */
void cCharacter::SetAnimID(int animID)
{
    m_eAnimID = animID;
}

/**
 * Offset/Address/Size: 0xF90 | 0x8000EEDC | size: 0x50
 */
float cCharacter::SeekSpeedExponential(float currentValue, float targetValue, float responsiveness, float deltaTime)
{
    float adjustment;
    float distance;
    float difference;

    difference = targetValue - currentValue;
    distance = fabs(difference);

    if (distance > 0.1f)
    {
        adjustment = distance - (1.0f / ((responsiveness * deltaTime) + (1.0f / distance)));
        if (difference > 0.0f)
        {
            return currentValue + adjustment;
        }
        return currentValue - adjustment;
    }

    return targetValue;
}

/**
 * Offset/Address/Size: 0xFE0 | 0x8000EF2C | size: 0x3C
 */
void cCharacter::ResetEffects()
{
    u32 characterIndex = GetCharacterIndex(this);
    EmissionManager::Destroy(characterIndex, nullptr);
    m_pEffectsTexturing = 0;
}

/**
 * Offset/Address/Size: 0x101C | 0x8000EF68 | size: 0xF0
 */
void cCharacter::PostPhysicsUpdate()
{
    m_v3PrevPosition = m_v3Position;
    m_pPhysicsCharacter->GetCharacterPositionXY(&m_v3Position);
    m_pPhysicsCharacter->GetCharacterVelocityXY(&m_v3Velocity);

    m_fActualSpeed = nlGetLength2D(m_v3Velocity.f.x, m_v3Velocity.f.y);

    float angleRad = 0.0000958738f * (float)m_aActualFacingDirection;
    nlMakeRotationMatrixZ(m_m4WorldMatrix, angleRad);

    m_m4WorldMatrix.m[3][0] = m_v3Position.f.x;
    m_m4WorldMatrix.m[3][1] = m_v3Position.f.y;
    m_m4WorldMatrix.m[3][2] = m_v3Position.f.z;

    if (m_eClassType != GOALIE || ((m_v3Position.f.x * g_pBall->m_v3Position.f.x) > 0.0f))
    {
        m_pPoseAccumulator->MultNodeMatrices(&m_m4WorldMatrix);
    }
}

/**
 * Offset/Address/Size: 0x110C | 0x8000F058 | size: 0x6C
 */
void cCharacter::CreateWorldMatrix()
{
    nlMakeRotationMatrixZ(m_m4WorldMatrix, 0.0000958738f * (f32)m_aActualFacingDirection);
    m_m4WorldMatrix.m[3][0] = m_v3Position.f.x;
    m_m4WorldMatrix.m[3][1] = m_v3Position.f.y;
    m_m4WorldMatrix.m[3][2] = m_v3Position.f.z;
}

/**
 * Offset/Address/Size: 0x1178 | 0x8000F0C4 | size: 0x4
 */
void cCharacter::PreUpdate(float)
{
}

/**
 * Offset/Address/Size: 0x117C | 0x8000F0C8 | size: 0x68
 */
void cCharacter::PrePhysicsUpdate(float)
{
    if ((m_eClassType != GOALIE) || ((m_v3Position.f.x * g_pBall->m_v3Position.f.x) > 0.0f))
    {
        nlMatrix4 identityMatrix;
        identityMatrix.SetIdentity();
        m_pPoseAccumulator->Pose(*m_pPoseTree, identityMatrix);
    }
}

/**
 * Offset/Address/Size: 0x11E4 | 0x8000F130 | size: 0x4C
 */
void cCharacter::PoseSkinMesh(cPoseAccumulator* pPoseAccumulator)
{
    GLSkinMesh* skinMesh = m_pSkinMesh[m_ModelType];
    if (skinMesh == nullptr)
    {
        skinMesh = m_pSkinMesh[0];
    }
    skinMesh->Pose(pPoseAccumulator);
}

/**
 * Offset/Address/Size: 0x1230 | 0x8000F17C | size: 0x40
 */
void cCharacter::PoseLocalSpace()
{
    nlMatrix4 identityMatrix;
    identityMatrix.SetIdentity();
    m_pPoseAccumulator->Pose(*m_pPoseTree, identityMatrix);
}

/**
 * Offset/Address/Size: 0x1270 | 0x8000F1BC | size: 0x33C
 */
cPN_SAnimController* cCharacter::NewAnimController(int animID, bool bRestartCyclic, bool bForceMirrorSwap, void (*funcPlaybackSpeedCallback)(unsigned int, cPN_SAnimController*), unsigned int nPlaybackSpeedCallbackParam)
{
    FORCE_DONT_INLINE;
    return nullptr;
}

inline float ClampMin(float speedRatio, const float min)
{
    if (speedRatio >= min)
    {
        return speedRatio;
    }
    return min;
}

inline float ClampMax(float speedRatio, const float max)
{
    if (speedRatio <= max)
    {
        return speedRatio;
    }
    return max;
}

/**
 * Offset/Address/Size: 0x15AC | 0x8000F4F8 | size: 0xD4
 */
void cCharacter::MatchAnimSpeedToCharacterSpeed(unsigned int nParam, cPN_SAnimController* pController)
{
    cFielder* fielder = (cFielder*)nParam;
    if (fielder->m_eMovementState != MOVEMENT_FROM_ANIM && fielder->m_eMovementState != MOVEMENT_FROM_ANIM_SEEK)
    {
        if (fielder->m_eClassType == FIELDER)
        {
            if (fielder->m_eAnimID == 0x1a && fielder->m_eActionState == ACTION_RUNNING_WB_TURBO)
            {
                pController->m_fPlaybackSpeedScale = 2.0f;
                return;
            }

            pController->m_fPlaybackSpeedScale = ClampMax(ClampMin(fielder->m_fActualSpeed / pController->m_pSAnim->m_fLinearSpeed, 0.6f), 1.4f);
            return;
        }

        pController->m_fPlaybackSpeedScale = ClampMax(ClampMin(fielder->m_fActualSpeed / pController->m_pSAnim->m_fLinearSpeed, 0.6f), 1.4f);
    }
}

/**
 * Offset/Address/Size: 0x1680 | 0x8000F5CC | size: 0x1C
 */
void cCharacter::InitMovementStrafing(float fDirectionSeekSpeed, float fDirectionSeekFalloff, float fAccel, float fDecel)
{
    m_eMovementState = MOVEMENT_STRAFING;
    m_fDirectionSeekSpeed = fDirectionSeekSpeed;
    m_fDirectionSeekFalloff = fDirectionSeekFalloff;
    m_fAccel = fAccel;
    m_fDecel = fDecel;
}

/**
 * Offset/Address/Size: 0x169C | 0x8000F5E8 | size: 0x14
 */
void cCharacter::InitMovementRunningNoTurn(float fAccel, float fDecel)
{
    m_eMovementState = MOVEMENT_RUNNING_NO_TURN;
    m_fAccel = fAccel;
    m_fDecel = fDecel;
}

/**
 * Offset/Address/Size: 0x16B0 | 0x8000F5FC | size: 0x1C
 */
void cCharacter::InitMovementRunning(float fDirectionSeekSpeed, float fDirectionSeekFalloff, float fAccel, float fDecel)
{
    m_eMovementState = MOVEMENT_RUNNING;
    m_fDirectionSeekSpeed = fDirectionSeekSpeed;
    m_fDirectionSeekFalloff = fDirectionSeekFalloff;
    m_fAccel = fAccel;
    m_fDecel = fDecel;
}

/**
 * Offset/Address/Size: 0x16CC | 0x8000F618 | size: 0x14
 */
void cCharacter::InitMovementNone(float fDirectionSeekSpeed, float fDirectionSeekFalloff)
{
    m_eMovementState = MOVEMENT_NONE;
    m_fDirectionSeekSpeed = fDirectionSeekSpeed;
    m_fDirectionSeekFalloff = fDirectionSeekFalloff;
}

/**
 * Offset/Address/Size: 0x16E0 | 0x8000F62C | size: 0x14
 */
void cCharacter::InitMovementFromAnimSeek(float fDirectionSeekSpeed, float fDirectionSeekFalloff)
{
    m_eMovementState = MOVEMENT_FROM_ANIM_SEEK;
    m_fDirectionSeekSpeed = fDirectionSeekSpeed;
    m_fDirectionSeekFalloff = fDirectionSeekFalloff;
}

/**
 * Offset/Address/Size: 0x16F4 | 0x8000F640 | size: 0x3C
 */
void cCharacter::InitMovementFromAnim(short fDirectionSeekSpeed, const nlVector3& v3AnimMoveAdjust, float fAdjustEndTime, bool bBlended)
{
    m_eMovementState = MOVEMENT_FROM_ANIM;
    m_nAnimTurnAdjust = fDirectionSeekSpeed;
    m_v3AnimMoveAdjust = v3AnimMoveAdjust;
    m_fAnimAdjustBeginTime = m_pCurrentAnimController->m_fTime;
    m_fAnimAdjustEndTime = fAdjustEndTime;
    m_bFromAnimBlended = bBlended;
}

/**
 * Offset/Address/Size: 0x1730 | 0x8000F67C | size: 0x10
 */
void cCharacter::InitMovementDecelerateExponential(float fDecel)
{
    m_eMovementState = MOVEMENT_DECELERATE_EXPONENTIAL;
    m_fDecel = fDecel;
}

/**
 * Offset/Address/Size: 0x1740 | 0x8000F68C | size: 0xC
 */
void cCharacter::InitMovementCoast()
{
    m_eMovementState = MOVEMENT_COAST;
}

/**
 * Offset/Address/Size: 0x174C | 0x8000F698 | size: 0x44
 */
void cCharacter::EndBlur()
{
    if (m_pBlurHandler != NULL)
    {
        m_pBlurHandler->Die(0.0f);
        m_pBlurHandler = NULL;
    }
}

/**
 * Offset/Address/Size: 0x1790 | 0x8000F6DC | size: 0xBC
 */
void cCharacter::InitBlur(int nLength)
{
    char texturename[64];
    s32 maxEntries = nLength;

    if (m_pBlurHandler != NULL)
    {
        BlurManager::DestroyHandler(m_pBlurHandler, 0.15f);
        m_pBlurHandler = NULL;
    }

    if (maxEntries == 0)
    {
        maxEntries = 30;
    }

    if (m_eClassType == FIELDER)
    {
        nlStrNCat<char>(texturename, szMushroomBlurTextureBase, ((cPlayer*)this)->m_pTeam->GetCaptain()->m_szEffectsName, 0x40);
    }

    const char* finalTextureName;
    if (glTextureLoad(glGetTexture(texturename)))
    {
        finalTextureName = texturename;
    }
    else
    {
        finalTextureName = szMushroomBlurTexture;
    }

    m_pBlurHandler = BlurManager::GetNewHandler(finalTextureName, 0.35f, maxEntries, true);
}

/**
 * Offset/Address/Size: 0x184C | 0x8000F798 | size: 0x18
 */
nlVector3& cCharacter::GetPrevJointPosition(int jointIndex)
{
    nlMatrix4& prevMatrix = m_pPoseAccumulator->m_PrevNodeMatrices.mData[jointIndex];
    return *(nlVector3*)&prevMatrix.m[3];
}

/**
 * Offset/Address/Size: 0x1864 | 0x8000F7B0 | size: 0x244
 */
void cCharacter::GetCurrentAnimFuture(int, float, nlVector3&, nlVector3&, unsigned short&)
{
}

/**
 * Offset/Address/Size: 0x1AA8 | 0x8000F9F4 | size: 0x324
 */
nlVector3& cCharacter::GetJointPositionFuture(nlVector3*, int, int, float, bool, bool, bool)
{
    FORCE_DONT_INLINE;
    return m_v3AnimMoveAdjust;
}

/**
 * Offset/Address/Size: 0x1DCC | 0x8000FD18 | size: 0x28
 */
nlVector3& cCharacter::GetJointPosition(int jointIndex) const
{
    const nlMatrix4& poseMatrix = m_pPoseAccumulator->GetNodeMatrix(jointIndex);
    return *(nlVector3*)&poseMatrix.m[3];
}

/**
 * Offset/Address/Size: 0x1DF4 | 0x8000FD40 | size: 0x68
 */
s16 cCharacter::GetFacingDeltaToPosition(const nlVector3& position)
{
    float dy = position.f.y - m_v3Position.f.y;
    float dx = position.f.x - m_v3Position.f.x;
    float angleRad = nlATan2f(dy, dx);

    // Convert radians to 16-bit angle format (65536.0f / (2π) ≈ 10430.378f)
    float angle16 = 10430.378f * angleRad;
    u16 targetAngle = (u16)(s32)angle16;

    return (s16)(targetAngle - m_aActualFacingDirection);
}

/**
 * Offset/Address/Size: 0x1E5C | 0x8000FDA8 | size: 0x148
 */
s16 cCharacter::CalcAnimTurnAdjust(unsigned short param1, unsigned short param2, int animID)
{
    cSAnim* anim = m_pAnimInventory->GetAnim(animID);
    cPN_SAnimController* controller = AllocateSAnimController();
    if (controller == nullptr)
    {
        return 0;
    }

    const AnimRetarget* retarget = nullptr;
    if (m_pAnimRetargetList != nullptr)
    {
        retarget = m_pAnimRetargetList->GetAnimRetargetWithSignature(anim);
    }

    const bool mirrored = m_pAnimInventory->GetMirrored(animID);
    const ePlayMode playMode = m_pAnimInventory->GetPlayMode(animID);

    controller = new (controller) cPN_SAnimController(anim, retarget, playMode, nullptr, 0, mirrored);

    controller->m_fPrevTime = controller->m_fTime; // 0.0f
    controller->m_fTime = 0.0f;
    controller->m_fPrevTime = controller->m_fTime; // 0.0f
    controller->m_fTime = 1.0f;

    unsigned short rootRot;
    controller->GetRootRot(&rootRot);

    s16 combined = param1 + rootRot;

    delete controller;

    return (s16)(param2 - combined);
}

/**
 * Offset/Address/Size: 0x1FA4 | 0x8000FEF0 | size: 0x5C
 */
void cCharacter::AttachEffect(EmissionController* pEmissionController)
{
    u32 characterIndex = GetCharacterIndex(this);
    pEmissionController->m_uUserData = characterIndex;
    pEmissionController->SetPoseAccumulator(*m_pPoseAccumulator);
    pEmissionController->SetAnimController(*m_pCurrentAnimController);
    pEmissionController->m_aFacing = m_aActualFacingDirection;
}

/**
 * Offset/Address/Size: 0x2000 | 0x8000FF4C | size: 0x2C
 */
void cCharacter::AdjustPoseMatrices()
{
    m_pPoseAccumulator->MultNodeMatrices(&m_m4WorldMatrix);
}

/**
 * Offset/Address/Size: 0x202C | 0x8000FF78 | size: 0x24
 */
GLSkinMesh* cCharacter::GetSkinMesh() const
{
    GLSkinMesh* skinMesh = m_pSkinMesh[m_ModelType];
    if (skinMesh == nullptr)
    {
        skinMesh = m_pSkinMesh[0];
    }
    return skinMesh;
}

/**
 * Offset/Address/Size: 0x2050 | 0x8000FF9C | size: 0x1E8
 */
cCharacter::~cCharacter()
{
    u32 characterIndex = GetCharacterIndex(this);
    EmissionManager::Destroy(characterIndex, nullptr);
    m_pEffectsTexturing = nullptr;

    if (m_pPhysicsData != nullptr)
    {
        delete m_pPoseTree;
    }

    delete m_pPoseAccumulator;
    delete m_pSkinMesh[0];

    if (m_pSkinMesh[1] != nullptr)
    {
        delete m_pSkinMesh[1];
    }

    if (m_pPhysicsCharacter != nullptr)
    {
        delete m_pPhysicsCharacter;
    }

    delete m_pHeadTrack;
    delete m_pCharacterSFX;

    if (m_pBlinker != nullptr)
    {
        delete m_pBlinker;
    }
}

/**
 * Offset/Address/Size: 0x2238 | 0x80010184 | size: 0x468
 */
cCharacter::cCharacter(eCharacterClass, const int*, cSHierarchy*, cAnimInventory*, const CharacterPhysicsData*, float, float,
    AnimRetargetList*, eClassTypes)
{
}

/**
 * Offset/Address/Size: 0x26A0 | 0x800105EC | size: 0x1A58
 */
void AIEventHandler(Event*, void*)
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x80012044 | size: 0x6C
//  */
// cPN_SAnimController::~cPN_SAnimController()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800120B0 | size: 0x48
//  */
// cHeadTrack::~cHeadTrack()
// {
// }

// /**
//  * Offset/Address/Size: 0x48 | 0x800120F8 | size: 0x60
//  */
// PhysicsCharacter::~PhysicsCharacter()
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x80012158 | size: 0x48
 */
// GLSkinMesh::~GLSkinMesh()
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x800121A0 | size: 0x8
 */
u32 CharacterDirectionData::GetID()
{
    return 0x175;
}

/**
 * Offset/Address/Size: 0x8 | 0x800121A8 | size: 0x8
 */
u32 PowerupData::GetID()
{
    return 0x15c;
}

/**
 * Offset/Address/Size: 0x10 | 0x800121B0 | size: 0x8
 */
u32 PenaltyData::GetID()
{
    return 0x152;
}

/**
 * Offset/Address/Size: 0x18 | 0x800121B8 | size: 0x8
 */
u32 ShotAtGoalData::GetID()
{
    return 0x14a;
}

/**
 * Offset/Address/Size: 0x20 | 0x800121C0 | size: 0x8
 */
u32 ReceiveBallData::GetID()
{
    return 0x121;
}

/**
 * Offset/Address/Size: 0x28 | 0x800121C8 | size: 0x8
 */
u32 CollisionBobombData::GetID()
{
    return 0xED;
}

/**
 * Offset/Address/Size: 0x30 | 0x800121D0 | size: 0x8
 */
u32 CollisionPlayerBananaData::GetID()
{
    return 0xE2;
}

/**
 * Offset/Address/Size: 0x38 | 0x800121D8 | size: 0x8
 */
u32 CollisionBallShellData::GetID()
{
    return 0xC1;
}

/**
 * Offset/Address/Size: 0x40 | 0x800121E0 | size: 0x8
 */
u32 CollisionPlayerFreezeData::GetID()
{
    return 0xD7;
}

/**
 * Offset/Address/Size: 0x48 | 0x800121E8 | size: 0x8
 */
u32 CollisionPowerupStatsData::GetID()
{
    return 0x104;
}

/**
 * Offset/Address/Size: 0x50 | 0x800121F0 | size: 0x8
 */
u32 CollisionPlayerShellData::GetID()
{
    return 0xC9;
}

/**
 * Offset/Address/Size: 0x58 | 0x800121F8 | size: 0x8
 */
u32 CollisionBowserPlayerData::GetID()
{
    return 0x65;
}

/**
 * Offset/Address/Size: 0x60 | 0x80012200 | size: 0x8
 */
u32 CollisionChainPlayerData::GetID()
{
    return 0x5C;
}

/**
 * Offset/Address/Size: 0x68 | 0x80012208 | size: 0x8
 */
u32 CollisionPlayerShootToScoreBallData::GetID()
{
    return 0xB8;
}

/**
 * Offset/Address/Size: 0x70 | 0x80012210 | size: 0x8
 */
u32 CollisionPlayerBallData::GetID()
{
    return 0xA7;
}

/**
 * Offset/Address/Size: 0x78 | 0x80012218 | size: 0x8
 */
u32 CollisionPlayerWallData::GetID()
{
    return 0x6E;
}

// /**
//  * Offset/Address/Size: 0x80 | 0x80012220 | size: 0x8
//  */
// u32 CollisionPowerupWallData::GetID()
// {
//     return 0x9B;
// }

// /**
//  * Offset/Address/Size: 0x88 | 0x80012228 | size: 0x8
//  */
// u32 CollisionBallGoalpostData::GetID()
// {
//     return 0x10E;
// }

/**
 * Offset/Address/Size: 0x90 | 0x80012230 | size: 0x8
 */
u32 CollisionBallWallData::GetID()
{
    return 0x78;
}

/**
 * Offset/Address/Size: 0x98 | 0x80012238 | size: 0x8
 */
u32 CollisionBallGroundData::GetID()
{
    return 0x8F;
}

/**
 * Offset/Address/Size: 0xA0 | 0x80012240 | size: 0x8
 */
u32 CollisionPlayerPlayerData::GetID()
{
    return 0x51;
}

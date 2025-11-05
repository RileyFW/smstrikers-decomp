#include "Game/CharacterAudio.h"

namespace Audio
{

const char* gCharSoundTable[] = {
    "CHARSFX_NONE",
    "CHARSFX_RUN_01",
    "CHARSFX_RUN_02",
    "CHARSFX_RUN_03",
    "CHARSFX_RUN_04",
    "CHARSFX_RUN_05",
    "CHARSFX_WALK_01",
    "CHARSFX_WALK_02",
    "CHARSFX_WALK_03",
    "CHARSFX_WALK_04",
    "CHARSFX_WALK_05",
    "CHARSFX_LAND",
    "CHARSFX_SLIDE",
    "CHARSFX_JUMP",
    "CHARSFX_TURN",
    "CHARSFX_DEKE_LEFT",
    "CHARSFX_DEKE_RIGHT",
    "CHARSFX_BODYFALL",
    "CHARSFX_KICK_ATTEMPT",
    "CHARSFX_KICK_SUPER",
    "CHARSFX_SHOT_WINDUP",
    "CHARSFX_SHOT_LOCK",
    "CHARSFX_SHOT_RELEASE",
    "CHARSFX_S2S_METER_GLOW",
    "CHARSFX_HIT_BODY",
    "CHARSFX_HIT_BODY_BONE",
    "CHARSFX_HIT_SLIDE",
    "CHARSFX_BODYFALL_BONECRUNCH",
    "CHARSFX_SUPER_KICK_WINDUP",
    "CHARSFX_PWRUP_MUSH_IN_EFFECT",
    "CHARSFX_PWRUP_STAR_IN_EFFECT",
    "CHARSFX_SHELL_FREEZE_HIT",
    "CHARSFX_SHELL_FREEZE_END",
    "CHARSFX_EFFORTS_ATTACK_01",
    "CHARSFX_EFFORTS_ATTACK_02",
    "CHARSFX_EFFORTS_ATTACK_03",
    "CHARSFX_EFFORTS_HIT_01",
    "CHARSFX_EFFORTS_HIT_02",
    "CHARSFX_EFFORTS_HIT_03",
    "CHARSFX_EFFORTS_GET_HIT_01",
    "CHARSFX_EFFORTS_GET_HIT_02",
    "CHARSFX_EFFORTS_GET_HIT_03",
    "CHARSFX_EFFORTS_PAIN_01",
    "CHARSFX_EFFORTS_PAIN_02",
    "CHARSFX_EFFORTS_PAIN_03",
    "CHARSFX_EFFORTS_ELECTROCUTE_01",
    "CHARSFX_EFFORTS_ELECTROCUTE_02",
    "CHARSFX_EFFORTS_ELECTROCUTE_03",
    "CHARSFX_EFFORTS_EXERT_01",
    "CHARSFX_EFFORTS_EXERT_02",
    "CHARSFX_EFFORTS_EXERT_03",
    "CHARSFX_EFFORTS_KICK_01",
    "CHARSFX_EFFORTS_KICK_02",
    "CHARSFX_EFFORTS_KICK_03",
    "CHARSFX_EFFORTS_DAZED",
    "CHARSFX_EFFORTS_HEAD_SHAKE",
    "CHARSFX_EFFORTS_KICK_SUPER",
    "CHARSFX_EFFORTS_SHOT_WINDUP",
    "CHARSFX_EFFORTS_STS_JUMP_01",
    "CHARSFX_EFFORTS_STS_FLOAT_01",
    "CHARSFX_EFFORTS_STS_KICK_01",
    "CHARSFX_EFFORTS_PERFECT_PASS",
    "CHARSFX_BREATH_WITH_BALL",
    "CHARSFX_CALL_HEY_01",
    "CHARSFX_CALL_HEY_02",
    "CHARSFX_CALL_WO_01",
    "CHARSFX_CALL_WO_02",
    "CHARSFX_CALL_PERFECT_PASS",
    "CHARSFX_DAZED",
    "CHARSFX_HEAD_POP",
    "CHARSFX_ELECTROCUTED",
    "CHARSFX_THROW",
    "CHARSFX_SWISH_UP_01",
    "CHARSFX_SWISH_UP_02",
    "CHARSFX_SWISH_UP_03",
    "CHARSFX_SWISH_DOWN_01",
    "CHARSFX_SWISH_DOWN_02",
    "CHARSFX_SWISH_DOWN_03",
    "CHARSFX_GEN_STOS_JUMP",
    "CHARSFX_GEN_STOS_FLOAT",
    "CHARSFX_GEN_STOS_FLOAT_HYPER",
    "CHARSFX_NIS_CLAP_01",
    "CHARSFX_NIS_CLAP_02",
    "CHARSFX_NIS_CLAP_03",
    "CHARSFX_NIS_SPIN_LOOP",
    "CHARSFX_BOWSER_ENTER",
    "CHARSFX_BOWSER_ACTIVATE",
    "CHARSFX_BOWSER_HOWL_01",
    "CHARSFX_BOWSER_HOWL_02",
    "CHARSFX_BOWSER_HOWL_03",
    "CHARSFX_BOWSER_CHARGE_01",
    "CHARSFX_BOWSER_CHARGE_02",
    "CHARSFX_BOWSER_BREATH_FIRE",
    "CHARSFX_CRITTER_HIT_NET",
    "CHARSFX_CRITTER_EFFORTS_CATCH_MOUTH",
    "CHARSFX_CRITTER_EFFORTS_FEAR",
    "CHARSFX_CRITTER_EFFORTS_PUZZLED",
    "CHARSFX_CRITTER_EFFORTS_ANGER",
    "CHARSFX_CRITTER_HIT_HYPER",
    "CHARSFX_SUPER_LEFT_LEG_SERVO",
    "CHARSFX_SUPER_RIGHT_LEG_SERVO",
    "CHARSFX_TOAD_NIS_GOAL_HIGH_01",
    "CHARSFX_TOAD_NIS_GOAL_LOW_01",
    "CHARSFX_HAM_NIS_GOAL_HIGH_01",
    "CHARSFX_HAM_NIS_GOAL_LOW_01",
    "CHARSFX_KOOPA_NIS_GOAL_HIGH_01",
    "CHARSFX_KOOPA_NIS_GOAL_LOW_01",
    "CHARSFX_BIRDO_NIS_GOAL_HIGH_01",
    "CHARSFX_BIRDO_NIS_GOAL_LOW_01",
    "CHARSFX_DAISY_NIS_ENTER_HOME_01",
    "CHARSFX_DAISY_NIS_ENTER_AWAY_01",
    "CHARSFX_DAISY_NIS_ATTITUDE_01",
    "CHARSFX_DAISY_NIS_GOAL_HIGH_01",
    "CHARSFX_DAISY_NIS_GOAL_LOW_01",
    "CHARSFX_DAISY_NIS_GAME_WIN_01",
    "CHARSFX_DK_WIN_HOME_LOW",
    "CHARSFX_DK_END_GAME_HOME",
    "CHARSFX_DK_ATTITUDE_HOME_CHEST",
    "CHARSFX_DK_NIS_ENTER_HOME_01",
    "CHARSFX_DK_NIS_ENTER_AWAY_01",
    "CHARSFX_DK_NIS_ATTITUDE_01",
    "CHARSFX_DK_NIS_GOAL_HIGH_00",
    "CHARSFX_DK_NIS_GOAL_HIGH_01",
    "CHARSFX_DK_NIS_GOAL_LOW_01",
    "CHARSFX_DK_NIS_GAME_WIN_01",
    "CHARSFX_LUIGI_NIS_ENTER_HOME_01",
    "CHARSFX_LUIGI_NIS_ENTER_AWAY_01",
    "CHARSFX_LUIGI_NIS_ATTITUDE_01",
    "CHARSFX_LUIGI_NIS_GOAL_HIGH_01",
    "CHARSFX_LUIGI_NIS_GOAL_LOW_01",
    "CHARSFX_LUIGI_NIS_GAME_WIN_01",
    "CHARSFX_MARIO_NIS_ENTER_HOME_01",
    "CHARSFX_MARIO_NIS_ENTER_AWAY_01",
    "CHARSFX_MARIO_NIS_ATTITUDE_01",
    "CHARSFX_MARIO_NIS_ATTITUDE_02",
    "CHARSFX_MARIO_NIS_GOAL_HIGH_01",
    "CHARSFX_MARIO_NIS_GOAL_HIGH_02",
    "CHARSFX_MARIO_NIS_GOAL_LOW_01",
    "CHARSFX_MARIO_NIS_GAME_WIN_01",
    "CHARSFX_MARIO_NIS_GAME_WIN_02",
    "CHARSFX_PEACH_NIS_ENTER_HOME_01",
    "CHARSFX_PEACH_NIS_ENTER_AWAY_01",
    "CHARSFX_PEACH_NIS_ATTITUDE_01",
    "CHARSFX_PEACH_NIS_GOAL_HIGH_01",
    "CHARSFX_PEACH_NIS_GOAL_LOW_01",
    "CHARSFX_PEACH_NIS_GAME_WIN_01",
    "CHARSFX_WALUIGI_NIS_ENTER_HOME_01",
    "CHARSFX_WALUIGI_NIS_ENTER_AWAY_01",
    "CHARSFX_WALUIGI_NIS_ATTITUDE_01",
    "CHARSFX_WALUIGI_NIS_GOAL_HIGH_00",
    "CHARSFX_WALUIGI_NIS_GOAL_HIGH_01",
    "CHARSFX_WALUIGI_NIS_GOAL_LOW_01",
    "CHARSFX_WALUIGI_NIS_GAME_WIN_01",
    "CHARSFX_WARIO_NIS_ENTER_HOME_01",
    "CHARSFX_WARIO_NIS_ENTER_AWAY_01",
    "CHARSFX_WARIO_NIS_ATTITUDE_01",
    "CHARSFX_WARIO_NIS_GOAL_HIGH_01",
    "CHARSFX_WARIO_NIS_GOAL_LOW_01",
    "CHARSFX_WARIO_NIS_GAME_WIN_01",
    "CHARSFX_YOSHI_NIS_ENTER_HOME_01",
    "CHARSFX_YOSHI_NIS_ENTER_AWAY_01",
    "CHARSFX_YOSHI_NIS_ATTITUDE_01",
    "CHARSFX_YOSHI_NIS_GOAL_HIGH_01",
    "CHARSFX_YOSHI_NIS_GOAL_LOW_01",
    "CHARSFX_YOSHI_NIS_GAME_WIN_01",
    "CHARSFX_SUPER_NIS_ENTER_HOME_01",
    "CHARSFX_SUPER_NIS_ENTER_AWAY_01",
    "CHARSFX_SUPER_NIS_ATTITUDE_01",
    "CHARSFX_SUPER_NIS_GOAL_HIGH_01",
    "CHARSFX_SUPER_NIS_GOAL_LOW_01",
    "CHARSFX_SUPER_NIS_GAME_WIN_01",
    "CHARSFX_MYST_NIS_ENERGY_BLAST_01",
    "CHARSFX_MYST_NIS_ROCKET_BOOTS_01",
    "NUM_CHARSFX"
};

/**
 * Offset/Address/Size: 0x0 | 0x8014C3A4 | size: 0x14
 */
bool cCharacterSFX::IsMovementLoopStarted()
{
    // return m_movementLoopStarted != 0;
    return mpMovementLoopSound != NULL;
}

/**
 * Offset/Address/Size: 0x14 | 0x8014C3B8 | size: 0x24
 */
bool cCharacterSFX::IsMovementLoopPlaying()
{
    return Audio::IsEmitterActive(mpMovementLoopSound);
}

/**
 * Offset/Address/Size: 0x38 | 0x8014C3DC | size: 0x48
 */
void cCharacterSFX::StopMovementLoop()
{
    if (mpMovementLoopSound)
    {
        // Stop emitter with stop flag 0
        cGameSFX::StopEmitter(mpMovementLoopSound, 0);
        mpMovementLoopSound = nullptr;
        m_unk_0x33A0 = false;
    }
}

/**
 * Offset/Address/Size: 0x80 | 0x8014C424 | size: 0x164
 */
void cCharacterSFX::StartMovementLoop()
{
}

/**
 * Offset/Address/Size: 0x1E4 | 0x8014C588 | size: 0x10C
 */
// void cCharacterSFX::GetCharacterFromNisCharClass(NisCharacterClass)
// {
// }

/**
 * Offset/Address/Size: 0x2F0 | 0x8014C694 | size: 0x1C8
 */
// void cCharacterSFX::PlayNISRandomCharDialogue(CharDialogueType, NisCharacterClass, float, float, bool, const nlVector3*, const
// nlVector3*, unsigned long*)
// {
// }

/**
 * Offset/Address/Size: 0x4B8 | 0x8014C85C | size: 0x148
 */
void cCharacterSFX::PlayRandomWalkFootstep(float, bool)
{
}

/**
 * Offset/Address/Size: 0x600 | 0x8014C9A4 | size: 0x98
 */
void cCharacterSFX::StopPlayingAllRandomCharDialogue()
{
}

/**
 * Offset/Address/Size: 0x698 | 0x8014CA3C | size: 0x98
 */
// void cCharacterSFX::StopPlayingRandomCharDialogue(CharDialogueType)
// {
// }

/**
 * Offset/Address/Size: 0x730 | 0x8014CAD4 | size: 0x94
 */
// void cCharacterSFX::IsPlayingRandomCharDialogue(CharDialogueType)
// {
// }

/**
 * Offset/Address/Size: 0x7C4 | 0x8014CB68 | size: 0x498
 */
// void cCharacterSFX::PlayRandomCharDialogue(CharDialogueType, SoundAttributes&, bool, unsigned long*)
// {
// }

/**
 * Offset/Address/Size: 0xC5C | 0x8014D000 | size: 0x4D0
 */
// void cCharacterSFX::PlayRandomCharDialogue(CharDialogueType, PosUpdateMethod, float, float, bool)
// {
// }

/**
 * Offset/Address/Size: 0x112C | 0x8014D4D0 | size: 0x20
 */
void cCharacterSFX::Stop(eCharSFX sfxType, cGameSFX::StopFlag flag)
{
    cGameSFX::Stop(sfxType, flag);
}

/**
 * Offset/Address/Size: 0x114C | 0x8014D4F0 | size: 0x7C
 */
int cCharacterSFX::Play(SoundAttributes& attrs)
{
    attrs.me_ClassType = 1;
    attrs.mi_EmitterGroup = mGroup;

    if (attrs.posUpdateMethod == PHYSOBJ)
    {
        attrs.UsePhysObj(mpPhysObj);
    }

    if (attrs.mu_Type == 0U)
    {
        return Audio::GetSndIDError();
    }

    return cGameSFX::Play(attrs);
}

/**
 * Offset/Address/Size: 0x11C8 | 0x8014D56C | size: 0xCC
 */
void cCharacterSFX::Init()
{
    if (mbInited != 0)
    {
        return;
    }

    for (int i = 0; i < 173; i++)
    {
        mCharSFX[i].typeID = -1;
        mCharSFX[i].typeStr = nullptr;
        mCharSFX[i].musyxStr = nullptr;
        mCharSFX[i].musyxID = -1;
        mCharSFX[i].fVolume = 100.0f;
        mCharSFX[i].fDelay = -1.0f;
        mCharSFX[i].fVolReverb = 100.0f;
        mCharSFX[i].volGrp = -1;
        mCharSFX[i].sfxPriority = 0;
        mCharSFX[i].uHashVal = 0;
        mCharSFX[i].pSoundPropAccessor = nullptr;
        mCharSFX[i].bSoundPropTableReloaded = 0;
        mCharSFX[i].pSoundProp = nullptr;
        mCharSFX[i].pOwner = nullptr;
        mCharSFX[i].lastVoiceID = -1;
        mCharSFX[i].pLastEmitter = nullptr;
        mCharSFX[i].m_unk_0x40 = 0;

        mSoundTypeEnumMap[i] = -1;

        mDebugTimer[i] = 0.0f;
    }

    mpSFX = mCharSFX;
    mpSoundStrTable = Audio::gCharSoundTable;
    mNumSFXTypes = 173;
    meClassType = CHAR;

    cGameSFX::Init();
}

/**
 * Offset/Address/Size: 0x1294 | 0x8014D638 | size: 0x7C
 */
cCharacterSFX::~cCharacterSFX()
{
    mpPhysObj = NULL;
    mGroup = 0;
    mpMovementLoopSound = NULL;
    m_unk_0x339C = 100.0f;
    m_unk_0x33A0 = false;
}

/**
 * Offset/Address/Size: 0x1310 | 0x8014D6B4 | size: 0x60
 */
cCharacterSFX::cCharacterSFX()
{
    mGroup = 0;
    mpPhysObj = NULL;
    mpMovementLoopSound = NULL;
    m_unk_0x339C = 100.0f;
    m_unk_0x33A0 = false;
    meClassType = CHAR;
}

} // namespace Audio

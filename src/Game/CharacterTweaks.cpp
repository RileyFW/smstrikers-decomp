#pragma pool_data off

#include "Game/CharacterTweaks.h"

#define NL_LEXICALCAST_DEFINE
#include "NL/nlLexicalCast.h"

#include "NL/nlConfig.h"

f32 g_pTweaks[0x17] = {
    4000.0f,
    25.0f,
    45.0f,
    9.5f,
    4000.0f,
    17.5f,
    17.5f,
    2600.0f,
    22.5f,
    18.0f,
    3200.0f,
    25.0f,
    18.0f,
    10.0f,
    2600.0f,
    20.0f,
    20.0f,
    5.5f,
    22.5f,
    14.0f,
    75000.0f,
    4000.0f,
    6.0f,
};

/**
 * Offset/Address/Size: 0x342C | 0x80017E1C | size: 0x60
 */
PlayerTweaks::~PlayerTweaks()
{
}

/**
 * Offset/Address/Size: 0x2E9C | 0x8001788C | size: 0x590
 */
void PlayerTweaks::Init()
{
    Config cfg(Config::ALLOCATE_HIGH);
    cfg.LoadFromFile(mszFileName);

    fJoggingSpeed = GetConfigFloat(cfg, "Jog Speed", 1.6f);
    fRunningSpeed = GetConfigFloat(cfg, "Running Speed", 6.25f);
    fPhysCapsuleHeight = GetConfigFloat(cfg, "Capsule Height", 0.5f);
    fPhysCapsuleRadius = GetConfigFloat(cfg, "Capsule Width", 0.3f);
    fRunningDirectionSeekSpeed = GetConfigFloat(cfg, "Running Turn Speed", 105000.0f);
    fRunningDirectionSeekFalloff = g_pTweaks[0];
    fPassGroundSpeedMax = GetConfigFloat(cfg, "Pass Ground Speed Max", 16.0f);
    fPassGroundSpeedMin = GetConfigFloat(cfg, "Pass Ground Speed Min", 5.5f);
    fPassVolleySpeedMax = GetConfigFloat(cfg, "Pass Volley Speed Max", 14.0f);
    fPassVolleySpeedMin = GetConfigFloat(cfg, "Pass Volley Speed Min", 5.5f);
}

/**
 * Offset/Address/Size: 0x2E1C | 0x8001780C | size: 0x80
 */
FielderTweaks::FielderTweaks(const char* arg0)
    : PlayerTweaks(arg0)
{
    Init();
}

/**
 * Offset/Address/Size: 0x2DAC | 0x8001779C | size: 0x70
 */
FielderTweaks::~FielderTweaks()
{
}

/**
 * Offset/Address/Size: 0x19F4 | 0x800163E4 | size: 0x13B8
 */
void FielderTweaks::Init()
{
    PlayerTweaks::Init();

    Config cfg(Config::ALLOCATE_HIGH);
    cfg.LoadFromFile(mszFileName);

    fRunningAccel = g_pTweaks[1];
    fRunningDecel = g_pTweaks[2];
    fRunningStopDecel = g_pTweaks[3];
    fRunningStrafeDirectionSeekSpeed = GetConfigFloat(cfg, "Strafe Turn Speed", 140000.0f);
    fRunningStrafeDirectionSeekFalloff = g_pTweaks[4];
    fRunningStrafeSpeed = GetConfigFloat(cfg, "Strafe Speed", 3.5f);
    fRunningBackwardsSpeed = GetConfigFloat(cfg, "Run Backwards Speed", 4.0f);
    fRunningStrafeAccel = g_pTweaks[5];
    fRunningStrafeDecel = g_pTweaks[6];
    fRunningTurboDirectionSeekSpeed = GetConfigFloat(cfg, "Turbo Turn Speed", 65000.0f);
    fRunningTurboDirectionSeekFalloff = g_pTweaks[7];
    fRunningTurboSpeed = GetConfigFloat(cfg, "Turbo Speed", 7.5f);
    fRunningTurboAccel = g_pTweaks[8];
    fRunningTurboDecel = g_pTweaks[9];
    fRunningWBDirectionSeekSpeed = GetConfigFloat(cfg, "WB Run Turn Speed", 90000.0f);
    fRunningWBDirectionSeekFalloff = g_pTweaks[10];
    fRunningWBSpeed = GetConfigFloat(cfg, "WB Run Speed", 6.0f);
    fRunningWBAccel = g_pTweaks[11];
    fRunningWBDecel = g_pTweaks[12];
    fRunningWBStopDecel = g_pTweaks[13];
    fRunningWBTurboDirectionSeekSpeed = GetConfigFloat(cfg, "WB Run Turbo Turn Speed", 70000.0f);
    fRunningWBTurboDirectionSeekFalloff = g_pTweaks[14];
    fRunningWBTurboSpeedLevel1 = GetConfigFloat(cfg, "WB Run Turbo Level 1 Speed", 6.5f);

    fRunningWBTurboSpeedLevel2 = GetConfigFloat(cfg, "WB Run Turbo Level 2 Speed", 7.0f);
    fRunningWBTurboSpeedLevel3 = GetConfigFloat(cfg, "WB Run Turbo Level 3 Speed", 7.5f);

    fRunningWBTurboAccel = g_pTweaks[15];
    fRunningWBTurboDecel = g_pTweaks[16];
    fRunningWBTurboTurnSpeed = g_pTweaks[17];
    fRunningWBTurboTurnAccel = g_pTweaks[18];
    fRunningWBTurboTurnDecel = g_pTweaks[19];

    fShotWindupDirectionSeekSpeed = g_pTweaks[20];
    fShotWindupDirectionSeekFalloff = g_pTweaks[21];
    fShotWindupDecel = g_pTweaks[22];

    fCaptainS2SNisBeginFrame = GetConfigFloat(cfg, "S2S Nis Begin Frame", 9.0f);
    fCaptainS2SNisEndFrame = GetConfigFloat(cfg, "S2S Nis End Frame", 9.0f);
    fS2SKickFrame = GetConfigFloat(cfg, "S2S Kick Frame", 9.0f);
    fS2S1stJumpFrame = GetConfigFloat(cfg, "S2S 1st Jump Frame", 9.0f);

    nChanceForRedShell = GetConfigInt(cfg, "Red Shell Chance", 0x17);
    nChanceForGreenShell = GetConfigInt(cfg, "Green Shell Chance", 0x17);
    nChanceForSpinyShell = GetConfigInt(cfg, "Spiny Shell Chance", 0x17);
    nChanceForFreezeShell = GetConfigInt(cfg, "Freeze Shell Chance", 0x17);
    nChanceForMushroom = GetConfigInt(cfg, "Mushroom Chance", 0x17);
    nChanceForBanana = GetConfigInt(cfg, "Banana Chance", 0x17);
    nChanceForBoBomb = GetConfigInt(cfg, "Bobomb Chance", 0x17);

    fChanceForBig = GetConfigFloat(cfg, "Big Chance", 23.0f);
    fChanceForMultiples = GetConfigFloat(cfg, "Multiples Chance", 23.0f);

    fAggression = GetConfigFloat(cfg, "Aggression", 0.5f);
    fShooting = GetConfigFloat(cfg, "Shooting", 0.5f);
    fPassing = GetConfigFloat(cfg, "Passing", 0.5f);
    fDekeing = GetConfigFloat(cfg, "Dekeing", 0.5f);

    fShotMinSpeed = GetConfigFloat(cfg, "Shot Min Speed", 0.0f);
    fShotMaxSpeed = GetConfigFloat(cfg, "Shot Max Speed", 0.0f);
    fShotChipMinSpeed = GetConfigFloat(cfg, "Chip Shot Min Speed", 0.0f);
    fShotChipMaxSpeed = GetConfigFloat(cfg, "Chip Shot Max Speed", 0.0f);
}

/**
 * Offset/Address/Size: 0x1974 | 0x80016364 | size: 0x80
 */
GoalieTweaks::GoalieTweaks(const char* arg0)
    : PlayerTweaks(arg0)
{
    Init();
}

/**
 * Offset/Address/Size: 0x1904 | 0x800162F4 | size: 0x70
 */
GoalieTweaks::~GoalieTweaks()
{
}

inline float max_float(float a, float b)
{
    return (a >= b) ? a : b;
}

/**
 * Offset/Address/Size: 0x0 | 0x800149F0 | size: 0x1904
 */
void GoalieTweaks::Init()
{
    PlayerTweaks::Init();

    Config cfg(Config::ALLOCATE_HIGH);
    cfg.LoadFromFile(mszFileName);

    fThrowingDirectionSeekSpeed = GetConfigFloat(cfg, "Throwing Turn Speed", 50000.0f);
    fThrowingDirectionSeekFalloff = GetConfigFloat(cfg, "Throwing Turn falloff", 4000.0f);
    fKickDistanceMin = GetConfigFloat(cfg, "Minimum Kick Distance", 13.0f);
    fOverhandThrowDistanceMin = GetConfigFloat(cfg, "Minimum Overhand Throw Distance", 7.0f);
    fKickVelocityMin = GetConfigFloat(cfg, "Minimum Kick Velocity", 12.0f);
    fKickVelocityMax = GetConfigFloat(cfg, "Maximum Kick Velocity", 16.0f);
    fKickAngleMin = GetConfigFloat(cfg, "Minimum Kick Angle", 50.0f);
    fKickAngleMax = GetConfigFloat(cfg, "Maximum Kick Angle", 60.0f);
    fFatigueRecoverRate = GetConfigFloat(cfg, "Fatigue Recover Rate", 2.0f);
    fFatigueCatchThreshold = GetConfigFloat(cfg, "Fatigue Catch Threshold", 60.0f);
    fCatchSaveMaxSpeed = GetConfigFloat(cfg, "Catch Save Max Speed", 0.5f);
    fGetupEnergyHigh = GetConfigFloat(cfg, "High Getup Energy", 80.0f);
    fGetupEnergyLow = GetConfigFloat(cfg, "Low Getup Energy", 20.0f);
    fGetupSpeedLow = GetConfigFloat(cfg, "Low Getup Speed", 0.5f);
    fStrafeSpeedLow = GetConfigFloat(cfg, "Low Strafe Speed", 0.8f);
    fGoalieBallTime = GetConfigFloat(cfg, "Goalie Ball Time", 5.0f);
    fGoalieStunTimeMin = GetConfigFloat(cfg, "Min STS Stun Time", 1.5f);
    fGoalieStunTimeMax = GetConfigFloat(cfg, "Max STS Stun Time", 3.0f);
    fLooseBallShotDistance = GetConfigFloat(cfg, "Loose Ball Shot Distance", 10.0f);
    fSaveDirectionSeekSpeed = GetConfigFloat(cfg, "Save Turn Speed", 100000.0f);
    fSaveDirectionSeekFalloff = GetConfigFloat(cfg, "Save Turn Falloff", 4000.0f);
    fSaveBackRunTimeScale = GetConfigFloat(cfg, "Save Back Run Scale", 1.5f);
    fSaveIgnoreMargin = GetConfigFloat(cfg, "Save Ignore Margin", 1.0f);
    fSaveMissDelay = GetConfigFloat(cfg, "Miss Save Delay", 0.1f);
    fLobShotStumbleChance = GetConfigFloat(cfg, "Lob Shot Stumble Chance", 0.3f);
    fInterceptSaveTolerance = GetConfigFloat(cfg, "Intercept Save Tolerance", 0.5f);
    fSaveCatchTolerance = GetConfigFloat(cfg, "Catch Save Tolerance", 0.7f);
    fShotFatigueDefault = GetConfigFloat(cfg, "Shot Fatigue Default", 10.0f);
    fShotFatigueStandCatch = GetConfigFloat(cfg, "Shot Fatigue Stand Catch", 5.0f);
    fShotFatigueDiveCatch = GetConfigFloat(cfg, "Shot Fatigue Dive Catch", 10.0f);
    fShotFatigueStandDeflect = GetConfigFloat(cfg, "Shot Fatigue Stand Deflection", 5.0f);
    fShotFatigueDiveDeflect = GetConfigFloat(cfg, "Shot Fatigue Dive Deflection", 10.0f);
    fShotFatigueStandPunch = GetConfigFloat(cfg, "Shot Fatigue Stand Punch", 7.0f);
    fShotFatigueLegSave = GetConfigFloat(cfg, "Shot Fatigue Leg Save", 6.0f);
    fShotFatigueSTSSave = GetConfigFloat(cfg, "Shot Fatigue STS Save", 15.0f);
    fShotFatigueSTSStun = GetConfigFloat(cfg, "Shot Fatigue STS Stun", 20.0f);

    // Find the maximum fatigue value
    fShotFatigueMax = max_float(fShotFatigueDefault, fShotFatigueStandCatch);
    fShotFatigueMax = max_float(fShotFatigueMax, fShotFatigueDiveCatch);
    fShotFatigueMax = max_float(fShotFatigueMax, fShotFatigueStandDeflect);
    fShotFatigueMax = max_float(fShotFatigueMax, fShotFatigueDiveDeflect);
    fShotFatigueMax = max_float(fShotFatigueMax, fShotFatigueStandPunch);
    fShotFatigueMax = max_float(fShotFatigueMax, fShotFatigueLegSave);
    fShotFatigueMax = max_float(fShotFatigueMax, fShotFatigueSTSSave);
    fShotFatigueMax = max_float(fShotFatigueMax, fShotFatigueSTSStun);

    fSTSAttackCloseDistance = GetConfigFloat(cfg, "STS Attack Close Distance", 1.0f);
    fSTSAttackMaxDistance = GetConfigFloat(cfg, "STS Attack Max Distance", 7.0f);
    fSTSAttackChancePerFrame = GetConfigFloat(cfg, "STS Attack Chance Per Frame", 0.01f);
    fSTSAttackBallVelMult = GetConfigFloat(cfg, "STS Attack Ball Speed Multiplier", 0.3f);
    fPounceRange = GetConfigFloat(cfg, "Pounce Range", 1.0f);
}

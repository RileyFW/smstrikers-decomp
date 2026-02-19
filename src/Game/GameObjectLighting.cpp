#include "Game/GameObjectLighting.h"

#include "Game/GameInfo.h"
#include "NL/gl/glState.h"
#include "types.h"

struct StadiumLightingParams
{
    u32 lightRamp;
    u8 pad[0x38];
};

StadiumLightingParams gStadiumGameObjectLightingParams[7] = {
    { glGetTexture("MarioStadiumPlayerLightRamp") },
    { glGetTexture("PeachToadStadiumPlayerLightRamp") },
    { glGetTexture("DKDaisyStadiumPlayerLightRamp") },
    { glGetTexture("WarioStadiumPlayerLightRamp") },
    { glGetTexture("YoshiStadiumPlayerLightRamp") },
    { glGetTexture("SuperStadiumPlayerLightRamp") },
    { glGetTexture("ForbiddenDomePlayerLightRamp") }
};

/**
 * Offset/Address/Size: 0xB0C | 0x8012B348 | size: 0x8
 */
void* GetCameraRelativeLightData()
{
    FORCE_DONT_INLINE;
    return NULL;
}

/**
 * Offset/Address/Size: 0xB04 | 0x8012B340 | size: 0x8
 */
void* GetInGameLightData()
{
    FORCE_DONT_INLINE;
    return NULL;
}

bool gAlwaysUseCameraRelativeCharacterLighting;

/**
 * Offset/Address/Size: 0xAFC | 0x8012B338 | size: 0x8
 */
bool AlwaysUseCameraRelativeCharacterLighting()
{
    return gAlwaysUseCameraRelativeCharacterLighting;
}

/**
 * Offset/Address/Size: 0x244 | 0x8012AA80 | size: 0x8B8
 */
void InitializeGameObjectLighting()
{
}

/**
 * Offset/Address/Size: 0x34 | 0x8012A870 | size: 0x210
 */
void UpdateGameObjectLighting()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x0 | 0x8012A83C | size: 0x34
 */
u32 GetGameObjectLightRamp()
{
    return gStadiumGameObjectLightingParams[nlSingleton<GameInfoManager>::s_pInstance->GetStadium()].lightRamp;
}

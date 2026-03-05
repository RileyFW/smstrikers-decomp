#include "Game/GameObjectLighting.h"

#include "Game/GameInfo.h"
#include "Game/Camera/CameraMan.h"
#include "Game/Drawable/DrawableCharacter.h"
#include "NL/gl/glState.h"
#include "NL/gl/glLightUserData.h"
#include "NL/gl/glUserData.h"
#include "types.h"

struct StadiumLightingParams
{
    u32 lightRamp;          // +0x00
    u8 pad1[0x18];          // +0x04
    f32 keyLightIntensity;  // +0x1C
    f32 fillLightIntensity; // +0x20
    u8 pad2[0x18];          // +0x24
}; // total size: 0x3C

struct GameObjectLightArray
{
    u32 numLights;             // +0x00
    GLLightUserData lights[2]; // +0x04
}; // total size: 0x54

StadiumLightingParams gStadiumGameObjectLightingParams[7] = {
    { glGetTexture("MarioStadiumPlayerLightRamp") },
    { glGetTexture("PeachToadStadiumPlayerLightRamp") },
    { glGetTexture("DKDaisyStadiumPlayerLightRamp") },
    { glGetTexture("WarioStadiumPlayerLightRamp") },
    { glGetTexture("YoshiStadiumPlayerLightRamp") },
    { glGetTexture("SuperStadiumPlayerLightRamp") },
    { glGetTexture("ForbiddenDomePlayerLightRamp") }
};

void* g_pCameraRelativeLightData = NULL;

/**
 * Offset/Address/Size: 0xB0C | 0x8012B348 | size: 0x8
 */
void* GetCameraRelativeLightData()
{
    return g_pCameraRelativeLightData;
}

/**
 * Offset/Address/Size: 0xB04 | 0x8012B340 | size: 0x8
 */
void* GetInGameLightData()
{
    extern void* g_pInGameLightData;
    return g_pInGameLightData;
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
 * TODO: 99.4% match in scratch - remaining diffs are label/address `i` diffs
 * from static local variable numbering and constant pool labels.
 */
void UpdateGameObjectLighting()
{
    if (!DrawableCharacter::sCameraRelativeLighting && !gAlwaysUseCameraRelativeCharacterLighting)
        return;

    static nlVector3 keyLightInViewSpace;
    static nlVector3 fillLightInViewSpace;
    static bool initedLightInViewSpace;
    static s8 init;

    nlVector3 transformedDir;
    nlVector3 viewVec;
    nlMatrix4 viewRotMat;
    nlMatrix4 matZ;
    nlMatrix4 matY;

    void* pLightData = g_pCameraRelativeLightData;

    if (!init)
    {
        initedLightInViewSpace = false;
        init = true;
    }

    if (!initedLightInViewSpace)
    {
        nlVector3 initialDirection = { 1.0f, 0.0f, 0.0f };

        nlMakeRotationMatrixY(matY, 0.7853982f);
        nlMakeRotationMatrixZ(matZ, -0.69813174f);
        nlMultDirVectorMatrix(keyLightInViewSpace, initialDirection, matY);
        nlMultDirVectorMatrix(keyLightInViewSpace, keyLightInViewSpace, matZ);

        nlMakeRotationMatrixY(matY, 0.5235988f);
        nlMakeRotationMatrixZ(matZ, 0.34906587f);
        nlMultDirVectorMatrix(fillLightInViewSpace, initialDirection, matY);
        nlMultDirVectorMatrix(fillLightInViewSpace, fillLightInViewSpace, matZ);

        initedLightInViewSpace = true;
    }

    cCameraManager::GetViewVector(viewVec);

    f32 angle = nlATan2f(viewVec.f.y, viewVec.f.x);
    u16 u16Angle = (u16)(s32)(angle * 10430.378f);
    f32 radAngle = (f32)u16Angle * 0.0000958738f;

    nlMakeRotationMatrixZ(viewRotMat, radAngle);

    s32 stadium = nlSingleton<GameInfoManager>::s_pInstance->GetStadium();
    StadiumLightingParams* params = &gStadiumGameObjectLightingParams[stadium];

    GameObjectLightArray* pLights = (GameObjectLightArray*)glUserGetData(pLightData);

    nlMultDirVectorMatrix(transformedDir, keyLightInViewSpace, viewRotMat);

    nlVec3Set(pLights->lights[0].worldPosition, -transformedDir.f.x, -transformedDir.f.y, -transformedDir.f.z);
    pLights->lights[0].intensity = params->keyLightIntensity;

    nlMultDirVectorMatrix(transformedDir, fillLightInViewSpace, viewRotMat);

    nlVec3Set(pLights->lights[1].worldPosition, -transformedDir.f.x, -transformedDir.f.y, -transformedDir.f.z);
    pLights->lights[1].intensity = params->fillLightIntensity;
}

/**
 * Offset/Address/Size: 0x0 | 0x8012A83C | size: 0x34
 */
u32 GetGameObjectLightRamp()
{
    return gStadiumGameObjectLightingParams[nlSingleton<GameInfoManager>::s_pInstance->GetStadium()].lightRamp;
}

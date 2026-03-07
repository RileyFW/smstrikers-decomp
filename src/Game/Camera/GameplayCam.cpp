#include "Game/Camera/GameplayCam.h"

#include "Game/GameInfo.h"
#include "Game/Team.h"
#include "Game/AI/Fielder.h"
#include "Game/AI/AiUtil.h"
#include "NL/nlTask.h"
#include "NL/gl/glMatrix.h"
#include "math.h"

f32 CANT_COLLIDE = *(f32*)__float_max;
extern CameraData gCameraData[];
extern bool gGameplayCameraInReplay;

/**
 * Offset/Address/Size: 0x28 | 0x801AA440 | size: 0x14
 */
KnotTableBlendEntry::KnotTableBlendEntry()
{
}

/**
 * Offset/Address/Size: 0xCC8 | 0x801AA308 | size: 0x110
 */
GameplayCamera::GameplayCamera()
{
}

/**
 * Offset/Address/Size: 0xB24 | 0x801AA164 | size: 0x1A4
 */
void GameplayCamera::CalcDynamicZoom()
{
    m_fDesiredZoom = 0.0f;

    for (int i = 0; i < 2; i++)
    {
        int numFieldersInInnerZone = 0;
        int numFieldersInMidZone = 0;

        for (int j = 0; j < 4; j++)
        {
            cFielder* fielder = g_pTeams[i]->GetFielder(j);
            nlVector3 screenPosition = fielder->m_v3ScreenPosition;

            screenPosition.f.x = fabsf(screenPosition.f.x);
            screenPosition.f.y = fabsf(screenPosition.f.y);

            if (screenPosition.f.x <= 0.75f && screenPosition.f.y <= 0.75f)
            {
                numFieldersInInnerZone++;
            }

            if (screenPosition.f.x <= 1.0f && screenPosition.f.y <= 1.0f)
            {
                numFieldersInMidZone++;
            }
        }

        int numAssignedControllers = g_pTeams[i]->GetNumAssignedControllers();
        int teamDesiredNumFieldersOnScreen = 0;
        if (numAssignedControllers != 0)
        {
            teamDesiredNumFieldersOnScreen = numAssignedControllers >= 1 ? numAssignedControllers : 1;
        }

        Goalie* goalie = g_pTeams[i]->GetGoalie();
        if (goalie->m_pBall != NULL)
        {
            teamDesiredNumFieldersOnScreen = teamDesiredNumFieldersOnScreen >= 4 ? teamDesiredNumFieldersOnScreen : 4;
        }

        float currentZoom;
        float teamDesiredZoom = 0.0f;
        if (teamDesiredNumFieldersOnScreen > 0)
        {
            if (numFieldersInInnerZone >= teamDesiredNumFieldersOnScreen)
            {
                teamDesiredZoom = 0.0f;
            }
            else if (numFieldersInMidZone < teamDesiredNumFieldersOnScreen)
            {
                teamDesiredZoom = 1.0f;
            }
            else
            {
                teamDesiredZoom = m_fZoom;
            }
        }

        currentZoom = m_fDesiredZoom;
        currentZoom = (currentZoom >= teamDesiredZoom) ? currentZoom : teamDesiredZoom;
        m_fDesiredZoom = currentZoom;
    }
}

/**
 * Offset/Address/Size: 0x8CC | 0x801A9F0C | size: 0x258
 * TODO: 98.57% match - float register allocation differs (omega=f6 vs target f8,
 * change=f8 vs target f6) due to MWCC graph coloring. All instructions correct.
 * File uses -inline deferred which may contribute to the register allocation difference.
 */
void GameplayCamera::Update(float deltaTime)
{
    m_bDynamicZoom = nlSingleton<GameInfoManager>::s_pInstance->mUserInfo.mVisualOptions.mIsAutoZoomCamera;
    m_fDesiredZoom = 1.0f - nlSingleton<GameInfoManager>::s_pInstance->mUserInfo.mVisualOptions.mCameraZoomLevel;

    if (nlSingleton<GameInfoManager>::s_pInstance->mUserInfo.mVisualOptions.mIsWidescreen)
    {
        m_nearZoom.m_CameraData = gCameraData + 2;
        m_farZoom.m_CameraData = gCameraData + 3;
    }
    else
    {
        m_nearZoom.m_CameraData = gCameraData;
        m_farZoom.m_CameraData = gCameraData + 1;
    }

    m_nearZoom.Update(deltaTime, m_ForceNeutralAndNearZoom);
    m_farZoom.Update(deltaTime, m_ForceNeutralAndNearZoom);

    if (m_ForceNeutralAndNearZoom)
    {
        m_fZoom = 0.0f;
    }
    else
    {
        bool gamePaused = (nlTaskManager::m_pInstance->m_CurrState == 1);

        if (m_bDynamicZoom && !gamePaused && !gGameplayCameraInReplay)
        {
            CalcDynamicZoom();
        }

        float clampedDesiredZoom = Interpolate(0.2f, 0.7f, m_fDesiredZoom);
        float smoothTime;

        if (gamePaused)
        {
            smoothTime = 0.1f;
        }
        else
        {
            smoothTime = 0.75f;
        }

        float omega = 2.0f / smoothTime;
        float x = omega * deltaTime;
        float exp = 1.0f / ((x * (0.235f * x * x)) + ((0.48f * x * x) + (1.0f + x)));
        float change = m_fZoom - clampedDesiredZoom;
        float currentVelocity = m_fZoomSeekSpeed;
        float temp = deltaTime * ((change * omega) + currentVelocity);

        m_fZoomSeekSpeed = exp * (currentVelocity - (omega * temp));
        m_fZoom = (exp * (change + temp)) + clampedDesiredZoom;
    }

    float zoom = m_fZoom;
    float inverseZoom = 1.0f - zoom;

    m_v3Target.f.x = (inverseZoom * m_nearZoom.m_v3Target.f.x) + (zoom * m_farZoom.m_v3Target.f.x);
    m_v3Target.f.y = (inverseZoom * m_nearZoom.m_v3Target.f.y) + (zoom * m_farZoom.m_v3Target.f.y);
    m_v3Target.f.z = (inverseZoom * m_nearZoom.m_v3Target.f.z) + (zoom * m_farZoom.m_v3Target.f.z);

    zoom = m_fZoom;
    inverseZoom = 1.0f - zoom;

    m_v3Camera.f.x = (inverseZoom * m_nearZoom.m_v3Camera.f.x) + (zoom * m_farZoom.m_v3Camera.f.x);
    m_v3Camera.f.y = (inverseZoom * m_nearZoom.m_v3Camera.f.y) + (zoom * m_farZoom.m_v3Camera.f.y);
    m_v3Camera.f.z = (inverseZoom * m_nearZoom.m_v3Camera.f.z) + (zoom * m_farZoom.m_v3Camera.f.z);

    m_fFOV = Interpolate(m_nearZoom.m_CameraData->fov, m_farZoom.m_CameraData->fov, m_fZoom);

    glMatrixLookAt(m_matView, m_v3Camera, m_v3Target, mUpVector);
}

/**
 * Offset/Address/Size: 0x874 | 0x801A9EB4 | size: 0x58
 */
void GameplayCamera::Reactivate()
{
    m_nearZoom.CalcDesiredTarget();
    m_nearZoom.m_fDampenedTargetX = m_nearZoom.m_fDesiredTargetX;
    m_nearZoom.m_fDampenedTargetY = m_nearZoom.m_fDesiredTargetY;

    m_farZoom.CalcDesiredTarget();
    m_farZoom.m_fDampenedTargetX = m_farZoom.m_fDesiredTargetX;
    m_farZoom.m_fDampenedTargetY = m_farZoom.m_fDesiredTargetY;
}

/**
 * Offset/Address/Size: 0x470 | 0x801A9AB0 | size: 0x404
 */
void GameplayCameraZoomLevel::CalcDesiredTarget()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x5C | 0x801A969C | size: 0x414
 */
void GameplayCameraZoomLevel::Update(float, bool)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801A9640 | size: 0x5C
 */
GameplayCamera::~GameplayCamera()
{
}

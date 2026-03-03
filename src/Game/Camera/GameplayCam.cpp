#include "Game/Camera/GameplayCam.h"

#include "Game/Team.h"
#include "Game/AI/Fielder.h"
#include "math.h"

f32 CANT_COLLIDE = *(f32*)__float_max;

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
 */
void GameplayCamera::Update(float)
{
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

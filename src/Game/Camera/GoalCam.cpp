#include "Game/Camera/GoalCam.h"

static bool gbCamFreeze;
static s32 gnCamType;

f32 gfDistance = 10.0f;
f32 gfHeight = 3.0f;
f32 gfSideMult = 2.0f;
f32 gfSideBias = 0.4f;
f32 gfCamDir = 3.1415927f;
f32 gfCamTilt = 0.1f;
f32 gfCamDist = 14.0f;

/**
 * Offset/Address/Size: 0x6CC | 0x801AAC68 | size: 0x7C
 */
GoalCamera::GoalCamera()
{
    m_vecTarget.f.x = 0.0f;
    m_vecTarget.f.y = 0.0f;
    m_vecTarget.f.z = 0.0f;
    Update(0.0f);
}

/**
 * Offset/Address/Size: 0x670 | 0x801AAC0C | size: 0x5C
 */
GoalCamera::~GoalCamera()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801AA59C | size: 0x670
 */
void GoalCamera::Update(float)
{
    // TODO: decompile
}

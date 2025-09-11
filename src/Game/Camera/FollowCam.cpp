#include "Game/Camera/FollowCam.h"
#include "Game/Ball.h"
#include "Game/Team.h"
#include "Game/ReplayManager.h"

#include "NL/gl/glMatrix.h"

// extern s32 currentlySelectedTarget$647;
extern u8 g_bProfiling;
extern u8 g_bTweaking;
// extern u8 init$648;
static f32 g_fDistanceSeek = 0.5f;
static f32 g_fMaxDistance = 40.0f;
static f32 g_fMinDistance = 2.0f;
static f32 g_fFollowCamOOISeek = 0.1f;
static f32 g_fFollowCamOOIZSeek = 0.025f;
static f32 g_fFollowCamMaxRotPerFrame = 400.0f;
static u16 g_aFollowCamMaxPitch = 0x3555;
static u16 g_aFollowCamMinPitch = 0x4B9;
static f32 g_fFollowCamMaxZOffset = 3.0f;
static f32 g_fFollowCamMinZOffset = 0.6f;

inline float nlLerp(float a, float b, float t)
{
    return a + t * (b - a);
}

/**
 * Offset/Address/Size: 0x668 | 0x801A9580 | size: 0x90
 */
cFollowCamera::cFollowCamera(cFollowCamera::FollowTarget followTarget)
{
    m_FollowTarget = followTarget;
    m_bOOISet = false;
    m_aFacingDirection = 0;
    m_aPitch = 0x1000;
    m_fOOIDistance = 5.0f;
    m_bPitchLimits = true;
    m_bControlsLocked = false;

    m_matView.SetIdentity();
}

/**
 * Offset/Address/Size: 0x0 | 0x801A8F18 | size: 0x668
 */
void cFollowCamera::Update(float dt)
{
    cGlobalPad* pad = cPadManager::GetPad(0);
    if (!pad || !pad->IsConnected())
    {
        m_matView.SetIdentity();
        return;
    }

    switch (m_FollowTarget)
    {
    case FOLLOW_CHARACTER:
    {
        cPlayer* controlled = nullptr;
        for (int t = 0; t < 2 && !controlled; ++t)
            controlled = g_pTeams[t]->GetControlledPlayer(pad);

        if (!controlled)
        {
            m_matView.SetIdentity();
            return;
        }

        m_v3OOI = controlled->m_v3Position;
        break;
    }

    case FOLLOW_BALL:
    {
        m_v3OOI = *g_pBall->GetDrawablePosition();
        break;
    }

    case FOLLOW_SELECTABLE:
    {
        RenderSnapshot* snap = ReplayManager::Instance()->mRender;
        static s32 currentlySelectedTarget = 0;

        const int count = snap->NumDrawableObjects();

        if (!g_bTweaking && dt > 0.0f)
        {
            if (cPadManager::GetPad(0)->JustPressed(0x400, false) && !g_bTweaking)
            {
                int v = (currentlySelectedTarget + count - 1);
                currentlySelectedTarget = v - (v / count) * count; // mod
            }
            if (cPadManager::GetPad(0)->JustPressed(0x800, false) && !g_bTweaking)
            {
                int v = currentlySelectedTarget + 1;
                currentlySelectedTarget = v - (v / count) * count; // mod
            }
        }

        m_v3OOI = snap->GetPositionForDrawableObject(currentlySelectedTarget);
        break;
    }

    case FOLLOW_ANIM_VIEWER_CHARACTER:
        // The assembly simply falls through without changing m_v3OOI in this mode.
        // Keep whatever the tool/viewer has set externally.
        break;

    default:
        m_matView.SetIdentity();
        return;
    }

    const float minD = g_fMinDistance;
    const float maxD = g_fMaxDistance;
    const float frac = (m_fOOIDistance - minD) / (maxD - minD);
    const float zOff = nlLerp(g_fFollowCamMinZOffset, g_fFollowCamMaxZOffset, frac);
    m_v3OOI.f.z += zOff;

    m_v3OOIDampenedPrev = m_v3OOIDampened;

    const float seekXY = g_fFollowCamOOISeek;
    const float keepXY = 1.0f - seekXY;
    m_v3OOIDampened.f.x = seekXY * m_v3OOI.f.x + keepXY * m_v3OOIDampened.f.x;
    m_v3OOIDampened.f.y = seekXY * m_v3OOI.f.y + keepXY * m_v3OOIDampened.f.y;

    const float seekZ = g_fFollowCamOOIZSeek;
    const float keepZ = 1.0f - seekZ;
    m_v3OOIDampened.f.z = seekZ * m_v3OOI.f.z + keepZ * m_v3OOIDampened.f.z;

    const float aL = cPadManager::GetPad(0)->GetPressure(0x400, false);
    const float aR = cPadManager::GetPad(0)->GetPressure(0x800, false);
    if ((aL > 0.0f && cPadManager::GetPad(0)->JustPressed(0x800, false))
        || (aR > 0.0f && cPadManager::GetPad(0)->JustPressed(0x400, false)))
    {
        m_bControlsLocked = !m_bControlsLocked;
    }

    if (!g_bTweaking && !g_bProfiling && !m_bControlsLocked)
    {
        const float scroll = pad->AnalogLeftY();
        m_fOOIDistance -= g_fDistanceSeek * scroll;
    }

    // Clamp distance to [min,max]
    if (m_fOOIDistance > maxD)
        m_fOOIDistance = maxD;
    else if (m_fOOIDistance < minD)
        m_fOOIDistance = minD;

    {
        const float yawDeltaUnits = pad->AnalogRightX();
        const float pitchDeltaUnits = pad->AnalogRightY();
        m_aFacingDirection = static_cast<u16>(m_aFacingDirection + static_cast<int>(g_fFollowCamMaxRotPerFrame * yawDeltaUnits));
        m_aPitch = static_cast<u16>(m_aPitch + static_cast<int>(g_fFollowCamMaxRotPerFrame * pitchDeltaUnits));

        if (m_bPitchLimits)
        {
            if (m_aPitch > g_aFollowCamMaxPitch)
                m_aPitch = g_aFollowCamMaxPitch;
            if (m_aPitch < g_aFollowCamMinPitch)
                m_aPitch = g_aFollowCamMinPitch;
        }
    }

    {
        const float vx = -m_matView.m[0][2];
        const float vy = -m_matView.m[0][1];

        const float dx = (m_v3OOIDampened.f.x - m_v3OOIDampenedPrev.f.x);
        const float dy = (m_v3OOIDampened.f.y - m_v3OOIDampenedPrev.f.y);

        const float denom = nlSqrt(1.0f + vx * vx + vy * vy, true);
        const float t = (1.0f + (vx * dy + vy * dx)) / (denom * denom);

        float rx = dx - t * vx;
        float ry = dy - t * vy;
        const float len = nlSqrt(1.0f + rx * rx + ry * ry, true);

        const float invDist = len / m_fOOIDistance;
        const float angleShortF = 65536.0f * invDist;
        const u16 angleShort = static_cast<u16>(static_cast<int>(angleShortF));

        const float signCheck = (ry * vy - rx * vx);
        if (signCheck <= 0.0f)
            m_aFacingDirection = static_cast<u16>(m_aFacingDirection - angleShort);
        else
            m_aFacingDirection = static_cast<u16>(m_aFacingDirection + angleShort);
    }

    nlVec3Set(m_v3CameraPosition, m_fOOIDistance, 0.0f, 0.0f);

    nlMatrix4 rot; // temp
    {
        const float kAngle = /* radPerShort */ (2.0f * 3.14159265358979323846f / 65536.0f);

        nlMakeRotationMatrixY(rot, -static_cast<float>(static_cast<s16>(m_aPitch)) * kAngle);
        nlMultPosVectorMatrix(m_v3CameraPosition, m_v3CameraPosition, rot);

        nlMakeRotationMatrixZ(rot, static_cast<float>(static_cast<u16>(m_aFacingDirection)) * kAngle);
        nlMultPosVectorMatrix(m_v3CameraPosition, m_v3CameraPosition, rot);
    }

    m_v3CameraPosition.f.x += m_v3OOIDampened.f.x;
    m_v3CameraPosition.f.y += m_v3OOIDampened.f.y;
    m_v3CameraPosition.f.z += m_v3OOIDampened.f.z;

    glMatrixLookAt(m_matView, m_v3CameraPosition, m_v3OOIDampened, mUpVector);
}

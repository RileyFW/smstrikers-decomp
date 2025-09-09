#include "Game/Camera/GoalCam.h"

#include "NL/gl/glMatrix.h"
#include "NL/globalpad.h"

#include "Game/Ball.h"
#include "Game/Field.h"

// static bool init$541;
// static f32 fDir;
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

static inline u16 RadToAng16(f32 r)
{
    return (u16)(f32)(10430.378f * r);
}

/**
 * Offset/Address/Size: 0x0 | 0x801AA59C | size: 0x670
 */
void GoalCamera::Update(float /*dt*/)
{
    nlVector3 up;
    up.f.x = 0.0f;
    up.f.y = 0.0f;
    up.f.z = 1.0f;

    if (gnCamType == 0)
    {
        if (g_pBall->m_tShotTimer.m_uPackedTime == 0)
        {
            if (g_pBall->GetOwnerGoalie() != 0)
            {
                return;
            }
        }
    }

    if (gbCamFreeze != 0)
    {
        return;
    }

    static f32 fDir = 1.0;

    nlVector3 ballPos;
    {
        cPlayer* player = g_pBall->m_pOwner;
        if (player == NULL || player->m_eClassType == GOALIE)
        {
            ballPos = g_pBall->m_v3Position;
        }
        else
        {
            ballPos = player->m_v3Position;
        }
    }

    nlVector3 prevEye;
    nlVector3 prevCtr;
    nlVector3 newTarget;
    nlVector3 newEye;

    if (gnCamType == 0)
    {
        newTarget.f.x = fDir * cField::GetGoalLineX((unsigned int)1);
        newTarget.f.y = 0.0f;
        newTarget.f.z = 0.0f;

        nlVector3 dir;
        dir.f.x = ballPos.f.x - newTarget.f.x;
        dir.f.y = ballPos.f.y - newTarget.f.y;
        dir.f.z = ballPos.f.z - newTarget.f.z;

        f32 invLen = nlRecipSqrt(dir.f.x * dir.f.x + dir.f.y * dir.f.y + dir.f.z * dir.f.z, 1);
        dir.f.x *= invLen;
        dir.f.y *= invLen;
        dir.f.z *= invLen;

        newEye.f.x = ballPos.f.x + gfDistance * dir.f.x;
        newEye.f.y = ballPos.f.y + gfDistance * dir.f.y;
        newEye.f.z = gfHeight;

        const f32 a = 0.9f, b = 0.1f;
        newEye.f.x = a * prevEye.f.x + b * newEye.f.x;
        newEye.f.y = a * prevEye.f.y + b * newEye.f.y;
        newEye.f.z = a * prevEye.f.z + b * newEye.f.z;
    }
    else if (gnCamType == 1)
    {
        newTarget = ballPos;

        nlVector3_ v = { 1.0f, 0.0f, 0.3f };
        f32 invLen = nlRecipSqrt(v.f[0] * v.f[0] + v.f[1] * v.f[1] + v.f[2] * v.f[2], 1);
        v.f[0] *= invLen;
        v.f[1] *= invLen;
        v.f[2] *= invLen;
        nlVector3 fwd;
        fwd.f.x = -v.f[0];
        fwd.f.y = -v.f[1];
        fwd.f.z = v.f[2];

        newEye.f.x = newTarget.f.x + gfDistance * fwd.f.x;
        newEye.f.y = newTarget.f.y + gfDistance * fwd.f.y;
        newEye.f.z = newTarget.f.z + gfHeight;

        const f32 a = 0.8f, b = 0.2f;
        newEye.f.x = a * prevEye.f.x + b * newEye.f.x;
        newEye.f.y = a * prevEye.f.y + b * newEye.f.y;
        newEye.f.z = a * prevEye.f.z + b * newEye.f.z;
        newTarget.f.x = a * prevCtr.f.x + b * newTarget.f.x;
        newTarget.f.y = a * prevCtr.f.y + b * newTarget.f.y;
        newTarget.f.z = a * prevCtr.f.z + b * newTarget.f.z;
    }
    else
    {
        newTarget.f.x = fDir * cField::GetGoalLineX((unsigned int)1);
        newTarget.f.y = 0.0f;
        newTarget.f.z = gfHeight;

        f32 sDir, cDir, sTilt, cTilt;
        nlSinCos(&sDir, &cDir, RadToAng16(gfCamDir));
        nlSinCos(&sTilt, &cTilt, RadToAng16(gfCamTilt));

        nlVector3 offs;
        offs.f.x = sTilt * (gfCamDist * cDir);
        offs.f.y = sTilt * (gfCamDist * sDir);
        offs.f.z = gfCamDist * cTilt;

        newEye.f.x = newTarget.f.x + offs.f.x;
        newEye.f.y = newTarget.f.y + offs.f.y;
        newEye.f.z = newTarget.f.z + offs.f.z;

        const f32 a = 0.9f, b = 0.1f;
        newEye.f.x = a * prevEye.f.x + b * newEye.f.x;
        newEye.f.y = a * prevEye.f.y + b * newEye.f.y;
        newEye.f.z = a * prevEye.f.z + b * newEye.f.z;

        ballPos.f.x = newEye.f.x;
        ballPos.f.y = newEye.f.y;
        ballPos.f.z = gfHeight;
    }

    m_vecCamera = newEye;
    m_vecTarget = newTarget;

    {
        cGlobalPad* pad0 = cPadManager::GetPad(0);
        if (pad0 && pad0->IsPressed(0x800, 0))
        {
            nlVector3 eye, center;

            if (gnCamType != 1)
            {
                const f32 k = gfSideBias;
                const f32 k1 = 1.0f - k;

                f32 dx = m_vecTarget.f.x - ballPos.f.x;
                f32 dy = m_vecTarget.f.y - ballPos.f.y;

                center.f.x = k1 * m_vecTarget.f.x + k * ballPos.f.x;
                center.f.y = k1 * m_vecTarget.f.y + k * ballPos.f.y;
                center.f.z = k1 * m_vecTarget.f.z + k * ballPos.f.z;

                eye.f.x = gfSideMult * dy + center.f.x;
                eye.f.y = gfSideMult * (-dx) + center.f.y;
                eye.f.z = gfHeight;

                glMatrixLookAt(m_matView, eye, center, up);
                return;
            }
            else
            {
                nlVector3 fwd;
                {
                    nlVector3_ v = { 1.0f, 0.0f, 0.3f };
                    f32 invLen = nlRecipSqrt(v.f[0] * v.f[0] + v.f[1] * v.f[1] + v.f[2] * v.f[2], 1);
                    v.f[0] *= invLen;
                    v.f[1] *= invLen;
                    v.f[2] *= invLen;
                    fwd.f.x = -v.f[0];
                    fwd.f.y = -v.f[1];
                    fwd.f.z = v.f[2];
                }

                center = m_vecTarget;
                eye.f.x = center.f.x + gfDistance * fwd.f.x;
                eye.f.y = center.f.y + gfDistance * fwd.f.y;
                eye.f.z = center.f.z + gfHeight;

                glMatrixLookAt(m_matView, eye, center, up);
                return;
            }
        }
    }

    glMatrixLookAt(m_matView, m_vecCamera, m_vecTarget, up);
}

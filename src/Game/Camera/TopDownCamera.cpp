#include "Game/Camera/TopDownCamera.h"
#include "NL/nlMath.h"
#include "NL/gl/glMatrix.h"

#include "Game/Ball.h"
#include "Game/Field.h"

// float sfCameraHeight = 21.0f;
float sfFov = 90.0f;
bool sbFocusOnBall = false;

extern cBall* g_pBall;

// /**
//  * Offset/Address/Size: 0x18 | 0x801A60EC | size: 0x8
//  */
// void TopDownCamera::GetFOV() const
// {
// }

// /**
//  * Offset/Address/Size: 0x10 | 0x801A60E4 | size: 0x8
//  */
// void TopDownCamera::GetCameraPosition() const
// {
// }

// /**
//  * Offset/Address/Size: 0x8 | 0x801A60DC | size: 0x8
//  */
// void TopDownCamera::GetTargetPosition() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801A60D4 | size: 0x8
//  */
// void TopDownCamera::GetType()
// {
// }

/**
 * Offset/Address/Size: 0x174 | 0x801A6074 | size: 0x60
 */
TopDownCamera::TopDownCamera()
{
    m_Fov = sfFov;

    nlVec3Set(m_Position, 0.0f, -1.0f, 21.0f);

    // m_Position.unk0 = 0.0f;
    nlVec3Set(m_Target, 0.0f, 0.0f, 0.0f);

    // m_Target.unk0 = 0.0f;
    // m_Target.unk4 = 0.0f;
    // m_Target.unk8 = 0.0f;
}

/**
 * Offset/Address/Size: 0xBC | 0x801A5FBC | size: 0xB8
 */
void TopDownCamera::Update(float)
{
    // If focusing ball: copy its world position into Target; else zero target. :contentReference[oaicite:16]{index=16}
    if (sbFocusOnBall)
    {
        // Load from g_pBall + 0x40 .. 0x48
        // const nlVector3& p = reinterpret_cast<BallPosView*>(g_pBall)->pos;
        m_Target = g_pBall->m_v3Position;
    }
    else
    {
        nlVec3Set(m_Target, 0.f, 0.f, 0.f);
        // m_Target.unk0 = 0.0f; // "@197" = 0.0f               :contentReference[oaicite:17]{index=17}
        // m_Target.unk4 = 0.0f;
        // m_Target.unk8 = 0.0f;
    }

    // FOV set to 90 each frame (uses sdata2 "@198" = 90).   :contentReference[oaicite:18]{index=18}
    m_Fov = 90.0f;

    // Camera sits above target, slightly offset in -Y by 1.0f, Z = height.  :contentReference[oaicite:19]{index=19}
    m_Position.f.x = m_Target.f.x;
    m_Position.f.y = m_Target.f.y - 1.0f; // "@199" = 1.0f               :contentReference[oaicite:20]{index=20}
    m_Position.f.z = 21.0f;               // sfCameraHeight;

    // Clamp X within ±cField::GetGoalLineX(1).              :contentReference[oaicite:21]{index=21}
    {
        float gx = cField::GetGoalLineX((unsigned int)1);
        if (m_Position.f.x > gx)
            m_Position.f.x = gx;

        float ng = -gx;
        if (m_Position.f.x < ng)
            m_Position.f.x = ng;
    }
}

/**
 * Offset/Address/Size: 0x5C | 0x801A5F5C | size: 0x60
 */
const nlMatrix4& TopDownCamera::GetViewMatrix() const
{
    nlVector3_ up = { 0.0f, 1.0f, 0.0f };
    glMatrixLookAt((nlMatrix4&)m_View, m_Position, m_Target, (nlVector3&)up);
    return m_View;
}

/**
 * Offset/Address/Size: 0x0 | 0x801A5F00 | size: 0x5C
 */
TopDownCamera::~TopDownCamera()
{
}

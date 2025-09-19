#include "Game/Camera/rumblefilter.h"

#include "NL/nlTask.h"
#include "Game/Sys/eventman.h"

/**
 * Offset/Address/Size: 0x3D8 | 0x801A65F4 | size: 0x60
 */
cRumbleFilter::cRumbleFilter()
{
    nlVec2Set(v2Pos0, 0.0f, 0.0f);
    nlVec2Set(v2Pos1, 0.0f, 0.0f);
    nlVec2Set(v2Vel0, 0.0f, 0.0f);
    nlVec2Set(v2Vel1, 0.0f, 0.0f);
    nlVec2Set(v2Force0, 0.0f, 0.0f);
    nlVec2Set(v2Force1, 0.0f, 0.0f);
    Ks = 5000.0f;
    Kd = 10.0f;
}

/**
 * Offset/Address/Size: 0x334 | 0x801A6550 | size: 0xA4
 */
void cRumbleFilter::Filter(const nlMatrix4& matViewIn, nlMatrix4& matViewOut)
{
    matViewOut = matViewIn;
    matViewOut.f.m41 += v2Pos1.f.x;
    matViewOut.f.m42 += v2Pos1.f.y;
}

/**
 * Offset/Address/Size: 0x2D4 | 0x801A64F0 | size: 0x60
 */
void cRumbleFilter::Reset()
{
    nlVec2Set(v2Pos0, 0.0f, 0.0f);
    nlVec2Set(v2Pos1, 0.0f, 0.0f);
    nlVec2Set(v2Vel0, 0.0f, 0.0f);
    nlVec2Set(v2Vel1, 0.0f, 0.0f);
    nlVec2Set(v2Force0, 0.0f, 0.0f);
    nlVec2Set(v2Force1, 0.0f, 0.0f);
    g_pEventManager->CreateValidEvent(0x58, 0x14);
}

/**
 * Offset/Address/Size: 0x0 | 0x801A621C | size: 0x284
 */
void cRumbleFilter::Update(float dt)
{
    float fHTerm;
    float fDTerm;

    if (nlTaskManager::m_pInstance->m_CurrState == 1)
        return;

    dt = (dt <= 0.02f) ? dt : 0.02f;

    nlVector2 _p;
    _p.f.y = v2Pos0.f.y - v2Pos1.f.y;
    _p.f.x = v2Pos0.f.x - v2Pos1.f.x;
    // nlVec2Set(_p, v2Pos0.f.x - v2Pos1.f.x, v2Pos0.f.y - v2Pos1.f.y);
    const float temp = (_p.f.x * _p.f.x) + (_p.f.y * _p.f.y);
    const float len = nlSqrt(temp, true);
    fHTerm = Ks * len;

    nlVector2 _dv;
    _dv.f.y = v2Vel0.f.y - v2Vel1.f.y;
    _dv.f.x = v2Vel0.f.x - v2Vel1.f.x;
    // nlVec2Set(_dv, v2Vel0.f.x - v2Vel1.f.x, v2Vel0.f.y - v2Vel1.f.y);
    const float proj = (_dv.f.x * _p.f.x) + (_dv.f.y * _p.f.y);
    // const float proj = (v2Vel0.f.x - v2Vel1.f.x) * _p.f.x + (v2Vel0.f.y - v2Vel1.f.y) * _p.f.y;
    fDTerm = (len == 0.f) ? 0.0f : (proj * Kd) / len;

    float ux, uy;
    ux = 0.0f;
    if (len == 0.f)
    {
        uy = 0.0f;
    }
    else
    {
        static bool bIsBouncing = false;

        if (len < 0.01f)
        {
            if (bIsBouncing)
            {
                g_pEventManager->CreateValidEvent(0x58, 0x14);
                bIsBouncing = false;
            }
        }
        else
        {
            bIsBouncing = true;
        }

        const float invLen = 1.0f / len;
        ux = invLen * _p.f.x; // f1 path in asm
        uy = invLen * _p.f.y; // f5 path in asm
    }

    nlVec2Set(v2Force0, 0.f, 0.f);
    nlVec2Set(v2Force1, 0.f, 0.f);

    nlVec2Set(v2Force0,
        v2Force0.f.x + -(fHTerm + fDTerm) * ux,
        v2Force0.f.y + -(fHTerm + fDTerm) * uy);
    nlVec2Set(v2Force1,
        v2Force1.f.x - -(fHTerm + fDTerm) * ux,
        v2Force1.f.y - -(fHTerm + fDTerm) * uy);

    float factor0 = 0.f;
    nlVec2Set(v2Vel0,
        v2Vel0.f.x + (dt * (factor0 * v2Force0.f.x)),
        v2Vel0.f.y + (dt * (factor0 * v2Force0.f.y)));
    nlVec2Set(v2Pos0,
        v2Pos0.f.x + (dt * v2Vel0.f.x),
        v2Pos0.f.y + (dt * v2Vel0.f.y));

    float factor1 = 1.f;
    nlVec2Set(v2Vel1,
        v2Vel1.f.x + (dt * (factor1 * v2Force1.f.x)),
        v2Vel1.f.y + (dt * (factor1 * v2Force1.f.y)));
    nlVec2Set(v2Pos1,
        v2Pos1.f.x + (dt * v2Vel1.f.x),
        v2Pos1.f.y + (dt * v2Vel1.f.y));
}

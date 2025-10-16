#include "Game/Field.h"

#include "math.h"

extern cBall* g_pBall;

cNet* cField::mpNet[2]; // = { nullptr, nullptr };

nlVector3 cField::mv3FieldPosition = { 20.60211f, 12.0825f, 0.0f };
nlVector3 cField::mSidelines[4] = { { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } };

extern "C" void CollideWithWallCallback__5cBallFv(); // forward decl

Corner cField::mCorners = { 0.0f, 0.0f, 0.000000000000000000000000000000000000000022959f, 3.0f, 0.0f, 0.0f, 2.0078125f, 3.0f, 0.0f, 0.0f, &CollideWithWallCallback__5cBallFv, 3.0f, 0.0f, 0.0f, -2.0f, 3.0f };
// sCornerSegment cField::mCorners[4] = {
//     // Corner 0
//     {
//         { 0.0f, 0.0f }, // vCenter
//         0,              // thetaStart
//         3,              // thetaEnd
//         0.0f            // fRadius
//     },

//     // Corner 1
//     {
//         { 0.0f, 0.0f }, // vCenter
//         0,              // thetaStart
//         0,              // thetaEnd
//         2.0078125f      // fRadius
//     },

//     // Corner 2
//     {
//         { 0.0f, 0.0f }, // vCenter (note: -0.0f in hex)
//         0,              // thetaStart
//         0,              // thetaEnd
//         0.0f            // fRadius
//     },

//     // Corner 3
//     {
//         { 0.0f, 0.0f }, // vCenter
//         0,              // thetaStart
//         0,              // thetaEnd
//         -2.0f           // fRadius
//     }
// };

float cField::mfPenaltyBoxX = 13.5f;
float cField::mfPenaltyBoxY = 4.5f;

/**
 * Offset/Address/Size: 0x1CC | 0x800192B0 | size: 0x28
 */
void cField::Init(cNet* net0, cNet* net1)
{
    mpNet[0] = net0;
    mpNet[1] = net1;
    net0->m_baseLocation.f.x = -mv3FieldPosition.f.x;
    net1->m_baseLocation.f.x = mv3FieldPosition.f.x;
}

/**
 * Offset/Address/Size: 0x1A4 | 0x80019288 | size: 0x28
 */
float cField::GetGoalLineX(float side)
{
    if (side > 0)
    {
        return mv3FieldPosition.f.x;
    }
    return -mv3FieldPosition.f.x;
}

/**
 * Offset/Address/Size: 0x180 | 0x80019264 | size: 0x24
 */
float cField::GetGoalLineX(unsigned int side)
{
    if (side > 0)
    {
        return mv3FieldPosition.f.x;
    }
    return -mv3FieldPosition.f.x;
}

/**
 * Offset/Address/Size: 0x154 | 0x80019238 | size: 0x2C
 */
float cField::GetSidelineY(unsigned int side)
{
    if (side > 0)
    {
        return mv3FieldPosition.f.y;
    }
    return -mv3FieldPosition.f.y;
}

/**
 * Offset/Address/Size: 0x14C | 0x80019230 | size: 0x8
 */
float cField::GetCornerRadius()
{
    return 3.0f;
}

/**
 * Offset/Address/Size: 0x130 | 0x80019214 | size: 0x1C
 */
float cField::GetPenaltyBoxX(unsigned int side)
{
    return (side > 0) ? mfPenaltyBoxX : -mfPenaltyBoxX;
}

/**
 * Offset/Address/Size: 0x128 | 0x8001920C | size: 0x8
 */
float cField::GetPenaltyBoxY()
{
    return mfPenaltyBoxY;
}

/**
 * Offset/Address/Size: 0x108 | 0x800191EC | size: 0x20
 */
cNet* cField::GetNet(float side)
{
    if (side > 0.0f)
    {
        return mpNet[1];
    }
    return mpNet[0];
}

/**
 * Offset/Address/Size: 0xBC | 0x800191A0 | size: 0x4C
 */
bool cField::IsOnField(const nlVector3& location)
{
    if ((float)fabs(location.f.x) <= mv3FieldPosition.f.x)
    {
        if ((float)fabs(location.f.y) <= mv3FieldPosition.f.y)
        {
            return true;
        }
    }
    return false;
}

static inline float ClampMin(float v, float min)
{
    if (v >= min)
        return v;
    else
        return min; // forces: fcmpo / cror eq,gt,eq / bne / b / fmr
}

static inline float ClampMax(float v, float max)
{
    if (v <= max)
        return v;
    else
        return max; // forces: fcmpo / cror eq,lt,eq / bne / b / fmr
}

/**
 * Offset/Address/Size: 0x2C | 0x80019110 | size: 0x90
 */
void cField::FixOutOfBoundsPosition(nlVector3& v, float fMinDistanceFromWall)
{
    float min, max;
    float half;

    half = mv3FieldPosition.f.x;
    float& x = v.f.x;
    min = -half + fMinDistanceFromWall;
    max = half - fMinDistanceFromWall;
    v.f.x = ClampMax(ClampMin(x, min), max);

    float& y = v.f.y;
    half = mv3FieldPosition.f.y;
    min = -half + fMinDistanceFromWall;
    max = half - fMinDistanceFromWall;
    v.f.y = ClampMax(ClampMin(y, min), max);
}

/**
 * Offset/Address/Size: 0x0 | 0x800190E4 | size: 0x2C
 */
void cField::SetFieldDimensions(float, float, float)
{
    mpNet[0]->m_baseLocation.f.x = -mv3FieldPosition.f.x;
    mpNet[1]->m_baseLocation.f.x = mv3FieldPosition.f.x;
}

#include "Game/AI/AiUtil.h"

#include "math.h"

char* g_sPowerupNames[9] = {
    "GreenShell",
    "RedShell",
    "SpinyShell",
    "FreezeShell",
    "Banana",
    "BoBomb",
    "ChainChomp",
    "Mushroom",
    "Star"
};

f32 CANT_COLLIDE = *(f32*)__float_max;

/**
 * Offset/Address/Size: 0x1420 | 0x80006ECC | size: 0x90
 */
void MakePerpendicularPlane(const nlVector3& v3Positione, unsigned short aNormalAngle, nlVector4& v4Plane, float fPlaneOffset)
{
}

/**
 * Offset/Address/Size: 0x1354 | 0x80006E00 | size: 0xCC
 */
void MakePerpendicularPlane(const nlVector3& v3Position, const nlVector3& v3Normal, nlVector4& v4Plane, float fPlaneOffset)
{
}

/**
 * Offset/Address/Size: 0x1204 | 0x80006CB0 | size: 0x150
 */
void IsPointInCone(const nlVector3&, const nlVector3&, const nlVector3&, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x110C | 0x80006BB8 | size: 0xF8
 */
void SeekDirection(unsigned short, unsigned short, float, float, float)
{
}

/**
 * Offset/Address/Size: 0x10C0 | 0x80006B6C | size: 0x4C
 */
void SeekSpeed(float, float, float, float, float)
{
}

/**
 * Offset/Address/Size: 0xFA4 | 0x80006A50 | size: 0x11C
 */
void CalcInterceptXY(const nlVector3&, float, float, const nlVector3&, const nlVector3&, int&, float*)
{
}

/**
 * Offset/Address/Size: 0xED0 | 0x8000697C | size: 0xD4
 */
void ClipPositionToSidelines(nlVector3&, float)
{
}

/**
 * Offset/Address/Size: 0xDF4 | 0x800068A0 | size: 0xDC
 */
void TestCollision(float, const nlVector3&, const nlVector3&, float, const nlVector3&, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0xD90 | 0x8000683C | size: 0x64
 */
void Exp(float)
{
}

/**
 * Offset/Address/Size: 0xCE8 | 0x80006794 | size: 0xA8
 */
void GetClosingSpeed2D(const nlVector3&, const nlVector3&, const nlVector3&, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0xC0C | 0x800066B8 | size: 0xDC
 */
void GetClosingSpeed(const nlVector3&, const nlVector3&, const nlVector3&, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0xB74 | 0x80006620 | size: 0x98
 */
void GetLocalPoint(nlVector3& v3LocalPointOut, const nlVector3& v3WorldPointIn, const nlVector3& v3RefPosition, unsigned short aRefAngle)
{
    float fSin; // r1+0xC
    float fCos; // r1+0x8

    nlSinCos(&fSin, &fCos, aRefAngle);
    float dx = v3WorldPointIn.f.x - v3RefPosition.f.x;
    float dy = v3WorldPointIn.f.y - v3RefPosition.f.y;

    v3LocalPointOut.f.x = (fCos * dx) + (fSin * dy);
    v3LocalPointOut.f.y = (fCos * dy) - (fSin * dx);
    v3LocalPointOut.f.z = v3WorldPointIn.f.z;
}

/**
 * Offset/Address/Size: 0xABC | 0x80006568 | size: 0xB8
 */
void GetWorldPoint(nlVector3&, const nlVector3&, const nlVector3&, unsigned short)
{
}

/**
 * Offset/Address/Size: 0xA24 | 0x800064D0 | size: 0x98
 */
void RotateVectorZAxis(nlVector3&, const nlVector3&, unsigned short)
{
}

/**
 * Offset/Address/Size: 0x814 | 0x800062C0 | size: 0x210
 */
void GetRotationBetweenVectors(nlQuaternion&, const nlVector3&, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x70C | 0x800061B8 | size: 0x108
 */
void RotateVector(nlVector3&, const nlVector3&, nlQuaternion&)
{
}

/**
 * Offset/Address/Size: 0x700 | 0x800061AC | size: 0xC
 */
float Interpolate(float fMin, float fMax, float fPercent)
{
    return (fPercent * (fMax - fMin)) + fMin;
}

/**
 * Offset/Address/Size: 0x670 | 0x8000611C | size: 0x90
 */
void InterpolateRangeClamped(float, float, float, float, float)
{
}

/**
 * Offset/Address/Size: 0x5D0 | 0x8000607C | size: 0xA0
 */
void InterpolateRangeClamped(const nlVector2&, const nlVector2&, float)
{
}

/**
 * Offset/Address/Size: 0x580 | 0x8000602C | size: 0x50
 */
float NormalizeVal(float fromVal, const nlVector2& fromExtrema)
{
    if (fromExtrema.f.y == fromExtrema.f.x)
        return 1.0f;

    float t = (fromVal - fromExtrema.f.x) / (fromExtrema.f.y - fromExtrema.f.x);

    float lo = (t >= 0.0f) ? t : 0.0f;
    float res = (lo <= 1.0f) ? lo : 1.0f;

    return res;
}

/**
 * Offset/Address/Size: 0x538 | 0x80005FE4 | size: 0x48
 */
float NormalizeVal(float fromVal, float fromMin, float fromMax)
{
    if (fromMin == fromMax)
        return 1.0f;

    float t = (fromVal - fromMin) / (fromMax - fromMin);

    float lo = (t >= 0.0f) ? t : 0.0f;
    float res = (lo <= 1.0f) ? lo : 1.0f;

    return res;
}

/**
 * Offset/Address/Size: 0x518 | 0x80005FC4 | size: 0x20
 */
float AIsgn(float fValue)
{
    if (fValue >= 0.0f)
    {
        return 1.0f;
    }
    return -1.0f;
}

/**
 * Offset/Address/Size: 0x2E4 | 0x80005D90 | size: 0x234
 */
void GetClosestPointOnLineABFromPointC(const nlVector3&, const nlVector3&, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x160 | 0x80005C0C | size: 0x184
 */
void SortToMinOrMaxTotalSum(unsigned int*, float (*)[4], bool)
{
}

/**
 * Offset/Address/Size: 0x134 | 0x80005BE0 | size: 0x2C
 */
char* GetPowerupName(int powerup)
{
    if ((powerup >= 0) && (powerup < 9))
    {
        return g_sPowerupNames[powerup];
    }
    return "Unknown";
}

/**
 * Offset/Address/Size: 0x0 | 0x80005AAC | size: 0x134
 */
void GetClosestPointOnSidelines(const nlVector3&)
{
}

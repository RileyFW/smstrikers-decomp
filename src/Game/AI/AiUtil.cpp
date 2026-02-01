#include "Game/AI/AiUtil.h"

#include "Game/Field.h"
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
void MakePerpendicularPlane(const nlVector3& v3Position, unsigned short aNormalAngle, nlVector4& v4Plane, float fPlaneOffset)
{
    float fSin;
    float fCos;
    nlSinCos(&fSin, &fCos, aNormalAngle);

    v4Plane.f.x = fCos;
    v4Plane.f.y = fSin;
    v4Plane.f.z = 0.0f;

    float t0 = v3Position.f.y * fSin;
    float t1 = v3Position.f.x * fCos + t0;
    v4Plane.f.w = fPlaneOffset + t1;
}

/**
 * Offset/Address/Size: 0x1354 | 0x80006E00 | size: 0xCC
 * TODO: 85.2% match - register scheduling differences
 */
void MakePerpendicularPlane(const nlVector3& v3Position, const nlVector3& v3Normal, nlVector4& v4Plane, float fPlaneOffset)
{
    f32 ny = v3Normal.f.y;
    f32 nx = v3Normal.f.x;
    f32 ny2 = ny * ny;
    f32 nx2 = nx * nx;
    f32 nz = v3Normal.f.z;
    f32 nz2 = nz * nz;
    f32 lenSq = nx2 + ny2;
    f32 lenSq2 = nz2 + lenSq;

    f32 invLen = nlRecipSqrt(lenSq2, true);

    f32 normX = invLen * v3Normal.f.x;
    f32 normY = invLen * v3Normal.f.y;
    f32 posY = v3Position.f.y;
    f32 normZ = invLen * v3Normal.f.z;
    f32 posX = v3Position.f.x;

    v4Plane.f.x = normX;
    f32 posZ = v3Position.f.z;
    v4Plane.f.y = normY;
    v4Plane.f.z = normZ;

    f32 planeY = v4Plane.f.y;
    f32 planeX = v4Plane.f.x;
    f32 t0 = posY * planeY;
    f32 planeZ = v4Plane.f.z;
    f32 t1 = posX * planeX + t0;
    f32 t2 = posZ * planeZ + t1;
    f32 w = fPlaneOffset + t2;
    v4Plane.f.w = w;
}

/**
 * Offset/Address/Size: 0x1204 | 0x80006CB0 | size: 0x150
 */
bool IsPointInCone(const nlVector3&, const nlVector3&, const nlVector3&, const nlVector3&)
{
    return false;
}

/**
 * Offset/Address/Size: 0x110C | 0x80006BB8 | size: 0xF8
 * TODO: 96.2% match - r30/r31 register swap (current/diff allocation)
 */
#undef abs
extern "C" int abs(int n);

unsigned short SeekDirection(unsigned short aCurrent, unsigned short aDesired, float fSeekSpeed, float fFalloff, float fDeltaT)
{
    u16 current = aCurrent;
    u16 desired = aDesired;
    s16 diff = (s16)(desired - current);
    s16 delta;

    if (diff != 0)
    {
        f64 dDiff = (f64)(s16)diff;
        f64 absDiffD = __fabs(dDiff);
        f32 absDiff = (f32)absDiffD;

        if (absDiff < fFalloff)
        {
            f32 sqFalloff = fFalloff * fFalloff;
            f32 t1 = sqFalloff / fSeekSpeed;
            f32 t2 = t1 / absDiff;
            f32 t3 = fDeltaT + t2;
            f32 t4 = t1 / t3;
            f32 result = absDiff - t4;
            delta = (s16)(s32)result;
        }
        else
        {
            f32 result = fDeltaT * fSeekSpeed;
            delta = (s16)(s32)result;
        }

        int absDiffInt = abs(diff);
        if (absDiffInt < (s16)delta)
        {
            return desired;
        }

        if (diff > 0)
        {
            return (u16)(current + (s16)delta);
        }
        else
        {
            return (u16)(current - (s16)delta);
        }
    }

    return desired;
}

/**
 * Offset/Address/Size: 0x10C0 | 0x80006B6C | size: 0x4C
 */
float SeekSpeed(float fCurrent, float fDesired, float fSeekAccel, float fSeekDecel, float fDeltaT)
{
    float seekRate = (fCurrent <= fDesired) ? fSeekAccel : fSeekDecel;
    float delta = seekRate * fDeltaT;

    if (fCurrent <= fDesired)
    {
        float newValue = fCurrent + delta;
        if (newValue > fDesired)
        {
            return fDesired;
        }
        return newValue;
    }

    float newValue = fCurrent - delta;
    if (newValue < fDesired)
    {
        return fDesired;
    }
    return newValue;
}

/**
 * Offset/Address/Size: 0xFA4 | 0x80006A50 | size: 0x11C
 * TODO: 96.5% match - float register allocation (f4/f5/f6/f7/f9/f10 vs expected),
 */
void CalcInterceptXY(const nlVector3& pos1, f32 speed1, f32 speed2, const nlVector3& pos2, const nlVector3& vel, int& count, f32* times)
{
    f32 speed2Sq = speed2 * speed2;
    f32 speed1Sq = speed1 * speed1;

    f32 py2 = pos2.f.y;
    f32 py1 = pos1.f.y;
    f32 px2 = pos2.f.x;
    f32 px1 = pos1.f.x;

    f32 dy = py2 - py1;
    f32 dx = px2 - px1;
    f32 vy = vel.f.y;
    f32 vx = vel.f.x;

    f32 distSq = dx * dx + dy * dy;
    f32 velSq = vx * vx + vy * vy;
    f32 dotVelDelta = vx * dx + vy * dy;

    f32 a = velSq - speed1Sq;

    if (distSq <= speed2Sq)
    {
        count = 1;
        times[0] = 0.0f;
        return;
    }

    f32 b = 2.0f * (dotVelDelta - speed2 * speed1);
    f32 c = distSq - speed2Sq;

    f32 t2, t1;
    int numRoots;
    SolveQuadratic(a, b, c, numRoots, t1, t2);

    count = 0;
    if (numRoots == 0)
    {
        return;
    }

    if (t1 > 0.0f)
    {
        times[count] = t1;
        count++;
    }

    if (t2 > 0.0f)
    {
        times[count] = t2;
        count++;
    }
}

/**
 * Offset/Address/Size: 0xED0 | 0x8000697C | size: 0xD4
 */
bool ClipPositionToSidelines(nlVector3& position, float margin)
{
    bool wasClipped = false;

    float rightBound = cField::GetGoalLineX(1U) - margin;
    float topBound = cField::GetSidelineY(1U) - margin;

    if (position.f.x > rightBound)
    {
        position.f.x = rightBound;
        wasClipped = true;
    }
    else
    {
        float temp_f0 = -1.0f * rightBound;
        if (position.f.x < temp_f0)
        {
            position.f.x = temp_f0;
            wasClipped = true;
        }
    }

    float temp_f1 = -1.0f * topBound;
    if (position.f.y < temp_f1)
    {
        position.f.y = temp_f1;
        wasClipped = true;
    }
    else if (position.f.y > topBound)
    {
        position.f.y = topBound;
        wasClipped = true;
    }

    return wasClipped;
}

/**
 * Offset/Address/Size: 0xDF4 | 0x800068A0 | size: 0xDC
 */
bool TestCollision(float rp, const nlVector3& p1, const nlVector3& p2, float rq, const nlVector3& q1, const nlVector3& q2)
{
    float combinedRadius = rp + rq;
    float radiusSq = combinedRadius * combinedRadius;

    // Check start positions
    nlVector3 diff1;
    nlVec3Sub(diff1, q1, p1);
    float distSq1 = nlGetLengthSquared3D(diff1.f.x, diff1.f.y, diff1.f.z);

    if (distSq1 <= radiusSq)
    {
        return true;
    }

    // Check end positions
    nlVector3 diff2;
    nlVec3Sub(diff2, q2, p2);
    float distSq2 = nlGetLengthSquared3D(diff2.f.x, diff2.f.y, diff2.f.z);

    if (distSq2 <= radiusSq)
    {
        return true;
    }

    // Do sweep test
    float t = SweepSpheres(rp, p1, p2, rq, q1, q2);
    if (t >= 0.0f && t <= 1.0f)
    {
        return true;
    }

    return false;
}

/**
 * Offset/Address/Size: 0xD90 | 0x8000683C | size: 0x64
 */
float Exp(float x)
{
    float result = 1.0f;
    float neg_x = -x;
    float c0 = 0.24999869f;
    float c1 = 0.031257585f;
    float x_power;
    float c2 = 0.0025913713f;
    float c3 = 0.000171562f;
    float c4 = 0.0000054302f;
    float c5 = 0.0000006906f;
    float temp;

    result = c0 * neg_x + result;
    x_power = neg_x * neg_x;
    result = c1 * x_power + result;
    x_power *= neg_x;
    result = c2 * x_power + result;
    x_power *= neg_x;
    result = c3 * x_power + result;
    x_power *= neg_x;
    result = c4 * x_power + result;
    x_power *= neg_x;
    result = c5 * x_power + result;

    temp = result * result;
    temp = result * temp;
    temp = result * temp;

    return 1.0f / temp;
}

/**
 * Offset/Address/Size: 0xCE8 | 0x80006794 | size: 0xA8
 */
float GetClosingSpeed2D(const nlVector3& pos1, const nlVector3& vel1, const nlVector3& pos2, const nlVector3& vel2)
{
    float dx, dy;
    dy = pos2.f.y - pos1.f.y;
    dx = pos2.f.x - pos1.f.x;
    float distSq = dx * dx + dy * dy;
    float invDist = nlRecipSqrt(distSq, true);

    float normDx = invDist * dx;
    float normDy = invDist * dy;

    float vel1Proj = normDx * vel1.f.x + normDy * vel1.f.y;
    float vel2Proj = normDx * vel2.f.x + normDy * vel2.f.y;

    return vel1Proj - vel2Proj;
}

/**
 * Offset/Address/Size: 0xC0C | 0x800066B8 | size: 0xDC
 */
float GetClosingSpeed(const nlVector3& pos1, const nlVector3& vel1, const nlVector3& pos2, const nlVector3& vel2)
{
    float dx, dy, dz;
    dz = pos2.f.z - pos1.f.z;
    dy = pos2.f.y - pos1.f.y;
    dx = pos2.f.x - pos1.f.x;
    float distSq = dx * dx + dy * dy + dz * dz;
    float invDist = nlRecipSqrt(distSq, true);

    float normDx = invDist * dx;
    float normDy = invDist * dy;
    float normDz = invDist * dz;

    float vel1Proj = normDx * vel1.f.x + normDy * vel1.f.y + normDz * vel1.f.z;
    float vel2Proj = normDx * vel2.f.x + normDy * vel2.f.y + normDz * vel2.f.z;

    return vel1Proj - vel2Proj;
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
void GetWorldPoint(nlVector3& v3WorldPointOut, const nlVector3& v3LocalPointIn, const nlVector3& v3RefPosition, unsigned short aRefAngle)
{
    f32 fSin;
    f32 fCos;

    float localX = v3LocalPointIn.f.x;
    float localY = v3LocalPointIn.f.y;

    nlSinCos(&fSin, &fCos, aRefAngle);

    v3WorldPointOut.f.x = v3RefPosition.f.x + ((fCos * localX) - (fSin * localY));
    v3WorldPointOut.f.y = v3RefPosition.f.y + ((fCos * localY) + (fSin * localX));
    v3WorldPointOut.f.z = v3LocalPointIn.f.z;
}

/**
 * Offset/Address/Size: 0xA24 | 0x800064D0 | size: 0x98
 */
void RotateVectorZAxis(nlVector3& v3Out, const nlVector3& v3In, unsigned short angle)
{
    f32 fSin;
    f32 fCos;

    f32 localX = v3In.f.x;
    f32 localY = v3In.f.y;

    nlSinCos(&fSin, &fCos, angle);

    v3Out.f.x = (fCos * localX) - (fSin * localY);
    v3Out.f.y = (fCos * localY) + (fSin * localX);
    v3Out.f.z = v3In.f.z;
}

/**
 * Offset/Address/Size: 0x814 | 0x800062C0 | size: 0x210
 */
void GetRotationBetweenVectors(nlQuaternion&, const nlVector3&, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x70C | 0x800061B8 | size: 0x108
 * TODO: 92.0% match - work in progress..missing inline methods
 */
void RotateVector(nlVector3& result, const nlVector3& v, nlQuaternion& q)
{
    f32 qx = q.f.x;
    f32 qw = q.f.w;
    f32 qz = q.f.z;
    f32 qx2 = qx * qx;
    f32 two = 2.0f;
    f32 qw2 = qw * qw;
    f32 qy = q.f.y;
    f32 qz2 = qz * qz;
    f32 x2 = two * qx;
    f32 z2 = two * qz;
    f32 vy = v.f.y;
    f32 y2 = two * qy;
    f32 vx = v.f.x;
    f32 qy2 = qy * qy;

    f32 A = qw2 - qx2;
    f32 B = qx2 + qw2;
    f32 vz = v.f.z;

    f32 x2y = x2 * qy;
    f32 z2w = z2 * qw;
    f32 C = qy2 + A;
    f32 D = B - qy2;
    f32 E = x2y - z2w;
    f32 F = C - qz2;
    f32 G = A - qy2;
    f32 x2w = x2 * qw;
    f32 y2z = y2 * qz;
    f32 x2z = x2 * qz;
    f32 y2w = y2 * qw;
    f32 H = x2w + y2z;
    f32 I = D - qz2;
    f32 J = vy * E;
    f32 K = z2w + x2y;
    f32 L = vy * F;
    f32 M = x2z + y2w;
    f32 N = vx * I + J;
    f32 O = x2z - y2w;
    f32 P = vy * H;
    f32 Q = vz * M + N;
    f32 R = y2z - x2w;
    f32 S = vx * K + L;
    f32 T = qz2 + G;
    result.f.x = Q;
    f32 U = vx * O + P;
    f32 V = vz * R + S;
    f32 W = vz * T + U;
    result.f.y = V;
    result.f.z = W;
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
float InterpolateRangeClamped(float fResultMin, float fResultMax, float fInputMin, float fInputMax, float fInput)
{
    float range;

    if (fInputMin < fInputMax)
    {
        fInput = (fInput >= fInputMin) ? fInput : fInputMin;
        fInput = (fInput <= fInputMax) ? fInput : fInputMax;
    }
    else
    {
        fInput = (fInput >= fInputMax) ? fInput : fInputMax;
        fInput = (fInput <= fInputMin) ? fInput : fInputMin;
    }

    range = fInputMax - fInputMin;
    if (fabsf(range) < 0.001f)
    {
        return fResultMax;
    }

    return fResultMin + ((fInput - fInputMin) / range) * (fResultMax - fResultMin);
}

/**
 * Offset/Address/Size: 0x5D0 | 0x8000607C | size: 0xA0
 */
float InterpolateRangeClamped(const nlVector2& outputRange, const nlVector2& inputRange, float value)
{
    float maxVal = inputRange.f.y;
    float minVal = inputRange.f.x;
    float outMax = outputRange.f.y;
    float outMin = outputRange.f.x;

    // Clamp value to input range
    if (minVal < maxVal)
    {
        value = (value >= minVal) ? value : minVal;
        value = (value <= maxVal) ? value : maxVal;
    }
    else
    {
        value = (value >= maxVal) ? value : maxVal;
        value = (value <= minVal) ? value : minVal;
    }

    float range = maxVal - minVal;
    if ((float)__fabs((double)range) < 0.00001f)
    {
        return outMax;
    }

    return (value - minVal) / range * (outMax - outMin) + outMin;
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
nlVector3 GetClosestPointOnLineABFromPointC(const nlVector3& a, const nlVector3& b, const nlVector3& c)
{
    nlVector3 closestPoint;
    closestPoint.f.x = (a.f.x + b.f.x) / 2.0f;
    closestPoint.f.y = (a.f.y + b.f.y) / 2.0f;
    closestPoint.f.z = (a.f.z + b.f.z) / 2.0f;
    return closestPoint;
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

#include "types.h"

#include "math.h"

void* memcpy(void* dest, const void* src, size_t num);

static float fUnk_504 = 0.0000000004656613f;

struct coeffs
{
    s32 coeffs0;
    s32 coeffs1;
    s32 coeffs2;
    s32 coeffs3;
    s32 coeffs4;
    s32 coeffs5;
    s32 coeffs6;
    s32 coeffs7;
};

const struct coeffs coeffs1 = { 0, 7, 26, 98, 223, 400, 649, 1024 };
const struct coeffs coeffs2 = { 65408, 63104, 59680, 55008, 49536, 43680, 38016, 34112 };

extern void seedMT(u32 p);

/**
 * Offset/Address/Size: 0x0 | 0x801D1474 | size: 0x1D4
 */
float nlBezier(float* controlPoints, int degree, float t)
{
    f32* currentPoint;
    f32 temp_f0;
    f32 temp_f1;
    f32 oneMinusT;
    f32 result;
    f32 tPower;
    f32 tPowerInv;
    s32 temp_r0;
    s32 factorial;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r7;
    s32 loopCounter2;
    s32 loopCounter3;
    s32 factorialInv;
    s32 factorialResult;
    s32 factorialDivisor;
    s32 loopIndex;
    s32 unrolledLoopIndex;
    u32 unrolledLoopCount;

    if (t == 1.0f)
    {
        return controlPoints[(degree - 1)];
    }
    oneMinusT = 1.0f - t;
    factorialResult = 1;
    factorialInv = 1;
    temp_f1 = pow(oneMinusT, degree);
    tPowerInv = 1.0f;
    unrolledLoopIndex = 1;
    tPower = temp_f1;
    if (degree >= 1)
    {
        temp_r3 = degree - 8;
        if (degree > 8)
        {
            unrolledLoopCount = (temp_r3 + 7) >> 3;
            if (temp_r3 >= 1)
            {
                do
                {
                    temp_r7 = unrolledLoopIndex + 2;
                    temp_r6 = unrolledLoopIndex + 3;
                    temp_r5 = unrolledLoopIndex + 4;
                    temp_r4 = unrolledLoopIndex + 5;
                    factorialResult = factorialResult * unrolledLoopIndex * (unrolledLoopIndex + 1);
                    temp_r3_2 = unrolledLoopIndex + 6;
                    temp_r0 = unrolledLoopIndex + 7;
                    unrolledLoopIndex += 8;
                    factorialResult = factorialResult * temp_r7 * temp_r6 * temp_r5 * temp_r4 * temp_r3_2 * temp_r0;
                    unrolledLoopCount -= 1;
                } while (unrolledLoopCount != 0);
            }
        }
        loopCounter2 = (degree + 1) - unrolledLoopIndex;
        if (unrolledLoopIndex <= degree)
        {
            do
            {
                factorialResult *= unrolledLoopIndex;
                unrolledLoopIndex += 1;
                loopCounter2 -= 1;
            } while (loopCounter2 != 0);
        }
    }
    factorialDivisor = factorialResult;
    currentPoint = controlPoints + 4;
    result = *controlPoints * temp_f1;
    loopIndex = 1;
    loopCounter3 = degree;
    if (degree >= 1)
    {
        do
        {
            factorialInv *= loopIndex;
            if (loopIndex != degree)
            {
                factorialDivisor = factorialDivisor / ((degree - loopIndex) + 1);
            }
            temp_f0 = *currentPoint;
            tPower /= oneMinusT;
            currentPoint += 4;
            loopIndex += 1;
            tPowerInv *= t;
            result += (factorialResult / (factorialInv * factorialDivisor)) * (tPowerInv * tPower) * temp_f0;
            loopCounter3 -= 1;
        } while (loopCounter3 != 0);
    }
    return result;
}

/**
 * Offset/Address/Size: 0x1D4 | 0x801D1648 | size: 0x244
 */
float nlATan2f(float arg0, float arg1)
{
    f32 temp_f4;
    f32 temp_f5;
    f32 var_f3;
    s32 temp_r25;
    s32 temp_r25_2;
    s32 var_r0;
    s32 var_r0_2;

    // Static arrays for polynomial coefficients
    if (fabs(arg1) > 0.00001f)
    {
        temp_f4 = fabs(arg0 / arg1);
        if (temp_f4 > 1.0f)
        {
            temp_f5 = 1.0f / temp_f4;
            var_r0 = 7;
            temp_r25 = 8.0f * temp_f5;

            coeffs sp48 = coeffs1;
            coeffs sp68 = coeffs2;
            if (temp_r25 <= 7)
            {
                var_r0 = temp_r25;
            }
            var_f3 = 1.5707964f - ((temp_f5 * ((float*)&sp68)[var_r0]) + ((float*)&sp48)[var_r0]);
        }
        else
        {
            var_r0_2 = 7;
            temp_r25_2 = 8.0f * temp_f4;

            coeffs sp8 = coeffs1;
            coeffs sp28 = coeffs2;
            if (temp_r25_2 <= 7)
            {
                var_r0_2 = temp_r25_2;
            }
            var_f3 = (temp_f4 * ((float*)&sp28)[var_r0_2]) + ((float*)&sp8)[var_r0_2];
        }
        if (arg0 >= 0.0f)
        {
            if (arg1 >= 0.0f)
            {
                return var_f3;
            }
            return 3.1415927f - var_f3;
        }
        if (arg1 < 0.0f)
        {
            return 3.1415927f + var_f3;
        }
        return 6.2831855f - var_f3;
    }
    if (arg0 > 0.0f)
    {
        return 1.5707964f;
    }
    return 4.712389f;
}

/**
 * Offset/Address/Size: 0x418 | 0x801D188C | size: 0x48
 */
float nlTan(unsigned short angle)
{
    return (float)tan(angle * 0.0000958738f);
}

/**
 * Offset/Address/Size: 0x460 | 0x801D18D4 | size: 0x12C
 * TODO: 96.33% match - MWCC keeps clamped rad in f6 instead of f7 through NR/compare path,
 *       causing widespread f-register allocation differences in polynomial/sqrt sequence
 */
unsigned short nlACos(float x)
{
    u8 complement = (x < 0.0f);
    f32 y, temp, sqrtVal, rad;

    x = 1.0f - (f32)fabs(x);

    temp = 0.015098966f * x + 0.005516444f;
    y = x * temp + 0.047654245f;
    y = x * y + 0.16391061f;
    y = x * y + 2.0002916f;
    y = x * y + -0.000007239284f;

    rad = 2.0f * x;

    rad = (rad >= 0.00001f) ? rad : 0.00001f;

    if (rad > 0.0f)
    {
        f32 t = (f32)__frsqrte(rad);
        f32 t2 = 0.5f * t * -(rad * (t * t) - 3.0f);
        f32 t3 = 0.5f * t2 * -(rad * (t2 * t2) - 3.0f);
        sqrtVal = 0.5f * t3 * -(rad * (t3 * t3) - 3.0f);
    }
    else
    {
        f32 zero = 0.0f;
        if (rad != zero)
        {
            sqrtVal = *(f32*)&__float_nan;
        }
        else
        {
            sqrtVal = *(f32*)&__float_huge;
        }
    }

    rad = y * sqrtVal;

    if (complement)
    {
        return (unsigned short)(s32)(10430.378f * (3.1415927f - rad));
    }
    return (unsigned short)(s32)(10430.378f * rad);
}

/**
 * Offset/Address/Size: 0x58C | 0x801D1A00 | size: 0x164
 */
void nlSinCos(float* presult_sin, float* presult_cos, unsigned short angle)
{
    float angle_rad = (6.283185f / 65536.0f) * (float)angle;
    float octants = 1.2732395f * angle_rad;
    int k = (int)octants;
    float oct_f = (float)k;
    float y = angle_rad - 0.7853982f * oct_f;

    float y_squared = y * y;
    float s0 = -1.0f / 5040.0f;
    float s1 = 1.0f / 120.0f;
    float s2 = -1.0f / 6.0f;
    float c0 = -1.0f / 720.0f;
    float c1 = 1.0f / 24.0f;
    float s3 = 1.0f;
    float c2 = -0.5f;
    float c3 = 0.99999994f;

    float sin_poly = s0 * y_squared + s1;
    float cos_poly = c0 * y_squared + c1;
    float sin_tmp = y_squared * sin_poly + s2;
    float cos_tmp = y_squared * cos_poly + c2;
    sin_poly = y_squared * sin_tmp + s3;
    cos_poly = y_squared * cos_tmp + c3;
    sin_poly = y * sin_poly;

    float result_cos;
    float result_sin;

    switch (k & 7)
    {
    case 0:
        result_sin = sin_poly;
        result_cos = cos_poly;
        break;
    case 1:
    {
        float c = 0.70710678f;
        float s_1 = c * sin_poly;
        float s_2 = c * cos_poly;
        result_sin = s_1 + s_2;
        result_cos = s_2 - s_1;
        break;
    }
    case 2:
        result_sin = cos_poly;
        result_cos = -sin_poly;
        break;
    case 3:
    {
        float a = 0.70710678f;
        float b = -0.70710678f;
        float t1 = a * cos_poly;
        float t2 = a * sin_poly;
        result_sin = b * sin_poly + t1;
        result_cos = b * cos_poly - t2;
        break;
    }
    case 4:
        result_sin = -sin_poly;
        result_cos = -cos_poly;
        break;
    case 5:
    {
        float c = -0.70710678f;
        float s_1 = c * sin_poly;
        float s_2 = c * cos_poly;
        result_sin = s_1 + s_2;
        result_cos = s_2 - s_1;
        break;
    }
    case 6:
        result_sin = -cos_poly;
        result_cos = sin_poly;
        break;
    case 7:
    {
        float a = -0.70710678f;
        float b = 0.70710678f;
        float t1 = a * cos_poly;
        float t2 = a * sin_poly;
        result_sin = b * sin_poly + t1;
        result_cos = b * cos_poly - t2;
        break;
    }
    }

    *presult_sin = result_sin;
    *presult_cos = result_cos;
}

/**
 * Offset/Address/Size: 0x6F0 | 0x801D1B64 | size: 0xA0
 * TODO: 96% match - register allocation differences (f4/f5 swap), fneg instruction ordering
 */
float nlSin(unsigned short angle)
{
    float a = (float)angle * (6.283185f / 65536.0f); // Convert to radians (2*PI / 65536)
    float flip_sign = 1.0f;
    float working_a = a; // Create copy like target

    // Reduce angle to [-PI/2, PI/2]
    if (a >= 1.5707963f) // PI/2
    {
        working_a = a - 3.14159265f; // PI
    }
    else if (a >= 4.7123889f) // 3*PI/2
    {
        flip_sign = -flip_sign;     // Use fneg pattern
        working_a = a - 4.7123889f; // 3*PI/2
    }

    // Taylor series
    float a_squared = working_a * working_a;
    float result = working_a * (1.0f + a_squared * (-0.16666667f + a_squared * (0.00833333f + a_squared * (-0.00019841f + a_squared * 0.0000027557f))));

    return flip_sign * result;
}

/**
 * Offset/Address/Size: 0x790 | 0x801D1C04 | size: 0x70
 * TODO: 96.79% match - register allocation diffs in Newton-Raphson iterations
 */
float nlRecipSqrt(float x, bool)
{
    if (x > 0.0f)
    {
        // Newton-Raphson reciprocal square root
        float y = __frsqrte(x);
        y = 0.5f * y * (3.0f - x * y * y);
        y = 0.5f * y * (3.0f - x * y * y);
        y = 0.5f * y * (3.0f - x * y * y);
        return y;
    }
    else if (x != 0.0f)
    {
        return NAN;
    }
    else
    {
        return INFINITY;
    }
}

/**
 * Offset/Address/Size: 0x800 | 0x801D1C74 | size: 0xEC
 */
float nlSqrt(float x, bool bAccurate)
{
    if (x > 0.0f)
    {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        if (bAccurate)
        {
            guess = 0.5 * guess * (3.0 - guess * guess * x);
            guess = 0.5 * guess * (3.0 - guess * guess * x);
        }
        return (float)(x * guess);
    }
    else if (x < 0.0)
    {
        return NAN;
    }
    else
    {
        if (__fpclassifyf(x) == FP_NAN)
        {
            return NAN;
        }
        return x;
    }
}

/**
 * Offset/Address/Size: 0x8EC | 0x801D1D60 | size: 0x84
 * TODO: 59.4% match - MWCC pipeline scheduler produces different instruction
 * ordering and register allocation (r5/r6 swap for mulhwu, r0/r4 for addi,
 * XOR chain decomposition order, store order). Logic is correct.
 */
#pragma fp_contract off
float nlRandomf(float fMin, float fMax, unsigned int* pSeed)
{
    uint mixed;
    uint temp;
    uint seed;

    float range = fMax - fMin;
    float scale = (1.0f / 2147483647.0f) * range;
    seed = *pSeed;
    mixed = seed ^ 0x1D872B41;
    temp = mixed ^ (mixed >> 5);
    *pSeed = mixed ^ temp ^ (temp << 27);
    return fMin + scale * (f32)(seed % 0x7FFFFFFFu);
}
#pragma fp_contract on

/**
 * Offset/Address/Size: 0x970 | 0x801D1DE4 | size: 0x7C
 * TODO: match pending - instruction scheduling differences with -O4,p
 */
#pragma fp_contract off
float nlRandomf(float fMax, unsigned int* pSeed)
{
    float scale;
    unsigned int seed;
    unsigned int xored;
    unsigned int s0;
    unsigned int s1;
    unsigned int modResult;

    scale = fUnk_504 * fMax;
    seed = *pSeed;
    modResult = seed % 0x7FFFFFFFu;
    xored = seed ^ 0x1D872B41;
    s0 = xored >> 5;
    s1 = xored ^ s0;
    *pSeed = s1 ^ (xored ^ (s1 << 27));

    return scale * (float)modResult;
}
#pragma fp_contract on

/**
 * Offset/Address/Size: 0x9EC | 0x801D1E60 | size: 0x34
 */
uint nlRandom(uint range, uint* seed)
{
    uint next;
    uint temp;

    uint result = *seed % range;
    next = *seed ^ 0x1d872b41;
    temp = next ^ (next >> 5);
    *seed = temp ^ (next ^ (temp << 0x1b));
    return result;
}

/**
 * Offset/Address/Size: 0xA20 | 0x801D1E94 | size: 0x2C
 */
void nlSetRandomSeed(uint initialSeed, uint* seedStorage)
{
    uint shiftedValue;
    uint mixedValue;

    *seedStorage = initialSeed;

    mixedValue = *seedStorage ^ 0x1d872b41;        // Mix with constant
    shiftedValue = mixedValue ^ (mixedValue >> 5); // Mix with right-shifted value

    *seedStorage = shiftedValue ^ (mixedValue ^ (shiftedValue << 0x1b)); // Final mixing
}

/**
 * Offset/Address/Size: 0xA4C | 0x801D1EC0 | size: 0x24
 */
void nlInitRandom()
{
    seedMT(0x1105);
}

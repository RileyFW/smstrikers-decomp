#include "Game/FE/feTweenFuncs.h"

#include "math.h"
#include "NL/nlMath.h"

namespace TweenFunctions
{

/**
 * Offset/Address/Size: 0x0 | 0x800A2EC4 | size: 0x10
 */
float linear(float t, float b, float c, float d)
{
    return b + (c * t) / d;
}

/**
 * Offset/Address/Size: 0x10 | 0x800A2ED4 | size: 0xF4
 */
float easeoutelastic(float arg0, float arg1, float arg2, float arg3)
{
    f32 temp_f28;
    f32 temp_f3;
    f64 temp_f30;

    if (arg0 == 0.0f)
    {
        return arg1;
    }
    temp_f28 = arg0 / arg3;
    if (temp_f28 == 1.0f)
    {
        return arg1 + arg2;
    }

    temp_f3 = 0.3 * arg3;
    temp_f30 = nlSin((u16)(s32)(10430.378f * ((6.2831855f * ((temp_f28 * arg3) - (temp_f3 * 0.25f))) / temp_f3)));
    return (f32)((f64)arg1 + (((f64)arg2 * (float)pow(2.0, -10.0f * temp_f28) * temp_f30) + (f64)arg2));
}

/**
 * Offset/Address/Size: 0x104 | 0x800A2FC8 | size: 0xF4
 */
float easeinelastic(float t, float b, float c, float d)
{
    if (t == 0.0f)
        return b;

    float td = t / d;
    if (td == 1.0f)
        return b + c;

    float td_prime = td - 1.0f;

    // period = (float)(0.3 * (double)d), then s = period * 0.25
    float period = (float)(0.3 * (double)d);
    float s = 0.25f * period;
    float two_pi = 6.2831855f;
    float rad2idx = 10430.378f;

    // angle = (2*pi * ((td' * d) - s)) / period
    float angle = (two_pi * ((td_prime * d) - s)) / period;

    // index = (u16)(s32)(rad2idx * angle)
    unsigned short idx = (unsigned short)((int)(rad2idx * angle));

    // Keep the nlSin() result in a double live range (like f31)
    double sine_d = (double)nlSin(idx);

    // pow exponent as float first (fmuls with 10.0), then promoted to double
    float exp_f = 10.0f * td_prime;
    double pow_d = pow(2.0, (double)exp_f);

    // Multiply c * pow in double to match fmul with f30 (c) and pow result (f1)
    double cmul_d = ((double)c) * pow_d;

    // Return: -(cmul_d * sine_d - (double)b)  -> fnmsub f1,f0,f31,f29
    double r = -((cmul_d * sine_d) - (double)b);
    return (float)r;
}

} // namespace TweenFunctions

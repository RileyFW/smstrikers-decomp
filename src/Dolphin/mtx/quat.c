#include <dolphin.h>
#include <dolphin/mtx.h>
// #include <math.h>

extern f32 acosf(f32);
extern f32 sinf(f32);

void PSQUATScale(const register Quaternion* q, register Quaternion* r, register f32 scale)
{
    register f32 rxy, rzw;

    asm {
        psq_l rxy, 0(q), 0, 0
        psq_l rzw, 8(q), 0, 0
        ps_muls0 rxy, rxy, scale
        psq_st rxy, 0(r), 0, 0
        ps_muls0 rzw, rzw, scale
        psq_st rzw, 8(r), 0, 0
    }
}

f32 PSQUATDotProduct(const register Quaternion* p, const register Quaternion* q)
{
    register f32 pxy, pzw, qxy, qzw, dp;

    asm {
        psq_l pxy, 0(p), 0, 0
        psq_l qxy, 0(q), 0, 0
        ps_mul dp, pxy, qxy
        psq_l pzw, 8(p), 0, 0
        psq_l qzw, 8(q), 0, 0
        ps_madd dp, pzw, qzw, dp
        ps_sum0 dp, dp, dp, dp
    }

    return dp;
}

/* TODO: 94.73% - initial dot-product load/use ordering and f3/f6 allocation still differ. */
void C_QUATSlerp(float t, const Quaternion* p, const Quaternion* q, Quaternion* r)
{
    f32 tp;
    f32 tq;
    f32 theta;
    f32 sin_th;
    f32 cos_th;
    f32 mul0;
    f32 mul1;

    mul0 = p->x * q->x;
    mul1 = p->y * q->y;
    cos_th = mul0 + mul1;
    mul0 = p->z * q->z;
    cos_th = cos_th + mul0;
    mul0 = p->w * q->w;
    cos_th = cos_th + mul0;

    tq = 1.0f;
    if (cos_th < 0.0f)
    {
        cos_th = -cos_th;
        tq = -tq;
    }

    if (cos_th <= 0.99999f)
    {
        theta = acosf(cos_th);
        sin_th = sinf(theta);
        mul0 = sinf((1.0f - t) * theta);
        tp = mul0 / sin_th;
        mul0 = sinf(t * theta) / sin_th;
        tq = tq * mul0;
    }
    else
    {
        tq = tq * t;
        tp = 1.0f - t;
    }

    mul0 = tp * p->x;
    mul1 = tq * q->x;
    r->x = mul0 + mul1;

    mul0 = tp * p->y;
    mul1 = tq * q->y;
    r->y = mul0 + mul1;

    mul0 = tp * p->z;
    mul1 = tq * q->z;
    r->z = mul0 + mul1;

    mul0 = tp * p->w;
    mul1 = tq * q->w;
    r->w = mul0 + mul1;
}

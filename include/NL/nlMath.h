#ifndef _NLMATH_H_
#define _NLMATH_H_

#include "Dolphin/mtx.h"

struct nlVector2_
{
    float f[2];
};

struct nlVector2
{
    float x;
    float y;

    // nlVector2() { }
    // nlVector2(float _x, float _y)
    //     : x(_x)
    //     , y(_y)
    // {
    // }
};

#define NL_VECTOR3_SET(v, xval, yval, zval) \
    do                                      \
    {                                       \
        (v).f.x = (xval);                   \
        (v).f.y = (yval);                   \
        (v).f.z = (zval);                   \
    } while (0)

#define NL_VECTOR4_SET(v, xval, yval, zval) \
    do                                      \
    {                                       \
        (v).x = (xval);                     \
        (v).y = (yval);                     \
        (v).z = (zval);                     \
    } while (0)

struct nlVector3_
{
    float f[3];
};

struct nlVector3
{
    union
    {
        struct
        {
            float x;
            float y;
            float z;
        } f;
        u32 as_u32[3];
    };

    nlVector3() { }
    nlVector3(float _x, float _y, float _z)
    {
        f.x = _x;
        f.y = _y;
        f.z = _z;
    }
    void Set(float x, float y, float z);
};

struct nlVector4
{
    float x;
    float y;
    float z;
    float w;
    nlVector4() { }
    nlVector4(float x, float y, float z, float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }
};

struct nlMatrix3
{
    float m[3 * 3]; // Flat array access

    inline nlVector2 operator*(const nlVector2& v_in) const
    {
        nlVector2 tmp;
        tmp.x = m[6] + ((m[0] * v_in.x) + (m[3] * v_in.y));
        tmp.y = m[7] + ((m[1] * v_in.x) + (m[4] * v_in.y));
        return tmp;
    }
};

/*
m[0][0] m[0][1] m[0][2] m[0][3]  // Row 0: offset 0x00, 0x04, 0x08, 0x0C
m[1][0] m[1][1] m[1][2] m[1][3]  // Row 1: offset 0x10, 0x14, 0x18, 0x1C
m[2][0] m[2][1] m[2][2] m[2][3]  // Row 2: offset 0x20, 0x24, 0x28, 0x2C
m[3][0] m[3][1] m[3][2] m[3][3]  // Row 3: offset 0x30, 0x34, 0x38, 0x3C
*/
struct nlMatrix4
{
    Mtx44 m;

    void SetIdentity();
    void SetColumn(int col, const nlVector3& v);

    inline nlVector4 operator*(const nlVector4& v_in) const
    {
        nlVector4 tmp;
        tmp.x = m[0][0] * v_in.x + m[1][0] * v_in.y + m[2][0] * v_in.z + m[3][0] * v_in.w;
        tmp.z = m[0][2] * v_in.x + m[1][2] * v_in.y + m[2][2] * v_in.z + m[3][2] * v_in.w;
        tmp.y = m[0][1] * v_in.x + m[1][1] * v_in.y + m[2][1] * v_in.z + m[3][1] * v_in.w;
        tmp.w = m[0][3] * v_in.x + m[1][3] * v_in.y + m[2][3] * v_in.z + m[3][3] * v_in.w;
        return tmp;
    }
};

float nlBezier(float*, int, float);
float nlATan2f(float, float);
float nlTan(unsigned short);
float nlACos(float);
void nlSinCos(float*, float*, unsigned short);
float nlSin(unsigned short);
float nlRecipSqrt(float, bool);
float nlSqrt(float, bool);
float nlRandomf(float, float, unsigned int*);
float nlRandomf(float, unsigned int*);
int nlRandom(unsigned int, unsigned int*);
void nlSetRandomSeed(unsigned int, unsigned int*);
void nlInitRandom();

#include "NL/platvmath.h"
#include "NL/platqmath.h"
#include "NL/utility.h"

#endif

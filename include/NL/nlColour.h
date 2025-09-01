#ifndef _NLCOLOUR_H_
#define _NLCOLOUR_H_

#include "types.h"

struct nlColour_
{
    u8 rgba[4];
};

struct nlColour
{
    // union
    // {
    //     struct
    //     {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    //     } c;
    //     u32 as_u32;
    // };

    // nlColour()
    //     : r(0.0f)
    //     , g(0.0f)
    //     , b(0.0f)
    // {
    // }
    // nlColour(float _x, float _y, float _z)
    //     : r(_x)
    //     , g(_y)
    //     , b(_z)
    // {
    // }
};

#endif // _NLCOLOUR_H_

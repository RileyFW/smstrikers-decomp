#ifndef _NLCOLOUR_H_
#define _NLCOLOUR_H_

#include "types.h"

struct nlColour_
{
    u8 rgba[4];
};

struct nlColour
{
    unsigned char c[4];
};

inline void nlColourSet(nlColour& c0, u8 _r, u8 _g, u8 _b, u8 _a)
{
    c0.c[0] = _r;
    c0.c[1] = _g;
    c0.c[2] = _b;
    c0.c[3] = _a;
}

struct nlFloatColour
{
    float c[4]; // offset 0x0, size 0x10
}; // total size: 0x10

inline void nlFloatColourSet(nlFloatColour& c0, float _r, float _g, float _b, float _a)
{
    c0.c[0] = _r;
    c0.c[1] = _g;
    c0.c[2] = _b;
    c0.c[3] = _a;
}

#endif // _NLCOLOUR_H_

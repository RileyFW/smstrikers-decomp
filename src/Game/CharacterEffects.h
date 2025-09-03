#ifndef _CHARACTEREFFECTS_H_
#define _CHARACTEREFFECTS_H_

#include "types.h"

#include "NL/gl/glState.h"

enum eEffectsTextureType
{
    eEffectsTextureType_0 = 0,
    eEffectsTextureType_1,
    eEffectsTextureType_2,
    eEffectsTextureType_3,
    eEffectsTextureType_4
};

typedef struct FxTexturingEntry
{
    u32 t0;
    u32 t1;
    u32 t2;
} EffectsTexturing;

EffectsTexturing* fxGetTexturing(eEffectsTextureType);

#endif // _CHARACTEREFFECTS_H_

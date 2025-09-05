#include "Game/CharacterEffects.h"

EffectsTexturing fxTexturing[] = {
    { 0xFFFFFFFF, 0x00000000, 0x00000000 },
    { glGetTexture("effects/fx_env_ice"), 0x00000003, 0x00000000 },
    { glGetTexture("effects/fx_env_fire"), 0x00000003, 0x01000000 },
    { glGetTexture("effects/fx_yellow_glow"), 0x00000000, 0x00010000 },
    { glGetTexture("effects/fx_electrocution"), 0x00000000, 0x01000000 },
};

/**
 * Offset/Address/Size: 0x0 | 0x8012A7AC | size: 0x14
 */
EffectsTexturing* fxGetTexturing(eEffectsTextureType type)
{
    return &fxTexturing[type];
}

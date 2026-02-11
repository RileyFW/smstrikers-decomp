#include "Game/Render/Indicators.h"
#include "types.h"

static float s_fPulseRate;
static unsigned char s_bPulseGlowTexture;
static float s_fGlowIntensityScale;
static unsigned char s_bGlowIsRising;

/**
 * Offset/Address/Size: 0x868 | 0x8015FACC | size: 0x440
 */
void UpdateAndRenderOffScreenIndicators(float)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0xA8 | 0x8015F30C | size: 0x7C0
 */
void UpdateAndRenderPlayerIndicators(float)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x0 | 0x8015F264 | size: 0xA8
 */
void UpdateAndRenderIndicators(float dt)
{
    UpdateAndRenderOffScreenIndicators(dt);
    UpdateAndRenderPlayerIndicators(dt);

    if (s_bPulseGlowTexture)
    {
        if (s_bGlowIsRising)
        {
            s_fGlowIntensityScale += s_fPulseRate * dt;
            if (s_fGlowIntensityScale > 1.0f)
            {
                s_fGlowIntensityScale = 1.0f;
                s_bGlowIsRising = 0;
            }
        }
        else
        {
            s_fGlowIntensityScale -= s_fPulseRate * dt;
            if (s_fGlowIntensityScale < 0.0f)
            {
                s_fGlowIntensityScale = 0.0f;
                s_bGlowIsRising = 1;
            }
        }
    }
}

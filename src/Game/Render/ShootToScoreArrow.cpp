#include "Game/Render/ShootToScoreArrow.h"

#include "NL/gl/glDraw2.h"
#include "NL/gl/glState.h"

const unsigned long UnlitProgram = glGetProgram("3d unlit");
const unsigned long LitProgram = glGetProgram("3d pointlit");
const unsigned long LightTexture = glGetTexture("global/lightramp");
const unsigned long BlackTexture = glGetTexture("global/black");
const unsigned long WhiteTexture = glGetTexture("global/white");

bool useSubtractiveDarkening;

// static const nlColour black = { 0, 0, 0, 0 };

/**
 * Offset/Address/Size: 0x0 | 0x8015FFE0 | size: 0x1C8
 */
void WorldDarkening::UpdateAndRender(float deltaTime)
{
    u8 darkenAmount; // r5
    glPoly2 poly;    // r1+0x10

    mPos += mRate * deltaTime;

    if (mRate > 0.0f)
    {
        if (mPos > mTo)
        {
            mPos = mTo;
        }
    }
    if (mRate < 0.0f)
    {
        if (mPos < mTo)
        {
            mPos = mTo;
        }
    }

    if (mPos <= 0.0f)
    {
        mActive = false;
        return;
    }

    mActive = true;

    glSetDefaultState(true);
    glSetRasterState(GLS_DepthTest, 0);
    if (useSubtractiveDarkening != 0)
    {
        glSetRasterState(GLS_AlphaBlend, 7);
    }
    else
    {
        glSetRasterState(GLS_AlphaBlend, 1);
    }

    glSetCurrentTexture(glGetTexture("global/white"), GLTT_Diffuse);
    glSetCurrentTextureState(glHandleizeTextureState());
    glSetRasterState(GLS_DepthTest, 0);
    glSetCurrentRasterState(glHandleizeRasterState());

    poly.SetupRectangle(0.0f, 0.0f, 640.0f, 480.0f, -1.0f);

    darkenAmount = 255.0f * mPos;

    if (useSubtractiveDarkening != 0)
    {
        nlColour black = { 0, 0, 0, 0 };
        nlColour color = black;
        nlColourSet(color, darkenAmount, darkenAmount, darkenAmount, 255);
        poly.SetColour(color);
    }
    else
    {
        nlColour black = { 0, 0, 0, 0 };
        nlColour color = black;
        nlColourSet(color, 0, 0, 0, darkenAmount);
        poly.SetColour(color);
    }

    poly.Attach(GLV_BigBlackPolygon, 0, NULL, -1);
    glSetDefaultState(false);
}

/**
 * Offset/Address/Size: 0x1C8 | 0x801601A8 | size: 0xC
 */
void WorldDarkening::Fade(float rate, float to)
{
    this->mRate = rate;
    this->mTo = to;
}

/**
 * Offset/Address/Size: 0x1D4 | 0x801601B4 | size: 0x40
 */
WorldDarkening& WorldDarkening::Instance()
{
    static WorldDarkening instance;
    return instance;
}

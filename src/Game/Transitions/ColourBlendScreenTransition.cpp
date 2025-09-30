#include "Game/Transitions/ColourBlendScreenTransition.h"

/**
 * Offset/Address/Size: 0x94 | 0x802050E8 | size: 0x8
 */
float ColourBlendScreenTransition::GetTransitionLength()
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x84 | 0x802050D8 | size: 0x10
 */
float ColourBlendScreenTransition::Time() const
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x80 | 0x802050D4 | size: 0x4
 */
void ColourBlendScreenTransition::Cancel()
{
}

/**
 * Offset/Address/Size: 0x68 | 0x802050BC | size: 0x18
 */
bool ColourBlendScreenTransition::IsFinished()
{
    return false;
}

/**
 * Offset/Address/Size: 0x5C | 0x802050B0 | size: 0xC
 */
void ColourBlendScreenTransition::Reset()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80205054 | size: 0x5C
 */
ColourBlendScreenTransition::~ColourBlendScreenTransition()
{
}

/**
 * Offset/Address/Size: 0x380 | 0x80205044 | size: 0x10
 */
void ColourBlendScreenTransition::Update(float dt)
{
}

/**
 * Offset/Address/Size: 0x1D8 | 0x80204E9C | size: 0x1A8
 */
void ColourBlendScreenTransition::Render(eGLView)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80204CC4 | size: 0x1D8
 */
ColourBlendScreenTransition* ColourBlendScreenTransition::GetFromParser(SimpleParser*)
{
    return nullptr;
}

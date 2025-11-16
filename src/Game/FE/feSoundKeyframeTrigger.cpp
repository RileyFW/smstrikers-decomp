#include "Game/FE/feSoundKeyframeTrigger.h"

#include "Game/FE/feAnimation.h"

#include "NL/nlDLRing.h"

inline fAnimationKeyframe* GetAnimationKeyframe(fAnimationKeyframe* start, float t)
{
    fAnimationKeyframe* it = start;
    do
    {
        if (t <= it->unkC)
        {
            return it;
        }
        it = it->m_next;
    } while (it != start);
    return NULL;
}

/**
 * Offset/Address/Size: 0x0 | 0x8010EF64 | size: 0x1A8
 */
void SoundKeyframeTrigger::Update(float arg0, float arg1)
{
}

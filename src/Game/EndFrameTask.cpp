#include "Game/EndFrameTask.h"

#include "NL/gl/gl.h"
#include "Game/Debug/FrameCounter.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x8016E6D4 | size: 0xC
//  */
// void EndFrameTask::GetName()
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x8016E694 | size: 0x40
 */
void EndFrameTask::Run(float dt)
{
    glEndFrame();
    g_FrameCounter.StartTimer(1);
    glSendFrame();
    g_FrameCounter.FinishTiming();
}

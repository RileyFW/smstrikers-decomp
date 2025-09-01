#include "Game/FixedUpdateTask.h"

#include "NL/platpad.h"
#include "Game/FlickDetection.h"

extern float g_fFixedUpdateTick;

static bool g_bRunSimAndRenderInLockStep;
static float g_fSimulationTick = g_fFixedUpdateTick;

float FixedUpdateTask::mAccumulatedDeltaT;
float FixedUpdateTask::mSimulationTime;
float FixedUpdateTask::mfFrameLockTime;

/**
 * Offset/Address/Size: 0x2D8 | 0x8016E608 | size: 0x30
 */
FixedUpdateTask::FixedUpdateTask()
{
    mAccumulatedDeltaT = g_fFixedUpdateTick;
    mSimulationTime = 0.f;
    mfFrameLockTime = 0.f;
}

/**
 * Offset/Address/Size: 0x2CC | 0x8016E5FC | size: 0xC
 */
const char* FixedUpdateTask::GetName()
{
    return "Game Fixed Update";
}

/**
 * Offset/Address/Size: 0x0 | 0x8016E330 | size: 0x280
 */
void FixedUpdateTask::Run(float dt)
{
    // TODO: Implement

    UseDefaultPad();
    UpdatePlatPad(dt);
    cPadManager::Update(dt);
    FlickDetection::Update();
}

/**
 * Offset/Address/Size: 0x2C4 | 0x8016E5F4 | size: 0x8
 */
float FixedUpdateTask::GetPhysicsUpdateTick()
{
    return g_fSimulationTick;
}

/**
 * Offset/Address/Size: 0x280 | 0x8016E5B0 | size: 0x44
 */
void FixedUpdateTask::DecrementFrameLock(float f)
{
    float temp_f1 = mfFrameLockTime - f;
    mfFrameLockTime = temp_f1;
    if (temp_f1 < 0.f)
    {
        nlTaskManager::SetNextState(2);
        mfFrameLockTime = 0.f;
    }
}

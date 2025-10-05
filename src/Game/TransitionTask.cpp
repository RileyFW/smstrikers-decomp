#include "Game/TransitionTask.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x801731FC | size: 0x10
//  */
// void 0x8028D338..0x8028D33C | size : 0x4
// {
// }

/**
 * Offset/Address/Size: 0xC | 0x801731F8 | size: 0x4
 */
void TransitionTask::Run(float)
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x801731EC | size: 0xC
//  */
// void TransitionTask::GetName()
// {
// }

// /**
//  * Offset/Address/Size: 0x1BF4 | 0x801731C4 | size: 0x28
//  */
// void Detail::SwitchToStartScreenLoader::StartLoad(LoadingManager*)
// {
// }

/**
 * Offset/Address/Size: 0x1A10 | 0x80172FE0 | size: 0x1E4
 */
void LoadFonts()
{
}

/**
 * Offset/Address/Size: 0x19E0 | 0x80172FB0 | size: 0x30
 */
TransitionTask::TransitionTask()
{
    m_pAIHandler = nullptr;
    m_pGoalieHandler = nullptr;
    m_pLoadingManager = nullptr;
    m_TransitionState = eTS_Unknown;
}

/**
 * Offset/Address/Size: 0x19D8 | 0x80172FA8 | size: 0x8
 */
void TransitionTask::Initialize(LoadingManager& loadingManager)
{
    m_pLoadingManager = &loadingManager;
}

/**
 * Offset/Address/Size: 0x10B8 | 0x80172688 | size: 0x920
 */
void TransitionTask::StateTransition(unsigned int, unsigned int)
{
}

/**
 * Offset/Address/Size: 0x888 | 0x80171E58 | size: 0x830
 */
void TransitionTask::InitializeGameState()
{
}

/**
 * Offset/Address/Size: 0x4BC | 0x80171A8C | size: 0x3CC
 */
void TransitionTask::DestroyGameState()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801715D0 | size: 0x4BC
 */
void TransitionTask::InitializeFEState()
{
}

#include "Game/FrontEndTask.h"

#include "Game/FE/feInput.h"
#include "Game/FE/feManager.h"
#include "Game/FE/feResourceManager.h"
#include "Game/FE/feSceneManager.h"
#include "Game/FE/feAnimModelManager.h"
#include "Game/GameInfo.h"
#include "Game/DB/StatsTracker.h"
#include "NL/globalpad.h"
#include "NL/nlTask.h"
#include "NL/nlConfig.h"
#include "NL/gl/gl.h"
#include "Dolphin/pad.h"

float g_fUpTime;
float g_fIdleGameTime;

extern FrontEnd* g_pFrontEnd;
extern FEInput* g_pFEInput;

// TODO: missing header, Forward declaration
namespace TakeGameMemSnapshot
{
void Update(float);
}

/**
 * Offset/Address/Size: 0x484 | 0x8017071C | size: 0x2A8
 */
void FrontEndTask::Run(float dt)
{
    int buttonPressCount;
    cGlobalPad* pad;

    g_fUpTime += dt;
    g_pFEInput->Update(dt);
    HandleE3IdleReset(dt);

    if (nlTaskManager::m_pInstance->m_CurrState == 2)
    {
        for (int padIdx = 0; padIdx < 4; padIdx++)
        {
            short playingSide = nlSingleton<GameInfoManager>::s_pInstance->GetPlayingSide(padIdx);
            if (playingSide == -1)
            {
                continue;
            }

            pad = cPadManager::GetPad(padIdx);
            if (!pad->IsConnected())
            {
                continue;
            }

            buttonPressCount = 0;

            if (pad->JustPressed(PAD_BUTTON_A, false))
            {
                buttonPressCount++;
            }
            if (pad->JustPressed(PAD_BUTTON_B, false))
            {
                buttonPressCount++;
            }
            if (pad->JustPressed(PAD_BUTTON_X, false))
            {
                buttonPressCount++;
            }
            if (pad->JustPressed(PAD_BUTTON_Y, false))
            {
                buttonPressCount++;
            }

            if (buttonPressCount != 0)
            {
                short side = (short)(GameInfoManager::Instance()->GetPlayingSide(padIdx));
                StatsTracker::Instance()->AddStat(STATS_BUTTON_PRESSES, side, -1, buttonPressCount);
                StatsTracker::Instance()->AddUserStatByPad(STATS_BUTTON_PRESSES, padIdx, buttonPressCount);
            }
        }
    }

    if (nlTaskManager::m_pInstance->m_CurrState != 4)
    {
        FrontEnd::Update(dt);
    }

    if (FEResourceManager::Instance() != nullptr)
    {
        FEResourceManager::Instance()->Run(dt);
        FESceneManager::Instance()->Update(dt);
        FESceneManager::Instance()->RenderActiveScenes();
        if (!FESceneManager::Instance()->AreAllScenesValid())
        {
            glDiscardFrame(1);
        }
    }

    FEAnimModelManager* animModelManager = FEAnimModelManager::Instance();
    if (animModelManager != nullptr)
    {
        animModelManager->Update(dt);
    }

    if (nlTaskManager::m_pInstance->m_CurrState != 4)
    {
        Config& config = Config::Global();
        if (GetConfigBool(config, "domemsnapshot", false))
        {
            TakeGameMemSnapshot::Update(dt);
        }
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x80170298 | size: 0x484
 */
void FrontEndTask::HandleE3IdleReset(float)
{
    FORCE_DONT_INLINE;
}

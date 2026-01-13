#include "Game/SH/SHSaveLoad.h"

#include "dolphin/card.h"
#include "Game/BaseGameSceneManager.h"
#include "Game/DB/SaveLoad.h"
#include "Game/FE/tlTextInstance.h"
#include "Game/ResetTask.h"
#include "Game/Sys/gcmemcard.h"
#include "types.h"

enum eSaveLoad
{
    ST_INVALID = -1,
    ST_SAVE = 0,
    ST_LOAD = 1,
    ST_GAMESAVEIDTEST = 2,
    ST_DELETE = 3,
    ST_FORMAT = 4,
    ST_ASK_SAVE = 5,
    ST_ASK_LOAD = 6,
    ST_CHECKING = 7,
    ST_ABOUT_AUTOSAVE = 8,
    ST_CONFIRM_FORMAT = 9,
    ST_SHOULD_LOAD_OR_SAVE = 10,
};

extern int gSceneTypeStackDepth;
extern enum eSaveLoad gSceneTypeStack[4];
extern bool gSaveLoadStarted;
extern bool gSaveLoadFinished;
extern bool gCallbackMade;
extern float gSceneTime;
extern bool gIgnoreMinWait;
extern bool gContinueWithoutOperation;
extern bool gSaveLoadEnabled;
extern long gResult;
extern float gRetryTimerDelay;

// extern bool s_InitDone__7MemCard;
extern MemCard** g_MemCards;
extern u8 WasCardRemoved;
extern u8 PreviousNoCardInSlotState;

/**
 * Offset/Address/Size: 0x28D0 | 0x800B2E58 | size: 0x14
 */
bool DidContinueWithoutOperation()
{
    return (gContinueWithoutOperation == true);
}

/**
 * Offset/Address/Size: 0x28C4 | 0x800B2E4C | size: 0xC
 */
void ResetEnableSaveLoadFlag()
{
    gSaveLoadEnabled = true;
}

/**
 * Offset/Address/Size: 0x28B4 | 0x800B2E3C | size: 0x10
 */
void SaveLoadCallback(long result)
{
    gResult = result;
    gCallbackMade = true;
}

/**
 * Offset/Address/Size: 0x2878 | 0x800B2E00 | size: 0x3C
 */
void ContinueWithoutSavingCB()
{
    gSceneTypeStackDepth = 1;
    SaveLoadScene* instance = SaveLoadScene::mInstance;
    gIgnoreMinWait = true;
    gSaveLoadFinished = true;
    gSaveLoadStarted = true;
    gSaveLoadEnabled = false;
    gContinueWithoutOperation = true;
    SaveLoadScene::mLastSaveLoadSuccess = false;
    if (instance->m_displayText != nullptr)
    {
        instance->m_displayText->m_bVisible = false;
    }
}

/**
 * Offset/Address/Size: 0x2840 | 0x800B2DC8 | size: 0x38
 */
void ContinueWithoutLoadingCB()
{
    gSceneTypeStackDepth = 1;
    SaveLoadScene* instance = SaveLoadScene::mInstance;
    gIgnoreMinWait = true;
    gSaveLoadFinished = true;
    gSaveLoadStarted = true;
    gContinueWithoutOperation = true;
    SaveLoadScene::mLastSaveLoadSuccess = false;
    if (instance->m_displayText != nullptr)
    {
        instance->m_displayText->m_bVisible = false;
    }
}

/**
 * Offset/Address/Size: 0x27DC | 0x800B2D64 | size: 0x64
 */
void ContinueLoadingCB()
{
    gCallbackMade = false;
    int stackIndex = --gSceneTypeStackDepth;
    gSaveLoadStarted = false;
    gSaveLoadFinished = false;
    ResetTask::s_resetPaused = (gSceneTypeStack[stackIndex] == 0);
    gSceneTypeStack[gSceneTypeStackDepth++] = ST_LOAD;
    gSaveLoadStarted = false;
    gSaveLoadFinished = false;
    gCallbackMade = false;
    gSceneTime = 0.0f;
    ResetTask::s_resetPaused = false;
}

/**
 * Offset/Address/Size: 0x25E0 | 0x800B2B68 | size: 0x1FC
 */
void RetryCB()
{
    gSceneTypeStackDepth = 0;

    switch (SaveLoadScene::mInstance->mSaveLoadMode)
    {
    case SaveLoadScene::SLM_AT_BOOT:
        gSceneTypeStack[gSceneTypeStackDepth++] = ST_SHOULD_LOAD_OR_SAVE;
        gSaveLoadStarted = false;
        gSaveLoadFinished = false;
        gCallbackMade = false;
        gSceneTime = 0.0f;
        ResetTask::s_resetPaused = false;
        break;

    case SaveLoadScene::SLM_SAVING:
        gSaveLoadStarted = false;
        gSceneTypeStack[gSceneTypeStackDepth++] = ST_SAVE;
        gSaveLoadFinished = false;
        gCallbackMade = false;
        gSceneTime = 0.0f;
        ResetTask::s_resetPaused = true;

        gSceneTypeStack[gSceneTypeStackDepth++] = ST_GAMESAVEIDTEST;
        gSaveLoadStarted = false;
        gSaveLoadFinished = false;
        gCallbackMade = false;
        gSceneTime = 0.0f;
        ResetTask::s_resetPaused = false;
        break;

    case SaveLoadScene::SLM_LOADING:
        gSceneTypeStack[gSceneTypeStackDepth++] = ST_LOAD;
        gSaveLoadStarted = false;
        gSaveLoadFinished = false;
        gCallbackMade = false;
        gSceneTime = 0.0f;
        ResetTask::s_resetPaused = false;
        break;

    case SaveLoadScene::SLM_ASK_BEFORE_SAVING:
        gSceneTypeStack[gSceneTypeStackDepth++] = ST_ASK_SAVE;
        gSaveLoadStarted = false;
        gSaveLoadFinished = false;
        gCallbackMade = false;
        gSceneTime = 0.0f;
        ResetTask::s_resetPaused = false;
        break;

    case SaveLoadScene::SLM_ASK_BEFORE_LOADING:
        gSceneTypeStack[gSceneTypeStackDepth++] = ST_ASK_LOAD;
        gSaveLoadStarted = false;
        gSaveLoadFinished = false;
        gCallbackMade = false;
        gSceneTime = 0.0f;
        ResetTask::s_resetPaused = false;
        break;
    }

    gSceneTypeStack[gSceneTypeStackDepth++] = ST_CHECKING;
    gCallbackMade = false;
    ResetTask::s_resetPaused = false;
    gSaveLoadStarted = true;
    gSaveLoadFinished = true;
    gIgnoreMinWait = false;
    gSceneTime = 0.0f;
    gContinueWithoutOperation = false;

    if (SaveLoadScene::mInstance->m_displayText != nullptr)
    {
        SaveLoadScene::mInstance->m_displayText->m_bVisible = true;
    }

    gRetryTimerDelay = 1.0f;
    SaveLoadScene::mInstance->SceneCreated();
}

/**
 * Offset/Address/Size: 0x25A0 | 0x800B2B28 | size: 0x40
 */
void DeleteFileCB()
{
    gSceneTypeStack[gSceneTypeStackDepth++] = ST_DELETE;
    gSaveLoadStarted = false;
    gSaveLoadFinished = false;
    gCallbackMade = false;
    gSceneTime = 0.0f;
    ResetTask::s_resetPaused = false;
}

/**
 * Offset/Address/Size: 0x2540 | 0x800B2AC8 | size: 0x60
 */
void FormatConfirmCB()
{
    SaveLoad::RememberCurrentMemCardSerialID(0);
    gSceneTypeStack[gSceneTypeStackDepth++] = ST_CONFIRM_FORMAT;
    gSaveLoadStarted = false;
    gSaveLoadFinished = false;
    gCallbackMade = false;
    ResetTask::s_resetPaused = false;
    gSceneTime = 999.9f;
}

/**
 * Offset/Address/Size: 0x2500 | 0x800B2A88 | size: 0x40
 */
void FormatCB()
{
    gSceneTypeStack[gSceneTypeStackDepth++] = ST_FORMAT;
    gSaveLoadStarted = false;
    gSaveLoadFinished = false;
    gCallbackMade = false;
    gSceneTime = 0.0f;
    ResetTask::s_resetPaused = false;
}

/**
 * Offset/Address/Size: 0x24E0 | 0x800B2A68 | size: 0x20
 */
void ManageMemCardCB()
{
    ResetTask::s_ResetMode = 1;
    ResetTask::s_ResetState = (ResetTask::s_ResetState == RS_RUNNING) ? RS_STARTRESET : ResetTask::s_ResetState;
}

/**
 * Offset/Address/Size: 0x247C | 0x800B2A04 | size: 0x64
 */
void OverwriteFileAndContinueCB()
{
    gCallbackMade = false;
    int stackIndex = --gSceneTypeStackDepth;
    gSaveLoadStarted = false;
    gSaveLoadFinished = false;
    ResetTask::s_resetPaused = (gSceneTypeStack[stackIndex] == 0);
    gSceneTypeStackDepth = stackIndex + 1;
    gSceneTypeStack[stackIndex] = ST_SAVE;
    gSaveLoadStarted = false;
    gSaveLoadFinished = false;
    gCallbackMade = false;
    gSceneTime = 0.0f;
    ResetTask::s_resetPaused = true;
}

/**
 * Offset/Address/Size: 0x2420 | 0x800B29A8 | size: 0x5C
 */
void CreateFileAndSaveCB()
{
    gCallbackMade = false;
    int stackIndex = --gSceneTypeStackDepth;
    SaveLoadScene* instance = SaveLoadScene::mInstance;
    gSaveLoadStarted = false;
    gSaveLoadFinished = false;
    ResetTask::s_resetPaused = (gSceneTypeStack[stackIndex] == 0);
    instance->SetupForAboutAutoSave();
}

/**
 * Offset/Address/Size: 0x15E4 | 0x800B1B6C | size: 0xE3C
 */
void CheckResults()
{
}

/**
 * Offset/Address/Size: 0x1408 | 0x800B1990 | size: 0x1DC
 */
void PushNoCardMessage()
{
}

/**
 * Offset/Address/Size: 0x11C8 | 0x800B1750 | size: 0x240
 */
SaveLoadScene::SaveLoadScene(SaveLoadScene::eSaveLoadMode)
{
}

/**
 * Offset/Address/Size: 0x1124 | 0x800B16AC | size: 0xA4
 */
SaveLoadScene::~SaveLoadScene()
{
}

/**
 * Offset/Address/Size: 0xF0C | 0x800B1494 | size: 0x218
 */
void SaveLoadScene::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x8C8 | 0x800B0E50 | size: 0x644
 */
void SaveLoadScene::Update(float)
{
}

/**
 * Offset/Address/Size: 0x7D4 | 0x800B0D5C | size: 0xF4
 */
bool SaveLoadScene::IsIOEnabled()
{
    return true;
}

/**
 * Offset/Address/Size: 0x6D8 | 0x800B0C60 | size: 0xFC
 */
void SaveLoadScene::SetupForAboutAutoSave()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x600 | 0x800B0B88 | size: 0xD8
 */
void SaveLoadScene::UpdateForAboutToSaveSlide()
{
}

/**
 * Offset/Address/Size: 0x224 | 0x800B07AC | size: 0x3DC
 */
void SaveLoadScene::HandleSaveLoadFinishedResult()
{
}

/**
 * Offset/Address/Size: 0xB0 | 0x800B0638 | size: 0x174
 */
void SaveLoadScene::StartSaveNow()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800B0588 | size: 0xB0
 */
void SaveLoadScene::UpdateCardRemovedFlag()
{
    if (!MemCard::s_InitDone)
    {
        return;
    }

    MemCard* memCard = g_MemCards[0];

    s32 result = CARDProbeEx(memCard->m_Slot, &memCard->m_CardInfo.CardSize, &memCard->m_CardInfo.SectorSize);
    if (result != 0)
    {
        memCard->m_State = IS_IDLE;
        memCard->m_CardState = CS_IDLE;
    }

    if (result == CARD_RESULT_NOCARD)
    {
        // Reload pointer in case it changed
        memCard = g_MemCards[0];

        result = CARDProbeEx(memCard->m_Slot, &memCard->m_CardInfo.CardSize, &memCard->m_CardInfo.SectorSize);
        if (result != 0)
        {
            memCard->m_State = IS_IDLE;
            memCard->m_CardState = CS_IDLE;
        }

        u8 currentNoCardState = (result == CARD_RESULT_NOCARD) ? 1 : 0;
        if (PreviousNoCardInSlotState != currentNoCardState)
        {
            WasCardRemoved = 1;
        }
    }
}

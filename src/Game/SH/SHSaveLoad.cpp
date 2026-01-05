#include "Game/SH/SHSaveLoad.h"

#include "Dolphin/card.h"
#include "Game/BaseGameSceneManager.h"
#include "Game/DB/SaveLoad.h"
#include "Game/FE/tlTextInstance.h"
#include "Game/ResetTask.h"
#include "types.h"

extern int gSceneTypeStackDepth;
extern int gSceneTypeStack[];
extern bool gSaveLoadStarted;
extern bool gSaveLoadFinished;
extern bool gCallbackMade;
extern float gSceneTime;
extern bool gIgnoreMinWait;
extern bool gContinueWithoutOperation;
extern bool gSaveLoadEnabled;
extern long gResult;

class MemCard;

extern bool s_InitDone__7MemCard;
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
    gSceneTypeStack[gSceneTypeStackDepth++] = 1;
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
}

/**
 * Offset/Address/Size: 0x25A0 | 0x800B2B28 | size: 0x40
 */
void DeleteFileCB()
{
    gSceneTypeStack[gSceneTypeStackDepth++] = SCENE_MAIN_MENU;
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
    gSceneTypeStack[gSceneTypeStackDepth++] = SCENE_STADIUM_SELECT;
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
    gSceneTypeStack[gSceneTypeStackDepth++] = 4;
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
    gSceneTypeStack[stackIndex] = 0;
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
void SaveLoadScene::IsIOEnabled()
{
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
    if (!s_InitDone__7MemCard)
    {
        return;
    }

    MemCard* memCard = g_MemCards[0];
    if (memCard == nullptr)
    {
        return;
    }

    // Access MemCard fields via pointer arithmetic
    // offset 0x0: status field 1
    // offset 0x4: channel
    // offset 0x8: status field 2
    // offset 0xC: memSize
    // offset 0x10: sectorSize
    s32* channel = (s32*)((u8*)memCard + 0x4);
    s32* memSize = (s32*)((u8*)memCard + 0xC);
    s32* sectorSize = (s32*)((u8*)memCard + 0x10);
    u32* status1 = (u32*)((u8*)memCard + 0x0);
    u32* status2 = (u32*)((u8*)memCard + 0x8);

    s32 result = CARDProbeEx(*channel, memSize, sectorSize);
    if (result != 0)
    {
        *status1 = 0;
        *status2 = 0;
    }

    if (result == CARD_RESULT_NOCARD)
    {
        // Reload pointer in case it changed
        memCard = g_MemCards[0];
        if (memCard != nullptr)
        {
            channel = (s32*)((u8*)memCard + 0x4);
            memSize = (s32*)((u8*)memCard + 0xC);
            sectorSize = (s32*)((u8*)memCard + 0x10);
            status1 = (u32*)((u8*)memCard + 0x0);
            status2 = (u32*)((u8*)memCard + 0x8);

            result = CARDProbeEx(*channel, memSize, sectorSize);
            if (result != 0)
            {
                *status1 = 0;
                *status2 = 0;
            }

            u8 currentNoCardState = (result == CARD_RESULT_NOCARD) ? 1 : 0;
            if (PreviousNoCardInSlotState != currentNoCardState)
            {
                WasCardRemoved = 1;
            }
        }
    }
}

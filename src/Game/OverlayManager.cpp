#include "Game/OverlayManager.h"
#include "Game/BaseGameSceneManager.h"
#include "Game/FE/feInGameMessengerManager.h"
#include "Game/GameInfo.h"
#include "Game/OverlayHandlerHUD.h"
#include "NL/nlSingleton.h"
#include "NL/nlTask.h"
#include "NL/nlBasicString.h"
#include "Game/OverlayHandlerInGameText.h"
nlSingleton<OverlayManager> OverlayManager::s_pInstance;

/**
 * Offset/Address/Size: 0xB48 | 0x800C8974 | size: 0x60
 */
OverlayManager::OverlayManager()
{
    this->mInGameTextOverlay = nullptr;
    this->mIsHUDSlideIn = false;
    this->mDoHUDSlideIn = false;
    this->mIsInHighlights = false;
    this->mIsDemoSlideVisible = false;
    this->mHUDDelay = 0.0f;
    this->mIGMessengerManager = nullptr;
}

/**
 * Offset/Address/Size: 0xAE8 | 0x800C8914 | size: 0x60
 */
OverlayManager::~OverlayManager()
{
}

/**
 * Offset/Address/Size: 0xA9C | 0x800C88C8 | size: 0x4C
 */
BaseSceneHandler* OverlayManager::Push(SceneList newOverlay, ScreenMovement movement, bool popFirst)
{
    BaseSceneHandler* newscene = BaseGameSceneManager::Push(newOverlay, movement, popFirst);
    if (newscene != NULL && newOverlay == OVERLAY_TEXT)
    {
        this->mInGameTextOverlay = (InGameTextOverlay*)newscene;
    }
    return newscene;
}

/**
 * Offset/Address/Size: 0xA7C | 0x800C88A8 | size: 0x20
 */
void OverlayManager::Pop()
{
    BaseGameSceneManager::Pop();
}

/**
 * Offset/Address/Size: 0xA50 | 0x800C887C | size: 0x2C
 */
void OverlayManager::SetCurrentTextOverlaySlide(OverlaySlideName slideName)
{
    if (this->mInGameTextOverlay != NULL)
    {
        mInGameTextOverlay->SetSlide(slideName);
    }
}

/**
 * Offset/Address/Size: 0x968 | 0x800C8794 | size: 0xE8
 */
void OverlayManager::Update(float fDeltaT)
{
    if (this->mIGMessengerManager != nullptr)
    {
        this->mIGMessengerManager->Update(fDeltaT);
    }
    if (this->mHUDDelay > 0.0f && nlTaskManager::m_pInstance->m_CurrState == 2)
    {
        this->mHUDDelay -= fDeltaT;
        if (this->mHUDDelay <= 0.0f)
        {
            this->mHUDDelay = 0.0f;
            if (mDoHUDSlideIn)
            {
                this->mHUDDelay = 0.0f;
                if (!mIsHUDSlideIn)
                {
                    HUDOverlay* hudSlideIn = (HUDOverlay*)GetScene(OVERLAY_HUD);
                    hudSlideIn->SetSlideIn();
                    mIsHUDSlideIn = true;
                }
            }
            else
            {
                this->mHUDDelay = 0.0f;
                if (mIsHUDSlideIn == 1)
                { // For some reason doing (mIsHudSlideIn) doesn't match?
                    HUDOverlay* hudSlideOut = (HUDOverlay*)GetScene(OVERLAY_HUD);
                    hudSlideOut->SetSlideOut();
                    mIsHUDSlideIn = false;
                }
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x330 | 0x800C815C | size: 0x638
 */
void OverlayManager::FEEventHandler(Event*, void*)
{
}

/**
 * Offset/Address/Size: 0x1A8 | 0x800C7FD4 | size: 0x188
 */
void OverlayManager::SetVisible(SceneList scene, bool visibility, bool overrideStateSettings)
{
    BasicString fileName;             // r1+0xC
    u32 uHashID;                      // r4
    BaseOverlayHandler* sceneHandler; // r3
    u32 state;                        // r4

    if (nlSingleton<GameInfoManager>::s_pInstance->m_unk_0x4960->m_unk_0x04 != SK_MYSTERY || scene == OVERLAY_HUD)
    {
    }
}

/**
 * Offset/Address/Size: 0xCC | 0x800C7EF8 | size: 0xDC
 */
void OverlayManager::HandleStateTransition(unsigned long to, unsigned long param_2)
{
}

/**
 * Offset/Address/Size: 0x88 | 0x800C7EB4 | size: 0x44
 */
void OverlayManager::DestroyMessengerManager()
{
    if (this->mIGMessengerManager != NULL)
    {
        delete this->mIGMessengerManager;
        this->mIGMessengerManager = 0;
    }
}

/**
 * Offset/Address/Size: 0x28 | 0x800C7E54 | size: 0x60
 */
void OverlayManager::ShowDemoSlide()
{
    class BaseSceneHandler* scene;
    if (!this->mIsDemoSlideVisible)
    {
        scene = BaseGameSceneManager::GetScene(OVERLAY_DEMO);
        if (scene != nullptr)
        {
            scene->SetVisible(true);
            this->mIsDemoSlideVisible = true;
        }
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x800C7E2C | size: 0x28
 */
void OverlayManager::RestartGoalOverlay()
{
}

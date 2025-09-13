#include "Game/OverlayHandlerSTSX2.h"
#include "Game/BaseSceneHandler.h"
#include "Game/FE/FEAudio.h"
#include "Game/Sys/eventman.h"
#include "NL/nlBundleFile.h"
#include "NL/nlTask.h"

/**
 * Offset/Address/Size: 0x280 | 0x8010705C | size: 0xA8
 */
STSX2Overlay::STSX2Overlay()
    : BaseOverlayHandler(2)
{
    this->m_EventHandler = 0;
    this->m_EventHandler = g_pEventManager->AddEventHandler(EventHandlerFunc(this->m_EventHandler->m_event, this), this, 1);
}

/**
 * Offset/Address/Size: 0x1E8 | 0x80106FC4 | size: 0x98
 */
STSX2Overlay::~STSX2Overlay()
{
    if (this->m_EventHandler)
    {
        g_pEventManager->RemoveEventHandler(this->m_EventHandler);
        this->m_EventHandler = NULL;
    }
}

/**
 * Offset/Address/Size: 0x1B8 | 0x80106F94 | size: 0x30
 */
void STSX2Overlay::SceneCreated()
{
    this->SetVisible(false);
}

/**
 * Offset/Address/Size: 0xF0 | 0x80106ECC | size: 0xC8
 */
/**
 * Offset/Address/Size: 0xF0 | 0x80106ECC | size: 0xC8
 */
void STSX2Overlay::Update(float fDeltaT)
{
    if (this->mVisibilityMask & nlTaskManager::m_pInstance->m_CurrState)
    {
        if (!m_bVisible)
        {
            FEAudio::EnableSounds(false);
        }
        BaseSceneHandler::Update(fDeltaT);
        if (m_bVisible)
        {
            TLSlide* CurrentSlide = this->m_pFEPresentation->m_currentSlide;
            if (CurrentSlide != NULL)
            {
                if (CurrentSlide->m_time >= (CurrentSlide->m_start + CurrentSlide->m_duration))
                {
                    SetVisible(false);
                }
            }
        }
        FEAudio::EnableSounds(true);
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x80106DDC | size: 0xF0
 */
EventCallback STSX2Overlay::EventHandlerFunc(Event* arg0, void* arg1)
{
    if (m_uHashID == 5)
    {
        if (this->m_pActiveScreenHandler->fnc1() == -1)
        {
            nlPrintf("Error: Trying to get event data on event with none!\n");
        }
    }
}

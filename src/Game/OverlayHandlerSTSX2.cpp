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
    : BaseOverlayHandler(0xA)
{
    m_uHashID = 0x102;
    m_EventHandler = NULL;
    m_EventHandler = g_pEventManager->AddEventHandler(EventHandlerFunc, this, 1);
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
void STSX2Overlay::EventHandlerFunc(Event* event, void* arg1)
{
    STSX2Overlay* self = static_cast<STSX2Overlay*>(arg1);

    if (event->m_uEventID == 5)
    {
        u32 id = self->m_pActiveScreenHandler->fnc1();
        if (id == -1)
        {
            nlPrintf("Error: Trying to get event data on event with none!\n");
            return;
        }

        id = self->m_pActiveScreenHandler->fnc1();
        if (id != 0x18A)
        {
            nlPrintf("Error: Event data ID mismatch!\n");
            return;
        }

        BaseScreenHandler* handler = self->m_pActiveScreenHandler;
        u16* handlerWord = (u16*)((u8*)handler + 0x6);
        u16 extracted = (*handlerWord >> 1) & 0x7FFF;

        if (extracted == 6)
        {
            FEPresentation* presentation = *(FEPresentation**)((u8*)event + 0x14);
            presentation->m_fadeDuration = presentation->m_currentSlide->m_start;
            presentation->Update(1.0f);

            // void** vtable = *(void***)event;
            // typedef void (*EventVFunc)(Event*, s32);
            // EventVFunc method = (EventVFunc)vtable[10]; // 0x28 / 4 = 10
            // method(event, 1);
        }
    }
}

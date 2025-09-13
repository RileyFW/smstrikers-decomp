#include "Game/SH/SHBackground.h"

/**
 * Offset/Address/Size: 0x16C | 0x800A9A18 | size: 0x44
 */
BackgroundScene::BackgroundScene()
    : BaseSceneHandler()
{
    m_unk_0x1C = 3;
    m_unk_0x20 = 3;
}

/**
 * Offset/Address/Size: 0x110 | 0x800A99BC | size: 0x5C
 */
BackgroundScene::~BackgroundScene()
{
}

/**
 * Offset/Address/Size: 0xA8 | 0x800A9954 | size: 0x68
 */
void BackgroundScene::SceneCreated()
{
    if (m_unk_0x1C != 3)
    {
        TLSlide* slide = m_pFEPresentation->m_currentSlide;
        switch (m_unk_0x1C)
        {
        case 1:
            slide->m_wrapMode = 1;
            break;
        case 2:
            slide->m_wrapMode = 0;
            break;
        }
        slide->m_time = 0.0f;
        slide->Update(0.0f);
    }
}

#define assert(condition) ((condition) ? ((void)0) : ((void)0))
#define _ASSERT(cond)

// #define ASSERT(cond) ((cond) || (OSPanic(__FILE__, __LINE__, "Failed assertion " #cond), 0))
// #define _ASSERT(cond) ((cond) || (OSPanic(__FILE__, __LINE__, "Assertion failed: " #cond), 0))

#define ASSERTLINE(line, cond)                      (void)0
#define ASSERTMSGLINE(line, cond, msg)              (void)0
#define ASSERTMSG1LINE(line, cond, msg, arg1)       (void)0
#define ASSERTMSG2LINE(line, cond, msg, arg1, arg2) (void)0
#define ASSERTMSGLINEV(line, cond, ...)             (void)0
// #endif

#define ASSERT(cond) ASSERTLINE(__LINE__, cond)

/**
 * Offset/Address/Size: 0x0 | 0x800A98AC | size: 0xA8
 */
void BackgroundScene::Update(float dt)
{
    if ((m_unk_0x20 != m_unk_0x1C) && (m_unk_0x1C != 3))
    {
        TLSlide* slide = m_pFEPresentation->m_currentSlide;
        switch (m_unk_0x1C)
        {
        case 1:
            slide->m_wrapMode = 1;
            break;
        case 2:
            slide->m_wrapMode = 0;
            break;
        }
        slide->m_time = 0.0f;
        slide->Update(0.0f);
    }

    ASSERT(m_unk_0x1C == 0);

    // assert(m_unk_0x1C == 0);
    // (m_unk_0x1C == 0) ? m_unk_0x1C : m_unk_0x1C; // just to produce "cmplwi r3, 0x0"

    BaseSceneHandler::Update(dt);
}

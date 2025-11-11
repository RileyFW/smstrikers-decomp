#include "Game/OverlayHandlerGoal.h"
#include "Game/FE/feNSNMessenger.h"
#include "Game/Game.h"

/**
 * Offset/Address/Size: 0x106C | 0x80104868 | size: 0xCF0
 */
// void FormatImpl<BasicString<unsigned short, Detail::TempStringAllocator>>::operator%<BasicString<unsigned short, Detail::TempStringAllocator>>(const BasicString<unsigned short, Detail::TempStringAllocator>&)
//{
// }

/**
 * Offset/Address/Size: 0xF40 | 0x8010473C | size: 0x12C
 */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, unsigned short[32], BasicString<unsigned short, Detail::TempStringAllocator>>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short(&)[32], const BasicString<unsigned short, Detail::TempStringAllocator>&)
//{
// }

/**
 * Offset/Address/Size: 0xE1C | 0x80104618 | size: 0x124
 */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, unsigned short[16], unsigned short[16]>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short(&)[16], const unsigned short(&)[16])
//{
// }

/**
 * Offset/Address/Size: 0x12C | 0x80103928 | size: 0xCF0
 */
// void FormatImpl<BasicString<unsigned short, Detail::TempStringAllocator>>::operator%<const unsigned short*>(const unsigned short* const&)
//{
// }

/**
 * Offset/Address/Size: 0x0 | 0x801037FC | size: 0x12C
 */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, const unsigned short*, unsigned short[32], unsigned short[32]>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short* const&, const unsigned short(&)[32], const unsigned short(&)[32])
//{
// }

/**
 * Offset/Address/Size: 0x140 | 0x801036A0 | size: 0x15C
 */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
//{
// }

/**
 * Offset/Address/Size: 0xBC | 0x8010361C | size: 0x84
 */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
//{
// }

/**
 * Offset/Address/Size: 0x38 | 0x80103598 | size: 0x84
 */
// void FEFinder<TLTextInstance, 3>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
//{
// }

/**
 * Offset/Address/Size: 0x0 | 0x80103560 | size: 0x38
 */
// void FEFinder<TLTextInstance, 3>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
//{
// }

/**
 * Offset/Address/Size: 0xBC | 0x8010337C | size: 0x1E4
 */
// void BasicString<char, Detail::TempStringAllocator>::AppendInPlace<Detail::TempStringAllocator>(const BasicString<char, Detail::TempStringAllocator>&)
//{
// }

/**
 * Offset/Address/Size: 0x0 | 0x801032C0 | size: 0xBC
 */
// void BasicString<char, Detail::TempStringAllocator>::Append<Detail::TempStringAllocator>(const BasicString<char, Detail::TempStringAllocator>&) const
//{
// }

/**
 * Offset/Address/Size: 0x3150 | 0x801031C0 | size: 0x100
 */
GoalOverlay::GoalOverlay()
    : BaseOverlayHandler(2)
{
}

/**
 * Offset/Address/Size: 0x30B8 | 0x80103128 | size: 0x98
 */
GoalOverlay::~GoalOverlay()
{
    if (mEventHandler != nullptr)
    {
        g_pEventManager->RemoveEventHandler(mEventHandler);
        mEventHandler = nullptr;
    }
}

/**
 * Offset/Address/Size: 0x30AC | 0x8010311C | size: 0xC
 */
void GoalOverlay::SceneCreated()
{
    mIsCreated = true;
}

/**
 * Offset/Address/Size: 0x305C | 0x801030CC | size: 0x50
 */
void GoalOverlay::Update(float dt)
{
    BaseSceneHandler::Update(dt);

    if (!mIsInOvertime)
    {
        if (g_pGame->m_eGameState == GS_OVERTIME)
        {
            mIsInOvertime = true;
        }
    }
}

/**
 * Offset/Address/Size: 0x2F44 | 0x80102FB4 | size: 0x118
 */
void GoalOverlay::eventHandler(Event*, void*)
{
}

/**
 * Offset/Address/Size: 0x19A8 | 0x80101A18 | size: 0x159C
 */
void GoalOverlay::UpdateGoalInfo(int, int, bool, int)
{
}

/**
 * Offset/Address/Size: 0x1590 | 0x80101600 | size: 0x418
 */
void GoalOverlay::SetHighlightNumber(int)
{
}

/**
 * Offset/Address/Size: 0xDA4 | 0x80100E14 | size: 0x7EC
 */
void GoalOverlay::DoMatchEndOverlay()
{
}

/**
 * Offset/Address/Size: 0x6E8 | 0x80100758 | size: 0x6BC
 */
void GoalOverlay::SetWinnerTitle()
{
}

/**
 * Offset/Address/Size: 0x20 | 0x80100090 | size: 0x6C8
 */
void GoalOverlay::DoCupWinOverlay()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80100070 | size: 0x20
 */
void GoalOverlay::Restart()
{
    if (mIsCreated)
    {
        m_pFEPresentation->m_fadeDuration = m_pFEPresentation->m_currentSlide->m_start;
    }
}

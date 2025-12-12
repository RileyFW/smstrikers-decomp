#ifndef _OVERLAYHANDLERINGAMETEXT_H_
#define _OVERLAYHANDLERINGAMETEXT_H_

#include "Game/BaseSceneHandler.h"
#include "Game/FE/feNSNMessenger.h"
#include "Game/OverlayManager.h"
#include "types.h"

struct InGameTextEntry
{
    // total size: 0xC
    enum OverlaySlideName mOverlayEnum; // offset 0x0, size 0x4
    const char* mSlideName;             // offset 0x4, size 0x4
    u32 mTaskVisibility;                // offset 0x8, size 0x4
};

static char* TEAM_SLIDE_NAMES[8] = {
    "DAISY",
    "DK",
    "LUIGI",
    "MARIO",
    "PEACH",
    "WALUIGI",
    "WARIO",
    "YOSHI"

}; // size: 0x20, address: 0x802BFE60
static const char* OVERLAY_HANDLER_LAYER_NAME = "Layer"; // size: 0x4, address: 0x80395EAC

static const struct InGameTextEntry IGTTable[8] = {
    { SLIDE_NAME_TEXT_GOAL, "GOAL!", 0 },
    { SLIDE_NAME_TEXT_KICKOFF, "KICKOFF!", 0 },
    { SLIDE_NAME_TEXT_WINNER, "WINNER!", 1 },
    { SLIDE_NAME_TEXT_PAUSE, "Pause", 1 },
    { SLIDE_NAME_TEXT_TIE, "TIE!", 1 },
    { SLIDE_NAME_TEXT_LOADING, "LOADING...", 1 },
    { SLIDE_NAME_TEXT_SHOOT, "Shoot!", 2 },
    { SLIDE_NAME_TEXT_REPLAY, "REPLAY", 16 }
}; // size: 0x60, address: 0x802AD8E0

class InGameTextOverlay : public BaseOverlayHandler
{
public:
    InGameTextOverlay();
    virtual ~InGameTextOverlay();
    virtual void Update(float);
    virtual void SceneCreated();
    void SetSlide(OverlaySlideName);
    void DisplayFinalScore();

    /*  0x28 */ OverlaySlideName mCurrentSlideName;
    /*  0x2C */ OverlaySlideName mPendingSlideName;
    /*  0x30 */ u16 mScoresBuffer[32];
    /*  0x70 */ u16 mWinnerBuffer[32];
}; // total size: 0xB0

/*
class StatsTracker
{
public:
    void Track(ePlayerStats, int, int, int, int, int, int);
};


class FEFinder<TLComponentInstance, 4>
{
public:
    void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
    void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
    void _Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
    void Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
};


class FEFinder<TLInstance, 3>
{
public:
    void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
    void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
    void _Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
    void Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
};


class FEFinder<TLTextInstance, 3>
{
public:
    void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
    void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
    void _Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
    void Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
};


class BasicString<unsigned short, Detail
{
public:
    void TempStringAllocator>::AppendInPlace<Detail::TempStringAllocator>(const BasicString<unsigned short, Detail::TempStringAllocator>&);
    void TempStringAllocator>::Append<Detail::TempStringAllocator>(const BasicString<unsigned short, Detail::TempStringAllocator>&) const;
};
*/
#endif // _OVERLAYHANDLERINGAMETEXT_H_

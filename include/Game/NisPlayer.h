#ifndef _NISPLAYER_H_
#define _NISPLAYER_H_

#include "Game/Camera/animcam.h"
#include "Game/Render/Nis.h"
#include "Game/Sys/eventman.h"
#include "NL/nlFile.h"
#include "NL/nlMath.h"

enum NisUseStadiumOffset
{
    NIS_NO_STADIUM_OFFSET = 0,
    NIS_AWAY_STADIUM_OFFSET = 1,
    NIS_HOME_STADIUM_OFFSET = 2,
};

enum NisUseFilter
{
    NIS_NO_FILTER = 0,
    NIS_FILTER = 1,
};

class NisPlayer
{
public:
    virtual ~NisPlayer();
    void SetExtraNameFilter(const char*);
    void ResetEffects();
    void IsMirrored(NisTarget, const char*, NisWinnerType) const;
    void TargetToIndex(NisTarget, int, NisWinnerType) const;
    void EventHandler(Event*);
    void PlayCharacterDirection();
    void Load(const char*, NisTarget, NisUseStadiumOffset, NisUseFilter, NisWinnerType);
    void GetTargetFilter(NisTarget, NisWinnerType) const;
    void AsyncLoad(nlFile*, void*, unsigned int, unsigned long);
    void LoadTriggers(Nis&);
    void Load(char*, unsigned int, NisHeader&);
    void Render() const;
    void Play();
    void Reset();
    void Update(float);
    void HandleAsyncs();
    bool WorldIsFrozen() const;
    void TimeLeft() const;
    NisPlayer();

    static NisPlayer* Instance();

    virtual void DoFunctionCall(unsigned int);

    /* 0x24,  */ bool mActive;                  // offset 0x24, size 0x1
    /* 0x28,  */ int mDictSize;                 // offset 0x28, size 0x4
    /* 0x2C,  */ NisHeader mDict[256];          // offset 0x2C, size 0xB800
    /* 0xB82C */ char* mMemory;                 // offset 0xB82C, size 0x4
    /* 0xB830 */ int mMaxNumBallsVisible;       // offset 0xB830, size 0x4
    /* 0xB834 */ Nis* mPlaying[4];              // offset 0xB834, size 0x10
    /* 0xB844 */ Nis* mLoaded[4];               // offset 0xB844, size 0x10
    /* 0xB854 */ NisHeader* mLoadQueue[4];      // offset 0xB854, size 0x10
    /* 0xB864 */ bool mAsyncStarted[4];         // offset 0xB864, size 0x4
    /* 0xB868 */ bool mLoadingFromBack;         // offset 0xB868, size 0x1
    /* 0xB86C */ int mUsedFromFront;            // offset 0xB86C, size 0x4
    /* 0xB870 */ int mUsedFromBack;             // offset 0xB870, size 0x4
    /* 0xB874 */ cAnimCamera mCamera;           // offset 0xB874, size 0xAC
    /* 0xB920 */ Nis* mNisForTriggerLoading;    // offset 0xB920, size 0x4
    /* 0xB924 */ int mWinnerSide[2];            // offset 0xB924, size 0x8
    /* 0xB92C */ nlVector3 mBeginPositions[10]; // offset 0xB92C, size 0x78
    /* 0xB9A4 */ char mExtraNameFilter[128];    // offset 0xB9A4, size 0x80

    static NisPlayer* m_pInstance;
}; // total size: 0xBA24

#endif // _NISPLAYER_H_

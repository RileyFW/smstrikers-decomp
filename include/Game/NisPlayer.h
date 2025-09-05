#ifndef _NISPLAYER_H_
#define _NISPLAYER_H_

#include "types.h"
#include "NL/nlFile.h"

class Nis;
struct NisHeader;
class Event;

// Temporary typedefs for unknown enum-like types
typedef int NisTarget;
typedef int NisWinnerType;
typedef int NisUseStadiumOffset;
typedef int NisUseFilter;

// void nlToLower<char>(char*);
// void nlToLower<char>(char);
// void nlStrLen<char>(const char*);

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

    static NisPlayer* m_pInstance;
};

#endif // _NISPLAYER_H_

#ifndef _REPLAYCHOREO_H_
#define _REPLAYCHOREO_H_

#include "types.h"
#include "Game/Replay.h"
#include "Game/Sys/eventman.h"

class ReplayChoreo
{
public:
    enum HighlightQuality
    {
        HIGHLIGHT_QUALITY_EMPTY = 0,
        HIGHLIGHT_QUALITY_SAVE = 1,
        HIGHLIGHT_QUALITY_GOAL_DECREASE_DIFF = 2,
        HIGHLIGHT_QUALITY_GOAL_EQUALIZER = 3,
        HIGHLIGHT_QUALITY_GOAL_INCREASE_DIFF = 4,
        NUM_QUALITY_LEVELS = 5,
    };

    class Highlight
    {
        Highlight() { };
    };

    void DoFunctionCall(unsigned int);
    void Instance();
    void LoadScript();
    void EventHandler(Event*);
    void Reset();
    void CalcAutoReplayScriptName(ReplayType) const;
    void StartAutoReplay(ReplayType);
    void FlushHighlights();
    void Update(float);
    void Done() const;
    void SaveHighlight(ReplayChoreo::HighlightQuality);
    void NumHighlights() const;
    ~ReplayChoreo();
};

#endif // _REPLAYCHOREO_H_

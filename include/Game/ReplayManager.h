#ifndef _REPLAYMANAGER_H_
#define _REPLAYMANAGER_H_

#include "Game/Sys/eventman.h"

// void Blend<RenderSnapshot>(const float*, const RenderSnapshot&, const RenderSnapshot&, RenderSnapshot&);
// void Replayable<0, SaveFrame, RenderSnapshot>(SaveFrame&, RenderSnapshot&);
// void Replayable<0, LoadFrame, RenderSnapshot>(LoadFrame&, RenderSnapshot&);
// void 0x8028D2B8..0x8028D2BC | size: 0x4;

class ReplayManager
{
public:
    ~ReplayManager();
    ReplayManager* Instance();
    void Initialize();
    void InitializeSnapshots();
    void Uninitialize();
    void GrabSnapshot();
    void GetMutableRenderSnapshot();
    void Flush();
    void ResetSnapshots();
    void PrepareForRecording();
    void SetCurrentTime(float);
    void EventHandler(Event*);
    void RenderSnapshotAt(float);

    // total size: 0x5108
    class RenderSnapshot mSnapshots[3]; // offset 0x0, size 0x5034
    class RenderSnapshot* mCurrent;     // offset 0x5034, size 0x4
    class RenderSnapshot* mPrevious;    // offset 0x5038, size 0x4
    class RenderSnapshot* mRender;      // offset 0x503C, size 0x4
    class cFollowCamera mDebugCamera;   // offset 0x5040, size 0xA0
    unsigned int mEvents;               // offset 0x50E0, size 0x4
    float mSpeed;                       // offset 0x50E4, size 0x4
    float mSpeedUp;                     // offset 0x50E8, size 0x4
    float mDeltaTime;                   // offset 0x50EC, size 0x4
    float mTime;                        // offset 0x50F0, size 0x4
    float mBlend[3];                    // offset 0x50F4, size 0xC
    class Replay* mReplay;              // offset 0x5100, size 0x4
    char* mMemory;                      // offset 0x5104, size 0x4
};

// class cFollowCamera
// {
// public:
//     ~cFollowCamera();
// };

// class RenderSnapshot
// {
// public:
//     RenderSnapshot();
//     ~RenderSnapshot();
// };

// class cBaseCamera
// {
// public:
//     void Reactivate();
//     void GetFOV() const;
//     ~cBaseCamera();
// };

// class Replay
// {
// public:
//     void Play<RenderSnapshot>(float, RenderSnapshot&, RenderSnapshot&, float*) const;
//     void Record<RenderSnapshot>(float, RenderSnapshot&, unsigned int);
// };

#endif // _REPLAYMANAGER_H_

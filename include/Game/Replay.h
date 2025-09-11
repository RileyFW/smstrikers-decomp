#ifndef _REPLAY_H_
#define _REPLAY_H_

enum ReplayType
{
    REPLAY_TYPE_GOAL = 6,
    REPLAY_TYPE_HIGHLIGHT = 7,
    REPLAY_TYPE_HYPER_STRIKE = 8,
    NUM_REPLAY_TYPES = 9,
};

class Replay
{
public:
    class Reel
    {
        Reel() { };
    };

    class Frame
    {
        Frame(char*, int, Frame*) { };
    };

    Replay(char*, int, int);
    ~Replay();

    void Next(Frame*, int) const;
    void TimeOfLastOccurence(unsigned int) const;
    void NewFrame();
    void IsReelValid(int) const;
    void DidOccurInLastNumSeconds(unsigned int, float) const;
    void LockReel(float, int, int);
    void BeginTime() const;
    void EndTime() const;
    void PlayReel(int);
};

// class SlotPool < Replay
// {
// public:
//     void Frame > ::~SlotPool();
// };

#endif // _REPLAY_H_

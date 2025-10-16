#ifndef _PRIORITYSTREAM_H_
#define _PRIORITYSTREAM_H_


class PriorityStream
{
public:
    void Reset();
    void PlayStream(unsigned long, float, bool, unsigned long, unsigned long, const char*);
    void Stop(unsigned long, unsigned long);
    void FakePause(unsigned long);
    void FakeResume(bool);
    void TrackIdleCB();
    void GrabCrowdStream(unsigned long);
};

#endif // _PRIORITYSTREAM_H_
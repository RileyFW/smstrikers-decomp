#ifndef _MAIN_H_
#define _MAIN_H_

#include "Game/Sys/clock.h"
#include "Game/Sys/audio.h"
#include "NL/nlTask.h"

extern bool g_e3_Build;
extern bool g_Europe;
extern int g_Language;

int GetRegion();

class ClockUpdateTask : public nlTask
{
public:
    virtual void Run(float dt)
    {
        ClockManager::Update(dt);
    }
    virtual const char* GetName() { return "Clock"; };
};

class AudioUpdateTask : public nlTask
{
public:
    virtual void Run(float dt)
    {
        Audio::Update(dt);
    }
    virtual const char* GetName() { return "Audio"; };
};

#endif // _MAIN_H_

#ifndef _BASICSTADIUM_H_
#define _BASICSTADIUM_H_

#include "types.h"

#include "Game/World.h"
#include "NL/nlConfig.h"

class Event;

class BasicStadium : public World
{
public:
    void BasicStadiumEventHandler(Event*, void*);

    BasicStadium(const char*);
    virtual ~BasicStadium();

    virtual void GetTerrainType(const nlVector3&) const;

    virtual void Render();
    virtual void Update(float);
    virtual void UpdateInReplay(float);
    void GetCurrentStadium();
    virtual void DoLoad();
    virtual void DoInitialize();
};

// class Config
// {
// public:
//     void TagValuePair::Get<BasicString<char, Detail::TempStringAllocator>>() const;
//     void Get<BasicString<char, Detail::TempStringAllocator>>(const char*, BasicString<char, Detail::TempStringAllocator>);
// };

#endif // _BASICSTADIUM_H_

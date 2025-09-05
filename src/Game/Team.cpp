#include "Game/Team.h"

cFielder* cTeam::GetDefense() const
{
    return this->defender;
}

cFielder* cTeam::GetMidfield() const
{
    return this->midfielder;
}

cFielder* cTeam::GetStriker() const
{
    return this->striker;
}

cFielder* cTeam::GetCaptain()
{
    return this->captain;
}

// Callback function used in qsort calls as an anonymous function for comparison
// Usage of return value is "cmpwi r3, 0x0", suggesting a signed int return value
static int MostDefensivePlayer(const void*, const void*)
{
    return 0;
}

// Same qsort usage as MostDefensivePlayer
static int MostOffensiveThreat(const void*, const void*)
{
    return 0;
}

// Same qsort usage as MostDefensivePlayer
static int BestAbleToInterceptBall(const void*, const void*)
{
    return 0;
}

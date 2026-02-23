#ifndef _FORMATIONSCRIPT_H_
#define _FORMATIONSCRIPT_H_

#include "Game/AI/FuzzyVariant.h"
#include "Game/Team.h"

class Fuzzy
{
public:
    static FuzzyVariant GetStrategicBallCarrier(cTeam*);
    static FuzzyVariant GetBestBallInterceptor(cTeam*);
    static FuzzyVariant GetBestDefensiveFormation(cTeam*);
    static FuzzyVariant GetBestOffensiveFormation(cTeam*);
    static FuzzyVariant GetBestBallFormationSet(cTeam*);
};

#endif // _FORMATIONSCRIPT_H_

#ifndef _FORMATIONSCRIPT_H_
#define _FORMATIONSCRIPT_H_

#include "Game/Team.h"

class Fuzzy
{
public:
    void GetBestDefensiveFormation(cTeam*);
    void GetBestOffensiveFormation(cTeam*);
    void GetBestBallFormationSet(cTeam*);
};

#endif // _FORMATIONSCRIPT_H_

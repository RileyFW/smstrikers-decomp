#ifndef _DEFAULTLOOSE_H_
#define _DEFAULTLOOSE_H_

#include "Game/AI/DecisionEntity.h"

class Fuzzy
{
public:
    void AbortLoosePlay(cDecisionEntity*);
    void DefaultLoosePlay(cDecisionEntity*);
};

#endif // _DEFAULTLOOSE_H_

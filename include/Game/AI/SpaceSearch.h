#ifndef _SPACESEARCH_H_
#define _SPACESEARCH_H_

#include "NL/nlMath.h"
#include "Game/Player.h"

enum eFieldDirection
{
    DIR_NONE = 0,
    DIR_UPFIELD = 1,
    DIR_DOWNFIELD = 2,
    DIR_TOWARD_TARGET = 3,
    DIR_AWAYFROM_TARGET = 4,
    DIR_CUSTOM = 5,
    NUM_DIRECTIONS = 6,
};

void CalcIdealShootingPositionScore(const nlVector3&, const nlVector3&, const nlVector2&, float);

class SSearchCutAndBreak
{
public:
    SSearchCutAndBreak(cPlayer*);
    void EvaluatePosition(const nlVector3&, const nlVector3&, eFieldDirection, unsigned short);
    ~SSearchCutAndBreak();
};

class SSearchRunToNet
{
public:
    ~SSearchRunToNet();
    SSearchRunToNet(cPlayer*);
    void EvaluatePosition(const nlVector3&, const nlVector3&, eFieldDirection, unsigned short);
};

class SSearchIdealShot
{
public:
    void EvaluatePosition(const nlVector3&, const nlVector3&, eFieldDirection, unsigned short);
    ~SSearchIdealShot();
};

class SSearchOpenLane
{
public:
    SSearchOpenLane(cPlayer*, cPlayer*);
    void EvaluatePosition(const nlVector3&, const nlVector3&, eFieldDirection, unsigned short);
    ~SSearchOpenLane();
};

class SSearchBestPass
{
public:
    ~SSearchBestPass();
    SSearchBestPass(cPlayer*, cPlayer*, bool, bool);
    void EvaluatePosition(const nlVector3&, const nlVector3&, eFieldDirection, unsigned short);
};

class SpaceSearch
{
public:
    ~SpaceSearch();
    void FindBestPosition(nlVector3&, const nlVector3&, eFieldDirection, const nlVector3*, float, unsigned short);
};

#endif // _SPACESEARCH_H_

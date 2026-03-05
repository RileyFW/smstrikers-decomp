#ifndef _COMMONSCRIPT_H_
#define _COMMONSCRIPT_H_

#include "NL/nlSingleton.h"
#include "NL/nlAVLTreeSlotPool.h"
#include "Game/AI/FuzzyVariant.h"

class cTeam;
class cPlayer;
class cFielder;

extern unsigned char g_bScriptQuestionCachingOn;
extern unsigned char g_bScriptQuestionCachingUseSTD;

// Stub for std::map<unsigned long, FuzzyVariant> - size 0x10
struct StdMapStub
{
    u8 _data[0x10];
};

class Fuzzy
{
public:
    void GetStrategicBallCarrier(cTeam*);
    void GetBestBallInterceptor(cTeam*);
    void GetSwapControllerScore(cPlayer*);
    static FuzzyVariant ShouldIStrafeBall(cFielder*);
    static FuzzyVariant ShouldIStrafeMark(cFielder*);
    void ShouldIMarkBallOwner(cFielder*);
    void ShouldIAttemptOneTimer(cFielder*);
    void GetBestLooseBallPassTarget(cFielder*);
    void GetBestPassTarget(cPlayer*);
    void GoodPassTargetFrom(cFielder*, cFielder*);
    void GetBestHitTarget(cFielder*);
    void GetPassDirection(cPlayer*, cPlayer*);
    void GoodToShoot(cFielder*);
    void GoodToChipShot(cFielder*);
    void GetBestPassReceiveAction(cFielder*);
    void GetBestLooseBallAction(cFielder*);
    void GetBestWindupShotAction(cFielder*);
    void GetPowerupToUseForPassReceiveDefence(cFielder*);
    void GetPowerupToUseForWindupDefence(cFielder*);
    void InDanger(cFielder*);
    void InDangerDelayed(cFielder*);
    void GoalieAndGonnaPickupBall(cPlayer*);
};

// class FuzzyVariant
// {
// public:
//     FuzzyVariant(const FuzzyVariant&);
// };

class SaveConfidence
{
public:
    ~SaveConfidence();
};

class ScriptQuestionCache : public nlSingleton<ScriptQuestionCache>
{
public:
    unsigned char Lookup(unsigned long, FuzzyVariant&, const char*);
    const FuzzyVariant& AddToCache(unsigned long, const FuzzyVariant&, const char*);
    void Clear();

    /* 0x00 */ nlAVLTreeSlotPool<unsigned long, FuzzyVariant, DefaultKeyCompare<unsigned long> > mQuestionCacheMap;
    /* 0x28 */ StdMapStub mQuestionCacheMapSTD;
    /* 0x38 */ int mTotalLookups;
    /* 0x3C */ int mCacheHits;
};

// class std
// {
// public:
//     void __red_black_tree<1>::rotate_left(std::__red_black_tree<1>::node_base*, std::__red_black_tree<1>::node_base*&);
//     void __red_black_tree<1>::rotate_right(std::__red_black_tree<1>::node_base*, std::__red_black_tree<1>::node_base*&);
//     void __red_black_tree<1>::balance_insert(std::__red_black_tree<1>::node_base*, std::__red_black_tree<1>::node_base*);
//     void __tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::insert_node_at(std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::node*, bool, bool, const std::pair<const unsigned long, FuzzyVariant>&);
//     void __tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::find<unsigned long>(const unsigned long&);
//     void __tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::find_or_insert<unsigned long, FuzzyVariant>(const unsigned long&);
// };

#endif // _COMMONSCRIPT_H_

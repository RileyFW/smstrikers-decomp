#include "NL/nlSingleton.h"
// #include "NL/nlAVLTreeSlotPool.h"
#include "Game/AI/Scripts/ScriptQuestion.h"

class ScriptQuestionCache : public nlSingleton<ScriptQuestionCache>
{

    // class nlAVLTreeSlotPool mQuestionCacheMap; // offset 0x0, size 0x28
    // class map mQuestionCacheMapSTD;            // offset 0x28, size 0x10
    int mTotalLookups; // offset 0x38, size 0x4
    int mCacheHits;    // offset 0x3C, size 0x4
}; // total size: 0x40

ScriptQuestionCache* ScriptQuestionCache::s_pInstance; // size: 0x4, address: 0x803977DC
unsigned char g_bScriptQuestionCachingUseSTD;          // size: 0x1, address: 0x803977D8
unsigned char g_bScriptQuestionCachingOn;              // size: 0x1, address: 0x80395390

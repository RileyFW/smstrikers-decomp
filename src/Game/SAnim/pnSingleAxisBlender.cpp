#include "Game/SAnim/pnSingleAxisBlender.h"

// #include "math.h"
#include "NL/nlMemory.h"

// f32 CANT_COLLIDE = *(f32*)__float_max;

SlotPool<cPN_SingleAxisBlender> cPN_SingleAxisBlender::m_SingleAxisBlenderSlotPool;

extern "C"
{
    void __ct__12SlotPoolBaseFv(void*);
    void* __register_global_object(void* object, void* destructor, void* registration);
}

struct SingleAxisBlenderDestructorChain
{
    SingleAxisBlenderDestructorChain* next;
    void* destructor;
    void* object;
};

void SingleAxisBlenderSlotPoolDtor(void* obj, int)
{
    ((SlotPool<cPN_SingleAxisBlender>*)obj)->~SlotPool<cPN_SingleAxisBlender>();
}

/**
 * Offset/Address/Size: 0x6B0 | 0x801EF3F4 | size: 0x68
 * TODO: 99.23% match - relocation symbols differ for slot-pool destructor and @157 registration chain.
 */
extern "C" void __sinit_pnSingleAxisBlender_cpp()
{
    static SingleAxisBlenderDestructorChain chain;
    SlotPoolBase* pool = (SlotPoolBase*)&cPN_SingleAxisBlender::m_SingleAxisBlenderSlotPool;

    __ct__12SlotPoolBaseFv(pool);
    pool->m_Initial = 0x10;
    SlotPoolBase::BaseAddNewBlock(pool, 0x28);
    pool->m_Delta = 0x10;
    __register_global_object(pool, (void*)SingleAxisBlenderSlotPoolDtor, &chain);
}

// /**
//  * Offset/Address/Size: 0x0 | 0x801EF4C0 | size: 0x6C
//  */
// cPN_SingleAxisBlender::~cPN_SingleAxisBlender()
// {
// }

/**
 * Offset/Address/Size: 0x5DC | 0x801EF320 | size: 0xD4
 */
cPN_SingleAxisBlender::cPN_SingleAxisBlender(int numChildren, void (*callback)(unsigned int, cPN_SingleAxisBlender*), unsigned int callbackParam, float weightSeek)
    : cPoseNode(numChildren)
{
    m_fSmoothedWeight = 0.0f;
    m_fWeightCallback = callback;
    m_nCallbackParam1 = callbackParam;
    m_fDesiredWeight = 0.0f;
    m_fWeightSeek = weightSeek;

    for (int i = 0; i < m_numChildren; ++i)
    {
        SetChild(i, nullptr);
    }

    if (m_fWeightCallback != nullptr)
    {
        m_fWeightCallback(m_nCallbackParam1, this);
        m_fSmoothedWeight = m_fDesiredWeight;
    }
}

/**
 * Offset/Address/Size: 0x518 | 0x801EF25C | size: 0xC4
 */
cPoseNode* cPN_SingleAxisBlender::Update(float dt)
{
    for (int i = 0; i < m_numChildren; ++i)
    {
        SetChild(i, GetChild(i)->Update(dt));
    }

    if (m_fWeightCallback != nullptr)
    {
        m_fWeightCallback(m_nCallbackParam1, this);
        m_fSmoothedWeight = m_fSmoothedWeight + m_fWeightSeek * (m_fDesiredWeight - m_fSmoothedWeight);
    }

    return this;
}

/**
 * Offset/Address/Size: 0x3CC | 0x801EF110 | size: 0x14C
 */
void cPN_SingleAxisBlender::Evaluate(int nodeIndex, float weight, cPoseAccumulator* accum) const
{
    if (m_fSmoothedWeight >= 1.0f)
    {
        GetChild(m_numChildren - 1)->Evaluate(nodeIndex, weight, accum);
        return;
    }

    float scaledWeight = m_fSmoothedWeight * (float)(m_numChildren - 1);

    int childIndex = (int)scaledWeight;

    float frac = scaledWeight - (float)childIndex;

    GetChild(childIndex)->Evaluate(nodeIndex, weight * (1.0f - frac), accum);
    GetChild(childIndex + 1)->Evaluate(nodeIndex, weight * frac, accum);
}

/**
 * Offset/Address/Size: 0x298 | 0x801EEFDC | size: 0x134
 */
void cPN_SingleAxisBlender::Evaluate(float weight, cPoseAccumulator* accum) const
{
    if (m_fSmoothedWeight >= 1.0f)
    {
        GetChild(m_numChildren - 1)->Evaluate(weight, accum);
        return;
    }

    float scaledWeight = m_fSmoothedWeight * (float)(m_numChildren - 1);

    int childIndex = (int)scaledWeight;

    float frac = scaledWeight - (float)childIndex;

    GetChild(childIndex)->Evaluate(weight * (1.0f - frac), accum);
    GetChild(childIndex + 1)->Evaluate(weight * frac, accum);
}

/**
 * Offset/Address/Size: 0x14C | 0x801EEE90 | size: 0x14C
 */
void cPN_SingleAxisBlender::BlendRootTrans(nlVector3* outBase, float weight, float* scratch)
{
    if (m_fSmoothedWeight >= 1.0f)
    {
        GetChild(m_numChildren - 1)->BlendRootTrans(outBase, weight, scratch);
        return;
    }

    float scaledWeight = m_fSmoothedWeight * (float)(m_numChildren - 1);

    int childIndex = (int)scaledWeight;

    float frac = scaledWeight - (float)childIndex;

    GetChild(childIndex)->BlendRootTrans(outBase, weight * (1.0f - frac), scratch);
    GetChild(childIndex + 1)->BlendRootTrans(outBase, weight * frac, scratch);
}

/**
 * Offset/Address/Size: 0x0 | 0x801EED44 | size: 0x14C
 */
void cPN_SingleAxisBlender::BlendRootRot(unsigned short* outRot, float weight, float* scratch)
{
    if (m_fSmoothedWeight >= 1.0f)
    {
        GetChild(m_numChildren - 1)->BlendRootRot(outRot, weight, scratch);
        return;
    }

    float scaledWeight = m_fSmoothedWeight * (float)(m_numChildren - 1);

    int childIndex = (int)scaledWeight;

    float frac = scaledWeight - (float)childIndex;

    GetChild(childIndex)->BlendRootRot(outRot, weight * (1.0f - frac), scratch);
    GetChild(childIndex + 1)->BlendRootRot(outRot, weight * frac, scratch);
}

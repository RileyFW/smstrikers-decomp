#ifndef _PNFEATHER_H_
#define _PNFEATHER_H_


class cPN_Feather
{
public:
    void GetType();
    cPN_Feather(cSHierarchy*, void (*)(unsigned int, cPN_Feather*), unsigned int);
    ~cPN_Feather();
    void ClearNodeWeights();
    void SetNodeWeight(int, float, float);
    void SetChildFeatherWeight(int, float);
    void SetNodeWeight(int, float);
    void BeginBlendIn(float);
    void BeginBlendOut(float);
    void Update(float);
    void Evaluate(float, cPoseAccumulator*) const;
    void Evaluate(int, float, cPoseAccumulator*) const;
    void BlendRootTrans(nlVector3*, float, float*);
    void BlendRootRot(unsigned short*, float, float*);
};


class SlotPool<cPN_Feather>
{
public:
    void ~SlotPool();
};

#endif // _PNFEATHER_H_
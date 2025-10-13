#ifndef _PNBLENDER_H_
#define _PNBLENDER_H_


class cPN_Blender
{
public:
    void GetType();
    ~cPN_Blender();
    cPN_Blender(cPoseNode*, cPoseNode*, float);
    void Update(float);
    void Evaluate(float, cPoseAccumulator*) const;
    void Evaluate(int, float, cPoseAccumulator*) const;
    void BlendRootTrans(nlVector3*, float, float*);
    void BlendRootRot(unsigned short*, float, float*);
};


class SlotPool<cPN_Blender>
{
public:
    void ~SlotPool();
};

#endif // _PNBLENDER_H_
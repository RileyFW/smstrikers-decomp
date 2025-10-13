#ifndef _ELECTRICFENCE_H_
#define _ELECTRICFENCE_H_

void UpdateElectricFence(float);
void StopDisplayingElectricFence();
void DisplayElectricFence();
void FreeElectricFence();
void InitializeElectricFence();
void EmitElectricFenceCharacterEffect(const nlVector3&, const nlVector3&, unsigned long);
void EmitElectricFenceBallEffect(const nlVector3&, const nlVector3&, unsigned long, bool);
void RenderElectricFence(EmissionController&);
void ElectricFenceFinished(EmissionController&);
void GetWallPoint(const nlVector3&, float, float, nlVector3&);
void nlListRemoveElement<ElectricFenceData>(ElectricFenceData**, ElectricFenceData*, ElectricFenceData**);
void nlListAddEnd<ElectricFenceData>(ElectricFenceData**, ElectricFenceData**, ElectricFenceData*);

class ElectricFenceData
{
public:
    ElectricFenceData(EmissionController*);
};


class SlotPool<ElectricFenceGeometry>
{
public:
    void ~SlotPool();
};


class SlotPool<ElectricFenceData>
{
public:
    void ~SlotPool();
};

#endif // _ELECTRICFENCE_H_
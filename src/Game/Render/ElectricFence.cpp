#include "Game/Render/ElectricFence.h"

static f32 sfStartAngle;
static f32 sfElectricFenceDisplayAngle;
static bool sbIsElectricFenceBeingDisplayed;

class EmissionManager
{
public:
    static void DestroyAll(bool);
};

// /**
//  * Offset/Address/Size: 0x0 | 0x8016C898 | size: 0x64
//  */
// void SlotPool<ElectricFenceData>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x1E4 | 0x8016C834 | size: 0x64
//  */
// void SlotPool<ElectricFenceGeometry>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x9C | 0x8016C6EC | size: 0x2C
//  */
// void nlListAddEnd<ElectricFenceData>(ElectricFenceData**, ElectricFenceData**, ElectricFenceData*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8016C650 | size: 0x9C
//  */
// void nlListRemoveElement<ElectricFenceData>(ElectricFenceData**, ElectricFenceData*, ElectricFenceData**)
// {
// }

/**
 * Offset/Address/Size: 0x1370 | 0x8016C3A0 | size: 0x2B0
 */
void GetWallPoint(const nlVector3&, float, float, nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x12CC | 0x8016C2FC | size: 0xA4
 */
void ElectricFenceFinished(EmissionController& controller)
{
    ElectricFenceData* node = ElectricFenceData::sActiveElectricFences.m_pStart;
    while (node != NULL)
    {
        if (node->mpEmissionController == &controller)
        {
            if (node != NULL)
            {
                nlListRemoveElement<ElectricFenceData>(&ElectricFenceData::sActiveElectricFences.m_pStart, node, &ElectricFenceData::sActiveElectricFences.m_pEnd);
                ElectricFenceData::numAllocated--;
                ElectricFenceGeometry* geom = node->mpGeometry;
                if (geom != NULL)
                {
                    SlotPoolEntry* oldFree = ElectricFenceGeometry::sElectricFenceGeometryPool.m_FreeList;
                    *(SlotPoolEntry**)geom = oldFree;
                    ElectricFenceGeometry::sElectricFenceGeometryPool.m_FreeList = (SlotPoolEntry*)geom;
                }
                SlotPoolEntry* oldFree2 = ElectricFenceData::sElectricFenceDataPool.m_FreeList;
                *(SlotPoolEntry**)node = oldFree2;
                ElectricFenceData::sElectricFenceDataPool.m_FreeList = (SlotPoolEntry*)node;
            }
            return;
        }
        node = node->next;
    }
}

/**
 * Offset/Address/Size: 0xEAC | 0x8016BEDC | size: 0x420
 */
void RenderElectricFence(EmissionController&)
{
}

/**
 * Offset/Address/Size: 0xC8C | 0x8016BCBC | size: 0x220
 */
void EmitElectricFenceBallEffect(const nlVector3&, const nlVector3&, unsigned long, bool)
{
}

/**
 * Offset/Address/Size: 0xAB8 | 0x8016BAE8 | size: 0x1D4
 */
void EmitElectricFenceCharacterEffect(const nlVector3&, const nlVector3&, unsigned long)
{
}

/**
 * Offset/Address/Size: 0xAB4 | 0x8016BAE4 | size: 0x4
 */
void InitializeElectricFence()
{
}

/**
 * Offset/Address/Size: 0x9E8 | 0x8016BA18 | size: 0xCC
 */
void FreeElectricFence()
{
    ElectricFenceData* node;
    while ((node = ElectricFenceData::sActiveElectricFences.m_pStart) != NULL)
    {
        if (node != NULL)
        {
            nlListRemoveElement<ElectricFenceData>(&ElectricFenceData::sActiveElectricFences.m_pStart, node, &ElectricFenceData::sActiveElectricFences.m_pEnd);
            ElectricFenceData::numAllocated--;
            ElectricFenceGeometry* geom = node->mpGeometry;
            if (geom != NULL)
            {
                SlotPoolEntry* oldFree = ElectricFenceGeometry::sElectricFenceGeometryPool.m_FreeList;
                *(SlotPoolEntry**)geom = oldFree;
                ElectricFenceGeometry::sElectricFenceGeometryPool.m_FreeList = (SlotPoolEntry*)geom;
            }
            SlotPoolEntry* oldFree2 = ElectricFenceData::sElectricFenceDataPool.m_FreeList;
            *(SlotPoolEntry**)node = oldFree2;
            ElectricFenceData::sElectricFenceDataPool.m_FreeList = (SlotPoolEntry*)node;
        }
    }
    SlotPoolBase::BaseFreeBlocks(&ElectricFenceData::sElectricFenceDataPool, sizeof(ElectricFenceData));
    SlotPoolBase::BaseFreeBlocks(&ElectricFenceGeometry::sElectricFenceGeometryPool, sizeof(ElectricFenceGeometry));
}

/**
 * Offset/Address/Size: 0x5A0 | 0x8016B5D0 | size: 0x448
 */
ElectricFenceData::ElectricFenceData(EmissionController*)
{
}

/**
 * Offset/Address/Size: 0x58C | 0x8016B5BC | size: 0x14
 */
void DisplayElectricFence()
{
    sbIsElectricFenceBeingDisplayed = true;
    sfElectricFenceDisplayAngle = sfStartAngle;
}

/**
 * Offset/Address/Size: 0x560 | 0x8016B590 | size: 0x2C
 */
void StopDisplayingElectricFence()
{
    sbIsElectricFenceBeingDisplayed = false;
    EmissionManager::DestroyAll(true);
}

/**
 * Offset/Address/Size: 0x0 | 0x8016B030 | size: 0x560
 */
void UpdateElectricFence(float)
{
}

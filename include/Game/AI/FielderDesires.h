#ifndef _FIELDERDESIRES_H_
#define _FIELDERDESIRES_H_

#include "Game/AI/ScriptAction.h"
#include "Game/AI/FilteredRandom.h"

class CommonDesireData
{
public:
    CommonDesireData();
    ~CommonDesireData();
    CommonDesireData(const CommonDesireData&);
    float CalcFuzzyChance(float fChance);
    bool CalcBoolChance(float fChance);
    float NormalizeConfidence(float fConfidence);

    /* 0x00 */ eFielderDesireState m_DesireType;
    /* 0x04 */ nlVector2 m_ConfidenceExtrema;
    /* 0x0C */ FilteredRandomReal m_RandomGenerator;
    /* 0x50 */ FilteredRandomChance m_RandomChanceGen;
}; // total size: 0x64

CommonDesireData& GetCommonDesireData(eFielderDesireState desireType);

// class FilteredRandomRange
// {
// public:
//     ~FilteredRandomRange();
// };

#endif // _FIELDERDESIRES_H_

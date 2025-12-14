#ifndef _FIELDERDESIRES_H_
#define _FIELDERDESIRES_H_

#include "Game/AI/ScriptAction.h"

class CommonDesireData
{
public:
    CommonDesireData();
    ~CommonDesireData();
    CommonDesireData(const CommonDesireData&);
    float CalcFuzzyChance(float fChance);
    bool CalcBoolChance(float fChance);
    float NormalizeConfidence(float fConfidence);
};

CommonDesireData& GetCommonDesireData(eFielderDesireState desireType);

// class FilteredRandomRange
// {
// public:
//     ~FilteredRandomRange();
// };

#endif // _FIELDERDESIRES_H_

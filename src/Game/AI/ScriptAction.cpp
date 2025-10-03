#include "Game/AI/ScriptAction.h"

#include "Game/AI/Fuzzy.h"
#include "Game/AI/FielderDesires.h"

class FuzzyVariant fvNotSet;

// /**
//  * Offset/Address/Size: 0x68 | 0x800620BC | size: 0x64
//  */
// void SlotPool<ScriptAction>::~SlotPool()
// {
// }

SlotPool<ScriptAction> ScriptAction::m_ScriptActionSlotPool;

/**
 * Offset/Address/Size: 0xB4 | 0x80061E68 | size: 0x1EC
 */
ScriptAction::ScriptAction(eScriptActionType action_type, float fConfidence)
{
    // Initialize the first FuzzyVariant (m_sDesireParams.opt1) at offset 0x18
    // First set the vtable to Variant, then call Variant constructor
    // *((void**)this + 0x18) = &__vt__7Variant;
    // ((Variant*)((char*)this + 0x18))->Variant(); // Call Variant constructor

    // // Set vtable to FuzzyVariant
    // *((void**)this + 0x18) = &__vt__12FuzzyVariant;

    // // Initialize the base Variant part of the first FuzzyVariant
    // *((void**)this + 0x34) = &__vt__7Variant;
    // ((Variant*)((char*)this + 0x34))->Variant(); // Call Variant constructor

    // // Initialize the second FuzzyVariant (m_sDesireParams.opt2) at offset 0x48
    // // First set the vtable to Variant, then call Variant constructor
    // *((void**)this + 0x48) = &__vt__7Variant;
    // ((Variant*)((char*)this + 0x48))->Variant(); // Call Variant constructor

    // // Set vtable to FuzzyVariant
    // *((void**)this + 0x48) = &__vt__12FuzzyVariant;

    // // Initialize the base Variant part of the second FuzzyVariant
    // *((void**)this + 0x64) = &__vt__7Variant;
    // ((Variant*)((char*)this + 0x64))->Variant(); // Call Variant constructor

    // Initialize member variables with default values
    m_fConfidence = 0.0f;                                    // @252 = 0.0f
    m_sDesireParams.fDuration = 0.0f;                        // @253 = 0.0f
    m_sDesireParams.eDesireType = FIELDERDESIRE_END_OF_LIST; // -1

    // Copy data from fvNotSet to both FuzzyVariants
    // This appears to be copying a default/not-set state
    m_sDesireParams.opt1 = fvNotSet;
    m_sDesireParams.opt2 = fvNotSet;

    // memcpy((char*)this + 0x1C, &fvNotSet, sizeof(FuzzyVariant));
    // memcpy((char*)this + 0x4C, &fvNotSet, sizeof(FuzzyVariant));

    // Set the constructor parameters
    m_eType = action_type;
    m_fSelectionChance = fConfidence;
    m_sPlayParams.ePlayType = 0;
    m_sPlayParams.fDuration = 0.0f;
}

/**
 * Offset/Address/Size: 0x64 | 0x80061E18 | size: 0x50
 */
float ScriptAction::CalcSelectionChance()
{
    float fChance;
    if (m_eType == SAT_SET_DESIRE)
    {
        fChance = GetCommonDesireData(m_sDesireParams.eDesireType).CalcFuzzyChance(m_fSelectionChance);
        return fChance;
    }
    fChance = RandomChance(m_fSelectionChance);
    return fChance;
}

/**
 * Offset/Address/Size: 0x0 | 0x80061DB4 | size: 0x64
 */
bool ScriptAction::RollChanceDice()
{
    if (m_eType == SAT_SET_DESIRE)
    {
        return GetCommonDesireData(m_sDesireParams.eDesireType).CalcBoolChance(m_fSelectionChance);
    }
    else
    {
        return RandomChance(m_fSelectionChance) >= 0.0f;
    }
}

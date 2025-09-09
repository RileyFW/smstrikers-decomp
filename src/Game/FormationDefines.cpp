#include "Game/FormationDefines.h"

// /**
//  * Offset/Address/Size: 0x334 | 0x8003C1B4 | size: 0xFC
//  */
// void Detail::LexicalCastImpl<BasicString<char, Detail::TempStringAllocator>, float>::Do(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x304 | 0x8003C184 | size: 0x30
//  */
// void LexicalCast<BasicString<char, Detail::TempStringAllocator>, float>(const float&)
// {
// }

// /**
//  * Offset/Address/Size: 0x204 | 0x8003C084 | size: 0x100
//  */
// void Detail::LexicalCastImpl<BasicString<char, Detail::TempStringAllocator>, int>::Do(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x1D4 | 0x8003C054 | size: 0x30
//  */
// void LexicalCast<BasicString<char, Detail::TempStringAllocator>, int>(const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x30 | 0x8003BEB0 | size: 0x1A4
//  */
// void Detail::LexicalCastImpl<BasicString<char, Detail::TempStringAllocator>, bool>::Do(bool)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8003BE80 | size: 0x30
//  */
// void LexicalCast<BasicString<char, Detail::TempStringAllocator>, bool>(const bool&)
// {
// }

/**
 * Offset/Address/Size: 0x64 | 0x8003BE64 | size: 0x1C
 */
// FormationSet::FormationSet()
// {
//     m_ID = -1;
//     m_NumFormationDefs = 0;
//     FormationSpec* m_FormationDefArray = NULL;
//     m_AutoDelete = false;
// }

// /**
//  * Offset/Address/Size: 0x50 | 0x8003BE50 | size: 0x14
//  */
// FormationPos::FormationPos()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8003BE00 | size: 0x50
//  */
// FormationSpec::FormationSpec()
// {
// }

// /**
//  * Offset/Address/Size: 0xA8 | 0x8003BD7C | size: 0x84
//  */
// void Config::TagValuePair::Get<BasicString<char, Detail::TempStringAllocator> >() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8003BCD4 | size: 0xA8
//  */
// void Config::Get<BasicString<char, Detail::TempStringAllocator> >(const char*, BasicString<char, Detail::TempStringAllocator>)
// {
// }

/**
 * Offset/Address/Size: 0xE10 | 0x8003BC20 | size: 0xB4
 */
void FieldLocToAILoc(nlVector3&, const nlVector3&, eTeamSide)
{
}

/**
 * Offset/Address/Size: 0xD5C | 0x8003BB6C | size: 0xB4
 */
void AILocToFieldLoc(nlVector3&, const nlVector3&, eTeamSide)
{
}

/**
 * Offset/Address/Size: 0xD24 | 0x8003BB34 | size: 0x38
 */
void FormationPos::GetLocationForTeam(nlVector2& dest, int teamId) const
{
    if (teamId == 0)
    {
        dest = m_Location;
        return;
    }
    nlVec2Set(dest, -m_Location.f.x, -m_Location.f.y);
}

/**
 * Offset/Address/Size: 0xCF0 | 0x8003BB00 | size: 0x34
 */
void FormationSpec::GetKeyLocation() const
{
}

/**
 * Offset/Address/Size: 0xC94 | 0x8003BAA4 | size: 0x5C
 */
void FormationSpec::CalculateExtents(nlVector2&, nlVector2&, const nlVector2&) const
{
}

/**
 * Offset/Address/Size: 0xC84 | 0x8003BA94 | size: 0x10
 */
FormationSpec* FormationSet::GetFormationSpec(int index) const
{
    return &m_FormationDefArray[index];
}

/**
 * Offset/Address/Size: 0xC08 | 0x8003BA18 | size: 0x7C
 */
void FormationSet::GetFormationSpecFromID(int) const
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8003AE10 | size: 0xC08
 */
void FormationSet::LoadFormationSets(const char*, int&)
{
}

#include "Game/FormationDefines.h"

static const nlVector3 v3Zero = { 0.0f, 0.0f, 0.0f };

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
nlVector2& FormationSpec::GetKeyLocation() const
{
    if (m_iKeyIndex >= 0 && m_iKeyIndex < 4)
    {
        return const_cast<nlVector2&>(m_Positions[m_iKeyIndex].m_Location);
    }
    return *(nlVector2*)&const_cast<nlVector3&>(v3Zero);
}

/**
 * Offset/Address/Size: 0xC94 | 0x8003BAA4 | size: 0x5C
 */
void FormationSpec::CalculateExtents(nlVector2& minOut, nlVector2& maxOut, const nlVector2& input) const
{
    const float fieldHalfWidth = 18.541899f;
    const float fieldHalfHeight = 10.87425f;

    minOut.f.x = -fieldHalfWidth + (input.f.x - m_v2Min.f.x);
    minOut.f.y = -fieldHalfHeight + (input.f.y - m_v2Min.f.y);
    maxOut.f.x = fieldHalfWidth + (input.f.x - m_v2Max.f.x);
    maxOut.f.y = fieldHalfHeight + (input.f.y - m_v2Max.f.y);
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
FormationSpec* FormationSet::GetFormationSpecFromID(int formationID) const
{
    if (formationID < 0)
    {
        return nullptr;
    }
    if (formationID >= m_NumFormationDefs)
    {
        // Fall through to linear search
    }
    else
    {
        // Try direct index access first
        FormationSpec* spec = &m_FormationDefArray[formationID];
        if (spec->m_ID == formationID)
        {
            return spec;
        }
    }

    // Linear search through all formation defs
    FormationSpec* array = m_FormationDefArray;
    for (int i = 0; i < m_NumFormationDefs; i++)
    {
        if (array->m_ID == formationID)
        {
            return array;
        }
        array++;
    }

    return nullptr;
}

/**
 * Offset/Address/Size: 0x0 | 0x8003AE10 | size: 0xC08
 */
void FormationSet::LoadFormationSets(const char*, int&)
{
}

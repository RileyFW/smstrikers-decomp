#include "Game/CharacterTemplate.h"

cCharacter* g_pCharacters[10];
static tCharacterTemplateInfo g_aCharacterTemplateInfo[13];

s32 skiptexture = 0xFFFFFFFF;

static const char* const s_GoalieCharacterNames[9] = {
    "daisygoalie",      // @1109
    "donkeykonggoalie", // @1111
    "luigigoalie",      // @1113
    "mariogoalie",      // @1100
    "peachgoalie",      // @1115
    "waluigigoalie",    // @1117
    "wariogoalie",      // @1119
    "yoshigoalie",      // @1121
    "superteamgoalie"   // @1123
};

static const char* const s_GoalieTexturePaths[9] = {
    "characters/daisygoalie/daisygoalie.glt",           // @1110
    "characters/donkeykonggoalie/donkeykonggoalie.glt", // @1112
    "characters/luigigoalie/luigigoalie.glt",           // @1114
    "characters/mariogoalie/mariogoalie.glt",           // @1103
    "characters/peachgoalie/peachgoalie.glt",           // @1116
    "characters/waluigigoalie/waluigigoalie.glt",       // @1118
    "characters/wariogoalie/wariogoalie.glt",           // @1120
    "characters/yoshigoalie/yoshigoalie.glt",           // @1122
    "characters/superteamgoalie/superteamgoalie.glt"    // @1124
};

// tGoalieTemplateInfo g_GoalieTextureInfo[9];

// Global goalie texture info array
tGoalieTemplateInfo g_GoalieTextureInfo[9] = {
    { s_GoalieCharacterNames[0], s_GoalieTexturePaths[0], nullptr },
    { s_GoalieCharacterNames[1], s_GoalieTexturePaths[1], nullptr },
    { s_GoalieCharacterNames[2], s_GoalieTexturePaths[2], nullptr },
    { s_GoalieCharacterNames[3], s_GoalieTexturePaths[3], nullptr },
    { s_GoalieCharacterNames[4], s_GoalieTexturePaths[4], nullptr },
    { s_GoalieCharacterNames[5], s_GoalieTexturePaths[5], nullptr },
    { s_GoalieCharacterNames[6], s_GoalieTexturePaths[6], nullptr },
    { s_GoalieCharacterNames[7], s_GoalieTexturePaths[7], nullptr },
    { s_GoalieCharacterNames[8], s_GoalieTexturePaths[8], nullptr }
};

/**
 * Offset/Address/Size: 0x0 | 0x800122E8 | size: 0x1C0
 */
s32 GetGoalieIndex(int arg0)
{
    if (arg0 == 0)
    {
        cCharacter** ptr = g_pCharacters;
        for (s32 i = 0; i < 10; ++i, ptr++)
        {
            if (*ptr == g_pCharacters[8])
                return i;
        }
        return -1;
    }

    cCharacter** ptr = g_pCharacters;
    for (s32 i = 0; i < 10; ++i, ptr++)
    {
        if (*ptr == g_pCharacters[9])
            return i;
    }
    return -1;
}

/**
 * Offset/Address/Size: 0x1C0 | 0x800124A8 | size: 0xD4
 */
s32 GetCharacterIndex(const cCharacter* character)
{
    cCharacter** ptr = g_pCharacters;
    for (s32 i = 0; i < 10; ++i, ptr++)
    {
        if (*ptr == character)
            return i;
    }
    return -1;
}

/**
 * Offset/Address/Size: 0x294 | 0x8001257C | size: 0x6C0
 */
void DestroyCharacters()
{
}

/**
 * Offset/Address/Size: 0x954 | 0x80012C3C | size: 0x51C
 */
void CreateCharacters()
{
}

/**
 * Offset/Address/Size: 0xE70 | 0x80013158 | size: 0x634
 */
void CreateGoalie(eCharacterClass, bool)
{
}

/**
 * Offset/Address/Size: 0x14A4 | 0x8001378C | size: 0x5FC
 */
void CreateSidekick(int, int, eCharacterClass, eCharacterClass, bool)
{
}

/**
 * Offset/Address/Size: 0x1AA0 | 0x80013D88 | size: 0x1C
 */
s32 SidekickTexture_cb(unsigned long arg0)
{
    s32 var_r4 = -1;
    if (arg0 != skiptexture)
    {
        var_r4 = arg0;
    }
    return var_r4;
}

/**
 * Offset/Address/Size: 0x1ABC | 0x80013DA4 | size: 0x240
 */
void CreateCharacter(int, int, eCharacterClass, bool)
{
}

/**
 * Offset/Address/Size: 0x1CFC | 0x80013FE4 | size: 0x3F0
 */
void CharacterLoadingGuts(tCharacterTemplate*, const tCharacterTemplateInfo&, eCharacterClass, bool)
{
}

/**
 * Offset/Address/Size: 0x20EC | 0x800143D4 | size: 0x3C
 */
bool IsCaptain(eCharacterClass cc)
{
    if (((cc - 1) <= 1U) || ((cc - 5) <= 2U) || ((cc - 9) <= 2U) || (cc == 0xC))
    {
        return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0x2128 | 0x80014410 | size: 0x34
 */
char* GetCharacterName(eCharacterClass cc)
{
    if (cc < 13)
    {
        return (char*)g_aCharacterTemplateInfo[cc].szCharName;
    }
    return (char*)g_GoalieTextureInfo[cc - 13].szCharName;
}

// /**
//  * Offset/Address/Size: 0x0 | 0x80014444 | size: 0x10
//  */
// void DLListContainerBase<GCAudioStreaming::StereoAudioStream*, BasicSlotPool<DLListEntry<GCAudioStreaming::StereoAudioStream*>>>::DeleteEntry(DLListEntry<GCAudioStreaming::StereoAudioStream*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x10 | 0x80014454 | size: 0x90
//  */
// void DLListContainerBase<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL, BasicSlotPool<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>>::DeleteEntry(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xA0 | 0x800144E4 | size: 0x10
//  */
// void DLListContainerBase<AudioStreamTrack::StreamTrack::QUEUED_STREAM, nlStaticArrayAllocator<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>, 4>>::DeleteEntry(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800144F4 | size: 0x34
//  */
// void WalkHelper<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL, DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>, AudioStreamTrack::TrackManagerBase::FadeManager>::Callback(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80014528 | size: 0x24
//  */
// void ListContainerBase<cSHierarchy*, NewAdapter<ListEntry<cSHierarchy*>>>::DeleteEntry(ListEntry<cSHierarchy*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x24 | 0x8001454C | size: 0x24
//  */
// void ListContainerBase<AnimRetargetList*, NewAdapter<ListEntry<AnimRetargetList*>>>::DeleteEntry(ListEntry<AnimRetargetList*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80014570 | size: 0x48
//  */
// void Function0<void>::FunctorBase::~FunctorBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800145B8 | size: 0x60
//  */
// CharacterPhysicsData::~CharacterPhysicsData()
// {
// }

// /**
//  * Offset/Address/Size: 0x60 | 0x80014618 | size: 0xE0
//  */
// SebringAnimTagScriptInterpreter::~SebringAnimTagScriptInterpreter()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800146F8 | size: 0xD0
//  */
// AnimTagScriptInterpreter::~AnimTagScriptInterpreter()
// {
// }

// /**
//  * Offset/Address/Size: 0xD0 | 0x800147C8 | size: 0x4
//  */
// void AnimTagScriptInterpreter::TriggerFired(unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800147CC | size: 0x34
//  */
// void LexicalCast<bool, const char*>(const char* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x34 | 0x80014800 | size: 0x20
//  */
// void LexicalCast<bool, float>(const float&)
// {
// }

// /**
//  * Offset/Address/Size: 0x54 | 0x80014820 | size: 0x14
//  */
// void LexicalCast<bool, int>(const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x68 | 0x80014834 | size: 0x8
//  */
// void LexicalCast<bool, bool>(const bool&)
// {
// }

// /**
//  * Offset/Address/Size: 0x70 | 0x8001483C | size: 0x94
//  */
// void 0x800148D0..0x800149F0 | size: 0x120
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800148D0 | size: 0x68
//  */
// void nlWalkList<ListEntry<AnimRetargetList*>, ListContainerBase<AnimRetargetList*, NewAdapter<ListEntry<AnimRetargetList*>>>>(ListEntry<AnimRetargetList*>*, ListContainerBase<AnimRetargetList*, NewAdapter<ListEntry<AnimRetargetList*>>>*, void (ListContainerBase<AnimRetargetList*, NewAdapter<ListEntry<AnimRetargetList*>>>::*)(ListEntry<AnimRetargetList*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x68 | 0x80014938 | size: 0x68
//  */
// void nlWalkList<ListEntry<cSHierarchy*>, ListContainerBase<cSHierarchy*, NewAdapter<ListEntry<cSHierarchy*>>>>(ListEntry<cSHierarchy*>*, ListContainerBase<cSHierarchy*, NewAdapter<ListEntry<cSHierarchy*>>>*, void (ListContainerBase<cSHierarchy*, NewAdapter<ListEntry<cSHierarchy*>>>::*)(ListEntry<cSHierarchy*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xD0 | 0x800149A0 | size: 0x28
//  */
// void nlListAddStart<ListEntry<AnimRetargetList*>>(ListEntry<AnimRetargetList*>**, ListEntry<AnimRetargetList*>*, ListEntry<AnimRetargetList*>**)
// {
// }

// /**
//  * Offset/Address/Size: 0xF8 | 0x800149C8 | size: 0x28
//  */
// void nlListAddStart<ListEntry<cSHierarchy*>>(ListEntry<cSHierarchy*>**, ListEntry<cSHierarchy*>*, ListEntry<cSHierarchy*>**)
// {
// }

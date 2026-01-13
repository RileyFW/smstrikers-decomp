#ifndef _FEHELPFUNCS_H_
#define _FEHELPFUNCS_H_

#include "Game/GameInfo.h"
#include "Game/Team.h"
#include "Game/TrophyInfo.h"
#include "Game/DB/Cup.h"
#include "Game/DB/UserOptions.h"

#include "Game/FE/tlTextInstance.h"
#include "Game/Render/Nis.h"

struct NameTeamEntry
{
    const char* name;
    eTeamID id;
};

extern NameTeamEntry NameTeamTable[9];

struct NameSidekickEntry
{
    const char* name;
    eSidekickID id;
};

extern NameSidekickEntry NameSidekickTable[4];

void MakeTextBoxReallyWide(TLTextInstance&);
const char* GetCupStreamName(eTrophyType);
const char* GetMemCardDescription();
const char* GetMemCardTitle();
void EnableAutoPressed();
TLInstance* FindComponent(TLSlide*, const char*);
unsigned long GetLOCRank(int);
eSidekickID ConvertToSidekickID(const char*);
eTeamID ConvertToTeamID(const char*);
const char* GetSidekickName(eSidekickID);
char* GetTeamName(eTeamID);
NisCharacterClass ConvertToCharacterClass(eSidekickID);
NisCharacterClass ConvertToCharacterClass(eTeamID);
unsigned long GetLOCTrophyName(eTrophyType);
unsigned long GetLOCStandingsName(GameInfoManager::eGameModes);
unsigned long GetLOCModeName(GameInfoManager::eGameModes);
unsigned long GetLOCTeamName(eTeamID);
unsigned long GetLOCSidekickName(eSidekickID);
unsigned long GetLOCCharacterName(eTeamID, bool, bool);
unsigned long GetStadiumStringID(eStadiumID);

// class TakeGameMemSnapshot
// {
// public:
//     void WriteToDisk();
//     void ResetTimers();
//     void Update(float);
//     void Format<BasicString<char, Detail::TempStringAllocator>, unsigned long, unsigned int, unsigned int>(const BasicString<char, Detail::TempStringAllocator>&, const unsigned long&, const unsigned int&, const unsigned int&);
//     void FormatImpl<BasicString<char, Detail::TempStringAllocator> >::operator BasicString<char, Detail::TempStringAllocator>() const;
//     void FormatImpl<BasicString<char, Detail::TempStringAllocator> >::operator% <unsigned int>(const unsigned int&);
//     void FormatImpl<BasicString<char, Detail::TempStringAllocator> >::operator% <unsigned long>(const unsigned long&);
//     void LexicalCast<BasicString<char, Detail::TempStringAllocator>, unsigned long>(const unsigned long&);
//     void Detail::LexicalCastImpl<BasicString<char, Detail::TempStringAllocator>, unsigned long>::Do(unsigned long);
//     void LexicalCast<BasicString<char, Detail::TempStringAllocator>, unsigned int>(const unsigned int&);
//     void Detail::LexicalCastImpl<BasicString<char, Detail::TempStringAllocator>, unsigned int>::Do(unsigned int);
// };

class FECharacterSound
{
public:
    static void PlayCaptainSlideIn(eTeamID);
    static void PlaySidekickName(eSidekickID);
    static const char* PlayCaptainName(eTeamID);
};

// class CaptainSidekickFilename
// {
// public:
//     void Build(CaptainSidekickFilename::Type, char*, int, int, int);
// };

// class SingleHighlite
// {
// public:
//     void CloseItem(TLComponentInstance*);
//     void OpenItem(TLComponentInstance*);
//     void TempDisableSound();
// };

// class DoubleHighlite
// {
// public:
//     void CloseItem(TLComponentInstance*);
//     void OpenItem(TLComponentInstance*);
//     void TempDisableSound();
// };

// class GetLOCDifficultyName(GameplaySettings
// {
// public:
//     void eSkillLevel);
// };

// class GetLOCStandingsName(GameInfoManager
// {
// public:
//     void eGameModes);
// };

// class GetLOCModeName(GameInfoManager
// {
// public:
//     void eGameModes);
// };

// class FEFinder<TLImageInstance, 2>
// {
// public:
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// };

// class FEFinder<TLComponentInstance, 4>
// {
// public:
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// };

#endif // _FEHELPFUNCS_H_

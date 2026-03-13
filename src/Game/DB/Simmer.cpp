#include "Game/DB/Simmer.h"
#include "Game/GameInfo.h"
#include "NL/nlLexicalCast.h"
#include "NL/nlString.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/stdio.h"

typedef struct _FILE FILE;
extern FILE* fopen(const char*, const char*);
extern int fclose(FILE*);
extern char* fgets(char*, int, FILE*);

static const char* SIM_FILE = "";

// /**
//  * Offset/Address/Size: 0x3D0 | 0x80191868 | size: 0x38
//  */
// void Tokenizer<BasicString<char, Detail::TempStringAllocator> >::begin() const
// {
// }

// /**
//  * Offset/Address/Size: 0x398 | 0x80191830 | size: 0x38
//  */
// void Tokenizer<BasicString<char, Detail::TempStringAllocator> >::iterator::operator++()
// {
// }

// /**
//  * Offset/Address/Size: 0x88 | 0x80191520 | size: 0x310
//  */
// void Tokenizer<BasicString<char, Detail::TempStringAllocator> >::iterator::FindNextToken()
// {
// }

// /**
//  * Offset/Address/Size: 0x44 | 0x801914DC | size: 0x44
//  */
// void Tokenizer<BasicString<char, Detail::TempStringAllocator> >::iterator::iterator(const Tokenizer<BasicString<char, Detail::TempStringAllocator> >&, const char*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80191498 | size: 0x44
//  */
// void Tokenizer<BasicString<char, Detail::TempStringAllocator> >::end() const
// {
// }

/**
 * Offset/Address/Size: 0xC18 | 0x80191494 | size: 0x4
 */
Simulator::Simulator()
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0x0 | 0x8019087C | size: 0xC18
 * TODO: 46.26% match - tokenizer iteration/stat writes and exact constants remain incomplete.
 */
void Simulator::InitializeStats()
{
    GameplaySettings::eSkillLevel skillLevel = GameInfoManager::s_pInstance->GetGameplayOptions().SkillLevel;
    int length = GameInfoManager::s_pInstance->GetGameplayOptions().GameTime;
    bool isMeanFound = false;
    bool isSDFound = false;
    bool doMean = true;
    int diff;

    if (skillLevel == GameplaySettings::ROOKIE)
    {
        diff = 1;
    }
    else if (skillLevel == GameplaySettings::PROFESSIONAL)
    {
        diff = 2;
    }
    else
    {
        diff = 3;
    }

    BasicString<char, Detail::TempStringAllocator> searchString = LexicalCast<BasicString<char, Detail::TempStringAllocator> >(diff);

    if (length <= 0x78)
    {
        searchString = searchString.Append("A");
    }
    else if (length <= 0x12C)
    {
        searchString = searchString.Append("B");
    }
    else
    {
        searchString = searchString.Append("C");
    }

    BasicString<char, Detail::TempStringAllocator> meanString = searchString.Append("M");
    BasicString<char, Detail::TempStringAllocator> SDString = searchString.Append("S");
    BasicString<char, Detail::TempStringAllocator> statString;

    FILE* pFile = fopen(SIM_FILE, "r");
    if (pFile == 0)
    {
        return;
    }

    char line[0x100];
    while (fgets(line, 0x100, pFile) != 0)
    {
        bool isLineFound = false;

        unsigned long meanLen;
        if (meanString.m_data != 0)
        {
            meanLen = (unsigned long)(*(int*)((char*)meanString.m_data + 4) - 1);
        }
        else
        {
            meanLen = 0;
        }

        const char* meanCstr;
        if (meanString.m_data != 0)
        {
            meanCstr = *(const char**)meanString.m_data;
        }
        else
        {
            static char emptyString = 0;
            meanCstr = &emptyString;
        }

        if (nlStrNCmp<char>(meanCstr, line, meanLen) == 0)
        {
            isMeanFound = true;
            doMean = true;
            statString = statString.Append(line);
            isLineFound = true;
        }
        else
        {
            unsigned long sdLen;
            if (SDString.m_data != 0)
            {
                sdLen = (unsigned long)(*(int*)((char*)SDString.m_data + 4) - 1);
            }
            else
            {
                sdLen = 0;
            }

            const char* sdCstr;
            if (SDString.m_data != 0)
            {
                sdCstr = *(const char**)SDString.m_data;
            }
            else
            {
                static char emptyString2 = 0;
                sdCstr = &emptyString2;
            }

            if (nlStrNCmp<char>(sdCstr, line, sdLen) == 0)
            {
                isSDFound = true;
                doMean = false;
                statString = statString.Append(line);
                isLineFound = true;
            }
        }

        if (isLineFound)
        {
            if (isMeanFound && isSDFound)
            {
                break;
            }
        }
    }

    fclose(pFile);
}

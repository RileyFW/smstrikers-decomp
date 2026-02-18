#include "NL/nlLocalization.h"
#include "NL/nlMemory.h"
#include "NL/nlFile.h"
#include "NL/nlPrint.h"

extern void* g_pLocalization;

/**
 * Offset/Address/Size: 0x0 | 0x802107AC | size: 0x148
 */
unsigned char nlLocalization::Load(nlLanguage Language, bool ingameloc)
{
    m_CurrentLanguage = Language;

    char Filename[64];
    if (ingameloc)
    {
        nlSNPrintf(Filename, 64, "localization/%s/%s", LanguageName[Language]);
    }
    else
    {
        nlSNPrintf(Filename, 64, "localization/%s", LanguageName[Language]);
    }

    unsigned long FileSize;
    m_pFile = (LOCHeader*)nlLoadEntireFile(Filename, &FileSize, 32, AllocateStart);

    if (m_pFile == 0)
    {
        m_LookupTable = 0;
        m_FirstString = 0;
        return 0;
    }

    if (memcmp(m_pFile, Thumbprint, 4) != 0 || m_pFile->Version != 1 || m_pFile->Language != LanguageId[Language])
    {
        nlFree(m_pFile);
        m_pFile = 0;
        return 0;
    }

    m_LookupTable = (StringLookup*)(m_pFile + 1);
    m_FirstString = (unsigned short*)(&m_LookupTable[m_pFile->StringCount]);
    return 1;
}

/**
 * Offset/Address/Size: 0x148 | 0x802108F4 | size: 0x48
 */
void nlLocalization::Initialize()
{
    void* ptr = nlMalloc(16, 8, false);
    if (ptr != 0)
    {
        ((unsigned long*)ptr)[0] = 0;
        ((unsigned long*)ptr)[1] = 0;
        ((unsigned long*)ptr)[2] = 0;
    }
    g_pLocalization = ptr;
}

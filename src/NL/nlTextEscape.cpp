#include "NL/nlTextEscape.h"

#include "NL/nlQSort.h"
#include "NL/nlBSearch.h"

extern "C" unsigned long wcstoul(const unsigned short* str, unsigned short** end, int base);

/**
 * Offset/Address/Size: 0x0 | 0x8021251C | size: 0xB0
 */
nlColour nlEscapeSequence::GetExtendedColour()
{
    unsigned short str[3] = { 0, 0, 0 };
    nlColour colour;

    if ((int)m_Extended[0] == 0x70)
    {
        colour.c[3] = 0;
        return colour;
    }

    int channel = 0;
    for (channel = 0; channel < 3; channel++)
    {
        str[0] = m_Extended[channel * 2];
        str[1] = m_Extended[channel * 2 + 1];
        colour.c[channel] = (u8)wcstoul(str, 0, 16);
    }
    colour.c[3] = 0xFF;
    return colour;
}

/**
 * Offset/Address/Size: 0xB0 | 0x802125CC | size: 0x174
 */
nlEscapeSequence::nlEscapeSequence(const unsigned short* str)
{
    const unsigned short* extPtr = 0;
    int count = 0;
    unsigned long cmdKey = 0;

    const unsigned short* p = str;
    char* cmdBuf = (char*)&cmdKey;

    // Parse the command name between '{' and '}' or ':'
    while (true)
    {
        unsigned short ch = p[1];
        if (ch == '}')
            break;
        if (ch == ':')
        {
            extPtr = str + count + 2;
            break;
        }
        if ((unsigned int)count < 4)
        {
            *cmdBuf = (char)ch;
        }
        p++;
        cmdBuf++;
        count++;
    }

    // Parse extended data after ':'
    if (extPtr != 0)
    {
        count = 0;
        const unsigned short* ext = extPtr;
        for (int i = 0; i < 15; i++)
        {
            if (*ext == '}')
                break;
            m_Extended[count++] = *ext++;
        }
    }

    // Null-terminate extended data
    m_Extended[count] = 0;

    // Calculate end pointer (past the closing '}')
    const unsigned short* end;
    if (extPtr != 0)
    {
        end = extPtr;
    }
    else
    {
        end = str + 1;
    }
    m_pEnd = end + count + 1;

    // Look up escape type from command name
    ESCAPE_LOOKUP* result = nlBSearch(cmdKey, s_EscapeLookup, ESC_COUNT);
    if (result != 0)
    {
        m_Type = (ESCAPE_TYPE)result->type;
    }
    else
    {
        m_Type = ESC_UNKNOWN;
    }
}

// /**
//  * Offset/Address/Size: 0x0 | 0x80212740 | size: 0x8C
//  */
// template <typename T, typename U>
// T* nlBSearch(const U& key, T* array, int size)
// {
// }

// /**
//  * Offset/Address/Size: 0x124 | 0x80212864 | size: 0x28
//  */
// template <typename T>
// void nlQSort(T* array, int size, int (*compare)(const T*, const T*))
// {
// }

// /**
//  * Offset/Address/Size: 0x14C | 0x8021288C | size: 0x2C
//  */
// template <typename T>
// int nlDefaultQSortComparer(const T* a, const T* b)
// {
// }

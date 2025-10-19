#include "Game/Sys/simpleparser.h"

#include "ctype.h"

/**
 * Offset/Address/Size: 0x988 | 0x801D732C | size: 0x10
 */
SimpleParser::SimpleParser()
{
    m_EndOfLine = nullptr;
    m_CurrentBuffer = 0;
}

/**
 * Offset/Address/Size: 0x81C | 0x801D71C0 | size: 0x16C
 */
bool SimpleParser::StartParsing(char* data, int size, bool bSpacesAreWhitespace)
{
    unsigned char isWhitespace;
    char currentChar;
    char* lineStart;

    m_EndOfLine = data;
    m_AmountLeft = size;
    m_bSpacesAreWhitespace = bSpacesAreWhitespace;

    if (m_AmountLeft <= 1)
        return false;

restart:
    for (;;)
    {
        isWhitespace = 0;
        lineStart = m_EndOfLine;
        currentChar = *lineStart;
        int charValue = (s8) * (u8*)lineStart;
        if ((__ctype_map[(u8)charValue] & 0x6) != 0)
        {
            if (m_bSpacesAreWhitespace || charValue != 0x20)
                isWhitespace = 1;
        }

        if (!isWhitespace)
            break;

        unsigned char canAdvance;
        if (m_AmountLeft <= 1)
        {
            canAdvance = 0;
        }
        else
        {
            canAdvance = 1;
            m_EndOfLine += 1;
            m_AmountLeft -= 1;
        }

        if (canAdvance == 0)
        {
            return false;
        }
    }

    if ((int)(signed char)currentChar == 0x23)
    {
        for (;;)
        {
            unsigned char hasAdvanced;
            if (m_AmountLeft <= 1)
            {
                hasAdvanced = 0;
            }
            else
            {
                hasAdvanced = 1;
                m_EndOfLine += 1;
                m_AmountLeft -= 1;
            }

            unsigned char foundNewline;
            if (hasAdvanced == 0)
            {
                foundNewline = 0;
            }
            else
            {
                if (*m_EndOfLine == '\n')
                {
                    foundNewline = 1;
                }
                else
                {
                    continue;
                }
            }

            if (foundNewline == 0)
                return false;

            goto restart; // I am sure this was not in the original code, but it is here to make the assembly match.
        }
    }

    m_CurrPos = lineStart;

    for (;;)
    {
        unsigned char canStep;
        if (m_AmountLeft <= 1)
        {
            canStep = 0;
        }
        else
        {
            canStep = 1;
            m_EndOfLine += 1;
            m_AmountLeft -= 1;
        }

        if (!canStep)
            break;

        if (*m_EndOfLine == '\n')
            break;
    }

    return true;
}

/**
 * Offset/Address/Size: 0x33C | 0x801D6CE0 | size: 0x4E0
 */
char* SimpleParser::NextToken(bool)
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x160 | 0x801D6B04 | size: 0x1DC
 */
char* SimpleParser::NextTokenOnLine(bool)
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x0 | 0x801D69A4 | size: 0x160
 */
bool SimpleParser::AdvanceLine()
{
    unsigned char skip;
    unsigned char step;
    char cur;
    char* p;

    if (m_AmountLeft <= 1)
        return false;

    unsigned char* ctype = __ctype_map;

restart:
    for (;;)
    {
        skip = 0;
        p = m_EndOfLine;
        cur = *p;

        int ch = (signed char)(*(unsigned char*)p);

        if ((ctype[(unsigned char)ch] & 0x06) != 0)
        {
            if (m_bSpacesAreWhitespace || ch != 0x20)
                skip = 1;
        }

        if (!skip)
            break;

        if (m_AmountLeft <= 1)
        {
            step = 0;
        }
        else
        {
            step = 1;
            m_EndOfLine += 1;
            m_AmountLeft -= 1;
        }

        if (step == 0)
            return false;
    }

    if ((int)(signed char)cur == 0x23)
    {
        for (;;)
        {
            unsigned char hasAdvanced;
            if (m_AmountLeft <= 1)
            {
                hasAdvanced = 0;
            }
            else
            {
                hasAdvanced = 1;
                m_EndOfLine += 1;
                m_AmountLeft -= 1;
            }

            unsigned char foundNewline;
            if (hasAdvanced == 0)
            {
                foundNewline = 0;
            }
            else
            {
                if (*m_EndOfLine == '\n')
                {
                    foundNewline = 1;
                }
                else
                {
                    continue;
                }
            }

            if (foundNewline == 0)
                return false;

            goto restart; // I am sure this was not in the original code, but it is here to make the assembly match.
        }
    }

    m_CurrPos = p;

    for (;;)
    {
        if (m_AmountLeft <= 1)
        {
            step = 0;
        }
        else
        {
            step = 1;
            m_EndOfLine += 1;
            m_AmountLeft -= 1;
        }

        if (!step)
            break;

        if (*m_EndOfLine == '\n')
            break;
    }

    return true;
}

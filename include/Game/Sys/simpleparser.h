#ifndef _SIMPLEPARSER_H_
#define _SIMPLEPARSER_H_

#include "types.h"

class SimpleParser
{
public:
    SimpleParser();
    bool StartParsing(char*, int, bool);
    char* NextToken(bool);
    char* NextTokenOnLine(bool);
    void AdvanceLine();

    /* 0x000 */ s8 m_TokenBuffer[5][256];
    /* 0x500 */ s8* m_CurrPos;
    /* 0x504 */ s8* m_EndOfLine;
    /* 0x508 */ s32 m_AmountLeft;
    /* 0x50C */ s32 m_CurrentBuffer;
    /* 0x510 */ bool m_bSpacesAreWhitespace;

    // char m_TokenBuffer[5][256];  // [0x000..0x4FF]
    // char* m_CurrPos;             // [0x500] current position within line (token cursor)
    // char* m_EndOfLine;           // [0x504] current line end sentinel (points at '\n' or scan head)
    // int m_AmountLeft;            // [0x508] bytes left from mLineEnd to end of buffer
    // int m_CurrentBuffer;         // [0x50C] rotating token buffer index 0..4
    // bool m_bSpacesAreWhitespace; // [0x510] 1 => treat ' ' as whitespace; 0 => keep spaces in tokens
}; // size: 0x514

#endif // _SIMPLEPARSER_H_

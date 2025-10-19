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
    bool AdvanceLine();

    /* 0x000 */ char m_TokenBuffer[5][256];
    /* 0x500 */ char* m_CurrPos;
    /* 0x504 */ char* m_EndOfLine;
    /* 0x508 */ int m_AmountLeft;
    /* 0x50C */ int m_CurrentBuffer;
    /* 0x510 */ bool m_bSpacesAreWhitespace;
}; // size: 0x514

#endif // _SIMPLEPARSER_H_

#include "Game/Sys/simpleparser.h"

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
bool SimpleParser::StartParsing(char*, int, bool)
{
    return false;
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
void SimpleParser::AdvanceLine()
{
}

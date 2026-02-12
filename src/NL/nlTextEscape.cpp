#include "NL/nlTextEscape.h"

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
nlEscapeSequence::nlEscapeSequence(const unsigned short*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80212740 | size: 0x8C
 */
template <typename T, typename U>
T* nlBSearch(const U& key, T* array, int size)
{
}

/**
 * Offset/Address/Size: 0x124 | 0x80212864 | size: 0x28
 */
template <typename T>
void nlQSort(T* array, int size, int (*compare)(const T*, const T*))
{
}

/**
 * Offset/Address/Size: 0x14C | 0x8021288C | size: 0x2C
 */
template <typename T>
int nlDefaultQSortComparer(const T* a, const T* b)
{
}

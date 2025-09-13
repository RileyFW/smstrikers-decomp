#ifndef _NLLEXICALCAST_H_
#define _NLLEXICALCAST_H_

#include "types.h"
#include "strtold.h"

// Template declaration
template <typename To, typename From>
To LexicalCast(const From& value);

// Static template specializations
template <>
static int LexicalCast<int, float>(const float& value)
{
    FORCE_DONT_INLINE;
    return (int)value;
}

template <>
static int LexicalCast<int, int>(const int& value)
{
    FORCE_DONT_INLINE;
    return value;
}

template <>
static int LexicalCast<int, bool>(const bool& value)
{
    FORCE_DONT_INLINE;
    return (int)value;
}

template <>
static float LexicalCast<float, float>(const float& value)
{
    FORCE_DONT_INLINE;
    return value;
}

template <>
static float LexicalCast<float, int>(const int& value)
{
    FORCE_DONT_INLINE;
    return (float)value;
}

template <>
static float LexicalCast<float, bool>(const bool& value)
{
    FORCE_DONT_INLINE;
    return (float)value;
}

template <>
static float LexicalCast<float, const char*>(const char* const& value)
{
    FORCE_DONT_INLINE;
    return (float)atof(value);
}

template <>
static int LexicalCast<int, const char*>(const char* const& value)
{
    FORCE_DONT_INLINE;
    return (int)atof(value);
}

#endif // _NLLEXICALCAST_H_

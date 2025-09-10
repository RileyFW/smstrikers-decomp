#ifndef _NLLEXICALCAST_H_
#define _NLLEXICALCAST_H_

#include "types.h"
#include "strtold.h"

// Template declaration
template <typename To, typename From>
To LexicalCast(const From& value);

// Template specializations
template <>
int LexicalCast<int, float>(const float& value)
{
    FORCE_DONT_INLINE;
    return (int)value;
}

template <>
int LexicalCast<int, int>(const int& value)
{
    FORCE_DONT_INLINE;
    return value;
}

template <>
int LexicalCast<int, bool>(const bool& value)
{
    FORCE_DONT_INLINE;
    return (int)value;
}

template <>
float LexicalCast<float, float>(const float& value)
{
    FORCE_DONT_INLINE;
    return value;
}

template <>
float LexicalCast<float, int>(const int& value)
{
    FORCE_DONT_INLINE;
    return (float)value;
}

template <>
float LexicalCast<float, bool>(const bool& value)
{
    FORCE_DONT_INLINE;
    return (float)value;
}

template <>
float LexicalCast<float, const char*>(const char* const& value)
{
    FORCE_DONT_INLINE;
    return (float)atof(value);
}

template <>
int LexicalCast<int, const char*>(const char* const& value)
{
    FORCE_DONT_INLINE;
    return (int)atof(value);
}

// template <>
// bool LexicalCast<bool, bool>(const bool& value)
// {
//     FORCE_DONT_INLINE;
//     return false;
// }

// template <>
// bool LexicalCast<bool, int>(const int& value)
// {
//     FORCE_DONT_INLINE;
//     return false;
// }

// template <>
// bool LexicalCast<bool, float>(const float& value)
// {
//     FORCE_DONT_INLINE;
//     return false;
// }

// template <>
// bool LexicalCast<bool, const char*>(const char* const& value)
// {
//     FORCE_DONT_INLINE;
//     return false;
// }

#endif // _NLLEXICALCAST_H_

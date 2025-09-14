#ifndef _NLLEXICALCAST_H_
#define _NLLEXICALCAST_H_

#include "types.h"
#include "strtold.h"

template <typename To, typename From>
struct LexicalCastImpl;

template <typename To, typename From>
To LexicalCast(const From& value)
{
    return LexicalCastImpl<To, From>::cast(value);
}

// ---------------------- Explicit specializations ----------------------

// int <- float
template <>
struct LexicalCastImpl<int, float>
{
    static int cast(const float& value)
    {
        FORCE_DONT_INLINE;
        return (int)value;
    }
};

// int <- bool
template <>
struct LexicalCastImpl<int, bool>
{
    static int cast(const bool& value)
    {
        FORCE_DONT_INLINE;
        return (int)value;
    }
};

// float <- float
template <>
struct LexicalCastImpl<float, float>
{
    static float cast(const float& value)
    {
        FORCE_DONT_INLINE;
        return value;
    }
};

// float <- const char*
template <>
struct LexicalCastImpl<float, const char*>
{
    static float cast(const char* const& value)
    {
        FORCE_DONT_INLINE;
        return (float)atof(value);
    }
};

// float <- bool
template <>
struct LexicalCastImpl<float, bool>
{
    static float cast(const bool& value)
    {
        FORCE_DONT_INLINE;
        return (float)value;
    }
};

// int <- const char*
template <>
struct LexicalCastImpl<int, const char*>
{
    static int cast(const char* const& value)
    {
        FORCE_DONT_INLINE;
        return (int)atof(value);
    }
};

// bool <- bool
template <>
struct LexicalCastImpl<bool, bool>
{
    static bool cast(const bool& value)
    {
        FORCE_DONT_INLINE;
        return value;
    }
};

// bool <- int
template <>
struct LexicalCastImpl<bool, int>
{
    static bool cast(const int& value)
    {
        FORCE_DONT_INLINE;
        return value != 0;
    }
};

// bool <- float
template <>
struct LexicalCastImpl<bool, float>
{
    static bool cast(const float& value)
    {
        FORCE_DONT_INLINE;
        return value != 0.0f;
    }
};

// bool <- const char*
template <>
struct LexicalCastImpl<bool, const char*>
{
    static bool cast(const char* const& value)
    {
        FORCE_DONT_INLINE;
        // TODO: Implement
        return true;
    }
};

// int <- int
template <>
struct LexicalCastImpl<int, int>
{
    static int cast(const int& value)
    {
        FORCE_DONT_INLINE;
        return value;
    }
};

// float <- int
template <>
struct LexicalCastImpl<float, int>
{
    static float cast(const int& value)
    {
        FORCE_DONT_INLINE;
        return (float)value;
    }
};

#endif // _NLLEXICALCAST_H_

#include "NL/nlConfig.h"

// static Config* sGlobal = nullptr;

/**
 * Offset/Address/Size: 0x0 | 0x801D2C64 | size: 0x13EC
 */
// void Config::Parse(const char*, Config::Parser&)
// {
// }

/**
 * Offset/Address/Size: 0x13EC | 0x801D4050 | size: 0x21C
 */
void Config::LoadFileAsString(const char*)
{
}

/**
 * Offset/Address/Size: 0x1608 | 0x801D426C | size: 0x54
 */
void Config::Set(const char*, const BasicString<char, Detail::TempStringAllocator>&)
{
}

/**
 * Offset/Address/Size: 0x165C | 0x801D42C0 | size: 0x56C
 */
void Config::Set(const char*, const char*)
{
}

/**
 * Offset/Address/Size: 0x1BC8 | 0x801D482C | size: 0x12C
 */
void Config::Set(const char*, float)
{
}

/**
 * Offset/Address/Size: 0x1CF4 | 0x801D4958 | size: 0x120
 */
void Config::Set(const char*, bool)
{
}

/**
 * Offset/Address/Size: 0x1E14 | 0x801D4A78 | size: 0x120
 * TODO: 86.9% match - r28/r29 register swap in hash probe loop (idx/offset/tvp allocation),
 */
void Config::Set(const char* tag, int value)
{
    const char* p = tag;
    u32 hash = 0x1505;
    s32 c;
    while (c = (s8)*p)
    {
        p++;
        c = nlToUpper((char)c);
        c = (s8)c;
        u32 shifted = hash << 5;
        shifted += c;
        hash += shifted;
    }
    u32 idx = hash & 0x3FF;

    TagValuePair* tvp;
    while (true)
    {
        u32 offset = idx * 12;
        if (mTvpHash[idx].tag == NULL)
        {
            tvp = (TagValuePair*)((char*)mTvpHash + offset);
            break;
        }
        if (nlStrICmp(mTvpHash[idx].tag, tag) == 0)
        {
            tvp = (TagValuePair*)((char*)mTvpHash + offset);
            break;
        }
        idx = (idx + 1) & 0x3FF;
    }

    tvp->type = _INT;
    tvp->value.i = value;
    if (tvp->tag != NULL)
    {
        return;
    }

    char* strStart = mStringEnd;
    s32 ch;
    while (ch = (s8)*tag)
    {
        if (mStringEnd - mStringMemory >= 0x27FF)
        {
            break;
        }
        ch = nlToUpper((char)ch);
        *mStringEnd = (char)ch;
        mStringEnd++;
        tag++;
    }
    *mStringEnd = '\0';
    mStringEnd++;
    tvp->tag = strStart;
}

/**
 * Offset/Address/Size: 0x1F34 | 0x801D4B98 | size: 0xB8
 */
TagValuePair& Config::FindTvp(const char*)
{
    FORCE_DONT_INLINE;
    static TagValuePair defaultTvp = { nullptr, _BOOL, nullptr };
    return defaultTvp;
}

/**
 * Offset/Address/Size: 0x1FEC | 0x801D4C50 | size: 0x534
 */
bool Config::IsBool(const char*, bool&) const
{
    FORCE_DONT_INLINE;
    return false;
}

/**
 * Offset/Address/Size: 0x2520 | 0x801D5184 | size: 0xC8
 */
bool Config::Exists(const char*) const
{
    FORCE_DONT_INLINE;
    return false;
}

/**
 * Offset/Address/Size: 0x25E8 | 0x801D524C | size: 0x138
 */
void Config::LoadFromFile(const char*)
{
}

/**
 * Offset/Address/Size: 0x2720 | 0x801D5384 | size: 0xAC
 */
Config& Config::Global()
{
    FORCE_DONT_INLINE;
    // return *sGlobal;

    static Config sGlobal;
    return sGlobal;
}

/**
 * Offset/Address/Size: 0x27CC | 0x801D5430 | size: 0x68
 */
Config::~Config()
{
}

/**
 * Offset/Address/Size: 0x2834 | 0x801D5498 | size: 0xCC
 */
Config::Config(Config::AllocateWhere location)
{
}

/**
 * Offset/Address/Size: 0x2900 | 0x801D5564 | size: 0x4
 */
// SetTagValuePair::Comment(const BasicString<char, Detail::TempStringAllocator>&)
// {
// }

/**
 * Offset/Address/Size: 0x2904 | 0x801D5568 | size: 0x94
 */
// SetTagValuePair::Section(const BasicString<char, Detail::TempStringAllocator>&)
// {
// }

/**
 * Offset/Address/Size: 0x2998 | 0x801D55FC | size: 0x218
 */
// SetTagValuePair::TagValuePair(const BasicString<char, Detail::TempStringAllocator>&, const BasicString<char,
// Detail::TempStringAllocator>&)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x801D5814 | size: 0x4
 */
// Config::Parser::TagValuePair(const BasicString<char, Detail::TempStringAllocator>&, const BasicString<char,
// Detail::TempStringAllocator>&)
// {
// }

/**
 * Offset/Address/Size: 0x4 | 0x801D5818 | size: 0x4
 */
// void Config::Parser::Section(const BasicString<char, Detail::TempStringAllocator>&)
// {
// }

/**
 * Offset/Address/Size: 0x8 | 0x801D581C | size: 0x4
 */
// void Config::Parser::Comment(const BasicString<char, Detail::TempStringAllocator>&)
// {
// }

/**
 * Offset/Address/Size: 0xC | 0x801D5820 | size: 0x4
 */
// void Config::Parser::EmptyLine()
// {
// }

/**
 * Offset/Address/Size: 0x10 | 0x801D5824 | size: 0xC
 */
// void Config::TagValuePair::TagValuePair()
// {
// }

/**
 * Offset/Address/Size: 0x1C | 0x801D5830 | size: 0x20
 */
// Config::Set<BasicString<char, Detail::TempStringAllocator>>(const char*, BasicString<char, Detail::TempStringAllocator>)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x801D5850 | size: 0xBC
 */
// BasicString<char, Detail::TempStringAllocator>::Trim(const char*) const
// {
// }

/**
 * Offset/Address/Size: 0xBC | 0x801D590C | size: 0xBC4
 */
// BasicString<char, Detail::TempStringAllocator>::TrimInPlace(const char*)
// {
// }

/**
 * Offset/Address/Size: 0xC80 | 0x801D64D0 | size: 0xBC
 */
// BasicString<char, Detail::TempStringAllocator>::Append<Detail::TempStringAllocator>(const BasicString<char,
// Detail::TempStringAllocator>&) const
// {
// }

/**
 * Offset/Address/Size: 0xD3C | 0x801D658C | size: 0x1E4
 */
// BasicString<char, Detail::TempStringAllocator>::AppendInPlace<Detail::TempStringAllocator>(const BasicString<char,
// Detail::TempStringAllocator>&)
// {
// }

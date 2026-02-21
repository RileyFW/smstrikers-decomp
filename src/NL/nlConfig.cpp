#include "NL/nlConfig.h"

// static Config* sGlobal = nullptr;

/**
 * Offset/Address/Size: 0x0 | 0x801D2C64 | size: 0x13EC
 */
void Config::Parse(const char*, Config::Parser&)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x13EC | 0x801D4050 | size: 0x21C
 */
BasicString<char, Detail::TempStringAllocator> Config::LoadFileAsString(const char*)
{
    FORCE_DONT_INLINE;
    BasicString<char, Detail::TempStringAllocator> s;
    return s;
}

/**
 * Offset/Address/Size: 0x1608 | 0x801D426C | size: 0x54
 */
void Config::Set(const char* key, const BasicString<char, Detail::TempStringAllocator>& value) {
    Set(key, value.c_str());
}

/**
 * Offset/Address/Size: 0x165C | 0x801D42C0 | size: 0x56C
 */
void Config::Set(const char*, const char*)
{
}

/**
 * Offset/Address/Size: 0x1BC8 | 0x801D482C | size: 0x12C
 * TODO: 94.3% match - r28/r30 register swap for hash/idx in probe setup,
 * r29/r30 register swap for idx/offset and r28/r29 swap for dest/src in copy loop,
 * nlToUpper<Uc> vs nlToUpper<c> template instantiation (i diff),
 * bge vs blt/b branch pattern in copy loop
 */
void Config::Set(const char* tag, float value)
{
    TagValuePair* tvp;
    u32 hash = 0x1505;
    const char* p = tag;
    while (*p != 0)
    {
        s8 c = (s8)nlToUpper((u8)*p++);
        hash += (hash << 5) + c;
    }
    u32 idx = hash & 0x3FF;

    while (true)
    {
        u32 offset = idx * 12;
        if (mTvpHash[idx].tag == NULL || nlStrICmp(mTvpHash[idx].tag, tag) == 0)
        {
            tvp = (TagValuePair*)((u8*)mTvpHash + offset);
            break;
        }
        idx++;
        idx &= 0x3FF;
    }

    tvp->type = _FLOAT;
    tvp->value.f = value;

    if (tvp->tag == NULL)
    {
        const char* src = tag;
        char* dest = mStringEnd;
        while (*src != 0)
        {
            if (mStringEnd - mStringMemory >= 0x27FF)
            {
                break;
            }
            *mStringEnd = nlToUpper((u8)*src);
            src++;
            mStringEnd++;
        }
        *mStringEnd = 0;
        mStringEnd++;
        tvp->tag = dest;
    }
}

/**
 * Offset/Address/Size: 0x1CF4 | 0x801D4958 | size: 0x120
 * TODO: 92.9% match - r28/r29 register swap throughout (idx/offset/tvp allocation),
 * hash loop *p++ lbz r0 + extra extsb r3,r0 (same as Exists), add operand order swap,
 * copy loop extsb. r3,r3 vs r0,r3, bge vs blt/b branch pattern
 */
void Config::Set(const char* tag, bool value)
{
    const char* p = tag;
    u32 hash = 0x1505;
    while (*p != 0)
    {
        s32 c = (s8)nlToUpper(*p++);
        hash += (hash << 5) + c;
    }
    u32 idx = hash & 0x3FF;

    TagValuePair* tvp;
    do
    {
        u32 offset = idx * 12;
        if (mTvpHash[idx].tag == NULL || nlStrICmp(mTvpHash[idx].tag, tag) == 0)
        {
            tvp = (TagValuePair*)((u8*)mTvpHash + offset);
            break;
        }
        idx++;
        idx &= 0x3FF;
    } while (true);

    tvp->type = _BOOL;
    tvp->value.b = value;

    if (tvp->tag == NULL)
    {
        char* dest = mStringEnd;
        s32 ch;
        while ((ch = *tag) != 0)
        {
            if (mStringEnd - mStringMemory >= 0x27FF)
            {
                goto done;
            }
            *mStringEnd = nlToUpper((char)ch);
            tag++;
            mStringEnd++;
        }
        *mStringEnd = 0;
        mStringEnd++;
    done:
        tvp->tag = dest;
    }
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
 * TODO: 98.9% match - nlToUpper<Uc> vs nlToUpper<c> template instantiation (i diff),
 * r30/r31 register swap for idx/offset in probe loop (MWCC allocator quirk)
 */
TagValuePair& Config::FindTvp(const char* tag)
{
    u32 hash = 0x1505;
    const char* p = tag;
    while (*p != 0)
    {
        s8 c = (s8)nlToUpper((u8)*p++);
        hash = hash + (hash << 5) + c;
    }
    u32 idx = hash & 0x3FF;

    while (true)
    {
        u32 offset = idx * 12;
        if (mTvpHash[idx].tag == NULL || nlStrICmp(mTvpHash[idx].tag, tag) == 0)
        {
            return *(TagValuePair*)((char*)mTvpHash + offset);
        }
        idx = (idx + 1) & 0x3FF;
    }
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
 * TODO: 97.4% match - *p++ forces lbz into r0 + extra extsb r3,r0 (target loads lbz r3
 * directly), add operand order swap in hash computation (compiler scheduling)
 */
bool Config::Exists(const char* tag) const
{
    const char* p = tag;
    u32 hash = 0x1505;
    while (*p != 0)
    {
        s32 c = (s8)nlToUpper(*p++);
        hash += (hash << 5) + c;
    }
    u32 startIdx = hash & 0x3FF;

    TagValuePair* tvpHash = mTvpHash;
    u32 idx = startIdx;
    do
    {
        if (tvpHash[idx].tag == NULL)
        {
            return false;
        }
        if (nlStrICmp(tvpHash[idx].tag, tag) == 0)
        {
            return true;
        }
        idx++;
        idx &= 0x3FF;
    } while (idx != startIdx);
    return false;
}

/**
 * Offset/Address/Size: 0x25E8 | 0x801D524C | size: 0x138
 */
void Config::LoadFromFile(const char* filename)
{
    const BasicString<char, Detail::TempStringAllocator>& s = LoadFileAsString(filename);
    const char* str = s.c_str();
    SetTagValuePair stvp(*this);
    Parse(str, stvp);
}

/**
 * Offset/Address/Size: 0x2834 | 0x801D5498 | size: 0xCC
 */
Config::Config(Config::AllocateWhere allocateWhere)
{
    mTvpHash = new (nlMalloc(sizeof(TagValuePair) * 1024 + 0x10, 8, false)) TagValuePair[1024];
    char* mem = (char*)nlMalloc(0x2800, 8, false);
    mStringMemory = mem;
    mStringEnd = mem;
    mem[0x27FF] = '\0';
}

/**
 * Offset/Address/Size: 0x2720 | 0x801D5384 | size: 0xAC
 */
Config& Config::Global()
{
    static Config sGlobal(ALLOCATE_LOW);
    return sGlobal;
}

/**
 * Offset/Address/Size: 0x27CC | 0x801D5430 | size: 0x68
 */
Config::~Config()
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
void SetTagValuePair::Section(const BasicString<char, Detail::TempStringAllocator>& section)
{
    mCurrentSection = section;
}

/**
 * Offset/Address/Size: 0x2998 | 0x801D55FC | size: 0x218
 */
void SetTagValuePair::TagValuePair(const BasicString<char, Detail::TempStringAllocator>&, const BasicString<char, Detail::TempStringAllocator>&)
{
    FORCE_DONT_INLINE;
}

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

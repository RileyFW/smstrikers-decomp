#ifndef _NLCONFIG_H_
#define _NLCONFIG_H_

#include "types.h"
#include "NL/nlLexicalCast_.h"

enum Type
{
    _BOOL = 0,
    _INT = 1,
    _FLOAT = 2,
    _STRING = 3,
};

class SetTagValuePair
{
public:
    /* 0x00 */ char* m_unk_0x00; // tag
    /* 0x04 */ Type m_unk_0x04;  // type
    /* 0x08 */ char* m_unk_0x08; // value
};

class Config
{
public:
    enum AllocateWhere
    {
        AllocateWhere_0 = 0,
        AllocateWhere_1 = 1,
    };

    // void Parse(const char*, Config::Parser&);
    void LoadFileAsString(const char*);
    // void Set(const char*, const BasicString<char, Detail::TempStringAllocator>&);
    void Set(const char*, const char*);
    void Set(const char*, float);
    void Set(const char*, bool);
    void Set(const char*, int);
    SetTagValuePair* FindTvp(const char*);
    bool IsBool(const char*, bool&) const;
    bool Exists(const char*) const;
    void LoadFromFile(const char*);

    template <typename T>
    T Get(const char* key, T defaultValue)
    {
        FORCE_DONT_INLINE;
        SetTagValuePair* tvp = FindTvp(key);
        if (tvp->m_unk_0x00 == NULL)
        {
            Set(key, defaultValue);
            return defaultValue;
        }

        T val;
        if (tvp->m_unk_0x04 == 0)
        {
            val = LexicalCast<T, bool>(*(const bool*)&tvp->m_unk_0x08);
        }
        else if (tvp->m_unk_0x04 == 1)
        {
            val = LexicalCast<T, int>(*(const int*)&tvp->m_unk_0x08);
        }
        else if (tvp->m_unk_0x04 == 2)
        {
            val = LexicalCast<T, float>(*(const float*)&tvp->m_unk_0x08);
        }
        else if (tvp->m_unk_0x04 == 3)
        {
            val = LexicalCast<T, const char*>(*(const char**)&tvp->m_unk_0x08);
        }
        else
        {
            val = 0.f;
        }
        return val;
    };

    static Config& Global();

    ~Config();
    Config() { };
    Config(AllocateWhere);

    // Parser::TagValuePair(const BasicString<char, Detail::TempStringAllocator>&, const BasicString<char, Detail::TempStringAllocator>&);
    // Parser::Section(const BasicString<char, Detail::TempStringAllocator>&);
    // Parser::Comment(const BasicString<char, Detail::TempStringAllocator>&);
    // Parser::EmptyLine();
    // TagValuePair::TagValuePair();
    // Set<BasicString<char, Detail::TempStringAllocator>>(const char*, BasicString<char, Detail::TempStringAllocator>);
};

/* Config::Get<float> (char const *, float) */
// float Config::Get<float>(char const* key, float defaultValue)
// {
//     s32 temp_r0;
//     void* temp_r3;

//     // temp_r3 = FindTvp__6ConfigFPCc(this, arg0);
//     SetTagValuePair* tvp = FindTvp(key);
//     if (tvp->m_unk_0x00 == NULL)
//     {
//         Set(key, defaultValue);
//         return defaultValue;
//     }

//     // temp_r0 = temp_r3->unk4;
//     // switch (temp_r0)
//     // { /* irregular */
//     // case 0:
//     //     return LexicalCast<float, bool>(temp_r3 + 8);
//     // case 1:
//     //     return LexicalCast<float, int>(temp_r3 + 8);
//     // case 2:
//     //     return LexicalCast<float, float>(temp_r3 + 8);
//     // case 3:
//     //     return LexicalCast<float, const char*>(temp_r3 + 8);
//     // default:
//     //     return 0.0f;
//     // }
//     float val;
//     if (tvp->m_unk_0x04 == 0)
//     {
//         val = LexicalCast<float, bool>(*(const bool*)&tvp->m_unk_0x08);
//     }
//     else if (tvp->m_unk_0x04 == 1)
//     {
//         val = LexicalCast<float, int>(*(const int*)&tvp->m_unk_0x08);
//     }
//     else if (tvp->m_unk_0x04 == 2)
//     {
//         val = LexicalCast<float, float>(*(const float*)&tvp->m_unk_0x08);
//     }
//     else if (tvp->m_unk_0x04 == 3)
//     {
//         val = LexicalCast<float, const char*>(*(const char**)&tvp->m_unk_0x08);
//     }
//     else
//     {
//         val = 0.f;
//     }
//     return val;
// }

// class SetTagValuePair
// {
// public:
//     SetTagValuePair::Comment(const BasicString<char, Detail::TempStringAllocator>&);
//     SetTagValuePair::Section(const BasicString<char, Detail::TempStringAllocator>&);
//     SetTagValuePair::TagValuePair(const BasicString<char, Detail::TempStringAllocator>&, const BasicString<char,
//     Detail::TempStringAllocator>&);
// };

// class BasicString<char, Detail
// {
// public:
//     BasicString<char, Detail::TempStringAllocator>::Trim(const char*) const;
//     BasicString<char, Detail::TempStringAllocator>::TrimInPlace(const char*);
//     BasicString<char, Detail::TempStringAllocator>::Append<Detail::TempStringAllocator>(const BasicString<char,
//     Detail::TempStringAllocator>&) const; BasicString<char,
//     Detail::TempStringAllocator>::AppendInPlace<Detail::TempStringAllocator>(const BasicString<char, Detail::TempStringAllocator>&);
// };

#endif // _NLCONFIG_H_

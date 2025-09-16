#ifndef _NLCONFIG_H_
#define _NLCONFIG_H_

#include "types.h"
#include "NL/nlLexicalCast.h"

enum Type
{
    _BOOL = 0,
    _INT = 1,
    _FLOAT = 2,
    _STRING = 3,
};

union Value
{
    /* 0x0 */ const char* s;
    /* 0x0 */ int i;
    /* 0x0 */ bool b;
    /* 0x0 */ float f;
};

struct TagValuePair
{
    /* 0x00 */ const char* tag;
    /* 0x04 */ Type type;
    /* 0x08 */ Value value;
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
    TagValuePair& FindTvp(const char*);
    bool IsBool(const char*, bool&) const;
    bool Exists(const char*) const;
    void LoadFromFile(const char*);

    template <typename T>
    T Get(const char* key, T defaultValue)
    {
        FORCE_DONT_INLINE;
        TagValuePair& tvp = FindTvp(key);
        if (tvp.tag == NULL)
        {
            Set(key, defaultValue);
            return defaultValue;
        }

        T val;
        if (tvp.type == _BOOL)
        {
            val = LexicalCast<T, bool>(tvp.value.b);
        }
        else if (tvp.type == _INT)
        {
            val = LexicalCast<T, int>(tvp.value.i);
        }
        else if (tvp.type == _FLOAT)
        {
            val = LexicalCast<T, float>(tvp.value.f);
        }
        else if (tvp.type == _STRING)
        {
            val = LexicalCast<T, const char*>(tvp.value.s);
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

inline float GetConfigFloat(Config& cfg, const char* key, float defaultValue)
{
    TagValuePair& tvp = cfg.FindTvp(key);
    if (tvp.tag == NULL)
    {
        cfg.Set(key, defaultValue);
        return defaultValue;
    }

    float val;
    if (tvp.type == _BOOL)
    {
        val = LexicalCast<float, bool>(tvp.value.b);
    }
    else if (tvp.type == _INT)
    {
        val = LexicalCast<float, int>(tvp.value.i);
    }
    else if (tvp.type == _FLOAT)
    {
        val = LexicalCast<float, float>(tvp.value.f);
    }
    else if (tvp.type == _STRING)
    {
        val = LexicalCast<float, const char*>(tvp.value.s);
    }
    else
    {
        val = 0.f;
    }
    return val;
}

inline s32 GetConfigInt(Config& cfg, const char* key, s32 defaultValue)
{
    TagValuePair& tvp = cfg.FindTvp(key);
    if (tvp.tag == NULL)
    {
        cfg.Set(key, (int)defaultValue);
        return defaultValue;
    }

    int val;
    if (tvp.type == _BOOL)
    {
        val = LexicalCast<int, bool>(tvp.value.b);
    }
    else if (tvp.type == _INT)
    {
        val = LexicalCast<int, int>(tvp.value.i);
    }
    else if (tvp.type == _FLOAT)
    {
        val = LexicalCast<int, float>(tvp.value.f);
    }
    else if (tvp.type == _STRING)
    {
        val = LexicalCast<int, const char*>(tvp.value.s);
    }
    else
    {
        val = 0;
    }
    return val;
}

inline bool GetConfigBool(Config& cfg, const char* key, bool defaultValue)
{
    TagValuePair& tvp = cfg.FindTvp(key);
    bool val;
    if (tvp.tag == NULL)
    {
        cfg.Set(key, defaultValue);
        return defaultValue;
    }

    if (tvp.type == _BOOL)
    {
        val = LexicalCast<bool, bool>(tvp.value.b);
    }
    else if (tvp.type == _INT)
    {
        val = LexicalCast<bool, int>(tvp.value.i);
    }
    else if (tvp.type == _FLOAT)
    {
        val = LexicalCast<bool, float>(tvp.value.f);
    }
    else if (tvp.type == _STRING)
    {
        val = LexicalCast<bool, const char*>(tvp.value.s);
    }
    else
    {
        val = 0.f;
    }
    return val;
}

#endif // _NLCONFIG_H_

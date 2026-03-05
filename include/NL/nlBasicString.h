#ifndef _BASICSTRING_H_
#define _BASICSTRING_H_

#include "types.h"
#include "NL/nlMemory.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/string.h"
#include "NL/nlString.h"

// class Vector
// {
//     // total size: 0xC
//     char* mData;   // offset 0x0, size 0x4
//     int mSize;     // offset 0x4, size 0x4
//     int mCapacity; // offset 0x8, size 0x4
// };

// class Data
// {
//     // total size: 0x10
//     Vector mData;  // offset 0x0, size 0xC
//     int mRefCount; // offset 0xC, size 0x4
// };

// class BasicString
// {
//     // total size: 0x4
//     Data* mData; // offset 0x0, size 0x4
// };

// Forward declarations
namespace Detail
{
class TempStringAllocator;
}

template <typename CharT, typename Allocator>
class BasicString;

// Format function for single float argument (no variadic templates)
template <typename StringType>
void Format(StringType& result, const StringType& format, const float& value);

// Format function for two float arguments
template <typename StringType>
void Format(StringType& result, const StringType& format, const float& value1, const float& value2);

// Detail namespace with TempStringAllocator
namespace Detail
{
class TempStringAllocator
{
public:
    static void* allocate(size_t size)
    {
        return nlMalloc(size, 8, true);
    }

    static void deallocate(void* ptr)
    {
        nlFree(ptr);
    }
};
} // namespace Detail

// BasicString data storage struct
struct BasicStringInternal
{
    char* mData;   // offset 0x0 - the actual char* buffer
    int mSize;     // offset 0x4
    int mCapacity; // offset 0x8
    int mRefCount; // offset 0xC
};

// BasicString template class - total size: 0x4 (pointer to BasicStringInternal)
template <typename CharT, typename Allocator>
class BasicString
{
public:
    BasicStringInternal* m_data; // offset 0x0 - pointer to data struct

    BasicString()
        : m_data(nullptr)
    {
    }

    BasicString(const BasicString& other)
    {
        BasicStringInternal* data;
        if (other.m_data)
        {
            other.m_data->mRefCount++;
            data = other.m_data;
        }
        else
        {
            data = nullptr;
        }
        m_data = data;
    }

    ~BasicString()
    {
        if (m_data)
        {
            BasicStringInternal* data = m_data;
            if (--data->mRefCount == 0)
            {
                if (data)
                {
                    if (data)
                    {
                        delete[] data->mData;
                    }
                    if (data)
                    {
                        nlFree(data);
                    }
                }
            }
        }
    }

    BasicString& operator=(BasicString other);

    const CharT* c_str() const
    {
        static CharT emptyString = '\0';
        return m_data ? m_data->mData : &emptyString;
    }

    u32 size() const
    {
        return m_data ? m_data->mSize : 0;
    }

    BasicString Append(const char* rhs) const;

    template <typename OtherAllocator>
    BasicString Append(const BasicString<CharT, OtherAllocator>& rhs) const;
};

// Format template function for single float argument
template <typename StringType>
void Format(StringType& result, const StringType& format, const float& value)
{
    FORCE_DONT_INLINE;
}

// Format template function for two float arguments
template <typename StringType>
void Format(StringType& result, const StringType& format, const float& value1, const float& value2)
{
    FORCE_DONT_INLINE;
}

// Forward declaration for the operator== function
template <typename CharT, typename Allocator>
bool operator==(const BasicString<CharT, Allocator>& lhs, const char* rhs);

#ifdef NL_BASICSTRING_DEFINE
// Specialization for char with TempStringAllocator
template <>
bool operator== <char, Detail::TempStringAllocator>(const BasicString<char, Detail::TempStringAllocator>& lhs, const char* rhs)
{
    if (!rhs)
    {
        return lhs.m_data == nullptr || lhs.m_data->mSize == 0;
    }

    if (!lhs.m_data || !lhs.m_data->mData)
    {
        return *rhs == '\0';
    }

    return strcmp(lhs.m_data->mData, rhs) == 0;
}
#endif

#endif

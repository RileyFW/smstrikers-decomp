#ifndef _BASICSTRING_H_
#define _BASICSTRING_H_

#include "types.h"
#include "NL/nlMemory.h"

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
void Format(StringType& result, const StringType& format, float value);

// Format function for two float arguments
template <typename StringType>
void Format(StringType& result, const StringType& format, float value1, float value2);

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

// BasicString template class
template <typename CharT, typename Allocator>
class BasicString
{
public:
    CharT* m_data;
    u32 m_size;
    u32 m_capacity;
    u32 m_refCount;

    BasicString()
        : m_data(nullptr)
        , m_size(0)
        , m_capacity(0)
        , m_refCount(1)
    {
    }

    ~BasicString()
    {
        if (m_refCount > 0)
        {
            m_refCount--;
            if (m_refCount == 0)
            {
                if (m_data)
                {
                    Allocator::deallocate(m_data);
                }
            }
        }
    }

    const CharT* c_str() const
    {
        return m_data ? m_data : (const CharT*)"";
    }

    u32 size() const
    {
        return m_size;
    }

    u32 capacity() const
    {
        return m_capacity;
    }
};

// Format template function for single float argument
template <typename StringType>
void Format(StringType& result, const StringType& format, float value)
{
    // Simple implementation that replaces {0} with the float value
    const char* formatStr = format.c_str();
    u32 formatLen = format.size();

    // For now, just copy the format string as-is
    // In a real implementation, this would parse the format string and substitute arguments
    result.m_size = formatLen;
    result.m_capacity = formatLen + 1;
    result.m_data = (char*)Detail::TempStringAllocator::allocate(result.m_capacity);

    for (u32 i = 0; i < formatLen; i++)
    {
        result.m_data[i] = formatStr[i];
    }
    result.m_data[formatLen] = '\0';
    result.m_refCount = 1;
}

// Format template function for two float arguments
template <typename StringType>
void Format(StringType& result, const StringType& format, float value1, float value2)
{
    // Simple implementation that replaces {0} and {1} with the float values
    const char* formatStr = format.c_str();
    u32 formatLen = format.size();

    // For now, just copy the format string as-is
    // In a real implementation, this would parse the format string and substitute arguments
    result.m_size = formatLen;
    result.m_capacity = formatLen + 1;
    result.m_data = (char*)Detail::TempStringAllocator::allocate(result.m_capacity);

    for (u32 i = 0; i < formatLen; i++)
    {
        result.m_data[i] = formatStr[i];
    }
    result.m_data[formatLen] = '\0';
    result.m_refCount = 1;
}

#endif

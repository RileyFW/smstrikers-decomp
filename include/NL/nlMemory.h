#ifndef _NLMEMORY_H_
#define _NLMEMORY_H_

#include "Dolphin/os.h"
#include <stddef.h>

inline void* operator new(unsigned long, void* p)
{
    // ASSERT(p != NULL);
    return p;
}

inline void* operator new[](unsigned long, void* p)
{
    return p;
}

void nlFree(void*);
void* nlMalloc(unsigned long, unsigned int, bool);
void* nlMalloc(unsigned long);
void* operator new(unsigned long);
void operator delete[](void*);
void operator delete(void*);
unsigned int nlVirtualTotalFree();
unsigned int nlVirtualLargestBlock();
void nlVirtualFree(void*);
void* nlVirtualAlloc(unsigned long, bool);
void nlInitMemory();

#ifdef __cplusplus
extern "C"
{
#endif

// TODO: a bit messy include structure
#ifndef memcpy
    void* memcpy(void* dest, const void* src, size_t num);
#endif
#ifndef memmove
    void* memmove(void* dest, const void* src, size_t num);
#endif
#ifndef memset
    void* memset(void* dest, int ch, size_t count);
#endif
#ifndef memcmp
    int memcmp(const void* ptr1, const void* ptr2, size_t num);
#endif

    class DefaultAllocator
    {
    public:
        static void* allocate(size_t size)
        {
            return nlMalloc(size, 8, false); // 8-byte alignment, not at end
        }

        static void deallocate(void* ptr)
        {
            nlFree(ptr);
        }
    };

#ifdef __cplusplus
}
#endif

#endif // _NLMEMORY_H_

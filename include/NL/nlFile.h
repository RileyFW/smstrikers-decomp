#ifndef _NLFILE_H_
#define _NLFILE_H_

#include "types.h"

class nlFile;

typedef void (*ReadAsyncCallback)(nlFile*, void*, unsigned int, unsigned long);
typedef void (*LoadAsyncCallback)(void*, unsigned long, void*);

enum eAllocType
{
    AllocateStart = 0,
    AllocateEnd = 1,
};

class nlFile
{
public:
    virtual ~nlFile();
    nlFile();

    /* 0x0C */ virtual u32 FileSize(unsigned int* size) = 0;
    /* 0x10 */ virtual void Read(void* buffer, unsigned int size) = 0;

    /* 0x04 */ u32 m_unk_0x04;
    /* 0x08 */ u32 m_unk_0x08; // current position
};

bool nlLoadEntireFileAsync(const char*, LoadAsyncCallback callback, void* userData, unsigned int size, eAllocType type);
void nlLoadEntireFileAsyncCallback(nlFile*, void*, unsigned int, unsigned long);
void* nlLoadEntireFile(const char*, unsigned long*, unsigned int, eAllocType);
void nlClose(nlFile*);
void nlRead(nlFile*, void*, unsigned int);
void nlFileSize(nlFile*, unsigned int*);

#endif // _NLFILE_H_

#ifndef _LOADER_H_
#define _LOADER_H_

#include "types.h"

class LoadingManager;

// #include "NL/nlTask.h"

// class Loader;

// class LoadingManager : public nlTask
// {
// public:
//     virtual void Run(float);
//     virtual const char* GetName();

//     /* 0x18 */ unsigned int m_MaxEntries;
//     /* 0x1C */ unsigned int m_CurrEntry;
//     /* 0x20 */ unsigned int m_NumEntries;
//     /* 0x24 */ class Loader** m_LoaderQueue;
//     /* 0x28 */ unsigned char m_LoadFinished;
// }; // size 0x2C

class Loader
{
public:
    virtual bool StartLoad(LoadingManager*) = 0;
    // virtual bool Update() = 0;
    // virtual char* GetName() = 0;
    virtual bool Update() { return true; };
    virtual const char* GetName() { return NULL; };
};

#endif // _LOADER_H_

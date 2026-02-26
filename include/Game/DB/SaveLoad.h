#ifndef _SAVELOAD_H_
#define _SAVELOAD_H_

#include <dolphin/card.h>
#include "Game/Sys/gcmemcard.h"

void LoadMemoryCardIconData();

class SaveLoad
{
public:
    static bool CardBusy();
    static long StartSave(int, void (*)(long));
    static long StartLoad(int, void (*)(long), bool, bool);
    bool DidGameIDChange();
    static long StartDelete(int, void (*)(long));
    static long StartFormat(int, void (*)(long));
    static long StartFileExistsCheck(int, void (*)(long));
    static long StartMemoryCardIDCheck(int, void (*)(long));
    int GetSaveBlockSize(int);
    static u8 HasEnoughFreeSpace(int);
    void FreeAllCallbackMemory();
    static void RememberCurrentMemCardSerialID(int);
};

class MemoryCardIDCallbacks
{
public:
    void CardMountCB(unsigned long, long, void*);
};

class FileExistsCallbacks
{
public:
    void CardMountCB(unsigned long, long, void*);
};

class FormatCallbacks
{
public:
    void FormatDoneCB(unsigned long, long, void*);
    void CardMountCB(unsigned long, long, void*);
};

class DeleteCallbacks
{
public:
    void DeleteDoneCB(unsigned long, long, void*);
    void CardMountCB(unsigned long, long, void*);
};

// struct ICON_DATA_INFO
// {
//     unsigned short Comment1Offset;   // offset 0x0, size 0x2
//     unsigned short Comment2Offset;   // offset 0x2, size 0x2
//     unsigned short BannerOffset;     // offset 0x4, size 0x2
//     unsigned short BannerCLUTOffset; // offset 0x6, size 0x2
//     unsigned long IconOffset[8];     // offset 0x8, size 0x20
//     unsigned long IconCLUTOffset;    // offset 0x28, size 0x4
//     unsigned char* pHeaderData;      // offset 0x2C, size 0x4
// }; // total size: 0x30

// struct ICON_CONFIG
// {
//     unsigned char BannerFormat; // offset 0x0, size 0x1
//     unsigned char IconCount;    // offset 0x1, size 0x1
//     char IconFormat;            // offset 0x2, size 0x1
//     char IconAnimType;          // offset 0x3, size 0x1
//     char IconSpeeds[8];         // offset 0x4, size 0x8
//     unsigned long HeaderSize;   // offset 0xC, size 0x4
// }; // total size: 0x10

// struct MC_FILE
// {
//     struct CARDFileInfo FileInfo;  // offset 0x0, size 0x14
//     struct ICON_CONFIG IconCfg;    // offset 0x14, size 0x10
//     unsigned long TotalHeaderSize; // offset 0x24, size 0x4
// }; // total size: 0x28

class LoadCallbacks
{
public:
    void LoadIconDataDoneCB(unsigned long, long, void*);
    void ReadDoneCB(unsigned long, long, void*);
    void CardMountCB(unsigned long, long, void*);

    /* 0x00 */ void* m_pReadBuffer;
    /* 0x04 */ unsigned long m_AlignedReadBufferDataSize;
    /* 0x08 */ void* m_pIconReadBuffer;
    /* 0x0C */ unsigned long m_AlignedIconReadBufferDataSize;
    /* 0x10 */ MemCard::MC_FILE* m_pLoadFile;
    /* 0x14 */ bool m_TestGameID;
    /* 0x15 */ bool m_GameIDTestResult;
    /* 0x16 */ bool m_PerformLoad;
    /* 0x17 */ bool m_MustFreeBuffers;
    /* 0x18 */ unsigned long m_IconLoadedCRC;
}; // total size: 0x1C

class SaveCallbacks
{
public:
    void FileWriteCB(unsigned long, long, void*);
    void DoSave(unsigned long);
    void FileWriteIconCB(unsigned long, long, void*);
    void CreateFileCB(unsigned long, long, void*);
    void CardMountCB(unsigned long, long, void*);

    /* 0x00 */ MemCard::MC_FILE* m_pSaveFile;
    /* 0x04 */ void* m_pSaveGameBuffer;
    /* 0x08 */ unsigned long m_Slot;
    /* 0x0C */ unsigned long m_IconCRC;
    /* 0x10 */ unsigned char m_MustFreeMemory;
}; // total size: 0x14

// class IconDataCache
// {
// public:
//     ~IconDataCache();
// };

// class MemCardFunctor
// {
// public:
//     void MCMemberFunctor<LoadCallbacks>::Call(unsigned long, long);
//     void MCMemberFunctor<SaveCallbacks>::Call(unsigned long, long);
//     void MCMemberFunctor<DeleteCallbacks>::Call(unsigned long, long);
//     void MCMemberFunctor<FormatCallbacks>::Call(unsigned long, long);
//     void MCMemberFunctor<FileExistsCallbacks>::Call(unsigned long, long);
//     void MCMemberFunctor<MemoryCardIDCallbacks>::Call(unsigned long, long);
// };

#endif // _SAVELOAD_H_

#ifndef _GCMEMCARD_H_
#define _GCMEMCARD_H_

// #include "Game/DB/SaveLoad.h"
#include <dolphin/card.h>
#include "NL/nlStaticSortedSlot.h"

enum INTERNAL_STATE
{
    IS_IDLE = 0,
    IS_ERROR = 1,
    IS_MOUNTING = 2,
    IS_CARDCHECK = 3,
    IS_MOUNTED = 4,
    IS_MOUNTED_ERROR = 5,
    IS_FORMATTING = 6,
    IS_CREATING = 7,
    IS_DELETING = 8,
    IS_READING = 9,
    IS_WRITING = 10,
    IS_WRITINGSTATUS = 11,
};

enum CARD_STATE
{
    CS_IDLE = 0,
    CS_MOUNTING = 1,
    CS_MOUNTED = 2,
    CS_MOUNTED_ERROR = 3,
    CS_FORMATTING = 4,
    CS_CREATING = 5,
    CS_DELETING = 6,
    CS_READING = 7,
    CS_WRITING = 8,
    CS_END = 9,
};

struct CARD_INFO
{
    /* 0x0 */ long CardSize;
    /* 0x4 */ long SectorSize;
    /* 0x8 */ long FreeBytes;
    /* 0xC */ long FreeFiles;
}; // total size: 0x10

class MemCardFunctor
{
public:
    MemCardFunctor();

    /* 0x00 */ unsigned char m_FunctorMem[24];
}; // total size: 0x18

class MemCard
{
public:
    struct ICON_DATA_INFO
    {
        /* 0x00 */ unsigned short Comment1Offset;
        /* 0x02 */ unsigned short Comment2Offset;
        /* 0x04 */ unsigned short BannerOffset;
        /* 0x06 */ unsigned short BannerCLUTOffset;
        /* 0x08 */ unsigned long IconOffset[8];
        /* 0x28 */ unsigned long IconCLUTOffset;
        /* 0x2C */ unsigned char* pHeaderData;
    }; // total size: 0x30

    struct ICON_CONFIG
    {
        void GetValidDataInfo(ICON_DATA_INFO&) const;

        /* 0x0 */ unsigned char BannerFormat;
        /* 0x1 */ unsigned char IconCount;
        /* 0x2 */ char IconFormat;
        /* 0x3 */ char IconAnimType;
        /* 0x4 */ char IconSpeeds[8];
        /* 0xC */ unsigned long HeaderSize;
    }; // total size: 0x10

    struct MC_FILE
    {
        /* 0x00 */ CARDFileInfo FileInfo;
        /* 0x14 */ ICON_CONFIG IconCfg;
        /* 0x24 */ unsigned long TotalHeaderSize;
    }; // total size: 0x28

    void CardRemovedCB(long, long);
    void MountDoneCB(long, long);
    void CreateFileDoneCB(long, long);
    void FormatDoneCB(long, long);
    void DeleteFileDoneCB(long, long);
    void ReadFileDoneCB(long, long);
    void SetStatusDoneCB(long, long);
    void CardCheckBrokenDoneCB(long, long);
    void CardCheckDoneCB(long, long);
    void WriteFileDoneCB(long, long);
    void BeginCardAccess(const MemCardFunctor&);
    void CreateFile(const char*, unsigned long, MemCard::ICON_CONFIG*, MemCard::MC_FILE*&, const MemCardFunctor&);
    void OpenFile(const char*, MemCard::MC_FILE*&, unsigned long*);
    void FormatCard(const MemCardFunctor&);
    void DeleteFile(const char*, const MemCardFunctor&);
    void InternalReadFile(MemCard::MC_FILE*, void*, unsigned long, unsigned long, const MemCardFunctor&);
    void InternalWriteFile(MemCard::MC_FILE*, void*, unsigned long, unsigned long, const MemCardFunctor&, bool);
    void CloseFile(MemCard::MC_FILE*);
    void FileExists(const char*);
    void WriteFileIconData(MemCard::MC_FILE*, void*, const MemCardFunctor&);
    void AlignBytesToSectorSize(unsigned long);

    int GetSerialID() const { return 0; };

    INTERNAL_STATE m_State;                      // offset 0x0, size 0x4
    unsigned long m_Slot;                        // offset 0x4, size 0x4
    CARD_STATE m_CardState;                      // offset 0x8, size 0x4
    CARD_INFO m_CardInfo;                        // offset 0xC, size 0x10
    unsigned long m_LastTransferSize;            // offset 0x1C, size 0x4
    unsigned long m_TargetTransferSize;          // offset 0x20, size 0x4
    MemCardFunctor m_CB[9];                      // offset 0x24, size 0xD8
    nlStaticSortedSlot<MC_FILE, 16> m_OpenFiles; // offset 0xFC, size 0x314
    MC_FILE* m_pFileCB;                          // offset 0x410, size 0x4
    void* m_pDataCB;                             // offset 0x414, size 0x4
    unsigned long m_GameId;                      // offset 0x418, size 0x4
    unsigned short m_CompanyId;                  // offset 0x41C, size 0x2
    unsigned char m_CardWorkArea[41472];         // offset 0x41E, size 0xA200
}; // total size: 0xA620

// class nlBSearch < nlSortedSlot < MemCard
// {
// public:
//     void MC_FILE, 16 > ::EntryLookup<MemCard::MC_FILE>, unsigned long > (const unsigned long&, nlSortedSlot<MemCard::MC_FILE, 16>::EntryLookup<MemCard::MC_FILE>*, int);
// };

// class nlStaticSortedSlot < MemCard
// {
// public:
//     void MC_FILE, 16 > ::GetNewEntry();
//     void MC_FILE, 16 > ::FreeEntry(MemCard::MC_FILE*);
//     void MC_FILE, 16 > ::FreeLookup();
//     void MC_FILE, 16 > ::ExpandLookup();
// };

#endif // _GCMEMCARD_H_

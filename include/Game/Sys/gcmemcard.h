#ifndef _GCMEMCARD_H_
#define _GCMEMCARD_H_

// void 0x801CB768..0x801CB7BC | size: 0x54;
// class MemCardFunctor
// {
// public:
//     MemCardFunctor();
// };

// class MemCard
// {
// public:
//     void CardRemovedCB(long, long);
//     void MountDoneCB(long, long);
//     void CreateFileDoneCB(long, long);
//     void FormatDoneCB(long, long);
//     void DeleteFileDoneCB(long, long);
//     void ReadFileDoneCB(long, long);
//     void SetStatusDoneCB(long, long);
//     void CardCheckBrokenDoneCB(long, long);
//     void CardCheckDoneCB(long, long);
//     void WriteFileDoneCB(long, long);
//     void BeginCardAccess(const MemCardFunctor&);
//     void CreateFile(const char*, unsigned long, MemCard::ICON_CONFIG*, MemCard::MC_FILE*&, const MemCardFunctor&);
//     void OpenFile(const char*, MemCard::MC_FILE*&, unsigned long*);
//     void FormatCard(const MemCardFunctor&);
//     void DeleteFile(const char*, const MemCardFunctor&);
//     void InternalReadFile(MemCard::MC_FILE*, void*, unsigned long, unsigned long, const MemCardFunctor&);
//     void InternalWriteFile(MemCard::MC_FILE*, void*, unsigned long, unsigned long, const MemCardFunctor&, bool);
//     void CloseFile(MemCard::MC_FILE*);
//     void FileExists(const char*);
//     void WriteFileIconData(MemCard::MC_FILE*, void*, const MemCardFunctor&);
//     void ICON_CONFIG::GetValidDataInfo(MemCard::ICON_DATA_INFO&) const;
//     void AlignBytesToSectorSize(unsigned long);
//     void GetSerialID() const;
// };

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

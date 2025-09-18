#ifndef _SAVELOAD_H_
#define _SAVELOAD_H_

void LoadMemoryCardIconData();

class SaveLoad
{
public:
    static bool CardBusy();
    void StartSave(int, void (*)(long));
    void StartLoad(int, void (*)(long), bool, bool);
    void DidGameIDChange();
    void StartDelete(int, void (*)(long));
    void StartFormat(int, void (*)(long));
    void StartFileExistsCheck(int, void (*)(long));
    void StartMemoryCardIDCheck(int, void (*)(long));
    void GetSaveBlockSize(int);
    void HasEnoughFreeSpace(int);
    void FreeAllCallbackMemory();
    void RememberCurrentMemCardSerialID(int);
};

// class MemoryCardIDCallbacks
// {
// public:
//     void CardMountCB(unsigned long, long, void*);
// };

// class FileExistsCallbacks
// {
// public:
//     void CardMountCB(unsigned long, long, void*);
// };

// class FormatCallbacks
// {
// public:
//     void FormatDoneCB(unsigned long, long, void*);
//     void CardMountCB(unsigned long, long, void*);
// };

// class DeleteCallbacks
// {
// public:
//     void DeleteDoneCB(unsigned long, long, void*);
//     void CardMountCB(unsigned long, long, void*);
// };

// class LoadCallbacks
// {
// public:
//     void LoadIconDataDoneCB(unsigned long, long, void*);
//     void ReadDoneCB(unsigned long, long, void*);
//     void CardMountCB(unsigned long, long, void*);
// };

// class SaveCallbacks
// {
// public:
//     void FileWriteCB(unsigned long, long, void*);
//     void DoSave(unsigned long);
//     void FileWriteIconCB(unsigned long, long, void*);
//     void CreateFileCB(unsigned long, long, void*);
//     void CardMountCB(unsigned long, long, void*);
// };

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

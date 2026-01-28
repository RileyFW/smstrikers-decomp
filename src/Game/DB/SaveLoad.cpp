#include "Game/DB/SaveLoad.h"
#include "Game/Sys/gcmemcard.h"

bool InOperation = false;

LoadCallbacks LoadSystem;

static MemCard* s_MemCardStorage[2] = { nullptr, nullptr };
MemCard** g_MemCards = s_MemCardStorage;
struct MemCardIDInfo
{
    s64 serialID;
    // u32 cardID;
};
MemCardIDInfo mLastKnownMemCardID;

// /**
//  * Offset/Address/Size: 0x0 | 0x8018D40C | size: 0xA4
//  */
// void 0x8028D340..0x8028D344 | size: 0x4
// {
// }

// /**
//  * Offset/Address/Size: 0x104 | 0x8018D3D8 | size: 0x34
//  */
// void MemCardFunctor::MCMemberFunctor<LoadCallbacks>::Call(unsigned long, long)
// {
// }

// /**
//  * Offset/Address/Size: 0xD0 | 0x8018D3A4 | size: 0x34
//  */
// void MemCardFunctor::MCMemberFunctor<SaveCallbacks>::Call(unsigned long, long)
// {
// }

// /**
//  * Offset/Address/Size: 0x9C | 0x8018D370 | size: 0x34
//  */
// void MemCardFunctor::MCMemberFunctor<DeleteCallbacks>::Call(unsigned long, long)
// {
// }

// /**
//  * Offset/Address/Size: 0x68 | 0x8018D33C | size: 0x34
//  */
// void MemCardFunctor::MCMemberFunctor<FormatCallbacks>::Call(unsigned long, long)
// {
// }

// /**
//  * Offset/Address/Size: 0x34 | 0x8018D308 | size: 0x34
//  */
// void MemCardFunctor::MCMemberFunctor<FileExistsCallbacks>::Call(unsigned long, long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8018D2D4 | size: 0x34
//  */
// void MemCardFunctor::MCMemberFunctor<MemoryCardIDCallbacks>::Call(unsigned long, long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38E4 | 0x8018D240 | size: 0x94
//  */
// IconDataCache::~IconDataCache()
// {
// }

/**
 * Offset/Address/Size: 0x38DC | 0x8018D238 | size: 0x8
 */
bool SaveLoad::CardBusy()
{
    return InOperation;
}

/**
 * Offset/Address/Size: 0x3720 | 0x8018D07C | size: 0x1BC
 */
void LoadMemoryCardIconData()
{
}

// /**
//  * Offset/Address/Size: 0x355C | 0x8018CEB8 | size: 0x1C4
//  */
// void LoadCallbacks::LoadIconDataDoneCB(unsigned long, long, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x3254 | 0x8018CBB0 | size: 0x308
//  */
// void LoadCallbacks::ReadDoneCB(unsigned long, long, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x2DA8 | 0x8018C704 | size: 0x4AC
//  */
// void SaveCallbacks::FileWriteCB(unsigned long, long, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x2708 | 0x8018C064 | size: 0x6A0
//  */
// void SaveCallbacks::DoSave(unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x24EC | 0x8018BE48 | size: 0x21C
//  */
// void SaveCallbacks::FileWriteIconCB(unsigned long, long, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1F30 | 0x8018B88C | size: 0x5BC
//  */
// void SaveCallbacks::CreateFileCB(unsigned long, long, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1EC4 | 0x8018B820 | size: 0x6C
//  */
// void DeleteCallbacks::DeleteDoneCB(unsigned long, long, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1E58 | 0x8018B7B4 | size: 0x6C
//  */
// void FormatCallbacks::FormatDoneCB(unsigned long, long, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x11DC | 0x8018AB38 | size: 0xC7C
//  */
// void SaveCallbacks::CardMountCB(unsigned long, long, void*)
// {
// }

/**
 * Offset/Address/Size: 0x10D4 | 0x8018AA30 | size: 0x108
 */
void SaveLoad::StartSave(int, void (*)(long))
{
}

// /**
//  * Offset/Address/Size: 0xE88 | 0x8018A7E4 | size: 0x24C
//  */
// void LoadCallbacks::CardMountCB(unsigned long, long, void*)
// {
// }

/**
 * Offset/Address/Size: 0xBFC | 0x8018A558 | size: 0x28C
 */
void SaveLoad::StartLoad(int, void (*)(long), bool, bool)
{
}

/**
 * Offset/Address/Size: 0xBEC | 0x8018A548 | size: 0x10
 */
bool SaveLoad::DidGameIDChange()
{
    return LoadSystem.m_GameIDTestResult;
}

// /**
//  * Offset/Address/Size: 0xB10 | 0x8018A46C | size: 0xDC
//  */
// void DeleteCallbacks::CardMountCB(unsigned long, long, void*)
// {
// }

/**
 * Offset/Address/Size: 0xA54 | 0x8018A3B0 | size: 0xBC
 */
void SaveLoad::StartDelete(int, void (*)(long))
{
}

// /**
//  * Offset/Address/Size: 0x900 | 0x8018A25C | size: 0x154
//  */
// void FormatCallbacks::CardMountCB(unsigned long, long, void*)
// {
// }

/**
 * Offset/Address/Size: 0x844 | 0x8018A1A0 | size: 0xBC
 */
void SaveLoad::StartFormat(int, void (*)(long))
{
}

// /**
//  * Offset/Address/Size: 0x5EC | 0x80189F48 | size: 0x258
//  */
// void FileExistsCallbacks::CardMountCB(unsigned long, long, void*)
// {
// }

/**
 * Offset/Address/Size: 0x520 | 0x80189E7C | size: 0xCC
 */
void SaveLoad::StartFileExistsCheck(int, void (*)(long))
{
}

// /**
//  * Offset/Address/Size: 0x45C | 0x80189DB8 | size: 0xC4
//  */
// void MemoryCardIDCallbacks::CardMountCB(unsigned long, long, void*)
// {
// }

/**
 * Offset/Address/Size: 0x390 | 0x80189CEC | size: 0xCC
 */
void SaveLoad::StartMemoryCardIDCheck(int, void (*)(long))
{
}

/**
 * Offset/Address/Size: 0x264 | 0x80189BC0 | size: 0x12C
 */
void SaveLoad::GetSaveBlockSize(int)
{
}

/**
 * Offset/Address/Size: 0xD8 | 0x80189A34 | size: 0x18C
 */
void SaveLoad::HasEnoughFreeSpace(int)
{
}

/**
 * Offset/Address/Size: 0x34 | 0x80189990 | size: 0xA4
 */
void SaveLoad::FreeAllCallbackMemory()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8018995C | size: 0x34
 */
void SaveLoad::RememberCurrentMemCardSerialID(int id)
{
    mLastKnownMemCardID.serialID = g_MemCards[id]->GetSerialID();
}

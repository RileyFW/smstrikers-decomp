#include "Game/DB/SaveLoad.h"
#include "Game/GameInfo.h"
#include "Game/Sys/gcmemcard.h"
#include "Game/FE/feHelpFuncs.h"
#include "NL/nlFileGC.h"
#include <string.h>

extern void nlFree(void*);

IconDataCache gIconDataCache;

bool InOperation = false;

LoadCallbacks LoadSystem;
SaveCallbacks SaveSystem;
DeleteCallbacks DeleteSystem;
FormatCallbacks FormatSystem;

static MemCard* s_MemCardStorage[2] = { nullptr, nullptr };
void (*g_Callback)(long);
FileExistsCallbacks FileExistsSystem;
MemoryCardIDCallbacks MemoryCardIDSystem;
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
 * TODO: 93.0% match - r4/r0/r11 vs r0/r11/r10 register allocation for iconFmt/iconCount/bannerFmt loads;
 * expression scheduling (mulli/mullw order) differs; SDA vs absolute addressing for string literals;
 * lis r5 vs r6 for gIconDataCache after nlMalloc in file-reading sections
 */
#pragma push
#pragma opt_propagation off
void LoadMemoryCardIconData()
{
    nlFile* pFile1;
    unsigned int iconSize;
    unsigned int bannerSize;

    memset(&gIconDataCache, 0, sizeof(MemCard::ICON_CONFIG));

    gIconDataCache.mIconConfig.IconCount = 1;
    gIconDataCache.mIconConfig.IconFormat = 2;
    gIconDataCache.mIconConfig.IconSpeeds[0] = 3;
    gIconDataCache.mIconConfig.BannerFormat = 2;

    gIconDataCache.mIconConfig.GetValidDataInfo(gIconDataCache.mIconDataInfo);

    s8 iconFmt = gIconDataCache.mIconConfig.IconFormat;
    u8 iconCount = gIconDataCache.mIconConfig.IconCount;
    u8 bannerFmt = gIconDataCache.mIconConfig.BannerFormat;

    u32 headerSize = ((bannerFmt == 1) ? 0x200 : 0)
                   + (bannerFmt * 0xC00 + iconCount * (iconFmt << 10))
                   + ((iconFmt == 1) ? 0x200 : 0)
                   + 0x40;
    gIconDataCache.mIconConfig.HeaderSize = headerSize;

    gIconDataCache.mIconHdrBuffer = nlMalloc(headerSize, 0x20, false);
    gIconDataCache.mIconDataInfo.pHeaderData = (unsigned char*)gIconDataCache.mIconHdrBuffer;
    void* pHdrBuf = gIconDataCache.mIconDataInfo.pHeaderData;

    nlStrNCpy((char*)pHdrBuf, GetMemCardTitle(), 0x20);
    char* pDescDst = (char*)gIconDataCache.mIconDataInfo.pHeaderData + 0x20;
    nlStrNCpy(pDescDst, GetMemCardDescription(), 0x20);

    pFile1 = nlOpen("@2009");
    nlFileSize(pFile1, &bannerSize);
    void* bannerBuf = nlMalloc(bannerSize, 0x20, true);
    gIconDataCache.mBannerBuffer = bannerBuf;
    nlRead(pFile1, bannerBuf, bannerSize);
    nlClose(pFile1);

    nlFile* pFile2 = nlOpen("@2010");
    nlFileSize(pFile2, &iconSize);
    void* iconBuf = nlMalloc(iconSize, 0x20, true);
    gIconDataCache.mIconBuffer = iconBuf;
    nlRead(pFile2, iconBuf, iconSize);
    nlClose(pFile2);
}
#pragma pop

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
long SaveLoad::StartSave(int slot, void (*callback)(long))
{
    nlPrintf("StartSave\n");

    if (SaveSystem.m_MustFreeMemory)
    {
        if (SaveSystem.m_pSaveGameBuffer != nullptr)
        {
            nlFree(SaveSystem.m_pSaveGameBuffer);
            SaveSystem.m_pSaveGameBuffer = nullptr;
        }
    }

    SaveSystem.m_MustFreeMemory = false;
    InOperation = true;
    g_Callback = callback;

    typedef void (SaveCallbacks::*MemberCB)(unsigned long, long, void*);
    MemberCB cb = &SaveCallbacks::CardMountCB;

    MemCardFunctor functor;
    new (functor.m_FunctorMem) MemCardFunctor::MCMemberFunctor<SaveCallbacks>(&SaveSystem, cb);

    s32 result = g_MemCards[slot]->BeginCardAccess(functor);
    if (result != 0)
    {
        InOperation = false;
    }

    return result;
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
long SaveLoad::StartLoad(int, void (*)(long), bool, bool)
{
    return 0;
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
long SaveLoad::StartDelete(int slot, void (*callback)(long))
{
    nlPrintf("StartDelete\n");

    InOperation = true;

    typedef void (DeleteCallbacks::*MemberCB)(unsigned long, long, void*);
    MemberCB cb = &DeleteCallbacks::CardMountCB;

    MemCardFunctor functor;
    new (functor.m_FunctorMem) MemCardFunctor::MCMemberFunctor<DeleteCallbacks>(&DeleteSystem, cb);

    s32 result = g_MemCards[slot]->BeginCardAccess(functor);
    if (result != 0)
    {
        InOperation = false;
    }

    return result;
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
long SaveLoad::StartFormat(int slot, void (*callback)(long))
{
    nlPrintf("StartFormat\n");

    InOperation = true;

    typedef void (FormatCallbacks::*MemberCB)(unsigned long, long, void*);
    MemberCB cb = &FormatCallbacks::CardMountCB;

    MemCardFunctor functor;
    new (functor.m_FunctorMem) MemCardFunctor::MCMemberFunctor<FormatCallbacks>(&FormatSystem, cb);

    s32 result = g_MemCards[slot]->BeginCardAccess(functor);
    if (result != 0)
    {
        InOperation = false;
    }

    return result;
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
long SaveLoad::StartFileExistsCheck(int slot, void (*callback)(long))
{
    nlPrintf("StartFileExistsCheck\n");

    InOperation = true;
    g_Callback = callback;

    typedef void (FileExistsCallbacks::*MemberCB)(unsigned long, long, void*);
    MemberCB cb = &FileExistsCallbacks::CardMountCB;

    MemCardFunctor functor;
    new (functor.m_FunctorMem) MemCardFunctor::MCMemberFunctor<FileExistsCallbacks>(&FileExistsSystem, cb);

    s32 result = g_MemCards[slot]->BeginCardAccess(functor);
    if (result != 0)
    {
        InOperation = false;
    }

    return result;
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
long SaveLoad::StartMemoryCardIDCheck(int slot, void (*callback)(long))
{
    nlPrintf("StartMemoryCardIDCheck\n");

    InOperation = true;
    g_Callback = callback;

    typedef void (MemoryCardIDCallbacks::*MemberCB)(unsigned long, long, void*);
    MemberCB cb = &MemoryCardIDCallbacks::CardMountCB;

    MemCardFunctor functor;
    new (functor.m_FunctorMem) MemCardFunctor::MCMemberFunctor<MemoryCardIDCallbacks>(&MemoryCardIDSystem, cb);

    s32 result = g_MemCards[slot]->BeginCardAccess(functor);
    if (result != 0)
    {
        InOperation = false;
    }

    return result;
}

/**
 * Offset/Address/Size: 0x264 | 0x80189BC0 | size: 0x12C
 * TODO: 76.4% match - loop pre-check uses cmpwi path (target keeps addic flags), icon constant/register allocation differs (r3/r4/r5 vs r7/r4/r3), and second block-count path still inserts cmpwi/mr
 */
#pragma push
#pragma opt_propagation off
int SaveLoad::GetSaveBlockSize(int)
{
    int dataSize = nlSingleton<GameInfoManager>::s_pInstance->GetMemoryCardDataSize();
    int numBlocks = 0;

    if ((dataSize += 12) > 0)
    {
        int blocks = (u32)(dataSize + 0x1FFF) >> 13;
        int i = blocks;
        while (i-- > 0)
        {
            numBlocks++;
        }
    }

    MemCard::ICON_CONFIG IconCfg;
    IconCfg.BannerFormat = 0;
    IconCfg.IconCount = 0;
    IconCfg.IconFormat = 0;
    IconCfg.IconAnimType = 0;
    memset(IconCfg.IconSpeeds, 0, 8);

    memset(&IconCfg, 0, sizeof(MemCard::ICON_CONFIG));
    IconCfg.BannerFormat = 2;
    IconCfg.IconCount = 1;
    IconCfg.IconFormat = 2;
    IconCfg.IconSpeeds[0] = 3;

    int iconFormat = IconCfg.IconFormat;
    int iconCount = IconCfg.IconCount;

    int iconSize = (iconFormat << 10) * iconCount;
    int bannerClut = (iconFormat < 2) ? 0x200 : 0;
    int bannerSize = iconFormat * 0xC00;
    int iconClut = (iconCount <= 0) ? 0x200 : 0;

    IconCfg.HeaderSize = bannerClut + bannerSize + iconSize + iconClut + 0x40;

    if ((dataSize = (int)IconCfg.HeaderSize) > 0)
    {
        int blocks = (u32)(dataSize + 0x1FFF) >> 13;
        int i = blocks;
        while (i-- > 0)
        {
            numBlocks++;
        }
    }

    return numBlocks;
}
#pragma pop

/**
 * Offset/Address/Size: 0xD8 | 0x80189A34 | size: 0x18C
 * TODO: 74.0% match - register allocation rotated (slot offset/numBlocks/card in
 * r31/r29/r30 instead of r29/r30/r31); compiler constant-folds ~(iconCount|-1) eliminating
 * the nor+srawi+and chain; first/second block loops emit an extra early ble (target
 * speculatively schedules addi/srwi before branch); u8 return adds clrlwi masking
 */
u8 SaveLoad::HasEnoughFreeSpace(int Slot)
{
    MemCard* card = g_MemCards[Slot];
    int dataSize = nlSingleton<GameInfoManager>::s_pInstance->GetMemoryCardDataSize();
    int numBlocks = 0;

    if ((dataSize += 12) > 0)
    {
        dataSize = (u32)(dataSize + 0x1FFF) >> 13;
        while (dataSize-- > 0)
        {
            numBlocks++;
        }
    }

    MemCard::ICON_CONFIG IconCfg;
    IconCfg.BannerFormat = 0;
    IconCfg.IconCount = 0;
    IconCfg.IconFormat = 0;
    IconCfg.IconAnimType = 0;
    memset(IconCfg.IconSpeeds, 0, 8);

    memset(&IconCfg, 0, sizeof(MemCard::ICON_CONFIG));
    IconCfg.IconCount = 1;
    IconCfg.IconFormat = 2;
    IconCfg.IconSpeeds[0] = 3;
    IconCfg.BannerFormat = 2;

    int iconFormat = IconCfg.IconFormat;
    int iconCount = IconCfg.IconCount;

    int iconSize = (iconFormat << 10) * iconCount;
    int temp = ~(iconCount | -1);
    int bannerClut = (temp >> 31) & 0x200;
    int bannerSize = iconFormat * 0xC00;
    int iconClut = (temp >> 31) & 0x200;

    IconCfg.HeaderSize = bannerClut + bannerSize + iconSize + iconClut + 0x40;

    if ((dataSize = (int)IconCfg.HeaderSize) > 0)
    {
        dataSize = (u32)(dataSize + 0x1FFF) >> 13;
        while (dataSize-- > 0)
        {
            numBlocks++;
        }
    }

    unsigned long sectorSize = card->m_CardInfo.SectorSize;
    unsigned long bytestosave = numBlocks * sectorSize;
    unsigned long alignedSize = g_MemCards[Slot]->AlignBytesToSectorSize(bytestosave);
    MemCard* mc = g_MemCards[Slot];
    if (alignedSize > mc->m_CardInfo.FreeBytes)
    {
        return 0;
    }

    return mc->m_CardInfo.FreeFiles >= 1;
}

/**
 * Offset/Address/Size: 0x34 | 0x80189990 | size: 0xA4
 */
void SaveLoad::FreeAllCallbackMemory()
{
    if (SaveSystem.m_MustFreeMemory)
    {
        if (SaveSystem.m_pSaveGameBuffer != nullptr)
        {
            nlFree(SaveSystem.m_pSaveGameBuffer);
            SaveSystem.m_pSaveGameBuffer = nullptr;
        }
    }
    SaveSystem.m_MustFreeMemory = false;

    if (LoadSystem.m_MustFreeBuffers)
    {
        nlFree(LoadSystem.m_pReadBuffer);
        LoadSystem.m_pReadBuffer = nullptr;
        nlFree(LoadSystem.m_pIconReadBuffer);
        LoadSystem.m_pIconReadBuffer = nullptr;
    }
    LoadSystem.m_MustFreeBuffers = false;
}

/**
 * Offset/Address/Size: 0x0 | 0x8018995C | size: 0x34
 */
void SaveLoad::RememberCurrentMemCardSerialID(int id)
{
    mLastKnownMemCardID.serialID = g_MemCards[id]->GetSerialID();
}

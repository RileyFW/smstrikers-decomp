#include "Game/Sys/gcmemcard.h"

void nlPrintf(const char*, ...);

// /**
//  * Offset/Address/Size: 0x30 | 0x801CB798 | size: 0x24
//  */
// void nlStaticSortedSlot<MemCard::MC_FILE, 16>::GetNewEntry()
// {
// }

// /**
//  * Offset/Address/Size: 0x20 | 0x801CB788 | size: 0x10
//  */
// void nlStaticSortedSlot<MemCard::MC_FILE, 16>::FreeEntry(MemCard::MC_FILE*)
// {
// }

// /**
//  * Offset/Address/Size: 0x14 | 0x801CB77C | size: 0xC
//  */
// void nlStaticSortedSlot<MemCard::MC_FILE, 16>::FreeLookup()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801CB768 | size: 0x14
//  */
// void nlStaticSortedSlot<MemCard::MC_FILE, 16>::ExpandLookup()
// {
// }

// /**
//  * Offset/Address/Size: 0x8C | 0x801CB4DC | size: 0x28C
//  */
// void 0x801CB768..0x801CB7BC | size: 0x54
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801CB450 | size: 0x8C
//  */
// void nlBSearch<nlSortedSlot<MemCard::MC_FILE, 16>::EntryLookup<MemCard::MC_FILE>, unsigned long>(const unsigned long&, nlSortedSlot<MemCard::MC_FILE, 16>::EntryLookup<MemCard::MC_FILE>*, int)
// {
// }

// /**
//  * Offset/Address/Size: 0x904 | 0x801CB444 | size: 0xC
//  */
// MemCardFunctor::MemCardFunctor() - moved to header as inline
// {
// }

/**
 * Offset/Address/Size: 0x824 | 0x801CB364 | size: 0xE0
 */
void MemCard::CardRemovedCB(long, long)
{
}

/**
 * Offset/Address/Size: 0x6E0 | 0x801CB220 | size: 0x144
 */
void MemCard::MountDoneCB(long, long)
{
}

/**
 * Offset/Address/Size: 0x540 | 0x801CB080 | size: 0x1A0
 */
void MemCard::CreateFileDoneCB(long, long)
{
}

/**
 * Offset/Address/Size: 0x498 | 0x801CAFD8 | size: 0xA8
 */
void MemCard::FormatDoneCB(long channel, long result)
{
    long ch = (long)channel;
    MemCard* card = g_MemCards[ch];
    if (result == 0L)
    {
        CARDFreeBlocks(card->m_Slot, &card->m_CardInfo.FreeBytes, &card->m_CardInfo.FreeFiles);
        card->m_State = IS_MOUNTED;
        card->m_CardState = CS_MOUNTED;
    }
    else
    {
        card->m_State = IS_IDLE;
        card->m_CardState = CS_IDLE;
    }
    MemCardFunctor::MCInternalFunctorBase* pFunctor = (MemCardFunctor::MCInternalFunctorBase*)&card->m_CB[4];
    unsigned long slot = card->m_Slot;
    if (*(long*)pFunctor != 0)
    {
        pFunctor->Call(slot, result);
    }
    else
    {
        nlPrintf("Trying to call unset MC functor");
    }
}

/**
 * Offset/Address/Size: 0x3D0 | 0x801CAF10 | size: 0xC8
 */
void MemCard::DeleteFileDoneCB(long channel, long result)
{
    MemCard* card = g_MemCards[channel];
    CARDFreeBlocks(card->m_Slot, &card->m_CardInfo.FreeBytes, &card->m_CardInfo.FreeFiles);
    card->m_State = IS_MOUNTED;
    card->m_CardState = CS_MOUNTED;
    if (CARDProbeEx(card->m_Slot, &card->m_CardInfo.CardSize, &card->m_CardInfo.SectorSize) != 0)
    {
        card->m_State = IS_IDLE;
        card->m_CardState = CS_IDLE;
    }
    CARDFreeBlocks(card->m_Slot, &card->m_CardInfo.FreeBytes, &card->m_CardInfo.FreeFiles);
    MemCardFunctor::MCInternalFunctorBase* pFunctor = (MemCardFunctor::MCInternalFunctorBase*)&card->m_CB[6];
    unsigned long slot = card->m_Slot;
    if (*(long*)pFunctor != 0)
    {
        pFunctor->Call(slot, result);
    }
    else
    {
        nlPrintf("Trying to call unset MC functor");
    }
}

/**
 * Offset/Address/Size: 0x328 | 0x801CAE68 | size: 0xA8
 */
void MemCard::ReadFileDoneCB(long channel, long result)
{
    MemCard* card = g_MemCards[channel];
    card->m_State = IS_MOUNTED;
    card->m_CardState = CS_MOUNTED;
    if (CARDProbeEx(card->m_Slot, &card->m_CardInfo.CardSize, &card->m_CardInfo.SectorSize) != 0)
    {
        card->m_State = IS_IDLE;
        card->m_CardState = CS_IDLE;
    }
    MemCardFunctor::MCInternalFunctorBase* pFunctor = (MemCardFunctor::MCInternalFunctorBase*)&card->m_CB[7];
    unsigned long slot = card->m_Slot;
    if (*(long*)pFunctor != 0)
    {
        pFunctor->Call(slot, result);
    }
    else
    {
        nlPrintf("Trying to call unset MC functor");
    }
}

/**
 * Offset/Address/Size: 0x1F0 | 0x801CAD30 | size: 0x138
 */
void MemCard::SetStatusDoneCB(long channel, long result)
{
    MemCard* card = g_MemCards[channel];
    s32 err = 0;
    if (result == 0)
    {
        card->m_State = IS_MOUNTED;
        MC_FILE* file = card->m_pFileCB;
        void* data = card->m_pDataCB;
        unsigned long headerSize = file->TotalHeaderSize;

        if (card->m_State != IS_MOUNTED)
        {
            err = -100;
        }
        else
        {
            unsigned long sectorSize = card->m_CardInfo.SectorSize;
            unsigned long remainder = headerSize % sectorSize;
            if (remainder != 0)
            {
                nlPrintf("MC: Header size (%d) not aligned to sector (%d), rounding to %d\n", headerSize, sectorSize, headerSize + sectorSize - remainder);
                headerSize += card->m_CardInfo.SectorSize - remainder;
            }
            card->m_State = IS_WRITING;
            card->m_CardState = CS_WRITING;
            err = CARDWriteAsync(&file->FileInfo, data, headerSize, 0, WriteFileDoneCB);
            if (err != 0)
            {
                card->m_State = IS_MOUNTED;
                card->m_CardState = CS_MOUNTED;
            }
        }
        if (err != 0)
        {
            card->m_State = IS_MOUNTED;
            card->m_CardState = CS_MOUNTED;
        }
    }
    if (result != 0)
    {
        MemCardFunctor::MCInternalFunctorBase* pFunctor = (MemCardFunctor::MCInternalFunctorBase*)&card->m_CB[8];
        unsigned long slot = card->m_Slot;
        if (*(long*)pFunctor != 0)
        {
            pFunctor->Call(slot, result);
        }
        else
        {
            nlPrintf("Trying to call unset MC functor");
        }
    }
}

/**
 * Offset/Address/Size: 0x12C | 0x801CAC6C | size: 0xC4
 */
void MemCard::CardCheckBrokenDoneCB(long channel, long result)
{
    MemCard* card = g_MemCards[channel];
    if (result == 0)
    {
        CARDFreeBlocks(card->m_Slot, &card->m_CardInfo.FreeBytes, &card->m_CardInfo.FreeFiles);
    }
    else
    {
        card->m_State = IS_MOUNTED_ERROR;
        card->m_CardState = CS_MOUNTED_ERROR;
    }
    if (result == 0)
    {
        card->m_State = IS_MOUNTED;
        card->m_CardState = CS_MOUNTED;
    }
    else
    {
        card->m_State = IS_IDLE;
        card->m_CardState = CS_IDLE;
    }
    MemCardFunctor::MCInternalFunctorBase* pFunctor = (MemCardFunctor::MCInternalFunctorBase*)&card->m_CB[1];
    unsigned long slot = card->m_Slot;
    if (*(long*)pFunctor != 0)
    {
        pFunctor->Call(slot, result);
    }
    else
    {
        nlPrintf("Trying to call unset MC functor");
    }
}

/**
 * Offset/Address/Size: 0xA8 | 0x801CABE8 | size: 0x84
 */
void MemCard::CardCheckDoneCB(long channel, long result)
{
    MemCard* card = g_MemCards[channel];
    if (result == 0)
    {
        card->m_State = IS_MOUNTED;
        card->m_CardState = CS_MOUNTED;
    }
    else
    {
        card->m_State = IS_IDLE;
        card->m_CardState = CS_IDLE;
    }
    MemCardFunctor::MCInternalFunctorBase* pFunctor = (MemCardFunctor::MCInternalFunctorBase*)&card->m_CB[1];
    unsigned long slot = card->m_Slot;
    if (*(long*)pFunctor != 0)
    {
        pFunctor->Call(slot, result);
    }
    else
    {
        nlPrintf("Trying to call unset MC functor");
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x801CAB40 | size: 0xA8
 */
void MemCard::WriteFileDoneCB(long channel, long result)
{
    MemCard* card = g_MemCards[channel];
    card->m_State = IS_MOUNTED;
    card->m_CardState = CS_MOUNTED;
    if (CARDProbeEx(card->m_Slot, &card->m_CardInfo.CardSize, &card->m_CardInfo.SectorSize) != 0)
    {
        card->m_State = IS_IDLE;
        card->m_CardState = CS_IDLE;
    }
    MemCardFunctor::MCInternalFunctorBase* pFunctor = (MemCardFunctor::MCInternalFunctorBase*)&card->m_CB[8];
    unsigned long slot = card->m_Slot;
    if (*(long*)pFunctor != 0)
    {
        pFunctor->Call(slot, result);
    }
    else
    {
        nlPrintf("Trying to call unset MC functor");
    }
}

/**
 * Offset/Address/Size: 0x12DC | 0x801CAA4C | size: 0xF4
 */
s32 MemCard::BeginCardAccess(const MemCardFunctor&)
{
}

/**
 * Offset/Address/Size: 0xF28 | 0x801CA698 | size: 0x3B4
 */
void MemCard::CreateFile(const char*, unsigned long, MemCard::ICON_CONFIG*, MemCard::MC_FILE*&, const MemCardFunctor&)
{
}

/**
 * Offset/Address/Size: 0xBE8 | 0x801CA358 | size: 0x340
 */
void MemCard::OpenFile(const char*, MemCard::MC_FILE*&, unsigned long*)
{
}

/**
 * Offset/Address/Size: 0xB28 | 0x801CA298 | size: 0xC0
 */
void MemCard::FormatCard(const MemCardFunctor&)
{
}

/**
 * Offset/Address/Size: 0x930 | 0x801CA0A0 | size: 0x1F8
 */
void MemCard::DeleteFile(const char*, const MemCardFunctor&)
{
}

/**
 * Offset/Address/Size: 0x860 | 0x801C9FD0 | size: 0xD0
 */
void MemCard::InternalReadFile(MemCard::MC_FILE*, void*, unsigned long, unsigned long, const MemCardFunctor&)
{
}

/**
 * Offset/Address/Size: 0x740 | 0x801C9EB0 | size: 0x120
 */
void MemCard::InternalWriteFile(MemCard::MC_FILE*, void*, unsigned long, unsigned long, const MemCardFunctor&, bool)
{
}

/**
 * Offset/Address/Size: 0x620 | 0x801C9D90 | size: 0x120
 */
void MemCard::CloseFile(MemCard::MC_FILE*)
{
}

/**
 * Offset/Address/Size: 0x5DC | 0x801C9D4C | size: 0x44
 */
s32 MemCard::FileExists(const char* fileName)
{
    CARDFileInfo fileInfo;
    s32 result = CARDOpen(m_Slot, fileName, &fileInfo);
    if (result == 0)
    {
        CARDClose(&fileInfo);
    }
    return result;
}

/**
 * Offset/Address/Size: 0x204 | 0x801C9974 | size: 0x3D8
 */
void MemCard::WriteFileIconData(MemCard::MC_FILE*, void*, const MemCardFunctor&)
{
}

/**
 * Offset/Address/Size: 0x24 | 0x801C9794 | size: 0x1E0
 */
void MemCard::ICON_CONFIG::GetValidDataInfo(MemCard::ICON_DATA_INFO&) const
{
}

/**
 * Offset/Address/Size: 0x10 | 0x801C9780 | size: 0x14
 */
unsigned long MemCard::AlignBytesToSectorSize(unsigned long bytes)
{
    unsigned long sectorSize = m_CardInfo.SectorSize;
    unsigned long mask = sectorSize - 1;
    return (bytes + mask) & ~mask;
}

/**
 * Offset/Address/Size: 0x0 | 0x801C9770 | size: 0x10
 */
s64 MemCard::GetSerialID() const
{
    return m_SerialID;
}

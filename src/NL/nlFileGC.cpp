#include "NL/nlFileGC.h"
#include "NL/nlFile.h"
#include "NL/nlMemory.h"
#include "FILE_POS.h"
#include "direct_io.h"
#include "types.h"
#include <string.h>

static AsyncManager* s_pAsyncManager;
static GCFileSystem fileSystem;

namespace nlFileGC
{
AsyncToVirMemBufferLoad asyncToVirMemBufferLoad[4];
u8 asyncToVirMemBuffer[0x4000];
} // namespace nlFileGC

/**
 * Offset/Address/Size: 0x0 | 0x801CED54 | size: 0xEC
 * TODO: 98.6% in scratch - register swap r25/r26/r27 for counter1/counter2/chunkSize.
 * Scratch limitation: nlReadAsync gets inlined from context (defined later in TU).
 * In real build nlReadAsync should NOT inline, likely resolving register allocation.
 */
void nlReadAsyncToVirtualMemory(nlFile* file, void* buffer, int size, ReadAsyncCallback callback, unsigned long param,
    unsigned long chunkSize, void* userData)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if (nlFileGC::asyncToVirMemBufferLoad[i].numChunksLeft == 0)
        {
            unsigned int numChunks = (unsigned int)size / (unsigned int)chunkSize;
            unsigned long counter2 = i;
            unsigned long counter1 = i;
            unsigned int sz = chunkSize;
            nlFileGC::asyncToVirMemBufferLoad[i].numChunksLeft = numChunks + 1;
            nlFileGC::asyncToVirMemBufferLoad[i].param = param;
            nlFileGC::asyncToVirMemBufferLoad[i].callback = callback;
            nlFileGC::asyncToVirMemBufferLoad[i].size = size;
            int remainder = size - numChunks * chunkSize;
            nlFileGC::asyncToVirMemBufferLoad[i].target = (char*)buffer;

            int j;
            for (j = 0; j < (int)numChunks; j++)
            {
                nlReadAsync(file, userData, sz, nlFileGC::AsyncToVirMemBufferCallback, counter1);
            }

            nlReadAsync(file, userData, remainder, nlFileGC::AsyncToVirMemBufferCallback, counter2);
            return;
        }
    }
}

/**
 * Offset/Address/Size: 0xEC | 0x801CEE40 | size: 0x38
 */
void nlAsyncLoadFileToVirtualMemory(nlFile* file, int size, void* buffer, ReadAsyncCallback callback, unsigned long alignment)
{
    nlReadAsyncToVirtualMemory(file, buffer, size, callback, alignment, 0x4000, nlFileGC::asyncToVirMemBuffer);
}

namespace nlFileGC
{
/**
 * Offset/Address/Size: 0x124 | 0x801CEE78 | size: 0xAC
 */
void AsyncToVirMemBufferCallback(nlFile*, void*, unsigned int, unsigned long)
{
}
} // namespace nlFileGC

/**
 * Offset/Address/Size: 0x1D0 | 0x801CEF24 | size: 0xF4
 */
// nlCancelPendingAsyncReads(nlFile*, void (*)(nlFile*, void*, unsigned int, unsigned long, LoadAsyncCallback))
void nlCancelPendingAsyncReads(nlFile*)
{
}

/**
 * Offset/Address/Size: 0x2C4 | 0x801CF018 | size: 0x34
 */
bool nlAsyncReadsPending(nlFile* file)
{
    if (file != NULL)
    {
        return ((GCFile*)file)->PendingAsync.m_Count != 0;
    }
    return s_pAsyncManager->m_activeEntryList != nullptr;
}

/**
 * Offset/Address/Size: 0x2F8 | 0x801CF04C | size: 0x2D0
 */
void* nlLoadEntireFileToVirtualMemory(const char*, int*, unsigned int, void*, eAllocType)
{
    return NULL;
}

/**
 * Offset/Address/Size: 0x5C8 | 0x801CF31C | size: 0x9C
 */
void* nlReadToVirtualMemory(nlFile* file, void* buffer, unsigned int size, unsigned int chunkSize)
{
    unsigned int readSize;
    void* tempBuffer;
    unsigned int offset;

    tempBuffer = nlMalloc(chunkSize, 0x20, false);
    offset = 0;

    while (offset < size)
    {
        readSize = chunkSize;
        if (size - offset <= chunkSize)
        {
            readSize = size - offset;
        }
        nlRead(file, tempBuffer, readSize);
        memcpy((u8*)buffer + offset, tempBuffer, readSize);
        offset += readSize;
    }

    nlFree(tempBuffer);
    return buffer;
}

/**
 * Offset/Address/Size: 0x664 | 0x801CF3B8 | size: 0x8
 */
u32 nlGetFilePosition(nlFile* file)
{
    return ((GCFile*)file)->m_Position;
}

/**
 * Offset/Address/Size: 0x66C | 0x801CF3C0 | size: 0x8C
 */
void nlSeek(nlFile* file, unsigned int offset, unsigned long origin)
{
    GCFile* gcFile = (GCFile*)file;
    switch (origin)
    { /* irregular */
    case 0:
        gcFile->m_Position = offset;
        return;
    case 1:
        gcFile->m_Position = (s32)(gcFile->m_Position + offset);
        return;
    case 2:
        gcFile->m_Position = (s32)(gcFile->FileSize(NULL) - offset);
        return;
    }
}

/**
 * Offset/Address/Size: 0x6F8 | 0x801CF44C | size: 0x34
 */
void nlReadAsync(nlFile* file, void* buffer, unsigned int size, ReadAsyncCallback callback, unsigned long arg4)
{
    FORCE_DONT_INLINE;
    GameCubeReadAsync((GCFile*)file, callback, buffer, (u32)size, arg4);
}

/**
 * Offset/Address/Size: 0x72C | 0x801CF480 | size: 0x27C
 */
void nlServiceFileSystem()
{
}

/**
 * Offset/Address/Size: 0x9A8 | 0x801CF6FC | size: 0x35C
 */
void nlInitFileSystem()
{
}

/**
 * Offset/Address/Size: 0xD04 | 0x801CFA58 | size: 0x2E0
 */
void GameCubeReadBlocking(GCFile*, void*, unsigned long)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0xFE4 | 0x801CFD38 | size: 0x324
 */
static void GameCubeReadAsync(GCFile*, ReadAsyncCallback, void*, unsigned long, unsigned long)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x1308 | 0x801D005C | size: 0x6E0
 */
void UpdateReadState(AsyncEntry*)
{
}

/**
 * Offset/Address/Size: 0x19E8 | 0x801D073C | size: 0x4
 */
void nlFlushFileCash()
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0x19EC | 0x801D0740 | size: 0x18C
 * TODO: 96.5% match - r29/r31 register mismatch for result/file values, plus
 * extra mr r0,r3 shuttles in ftell/return paths and a shifted branch layout.
 */
nlFile* nlOpen(const char* fileName)
{
    s32 entryNum;
    _FILE* fp;
    nlFile* file;

    if (fileSystem == eGC_TDEV)
    {
        nlFile* result;

        fp = fopen(fileName, "rb");
        if (fp == NULL)
        {
            result = NULL;
        }
        else
        {
            result = (nlFile*)ftell(fp);
            fseek(fp, 0, 2);
            unsigned long size = ftell(fp);
            fseek(fp, (unsigned long)result, 0);

            if (size == 0xFFFFFFFF)
            {
                result = NULL;
            }
            else
            {
                result = new TDEVChunkFile(fp);
                while (fp == NULL)
                {
                }
            }
        }

        file = result;
    }
    else
    {
        nlFile* result;

        entryNum = DVDConvertPathToEntrynum(fileName);
        if (entryNum == -1)
        {
            result = NULL;
        }
        else
        {
            result = new DolphinFile(entryNum);
            while (result == NULL)
            {
            }
        }

        file = result;
    }

    return file;
}

/**
 * Offset/Address/Size: 0x1B78 | 0x801D08CC | size: 0xB0
 * TODO: 93.8% match - register allocation still differs in fread setup
 *   (amountRead/length/remainingBytes in r3/r6 vs target r7/r3/r6), plus
 *   post-fread compare/flag path keeps currentAmount/isComplete in r0/r4
 *   instead of target r4/r0; final shift emits rlwinm instead of srwi.
 */
s32 TDEVChunkFile::GetReadStatus()
{
    fseek(m_pFile, m_CurrentRead.Pos + m_CurrentRead.AmountRead, 0);

    u32 length = m_CurrentRead.Length;
    u32 amountRead = m_CurrentRead.AmountRead;
    u32 remainingBytes = length;
    remainingBytes -= amountRead;
    u8* dest = m_CurrentRead.Buffer + amountRead;

    u32 bytesRead = fread(dest, 1, (remainingBytes <= 0x3000U) ? remainingBytes : 0x3000U, m_pFile);
    u32 nextAmount = m_CurrentRead.AmountRead + bytesRead;
    m_CurrentRead.AmountRead = nextAmount;
    bool isComplete = false;
    u32 currentAmount = m_CurrentRead.AmountRead;
    u32 currentLength = m_CurrentRead.Length;

    if ((currentAmount == currentLength) || ((currentLength == 0x20U) && (currentAmount != 0U)))
    {
        isComplete = true;
    }
    return !isComplete;
}

/**
 * Offset/Address/Size: 0x1C28 | 0x801D097C | size: 0x40
 */
void TDEVChunkFile::ReadAsync(void* buffer, unsigned long length, unsigned long offset)
{
    m_CurrentRead.Buffer = (u8*)buffer;
    m_CurrentRead.Pos = offset;
    m_CurrentRead.Length = length;
    m_CurrentRead.AmountRead = 0;
    GetReadStatus();
}

/**
 * Offset/Address/Size: 0x1C68 | 0x801D09BC | size: 0x20
 */
void GCFile::Read(void* buffer, unsigned int size)
{
    GameCubeReadBlocking(this, buffer, size);
}

namespace nlFileGC
{
/**
 * Offset/Address/Size: 0x1E74 | 0x801D0BC8 | size: 0xC
 */
void AsyncToVirMemBufferLoad()
{
}
} // namespace nlFileGC

/**
 * Offset/Address/Size: 0x0 | 0x801D0BD4 | size: 0x90
 */
TDEVChunkFile::~TDEVChunkFile()
{
    fclose(m_pFile);
    m_pFile = NULL;
}

/**
 * Offset/Address/Size: 0x90 | 0x801D0C64 | size: 0x8C
 */
static inline unsigned int FileSize_helper(_FILE* pFile)
{
    unsigned long uPos = ftell(pFile);
    fseek(pFile, 0, 2);
    unsigned long uSize = ftell(pFile);
    fseek(pFile, uPos, 0);
    return uSize;
}

u32 TDEVChunkFile::FileSize(unsigned int* pSize)
{
    unsigned long Size = FileSize_helper(m_pFile);
    if (pSize != NULL)
    {
        *pSize = Size;
    }
    return Size;
}

/**
 * Offset/Address/Size: 0x11C | 0x801D0CF0 | size: 0x8
 */
u32 TDEVChunkFile::GetDiscPosition()
{
    return 0;
}

/**
 * Offset/Address/Size: 0x124 | 0x801D0CF8 | size: 0x60
 */
GCFile::~GCFile()
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0x184 | 0x801D0D58 | size: 0x88
 */
DolphinFile::~DolphinFile()
{
    DVDClose(&m_fileInfo);
}

/**
 * Offset/Address/Size: 0x20C | 0x801D0DE0 | size: 0x14
 */
u32 DolphinFile::FileSize(unsigned int* size)
{
    u32 s = m_fileInfo.length;
    if (size != NULL)
    {
        *size = s;
    }
    return s;
}

/**
 * Offset/Address/Size: 0x220 | 0x801D0DF4 | size: 0x24
 */
s32 DolphinFile::GetReadStatus()
{
    return DVDGetCommandBlockStatus(&m_fileInfo.cb);
}

/**
 * Offset/Address/Size: 0x244 | 0x801D0E18 | size: 0x2C
 */
void DolphinFile::ReadAsync(void* addr, unsigned long length, unsigned long offset)
{
    DVDReadAsyncPrio(&m_fileInfo, addr, (s32)length, (s32)offset, 0, 2);
}

/**
 * Offset/Address/Size: 0x270 | 0x801D0E44 | size: 0x8
 */
u32 DolphinFile::GetDiscPosition()
{
    return m_fileInfo.startAddr; // 0x3c
}

/**
 * Offset/Address/Size: 0x0 | 0x801D0E4C | size: 0x38
 */
// nlDLRingRemoveStart<AsyncEntry>(AsyncEntry**)
// {
// }

/**
 * Offset/Address/Size: 0x38 | 0x801D0E84 | size: 0x18
 */
// nlDLRingGetStart<AsyncEntry>(AsyncEntry*)
// {
// }

/**
 * Offset/Address/Size: 0x50 | 0x801D0E9C | size: 0x44
 */
// nlDLRingRemove<AsyncEntry>(AsyncEntry**, AsyncEntry*)
// {
// }

/**
 * Offset/Address/Size: 0x94 | 0x801D0EE0 | size: 0x3C
 */
// nlDLRingAddEnd<AsyncEntry>(AsyncEntry**, AsyncEntry*)
// {
// }

/**
 * Offset/Address/Size: 0xD0 | 0x801D0F1C | size: 0x38
 */
// nlDLRingAddStart<AsyncEntry>(AsyncEntry**, AsyncEntry*)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x801D0F54 | size: 0x20
 */
// nlRingIsEnd<AsyncEntry>(AsyncEntry*, AsyncEntry*)
// {
// }

/**
 * Offset/Address/Size: 0x20 | 0x801D0F74 | size: 0xCC
 */
// 0x8028D538..0x8028D53C | size: 0x4
// {
// }

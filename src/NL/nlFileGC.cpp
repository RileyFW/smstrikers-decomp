#include "NL/nlFileGC.h"
#include "NL/nlFile.h"
#include "NL/nlMemory.h"
#include "FILE_POS.h"
#include "direct_io.h"
#include "types.h"
#include <string.h>

static AsyncManager* s_pAsyncManager;

namespace nlFileGC
{
AsyncToVirMemBufferLoad asyncToVirMemBufferLoad[4];
u8 asyncToVirMemBuffer[0x4000];
} // namespace nlFileGC

/**
 * Offset/Address/Size: 0x0 | 0x801CED54 | size: 0xEC
 */
void nlReadAsyncToVirtualMemory(nlFile* file, void* buffer, int size, ReadAsyncCallback callback, unsigned long alignment,
    unsigned long length, void* userData)
{
    FORCE_DONT_INLINE;
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
 */
nlFile* nlOpen(const char*)
{
    return NULL;
}

/**
 * Offset/Address/Size: 0x1B78 | 0x801D08CC | size: 0xB0
 * TODO: 88.9% match - register allocation differs (r4/r7 swap for amountRead, r0/r4 swap)
 */
s32 TDEVChunkFile::GetReadStatus()
{
    fseek(m_pFile, m_CurrentRead.Pos + m_CurrentRead.AmountRead, 0);

    u32 amountRead = m_CurrentRead.AmountRead;
    u32 length = m_CurrentRead.Length;
    u32 readSize = 0x3000U;
    u8* buffer = m_CurrentRead.Buffer;
    u32 remainingBytes = length - amountRead;
    u8* dest = buffer + amountRead;
    if (remainingBytes <= 0x3000U)
    {
        readSize = remainingBytes;
    }

    u32 bytesRead = fread(dest, 1, readSize, m_pFile);
    u8 isComplete = 0;
    m_CurrentRead.AmountRead = m_CurrentRead.AmountRead + bytesRead;

    if ((m_CurrentRead.AmountRead == m_CurrentRead.Length) || ((m_CurrentRead.Length == 0x20U) && (m_CurrentRead.AmountRead != 0U)))
    {
        isComplete = 1;
    }
    return isComplete == 0;
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
 * TODO: 84.4% match - uses 3 registers (r29-r31) instead of 4 (r28-r31)
 */
u32 TDEVChunkFile::FileSize(unsigned int* pSize)
{
    _FILE* file = m_pFile;
    u32 currentPosition = ftell(file);
    fseek(file, 0, 2);
    u32 fileSize = ftell(file);
    fseek(file, currentPosition, 0);
    if (pSize != NULL)
    {
        *pSize = fileSize;
    }
    return fileSize;
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

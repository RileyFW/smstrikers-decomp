#include "NL/nlFileGC.h"
#include "FILE_POS.h"
#include "direct_io.h"

namespace nlFileGC
{
u8 asyncToVirMemBuffer[0x4000];
}

/**
 * Offset/Address/Size: 0x0 | 0x801CED54 | size: 0xEC
 */
void nlReadAsyncToVirtualMemory(nlFile* file, void* buffer, int size, ReadAsyncCallback callback, unsigned long alignment,
    unsigned long length, void* userData)
{
    s32 var_r11 = 0;
    nlReadAsync(file, buffer, size, &nlFileGC::AsyncToVirMemBufferCallback, var_r11);

    //     s32 *var_r10;
    //     s32 temp_r10;
    //     s32 var_ctr;
    //     s32 var_r11;
    //     s32 var_r23;
    //     u32 temp_r28;
    //     void *temp_r3;

    //     var_r11 = 0;
    //     var_r10 = &asyncToVirMemBufferLoad__22@unnamed@nlFileGC_cpp@;
    //     var_ctr = 4;
    // loop_1:
    //     if ((s32) *var_r10 == 0) {
    //         temp_r28 = arg2 / arg5;
    //         temp_r10 = var_r11 * 0x14;
    //         *(&asyncToVirMemBufferLoad__22@unnamed@nlFileGC_cpp@ + temp_r10) = temp_r28 + 1;
    //         temp_r3 = &asyncToVirMemBufferLoad__22@unnamed@nlFileGC_cpp@ + temp_r10;
    //         var_r23 = 0;
    //         temp_r3->unk4 = arg4;
    //         temp_r3->unk8 = arg3;
    //         temp_r3->unk10 = arg2;
    //         temp_r3->unkC = arg1;
    // loop_4:
    //         if (var_r23 < (s32) temp_r28) {
    //             nlReadAsync(arg0, arg6, arg5, &AsyncToVirMemBufferCallback__22@unnamed@nlFileGC_cpp@FP6nlFilePvUiUl, var_r11);
    //             var_r23 += 1;
    //             goto loop_4;
    //         }
    //         nlReadAsync(arg0, arg6, arg2 % arg5, &AsyncToVirMemBufferCallback__22@unnamed@nlFileGC_cpp@FP6nlFilePvUiUl, var_r11);
    //         return;
    //     }
    //     var_r10 += 0x14;
    //     var_r11 += 1;
    //     var_ctr -= 1;
    //     if (var_ctr == 0) {nin
    //         return;
    //     }
    //     goto loop_1;
}

/**
 * Offset/Address/Size: 0xEC | 0x801CEE40 | size: 0x38
 */
void nlAsyncLoadFileToVirtualMemory(nlFile* param_1, int param_2, void* param_3, ReadAsyncCallback param_4, unsigned long param_5)
{
    nlReadAsyncToVirtualMemory((GCFile*)param_1, param_3, param_2, param_4, param_5, 0x4000, &nlFileGC::asyncToVirMemBuffer);
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
bool nlAsyncReadsPending(nlFile*)
{
    return false;
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
void nlReadToVirtualMemory(nlFile*, void*, unsigned int, unsigned int)
{
}

/**
 * Offset/Address/Size: 0x664 | 0x801CF3B8 | size: 0x8
 */
u32 nlGetFilePosition(nlFile* file)
{
    return file->m_unk_0x08;
}

/**
 * Offset/Address/Size: 0x66C | 0x801CF3C0 | size: 0x8C
 */
void nlSeek(nlFile* file, unsigned int offset, unsigned long origin)
{
    switch (origin)
    { /* irregular */
    case 0:
        file->m_unk_0x08 = offset;
        return;
    case 1:
        file->m_unk_0x08 = (s32)(file->m_unk_0x08 + offset);
        return;
    case 2:
        file->m_unk_0x08 = (s32)(file->FileSize(NULL) - offset);
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
 */
BOOL TDEVChunkFile::GetReadStatus()
{
    s8 isComplete;
    u32 remainingBytes;
    u32 readSize;

    fseek(m_file, m_readOffset + m_bytesRead, 0);
    readSize = 0x3000U; // Default chunk size (12KB)
    remainingBytes = m_readLength - m_bytesRead;
    if (remainingBytes <= 0x3000U)
    {
        readSize = remainingBytes;
    }
    isComplete = 0;
    m_bytesRead = (u32)(m_bytesRead + fread((void*)((u8*)m_buffer + m_bytesRead), 1, readSize, m_file));
    if ((m_bytesRead == m_readLength) || ((m_readLength == 0x20U) && (m_bytesRead != 0U)))
    {
        isComplete = 1;
    }
    return isComplete == 0;
}

/**
 * Offset/Address/Size: 0x1C28 | 0x801D097C | size: 0x40
 */
BOOL TDEVChunkFile::ReadAsync(void* buffer, unsigned long length, unsigned long offset)
{
    m_buffer = buffer;
    m_readOffset = offset;
    m_readLength = length;
    m_bytesRead = 0;
    return GetReadStatus();
}

/**
 * Offset/Address/Size: 0x1C68 | 0x801D09BC | size: 0x20
 */
void GCFile::Read(void* buffer, unsigned int size)
{
    GameCubeReadBlocking(NULL, buffer, size);
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
    fclose(m_file);
    m_file = NULL;
}

/**
 * Offset/Address/Size: 0x90 | 0x801D0C64 | size: 0x8C
 */
u32 TDEVChunkFile::FileSize(unsigned int* size)
{
    u32 currentPosition;
    u32 fileSize;

    currentPosition = ftell(m_file);
    fseek(m_file, 0, 2);
    fileSize = ftell(m_file);
    fseek(m_file, currentPosition, 0);
    if (size != NULL)
    {
        *size = fileSize;
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
BOOL DolphinFile::GetReadStatus()
{
    return DVDGetCommandBlockStatus(&m_fileInfo.cb);
}

/**
 * Offset/Address/Size: 0x244 | 0x801D0E18 | size: 0x2C
 */
BOOL DolphinFile::ReadAsync(void* addr, unsigned long length, unsigned long offset)
{
    return DVDReadAsyncPrio(&m_fileInfo, addr, (s32)length, (s32)offset, 0, 2);
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

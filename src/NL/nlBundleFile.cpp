#include "NL/nlBundleFile.h"
#include "NL/nlMemory.h"
#include "NL/nlString.h"
#include <string.h>

inline u32 GetNormalizedFilenameHash(const char* filename)
{
    char tmp[252];
    char* puVar8 = tmp;
    u32 i = 0;
    char* pcVar10 = (char*)filename;
    for (; i < nlStrLen<char>(filename); puVar8++, pcVar10++, i++)
    {
        *puVar8 = nlToLower<char>(*pcVar10);
        if (*pcVar10 == '\\')
        {
            *puVar8 = 0x2f;
        }
    }
    tmp[i] = 0;
    return nlStringHash((char*)&tmp[0]);
}

/**
 * Offset/Address/Size: 0x0 | 0x801E85CC | size: 0xD4
 */
void BundleFile::ReadFileAsync(unsigned long hash, void* buffer, unsigned long size, FileReadAsyncCallback callback, unsigned long arg5)
{
    u32 index = FindHashIndex(hash);
    m_readAsyncCallback = callback;
    m_unk_0x10 = arg5;
    BundleFileDirectoryEntry* entry = &m_bundleEntries[index];
    nlSeek(m_file, entry->m_blockNumber * m_bundleHeader->m_blockSize, 0);
    nlReadAsync(m_file, buffer, size, &cbFileReadAsyncCallback, (unsigned long)this);
}

/**
 * Offset/Address/Size: 0xD4 | 0x801E86A0 | size: 0x138
 */
void BundleFile::ReadFileAsync(const char* filename, void* buffer, unsigned long size, FileReadAsyncCallback callback, unsigned long arg5)
{
    u32 index = FindHashIndex(GetNormalizedFilenameHash(filename));
    m_readAsyncCallback = callback;
    m_unk_0x10 = arg5;
    BundleFileDirectoryEntry* entry = &m_bundleEntries[index];
    nlSeek(m_file, entry->m_blockNumber * m_bundleHeader->m_blockSize, 0);
    nlReadAsync(this->m_file, buffer, size, &cbFileReadAsyncCallback, *(unsigned long*)this);
}

/**
 * Offset/Address/Size: 0x20C | 0x801E87D8 | size: 0x118
 */
void BundleFile::LoadFile(const char* filename, void* buffer)
{
    u32 index = FindHashIndex(GetNormalizedFilenameHash(filename));
    BundleFileDirectoryEntry* entry = &m_bundleEntries[index];
    nlSeek(m_file, entry->m_blockNumber * m_bundleHeader->m_blockSize, 0);
    nlRead(m_file, buffer, entry->m_length);
}

/**
 * Offset/Address/Size: 0x324 | 0x801E88F0 | size: 0x74
 */
void BundleFile::ReadFileByIndex(unsigned long index, void* buffer, unsigned long size)
{
    BundleFileDirectoryEntry* entry = &m_bundleEntries[index];
    nlSeek(m_file, entry->m_blockNumber * m_bundleHeader->m_blockSize, 0);
    nlRead(m_file, buffer, entry->m_length);
}

/**
 * Offset/Address/Size: 0x398 | 0x801E8964 | size: 0xC4
 */
void BundleFile::ReadFile(unsigned long hash, void* buffer, unsigned long arg3)
{
    u32 index = FindHashIndex(hash);
    BundleFileDirectoryEntry* entry = &m_bundleEntries[index];
    nlSeek(m_file, entry->m_blockNumber * m_bundleHeader->m_blockSize, 0);
    nlRead(m_file, buffer, entry->m_length);
}

/**
 * Offset/Address/Size: 0x45C | 0x801E8A28 | size: 0x118
 */
void BundleFile::ReadFile(const char* filename, void* buffer, unsigned long)
{
    u32 index = FindHashIndex(GetNormalizedFilenameHash(filename));
    BundleFileDirectoryEntry* entry = &m_bundleEntries[index];
    nlSeek(m_file, entry->m_blockNumber * m_bundleHeader->m_blockSize, 0);
    nlRead(m_file, buffer, entry->m_length);
}

/**
 * Offset/Address/Size: 0x574 | 0x801E8B40 | size: 0x50
 */
bool BundleFile::GetFileInfoByIndex(unsigned long index, BundleFileDirectoryEntry* entry)
{
    if (index < (u32)m_bundleHeader->m_entryCount)
    {
        memcpy((void*)entry, (void*)&m_bundleEntries[index], 0xC);
        return 1;
    }
    return 0;
}

/**
 * Offset/Address/Size: 0x5C4 | 0x801E8B90 | size: 0xE8
 */
bool BundleFile::GetFileInfo(unsigned long hash, BundleFileDirectoryEntry* entry, bool printError)
{
    u32 index = FindHashIndex(hash, printError);

    if ((index == -1U) && (printError == 0))
    {
        return 0;
    }

    if (index < (u32)m_bundleHeader->m_entryCount)
    {
        memcpy((void*)entry, &m_bundleEntries[index], 0xC);
        return 1;
    }

    return 0;
}

/**
 * Offset/Address/Size: 0x6AC | 0x801E8C78 | size: 0x13C
 */
bool BundleFile::GetFileInfo(const char* filename, BundleFileDirectoryEntry* entry, bool printError)
{
    u32 index = FindHashIndex(GetNormalizedFilenameHash(filename), printError);

    if ((index == -1U) && (printError == 0))
    {
        return 0;
    }

    if (index < (u32)m_bundleHeader->m_entryCount)
    {
        memcpy((void*)entry, &m_bundleEntries[index], 0xC);
        return 1;
    }

    return 0;
}

/**
 * Offset/Address/Size: 0x7E8 | 0x801E8DB4 | size: 0x58
 */
void BundleFile::Close()
{
    if ((u32)m_file != NULL)
    {
        nlClose(m_file);
        m_file = NULL;
    }

    if ((u32)m_bundleEntries != NULL)
    {
        delete[] m_bundleEntries;
        m_bundleEntries = NULL;
    }
}

/**
 * Offset/Address/Size: 0x840 | 0x801E8E0C | size: 0xA8
 */
bool BundleFile::Open(const char* filename)
{
    m_file = nlOpen(filename);
    if ((void*)m_file == NULL)
    {
        return 0;
    }
    nlRead(m_file, m_bundleHeader, 0x10);
    nlSeek(m_file, m_bundleHeader->m_unk_0x08 * m_bundleHeader->m_blockSize, 0);
    m_bundleEntries = (BundleFileDirectoryEntry*)nlMalloc(m_bundleHeader->m_entryCount * 0xC, 0x20, 0);
    nlRead(m_file, m_bundleEntries, m_bundleHeader->m_entryCount * 0xC);
    return 1;
}

/**
 * Offset/Address/Size: 0x8E8 | 0x801E8EB4 | size: 0x8C
 */
BundleFile::~BundleFile()
{
    if (m_file != NULL)
    {
        nlClose(m_file);
        m_file = NULL;
    }

    if (m_bundleEntries != 0U)
    {
        delete[] m_bundleEntries;
        m_bundleEntries = NULL;
    }

    delete m_bundleHeader;
    m_bundleHeader = NULL;
}

/**
 * Offset/Address/Size: 0x974 | 0x801E8F40 | size: 0x70
 */
BundleFile::BundleFile()
{
    m_file = 0;
    m_unk_0x04 = 0;
    m_unk_0x08 = 0;
    m_readAsyncCallback = NULL;
    m_unk_0x10 = 0;
    m_bundleHeader = 0;
    m_bundleEntries = 0;
    m_bundleHeader = (BundleFileDirectoryHeader*)nlMalloc(0x10, 0x20, 0);
    memset(m_bundleHeader, 0, 0x10);
}

/**
 * Offset/Address/Size: 0x9E4 | 0x801E8FB0 | size: 0x50
 */
static void cbFileReadAsyncCallback(nlFile*, void* buffer, unsigned int arg, unsigned long bundlePtr)
{
    BundleFile* bundleFile = (BundleFile*)bundlePtr;
    bundleFile->m_readAsyncCallback(buffer, arg, bundleFile->m_unk_0x10);
    bundleFile->m_readAsyncCallback = NULL;
    bundleFile->m_unk_0x10 = 0;
}

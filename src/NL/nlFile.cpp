#include "NL/nlFile.h"
#include "NL/nlFileGC.h"
#include "NL/nlMemory.h"

typedef struct
{
    nlFile* file;               // unk0
    void* alloc_data;           // unk4
    unsigned long datasize;     // unk8
    LoadAsyncCallback callback; // unkC
    void* user_data;            // unk10
} AsyncFileLoadData;

/**
 * Offset/Address/Size: 0x0 | 0x801CEA30 | size: 0xF8
 */
bool nlLoadEntireFileAsync(const char* filename, LoadAsyncCallback callback, void* user_data, unsigned int alignment, eAllocType type)
{
    unsigned int filesize;
    unsigned long datasize;
    nlFile* file;
    AsyncFileLoadData* _asyncData;
    void* alloc_data;

    file = nlOpen(filename);
    if (file == NULL)
    {
        return 0;
    }
    datasize = file->FileSize(&filesize);
    if (datasize != 0)
    {
        if (type == 1)
        {
            alloc_data = nlMalloc(filesize, alignment, 1);
        }
        else if (type == 0)
        {
            alloc_data = nlMalloc(filesize, alignment, 0);
        }
        else
        {
            alloc_data = user_data;
            user_data = NULL;
        }

        _asyncData = (AsyncFileLoadData*)nlMalloc(0x14, 8, 1);
        if (_asyncData != NULL)
        {
            _asyncData->file = file;
            _asyncData->alloc_data = alloc_data;
            _asyncData->datasize = datasize;
            _asyncData->callback = callback;
            _asyncData->user_data = user_data;
        }
        nlReadAsync(file, alloc_data, datasize, nlLoadEntireFileAsyncCallback, *(unsigned long*)_asyncData);
    }
    return 1;
}

/**
 * Offset/Address/Size: 0xF8 | 0x801CEB28 | size: 0x68
 */
void nlLoadEntireFileAsyncCallback(nlFile* file, void* arg2, unsigned int arg3, unsigned long arg4)
{
    void** temp_r3;
    AsyncFileLoadData* asyncData = (AsyncFileLoadData*)arg3;

    asyncData->callback(asyncData->alloc_data, asyncData->datasize, asyncData->user_data);
    // temp_r3 = asyncData->file;

    delete file;

    // if (temp_r3 != NULL) {
    //     (*temp_r3)->unk8(1);
    // }
    // __dl__FPv(arg3);
}

/**
 * Offset/Address/Size: 0x160 | 0x801CEB90 | size: 0xDC
 */
void* nlLoadEntireFile(const char* filename, unsigned long* fileSize, unsigned int alignment, eAllocType type)
{
    void* data = NULL;
    unsigned int filesize;
    nlFile* file = nlOpen(filename);
    if (file != NULL)
    {
        unsigned long datasize = file->FileSize(&filesize);
        if (datasize != 0)
        {
            if (type == 1)
            {
                data = nlMalloc(datasize, alignment, 1);
            }
            else
            {
                data = nlMalloc(datasize, alignment, 0);
            }

            file->Read(data, datasize);
        }

        delete file;

        if (fileSize != NULL)
        {
            *fileSize = datasize;
        }
    }
    return data;
}

/**
 * Offset/Address/Size: 0x23C | 0x801CEC6C | size: 0x38
 */
void nlClose(nlFile* file)
{
    delete file;
}

/**
 * Offset/Address/Size: 0x274 | 0x801CECA4 | size: 0x2C
 */
void nlRead(nlFile* file, void* buffer, unsigned int size)
{
    file->Read(buffer, size);
}

/**
 * Offset/Address/Size: 0x2A0 | 0x801CECD0 | size: 0x2C
 */
void nlFileSize(nlFile* file, unsigned int* size)
{
    file->FileSize(size);
}

/**
 * Offset/Address/Size: 0x2CC | 0x801CECFC | size: 0x48
 */
nlFile::~nlFile()
{
}

/**
 * Offset/Address/Size: 0x314 | 0x801CED44 | size: 0x10
 */
nlFile::nlFile()
{
}

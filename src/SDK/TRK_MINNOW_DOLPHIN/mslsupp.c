#include "PowerPC_EABI_Support/MetroTRK/trk.h"

extern u32 fn_80228F80(u32, u32);

// DSIOResult __read_file(u32 handle, u8* buffer, size_t* count, void* ref_con);
// DSIOResult __write_file(u32 handle, u8* buffer, size_t* count, void* ref_con);
// DSIOResult __close_file(u32 handle, u8* buffer, size_t* count, void* ref_con);
// DSIOResult __access_file(u32 handle, u8* buffer, size_t* count, void* ref_con, MessageCommandID cmd);

int __read_console(__file_handle file, unsigned char* buffer, size_t* count, __idle_proc idle_fn)
// DSIOResult __read_console(u32 handle, u8* buffer, size_t* count, void* ref_con)
{
    size_t countTemp;
    u32 r0;

    if (GetUseSerialIO() == 0)
    {
        return DS_IOError;
    }

    if (GetTRKConnected() == DS_NoError)
    {
        return DS_IOError;
    }

    countTemp = *count;
    r0 = TRKAccessFile(0, file, &countTemp, buffer);
    *count = countTemp;

    switch ((u8)r0)
    {
    case DS_IONoError:
        return DS_IONoError;
    case DS_IOEOF:
        return DS_IOEOF;
    }

    return DS_IOError;
}

int __TRK_write_console(u32 handle, u8* buffer, size_t* count, void* ref_con)
{
    if (GetUseSerialIO() == 0)
    {
        return DS_IOError;
    }
    return __write_file(DS_Stdout, buffer, count, (__idle_proc)ref_con);
}

// DSIOResult __read_file(u32 handle, u8* buffer, size_t* count, void* ref_con)
// {
//     return __access_file(handle, buffer, count, ref_con, DSMSG_ReadFile);
// }

// DSIOResult __write_file(u32 handle, u8* buffer, size_t* count, void* ref_con)
// {
//     return __access_file(handle, buffer, count, ref_con, DSMSG_WriteFile);
// }

// void __open_file(void)
// {
//     // UNUSED FUNCTION
// }

// DSIOResult __close_file(u32 handle, u8* buffer, size_t* count, void* ref_con)
// {
//     u32 r0;

//     if (GetTRKConnected() == DS_NoError)
//     {
//         return DS_IOError;
//     }

//     r0 = TRKCloseFile(DSMSG_CloseFile, handle);

//     switch ((u8)r0)
//     {
//     case DS_IONoError:
//         return DS_IONoError;
//     case DS_IOEOF:
//         return DS_IOEOF;
//     }

//     return DS_IOError;
// }

// void __position_file(void)
// {
//     // UNUSED FUNCTION
// }

// void convertFileMode(void)
// {
//     // UNUSED FUNCTION
// }

// DSIOResult __access_file(u32 handle, u8* buffer, size_t* count, void* ref_con, MessageCommandID cmd)
// {
//     size_t countTemp;
//     u32 r0;

//     if (GetTRKConnected() == DS_NoError)
//     {
//         return DS_IOError;
//     }

//     countTemp = *count;
//     r0 = TRKAccessFile(cmd, handle, &countTemp, buffer);
//     *count = countTemp;

//     switch ((u8)r0)
//     {
//     case DS_IONoError:
//         return DS_IONoError;
//     case DS_IOEOF:
//         return DS_IOEOF;
//     }

//     return DS_IOError;
// }

// void __open_temp_file(void)
// {
//     // UNUSED FUNCTION
// }

int __close_console(__file_handle file)
{
    u32 r0;

    if (GetTRKConnected() == 0)
    {
        return DS_IOError;
    }

    r0 = fn_80228F80(DSMSG_CloseFile, file);

    switch ((u8)r0)
    {
    case DS_IONoError:
        return DS_IONoError;
    case DS_IOEOF:
        return DS_IOEOF;
    }

    return DS_IOError;
}
int __write_console(__file_handle file, unsigned char* buf, size_t* count, __idle_proc idle_fn)
{
    return 0;
}

// int __read_console(__file_handle file, unsigned char* buf, size_t* count, __idle_proc idle_fn)
// {
//     return 0;
// }

int __close_file(__file_handle file)
{
    u32 r0;

    if (GetTRKConnected() == 0)
    {
        return DS_IOError;
    }

    r0 = fn_80228F80(DSMSG_CloseFile, file);

    switch ((u8)r0)
    {
    case DS_IONoError:
        return DS_IONoError;
    case DS_IOEOF:
        return DS_IOEOF;
    }

    return DS_IOError;
}

int __write_file(__file_handle file, unsigned char* buf, size_t* count, __idle_proc idle_fn)
{
    return 0;
}

int __read_file(__file_handle file, unsigned char* buf, size_t* count, __idle_proc idle_fn)
{
    return 0;
}

int __position_file(__file_handle handle, fpos_t* position, int mode, __idle_proc idle_proc)
{
    return 0;
}

#include "types.h"

#include "dolphin/Amc/AmcExi2Stubs.h"

void EXI2_Init(vu8**, AmcEXICallback)
{
}

void EXI2_EnableInterrupts(void)
{
}

int EXI2_Poll(void)
{
    return 0;
}

AmcExiError EXI2_ReadN(void*, u32)
{
    return AMC_EXI_NO_ERROR;
}

AmcExiError EXI2_WriteN(const void*, u32)
{
    return AMC_EXI_NO_ERROR;
}

void EXI2_Reserve(void)
{
}

void EXI2_Unreserve(void)
{
}

BOOL AMC_IsStub(void)
{
    return TRUE;
}

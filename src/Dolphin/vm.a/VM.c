#include <stddef.h>
#include <stdint.h>

#include <dolphin/ar.h>
#include <dolphin/types.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/vm/VM.h>

typedef void (*VMLogStatsCallback)(u32 faultAddr, u32 mainAddr, u32 pageIndex, u32 elapsed, u32 wroteBack);
typedef void (*VMSwapPageInCallback)(u32 virtualAddr);

static u32 g_vmSizeVMMainMemory;
static u32 g_vmBaseVMMainMemory;
static u32 g_vmSizeVMARAM;
static u32 g_vmNumPagesInMRAM;
static VMLogStatsCallback g_cbLogStats;
static u32 g_vmInitialized;

static u32 g_vmBaseVMARAM = 0x4000;

void* OSGetArenaLo(void);
void OSSetArenaLo(void* newLo);
BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
u64 OSGetTime(void);

void VMBASEInit(VMSwapPageInCallback cb);
void VMBASESetPageTableEntry(u32 virtualAddr, u32 physicalAddr, u32 mramPage);
void VMBASEClearPageTableEntry(u32 virtualAddr, u32 mramPage);
u32 VMBASEGetVirtualAddrFromPageInMRAM(u32 mramPage);
BOOL VMBASEIsPageDirty(u32 virtualAddr);

void __VMAllocVirtualToARAMLUT(void);
void __VMAllocARAMToVirtualLUT(void);
void __VMAllocMRAMSwapSpace(void);
void __VMSwapPageIn(u32 faultAddr);
u32 __VMGetPageToReplace(void);
void __VMSetARAMPageAsDirty(u32 virtualPage);
u32 __VMTranslateVMPageToARAMPage(u32 virtualPage);
BOOL __VMIsARAMPageDirty(u32 virtualPage);
BOOL __VMDoesMappingExist(u32 virtualPage);
void __VMMappingErrorAlert(u32 virtualPage);

static u32 __VMReadSwapTimeUnits(void)
{
    u64 t = OSGetTime();
    u32 timerClock = *(volatile u32*)0x800000F8 >> 2;
    u32 divisor = (u32)(((u64)0x431CDE83ULL * timerClock) >> 32) >> 15;

    if (divisor == 0)
    {
        return (u32)t;
    }
    return (u32)(t / divisor);
}

void VMInit(uintptr_t baseAddr, size_t initialCommitSize, uintptr_t limitAddr)
{
    BOOL oldInterrupts;

    if (g_vmInitialized != 0)
    {
        return;
    }

    oldInterrupts = OSDisableInterrupts();
    g_vmInitialized = 1;

    g_vmBaseVMARAM = (u32)initialCommitSize;
    g_vmSizeVMARAM = (u32)limitAddr;
    g_vmSizeVMMainMemory = (u32)baseAddr;
    g_vmNumPagesInMRAM = (u32)baseAddr >> 12;

    VMBASEInit(__VMSwapPageIn);
    __VMAllocVirtualToARAMLUT();
    __VMAllocARAMToVirtualLUT();
    __VMAllocMRAMSwapSpace();

    OSRestoreInterrupts(oldInterrupts);
}

void VMSetLogStatsCallback(VMLogStatsCallback cb)
{
    g_cbLogStats = cb;
}

u32 __VMGetNumPagesInMRAM(void)
{
    return g_vmNumPagesInMRAM;
}

u32 VMGetARAMSize(void)
{
    return g_vmSizeVMARAM;
}

u32 VMGetARAMBase(void)
{
    return g_vmBaseVMARAM;
}

void __VMAllocMRAMSwapSpace(void)
{
    g_vmBaseVMMainMemory = (u32)OSGetArenaLo();
    OSSetArenaLo((void*)(g_vmBaseVMMainMemory + g_vmSizeVMMainMemory));
}

void __VMSwapPageIn(u32 faultAddr)
{
    u32 startTicks;
    u32 endTicks;
    u32 virtualPage;
    u32 pageIndex;
    u32 mainAddr;
    u32 previousVirtualPage;
    BOOL oldInterrupts;
    u16 hadARInterrupt;
    u32 wroteBack = 0;

    startTicks = __VMReadSwapTimeUnits();
    virtualPage = faultAddr & ~0xFFF;

    pageIndex = __VMGetPageToReplace();
    mainAddr = g_vmBaseVMMainMemory + (pageIndex << 12);
    previousVirtualPage = VMBASEGetVirtualAddrFromPageInMRAM(pageIndex);

    oldInterrupts = OSDisableInterrupts();
    while (ARGetDMAStatus() != 0)
    {
    }
    hadARInterrupt = __ARGetInterruptStatus();

    if (previousVirtualPage != 0)
    {
        if (VMBASEIsPageDirty(previousVirtualPage))
        {
            __VMSetARAMPageAsDirty(previousVirtualPage);
            wroteBack = 1;
            DCFlushRange((void*)mainAddr, 0x1000);
            ARStartDMA(ARAM_DIR_MRAM_TO_ARAM, mainAddr, __VMTranslateVMPageToARAMPage(previousVirtualPage), 0x1000);
            while (ARGetDMAStatus() != 0)
            {
            }
        }
        VMBASEClearPageTableEntry(previousVirtualPage, pageIndex);
    }

    if (__VMIsARAMPageDirty(virtualPage))
    {
        ARStartDMA(ARAM_DIR_ARAM_TO_MRAM, mainAddr, __VMTranslateVMPageToARAMPage(virtualPage), 0x1000);
        while (ARGetDMAStatus() != 0)
        {
        }
        DCInvalidateRange((void*)mainAddr, 0x1000);
        ICInvalidateRange((void*)mainAddr, 0x1000);
    }
    else if (!__VMDoesMappingExist(virtualPage))
    {
        __VMMappingErrorAlert(virtualPage);
    }

    if (hadARInterrupt == 0)
    {
        __ARClearInterrupt();
    }

    VMBASESetPageTableEntry(virtualPage, mainAddr, pageIndex);
    OSRestoreInterrupts(oldInterrupts);

    if (g_cbLogStats != NULL)
    {
        endTicks = __VMReadSwapTimeUnits();
        g_cbLogStats(faultAddr, mainAddr, pageIndex, endTicks - startTicks, wroteBack);
    }
}

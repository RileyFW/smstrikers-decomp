#include <string.h>

#include <dolphin/ar.h>
#include <dolphin/types.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSException.h>
#include <dolphin/PPCArch.h>

typedef void (*VMSwapPageInCallback)(u32 virtualAddr);

static u32* g_vmBasePageTable;
static u32* g_vmBaseVMReversePageTable;
static u8* g_vmBaseLockedPageTable;
static VMSwapPageInCallback cbVMSwapPageIn;
static u32 g_baseInitialized;
static u32 g_originalSR7;
static u32 g_originalSDR1;

static __OSExceptionHandler s_prevDSIHandler;
static __OSExceptionHandler s_prevISIHandler;

void __VMBASESetupVMRegisters_SetSDR1(void);
void __VMBASESetupVMRegisters_End(void);
static asm void __VMBASEDSIExceptionHandler(__OSException exception, OSContext* context);
static asm void __VMBASEISIExceptionHandler(__OSException exception, OSContext* context);
void __VMBASEDSIExceptionHandler_SetOriginalInstruction(void);
void __VMBASEDSIExceptionHandler_SetBranchBack(void);
void __VMBASEISIExceptionHandler_SetOriginalInstruction(void);
void __VMBASEISIExceptionHandler_SetBranchBack(void);

void* OSGetArenaLo(void);
void OSSetArenaLo(void* newLo);
BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);

void __VMBASEInitLockedPageTable(void);
void __VMBASEInitReversePageTable(void);
void __VMBASEInitPageTable(void);
void __VMBASESetupExceptionHandlers(void);
void __VMBASESetupVMRegisters(void);
static void __VMBASESetupSDR1(u32 srr1, u32 sdr1, u32 unused);
void __VMBASEInvalidateEntireTLB(void);
void __VMBASESetSwapPageCallback(VMSwapPageInCallback cb);
u32* __VMBASEVirtualAddrToPageTableAddr(u32 virtualAddr);
void __VMBASEClearPageFromTLB(u32 virtualAddr);
void __VMBASESetVirtualAddressForPageInMRAM(u32 mramPage, u32 virtualAddr);
void VMBASESetPageLocked(u32 mramPage, BOOL locked);
void __VMBASEInvalidatePageTable(void);
void __VMBASEInvalidateLockedPageTable(void);
void __VMBASEInvalidateReversePageTable(void);
void __VMBASEDSIServiceExceptionPrep(OSContext* context, u32 faultAddr);
void __VMBASEDSIServiceException(OSContext* context, u32 faultAddr);
void __VMBASEISIServiceExceptionPrep(OSContext* context);
void __VMBASEISIServiceException(OSContext* context);

void VMBASEInit(VMSwapPageInCallback cb)
{
    u32 oldInterrupts;
    u32 arenaLo;
    u32 freeIn64K;

    if (g_baseInitialized != 0)
    {
        return;
    }

    oldInterrupts = OSDisableInterrupts();
    g_baseInitialized = 1;
    __VMBASESetSwapPageCallback(cb);

    arenaLo = (u32)OSGetArenaLo();
    freeIn64K = 0x10000 - (arenaLo & 0xFFFF);

    if (freeIn64K >= 0x5000)
    {
        __VMBASEInitLockedPageTable();
        __VMBASEInitReversePageTable();
        __VMBASEInitPageTable();
    }
    else if (freeIn64K >= 0x4000)
    {
        __VMBASEInitReversePageTable();
        __VMBASEInitPageTable();
        __VMBASEInitLockedPageTable();
    }
    else if (freeIn64K >= 0x1000)
    {
        __VMBASEInitLockedPageTable();
        __VMBASEInitPageTable();
        __VMBASEInitReversePageTable();
    }
    else
    {
        __VMBASEInitPageTable();
        __VMBASEInitLockedPageTable();
        __VMBASEInitReversePageTable();
    }

    __VMBASESetupExceptionHandlers();
    __VMBASESetupVMRegisters();
    __VMBASEInvalidateEntireTLB();
    OSRestoreInterrupts(oldInterrupts);
}

void VMBASESetPageTableEntry(u32 virtualAddr, u32 physicalAddr, u32 mramPage)
{
    u32* pteAddr = __VMBASEVirtualAddrToPageTableAddr(virtualAddr);
    u32 oldInterrupts = OSDisableInterrupts();

    pteAddr[0] = 0x80000000 | ((virtualAddr >> 22) & 0x3F);
    pteAddr[1] = physicalAddr & 0x0FFFF000;

    DCStoreRange(pteAddr, 8);
    __VMBASEClearPageFromTLB(virtualAddr);
    __VMBASESetVirtualAddressForPageInMRAM(mramPage, virtualAddr);

    OSRestoreInterrupts(oldInterrupts);
}

void VMBASEClearPageTableEntry(u32 virtualAddr, u32 mramPage)
{
    u32 oldInterrupts = OSDisableInterrupts();
    u32* pteAddr = __VMBASEVirtualAddrToPageTableAddr(virtualAddr);

    pteAddr[0] = 0;
    pteAddr[1] = 0;
    DCStoreRange(pteAddr, 8);

    __VMBASEClearPageFromTLB(virtualAddr);
    __VMBASESetVirtualAddressForPageInMRAM(mramPage, 0);
    VMBASESetPageLocked(mramPage, FALSE);

    OSRestoreInterrupts(oldInterrupts);
}

BOOL VMBASEIsPageValid(u32 virtualAddr)
{
    u32* pteAddr = __VMBASEVirtualAddrToPageTableAddr(virtualAddr);
    return (BOOL)((pteAddr[0] >> 31) & 1);
}

BOOL VMBASEIsPageReferenced(u32 virtualAddr)
{
    u32* pteAddr = __VMBASEVirtualAddrToPageTableAddr(virtualAddr);
    return (BOOL)((pteAddr[1] & 0x100) != 0);
}

BOOL VMBASEIsPageDirty(u32 virtualAddr)
{
    u32* pteAddr = __VMBASEVirtualAddrToPageTableAddr(virtualAddr);
    return (BOOL)((pteAddr[1] >> 7) & 1);
}

void VMBASESetPageReferenced(u32 virtualAddr, BOOL referenced)
{
    u32 oldInterrupts = OSDisableInterrupts();
    u32* pteAddr = __VMBASEVirtualAddrToPageTableAddr(virtualAddr);

    if (referenced)
    {
        pteAddr[1] |= 0x100;
    }
    else
    {
        pteAddr[1] &= ~0x100;
    }

    DCStoreRange(&pteAddr[1], 4);
    __VMBASEClearPageFromTLB(virtualAddr);
    OSRestoreInterrupts(oldInterrupts);
}

#pragma scheduling off
asm void __VMBASEClearPageFromTLB(register u32 virtualAddr) {
    // clang-format off
    nofralloc

    rlwinm r0, virtualAddr, 0, 14, 19
    tlbsync
    tlbie r0
    blr
    // clang-format on
}
#pragma scheduling reset

u32 VMBASEGetVirtualAddrFromPageInMRAM(u32 mramPage)
{
    return g_vmBaseVMReversePageTable[mramPage];
}

void __VMBASESetVirtualAddressForPageInMRAM(u32 mramPage, u32 virtualAddr)
{
    g_vmBaseVMReversePageTable[mramPage] = virtualAddr;
}

BOOL VMBASEIsPageLocked(u32 mramPage)
{
    return g_vmBaseLockedPageTable[mramPage];
}

void VMBASESetPageLocked(u32 mramPage, BOOL locked)
{
    if (locked)
    {
        g_vmBaseLockedPageTable[mramPage] = 1;
        return;
    }
    g_vmBaseLockedPageTable[mramPage] = 0;
}

void __VMBASESetSwapPageCallback(VMSwapPageInCallback cb)
{
    cbVMSwapPageIn = cb;
}

void __VMBASEInitPageTable(void)
{
    u32 arenaLo = (u32)OSGetArenaLo();
    u32 base = (arenaLo + 0x10000) - (arenaLo & 0xFFFF);

    g_vmBasePageTable = (u32*)base;
    OSSetArenaLo((void*)(base + 0x10000));
    __VMBASEInvalidatePageTable();
}

void __VMBASEInitLockedPageTable(void)
{
    g_vmBaseLockedPageTable = (u8*)OSGetArenaLo();
    OSSetArenaLo((void*)((u8*)g_vmBaseLockedPageTable + 0x1000));
    __VMBASEInvalidateLockedPageTable();
}

/**
 * Offset/Address/Size: 0x3DC | 0x8025FF14 | size: 0x30
 * TODO: 64.7% match - body is correct but MWCC generates 0x08 stack frame instead of
 *       target's 0x10 frame, causing prologue/epilogue ordering differences.
 *       Same issue affects __VMBASEInitLockedPageTable and __VMBASEInitPageTable.
 */
void __VMBASEInitReversePageTable(void)
{
    void* lo = OSGetArenaLo();
    g_vmBaseVMReversePageTable = (u32*)lo;
    OSSetArenaLo((void*)((u8*)lo + 0x4000));
    __VMBASEInvalidateReversePageTable();
}

void __VMBASEInvalidatePageTable(void)
{
    void __VMBASEInvalidateEntireTLB();
    u32 oldInterrupts = OSDisableInterrupts();
    u32 offset;

    for (offset = 0; offset < 0x10000; offset += 8)
    {
        ((u32*)((u8*)g_vmBasePageTable + offset))[0] = 0;
        ((u32*)((u8*)g_vmBasePageTable + offset))[1] = 0;
    }

    DCStoreRange(g_vmBasePageTable, 0x10000);
    __VMBASEInvalidateEntireTLB();

    OSRestoreInterrupts(oldInterrupts);
}

void __VMBASEInvalidateLockedPageTable(void)
{
    memset(g_vmBaseLockedPageTable, 0, 0x1000);
}

void __VMBASEInvalidateReversePageTable(void)
{
    memset(g_vmBaseVMReversePageTable, 0, 0x4000);
}

u32* __VMBASEVirtualAddrToPageTableAddr(u32 virtualAddr)
{
    return (u32*)((u32)g_vmBasePageTable | ((virtualAddr >> 6) & 0xFFC0) | ((virtualAddr >> 19) & 0x38));
}

#pragma scheduling off
void __VMBASEInvalidateEntireTLB(void)
{
    // clang-format off
    asm {
        li r3, 0
        tlbsync
        li r0, 8
        mtctr r0
    loop:
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        bdnz loop
    }
    // clang-format on
}
#pragma scheduling reset

void __VMBASESetupVMRegisters(void)
{
    register u32 msr;
    register u32 sr7;
    register u32 pageTableBase;
    register u32 sdr1;
    register u32 sdr1Low;

    msr = 0;

    asm {
        mfsr sr7, 7
        mtsr 7, msr
    }

    g_originalSR7 = sr7;

    asm {
        mfmsr msr
        mfsdr1 sdr1
    }

    pageTableBase = (u32)g_vmBasePageTable;
    sdr1Low = sdr1 & 0xFFFF;

    __VMBASESetupSDR1(msr & ~(MSR_IR | MSR_DR), (g_originalSDR1 = sdr1, sdr1Low + (pageTableBase & 0x7FFF0000)), 0);
}

#pragma scheduling off
static asm void __VMBASESetupSDR1(register u32 srr1, register u32 sdr1, register u32 unused)
{
    // clang-format off
    nofralloc

    mtsrr1 srr1
    lis unused, __VMBASESetupVMRegisters_SetSDR1@ha
    addi unused, unused, __VMBASESetupVMRegisters_SetSDR1@l
    clrlwi unused, unused, 1
    mtsrr0 unused
    rfi

__VMBASESetupVMRegisters_SetSDR1:
    sync
    mtsdr1 sdr1
    sync
    mfmsr srr1
    ori srr1, srr1, 0x30
    mtsrr1 srr1
    lis unused, __VMBASESetupVMRegisters_End@ha
    addi unused, unused, __VMBASESetupVMRegisters_End@l
    mtsrr0 unused
    rfi

__VMBASESetupVMRegisters_End:
    nop
    blr
    // clang-format on
}
#pragma scheduling reset

void __VMBASESetupExceptionHandlers(void)
{
    s_prevDSIHandler = __OSSetExceptionHandler(__OS_EXCEPTION_DSI, __VMBASEDSIExceptionHandler);
    s_prevISIHandler = __OSSetExceptionHandler(__OS_EXCEPTION_ISI, __VMBASEISIExceptionHandler);
}

#pragma scheduling off
static asm void __VMBASEDSIExceptionHandler(__OSException exception, OSContext* context)
{
    // clang-format off
    nofralloc

    // Save r4, r5, r6 to SPRGs
    mtsprg  0, r4
    mtsprg  1, r5
    mtsprg  2, r6

    // Save CR to SPRG3
    mfcr    r4
    mtsprg  3, r4

    // Check if DAR (fault address) is in range [0x7E000000, 0x80000000)
    mfdar   r5
    li      r6, 0x7e
    slwi    r6, r6, 24
    cmplw   r5, r6
    blt     not_vm_fault

    mfdar   r5
    li      r6, 0x80
    slwi    r6, r6, 24
    cmplw   r5, r6
    bge     not_vm_fault

    // Check DSISR bit 1 (store operation bit)
    mfdsisr r5
    rlwinm  r6, r5, 0, 1, 1
    cmplwi  r6, 0
    beq     not_vm_fault

    // VM fault confirmed - restore registers then save full context
    mfsprg  r4, 3
    mtcrf   255, r4
    mfsprg  r4, 0
    mfsprg  r5, 1
    mfsprg  r6, 2

    // Save r4 to SPRG0 and load current context from physical address
    mtsprg  0, r4
    lwz     r4, 0x00C0

    // Save r3, original r4, r5 to context
    stw     r3, OS_CONTEXT_R3(r4)
    mfsprg  r3, 0
    stw     r3, OS_CONTEXT_R4(r4)
    stw     r5, OS_CONTEXT_R5(r4)

    // Set exception state flag
    lhz     r3, OS_CONTEXT_STATE(r4)
    ori     r3, r3, OS_CONTEXT_STATE_EXC
    sth     r3, OS_CONTEXT_STATE(r4)

    // Save special registers to context
    mfcr    r3
    stw     r3, OS_CONTEXT_CR(r4)
    mflr    r3
    stw     r3, OS_CONTEXT_LR(r4)
    mfctr   r3
    stw     r3, OS_CONTEXT_CTR(r4)
    mfxer   r3
    stw     r3, OS_CONTEXT_XER(r4)
    mfsrr0  r3
    stw     r3, OS_CONTEXT_SRR0(r4)
    mfsrr1  r3
    stw     r3, OS_CONTEXT_SRR1(r4)
    mr      r5, r3

    // Enable address translation
    mfmsr   r3
    ori     r3, r3, 0x30
    mtsrr1  r3

    // Set up RFI to __VMBASEDSIServiceExceptionPrep
    lwz     r3, 0xD4
    lis     r5, __VMBASEDSIServiceExceptionPrep@ha
    addi    r5, r5, __VMBASEDSIServiceExceptionPrep@l
    mtsrr0  r5
    rfi

not_vm_fault:
    // Not our exception - restore all saved registers
    mfsprg  r4, 3
    mtcrf   255, r4
    mfsprg  r4, 0
    mfsprg  r5, 1
    mfsprg  r6, 2

    // These are patched at runtime with original instruction and branch back
entry __VMBASEDSIExceptionHandler_SetOriginalInstruction
    nop
entry __VMBASEDSIExceptionHandler_SetBranchBack
    nop
    // clang-format on
}
#pragma scheduling reset

void __VMBASEDSIServiceExceptionPrep(OSContext* context, u32 faultAddr)
{
    __VMBASEDSIServiceException(context, faultAddr);
}

void __VMBASEDSIServiceException(OSContext* context, u32 faultAddr)
{
    OSContext tempContext;

    OSClearContext(&tempContext);
    OSSetCurrentContext(&tempContext);
    cbVMSwapPageIn(faultAddr);
    OSSetCurrentContext(context);
    OSLoadContext(context);
}

#pragma scheduling off
static asm void __VMBASEISIExceptionHandler(__OSException exception, OSContext* context)
{
    // clang-format off
    nofralloc

    // Save r4, r5, r6 to SPRGs
    mtsprg  0, r4
    mtsprg  1, r5
    mtsprg  2, r6

    // Save CR to SPRG3
    mfcr    r4
    mtsprg  3, r4

    // Check if SRR0 (fault address) is in range [0x7E000000, 0x80000000)
    mfsrr0  r5
    li      r6, 0x7e
    slwi    r6, r6, 24
    cmplw   r5, r6
    blt     not_vm_fault

    mfsrr0  r5
    li      r6, 0x80
    slwi    r6, r6, 24
    cmplw   r5, r6
    bge     not_vm_fault

    // Check SRR1 bit 1 (0x40000000 - page fault bit)
    mfsrr1  r5
    rlwinm  r6, r5, 0, 1, 1
    cmplwi  r6, 0
    beq     not_vm_fault

    // VM fault confirmed - restore registers then save full context
    mfsprg  r4, 3
    mtcrf   255, r4
    mfsprg  r4, 0
    mfsprg  r5, 1
    mfsprg  r6, 2

    // Save r4 to SPRG0 and load current context from physical address
    mtsprg  0, r4
    lwz     r4, 0x00C0

    // Save r3, original r4, r5 to context
    stw     r3, OS_CONTEXT_R3(r4)
    mfsprg  r3, 0
    stw     r3, OS_CONTEXT_R4(r4)
    stw     r5, OS_CONTEXT_R5(r4)

    // Set exception state flag
    lhz     r3, OS_CONTEXT_STATE(r4)
    ori     r3, r3, OS_CONTEXT_STATE_EXC
    sth     r3, OS_CONTEXT_STATE(r4)

    // Save special registers to context
    mfcr    r3
    stw     r3, OS_CONTEXT_CR(r4)
    mflr    r3
    stw     r3, OS_CONTEXT_LR(r4)
    mfctr   r3
    stw     r3, OS_CONTEXT_CTR(r4)
    mfxer   r3
    stw     r3, OS_CONTEXT_XER(r4)
    mfsrr0  r3
    stw     r3, OS_CONTEXT_SRR0(r4)
    mfsrr1  r3
    stw     r3, OS_CONTEXT_SRR1(r4)
    mr      r5, r3

    // Enable address translation
    mfmsr   r3
    ori     r3, r3, 0x30
    mtsrr1  r3

    // Set up RFI to __VMBASEISIServiceExceptionPrep
    lwz     r3, 0xD4
    lis     r5, __VMBASEISIServiceExceptionPrep@ha
    addi    r5, r5, __VMBASEISIServiceExceptionPrep@l
    mtsrr0  r5
    rfi

not_vm_fault:
    // Not our exception - restore all saved registers
    mfsprg  r4, 3
    mtcrf   255, r4
    mfsprg  r4, 0
    mfsprg  r5, 1
    mfsprg  r6, 2

    // These are patched at runtime
entry __VMBASEISIExceptionHandler_SetOriginalInstruction
    nop
entry __VMBASEISIExceptionHandler_SetBranchBack
    nop
    // clang-format on
}
#pragma scheduling reset

void __VMBASEISIServiceExceptionPrep(OSContext* context)
{
    __VMBASEISIServiceException(context);
}

void __VMBASEISIServiceException(OSContext* context)
{
    OSContext tempContext;

    OSClearContext(&tempContext);
    OSSetCurrentContext(&tempContext);

    cbVMSwapPageIn(context->srr0);

    OSSetCurrentContext(context);
    OSLoadContext(context);
}

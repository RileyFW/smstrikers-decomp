#include <dolphin/types.h>

static u32 g_vmFreePagesExist = 1;
static s32 g_vmPageReplacementPolicy = 1;
static u32 g_vmNextPageToSwap;

u32 __VMGetNumPagesInMRAM(void);
u32 VMBASEGetVirtualAddrFromPageInMRAM(u32 mramPage);
BOOL VMBASEIsPageValid(u32 virtualAddr);
BOOL VMBASEIsPageReferenced(u32 virtualAddr);
BOOL VMBASEIsPageDirty(u32 virtualAddr);
void VMBASESetPageReferenced(u32 virtualAddr, BOOL referenced);
BOOL VMBASEIsPageLocked(u32 mramPage);
u32 OSGetTick(void);

u32 __VMPageReplacementLRU(void);
u32 __VMPageReplacementRandom(void);
u32 __VMPageReplacementFIFO(void);

u32 __VMGetPageToReplace(void)
{
    if (g_vmPageReplacementPolicy == 0)
    {
        return __VMPageReplacementLRU();
    }
    if (g_vmPageReplacementPolicy == 1)
    {
        return __VMPageReplacementRandom();
    }
    return __VMPageReplacementFIFO();
}

u32 __VMPageReplacementLRU(void)
{
    u32 selected = 0;
    u32 startPage = g_vmNextPageToSwap;
    s32 class0x1 = -1;
    s32 class1x0 = -1;
    s32 class1x1 = -1;

    if (g_vmFreePagesExist != 0)
    {
        selected = startPage;
        goto done_select;
    }

    while (TRUE)
    {
        u32 currentPage = g_vmNextPageToSwap;
        u32 virtualAddr = VMBASEGetVirtualAddrFromPageInMRAM(currentPage);

        if (virtualAddr == 0)
        {
            selected = currentPage;
            break;
        }

        if (VMBASEIsPageValid(virtualAddr) != FALSE)
        {
            BOOL referenced = VMBASEIsPageReferenced(virtualAddr);
            BOOL dirty = VMBASEIsPageDirty(virtualAddr);

            if (!referenced && !dirty && !VMBASEIsPageLocked(currentPage))
            {
                selected = currentPage;
                break;
            }

            if (!referenced && dirty)
            {
                if (class0x1 < 0 && !VMBASEIsPageLocked(currentPage))
                {
                    class0x1 = (s32)currentPage;
                }
            }
            else if (referenced && !dirty)
            {
                if (class1x0 < 0 && !VMBASEIsPageLocked(currentPage))
                {
                    class1x0 = (s32)currentPage;
                }
            }
            else if (class1x1 < 0 && !VMBASEIsPageLocked(currentPage))
            {
                class1x1 = (s32)currentPage;
            }

            if (referenced)
            {
                VMBASESetPageReferenced(virtualAddr, FALSE);
            }
        }

        if (currentPage == startPage)
        {
            if (class0x1 >= 0)
            {
                selected = (u32)class0x1;
            }
            else if (class1x0 >= 0)
            {
                selected = (u32)class1x0;
            }
            else if (class1x1 >= 0)
            {
                selected = (u32)class1x1;
            }
            break;
        }

        g_vmNextPageToSwap = currentPage + 1;
        if (g_vmNextPageToSwap >= __VMGetNumPagesInMRAM())
        {
            g_vmNextPageToSwap = 0;
        }
    }

done_select:
    g_vmNextPageToSwap++;
    if (g_vmNextPageToSwap >= __VMGetNumPagesInMRAM())
    {
        g_vmFreePagesExist = 0;
        g_vmNextPageToSwap = 0;
    }

    return selected;
}

u32 __VMPageReplacementRandom(void)
{
    while (TRUE)
    {
        u32 page;

        if (g_vmFreePagesExist != 0)
        {
            page = g_vmNextPageToSwap;
            g_vmNextPageToSwap++;
            if (g_vmNextPageToSwap >= __VMGetNumPagesInMRAM())
            {
                g_vmFreePagesExist = 0;
                g_vmNextPageToSwap = 0;
            }
        }
        else
        {
            u32 numPages = __VMGetNumPagesInMRAM();
            page = (numPages == 0) ? 0 : (OSGetTick() % numPages);
        }

        if (!VMBASEIsPageLocked(page))
        {
            return page;
        }
    }
}

u32 __VMPageReplacementFIFO(void)
{
    while (TRUE)
    {
        u32 page = g_vmNextPageToSwap++;

        if (g_vmNextPageToSwap >= __VMGetNumPagesInMRAM())
        {
            g_vmFreePagesExist = 0;
            g_vmNextPageToSwap = 0;
        }

        if (!VMBASEIsPageLocked(page))
        {
            return page;
        }
    }
}

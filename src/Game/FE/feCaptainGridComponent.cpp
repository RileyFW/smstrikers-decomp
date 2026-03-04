#include "Game/FE/feCaptainGridComponent.h"
#include "Game/FE/feFinder.h"
#include "Game/FE/tlComponentInstance.h"
#include "Game/GameInfo.h"

extern unsigned long CaptainCellItems[];
extern unsigned long NUM_CAPTAIN_CELL_ITEMS;

/**
 * Offset/Address/Size: 0x0 | 0x800C16F4 | size: 0x24
 */
void ICaptainGridComponent::SetAllItemsActive()
{
    mMapMenu->SetAllItemsActive();
}

/**
 * Offset/Address/Size: 0x24 | 0x800C1718 | size: 0x90
 */
void ICaptainGridComponent::MoveHighlightToTarget(eTeamID teamID)
{
    int position;

    switch (teamID)
    {
    case TEAM_DAISY:
        position = 4;
        break;
    case TEAM_DONKEYKONG:
        position = 1;
        break;
    case TEAM_LUIGI:
        position = 5;
        break;
    case TEAM_MARIO:
        position = 0;
        break;
    case TEAM_PEACH:
        position = 3;
        break;
    case TEAM_WALUIGI:
        position = 2;
        break;
    case TEAM_WARIO:
        position = 6;
        break;
    case TEAM_YOSHI:
        position = 7;
        break;
    case TEAM_MYSTERY:
        position = 8;
        break;
    default:
        position = 0;
        break;
    }

    mMapMenu->SetSelectedItem(position);
}

/**
 * Offset/Address/Size: 0xB4 | 0x800C17A8 | size: 0xC8
 */
eTeamID ICaptainGridComponent::GetSelectedItem() const
{
    // TODO: 97.9% match - extra mr r5,r0 for pItems pointer init
    int selectedItem = mMapMenu->GetSelectedItem();
    unsigned long* pItems = CaptainCellItems;
    long count = (long)NUM_CAPTAIN_CELL_ITEMS;
    long i = 0;
    eTeamID result = TEAM_INVALID;

    for (; i < count; pItems += 2, i++)
    {
        if (selectedItem != (int)pItems[0])
        {
            continue;
        }
        switch (pItems[0])
        {
        case 0:
            result = TEAM_DAISY;
            break;
        case 1:
            result = TEAM_DONKEYKONG;
            break;
        case 2:
            result = TEAM_LUIGI;
            break;
        case 3:
            result = TEAM_MARIO;
            break;
        case 4:
            result = TEAM_PEACH;
            break;
        case 5:
            result = TEAM_WARIO;
            break;
        case 6:
            result = TEAM_WALUIGI;
            break;
        case 7:
            result = TEAM_YOSHI;
            break;
        case 8:
            result = TEAM_MYSTERY;
            break;
        default:
            result = TEAM_MARIO;
            break;
        }
    }
    return result;
}

/**
 * Offset/Address/Size: 0x17C | 0x800C1870 | size: 0x90
 */
void ICaptainGridComponent::IsValid(eTeamID teamID)
{
    int position;

    switch (teamID)
    {
    case TEAM_DAISY:
        position = 4;
        break;
    case TEAM_DONKEYKONG:
        position = 1;
        break;
    case TEAM_LUIGI:
        position = 5;
        break;
    case TEAM_MARIO:
        position = 0;
        break;
    case TEAM_PEACH:
        position = 3;
        break;
    case TEAM_WALUIGI:
        position = 2;
        break;
    case TEAM_WARIO:
        position = 6;
        break;
    case TEAM_YOSHI:
        position = 7;
        break;
    case TEAM_MYSTERY:
        position = 8;
        break;
    default:
        position = 0;
        break;
    }

    mMapMenu->IsItemActive(position);
}

/**
 * Offset/Address/Size: 0x20C | 0x800C1900 | size: 0x90
 */
void ICaptainGridComponent::SetValid(eTeamID teamID, bool valid)
{
    int position;

    switch (teamID)
    {
    case TEAM_DAISY:
        position = 4;
        break;
    case TEAM_DONKEYKONG:
        position = 1;
        break;
    case TEAM_LUIGI:
        position = 5;
        break;
    case TEAM_MARIO:
        position = 0;
        break;
    case TEAM_PEACH:
        position = 3;
        break;
    case TEAM_WALUIGI:
        position = 2;
        break;
    case TEAM_WARIO:
        position = 6;
        break;
    case TEAM_YOSHI:
        position = 7;
        break;
    case TEAM_MYSTERY:
        position = 8;
        break;
    default:
        position = 0;
        break;
    }

    mMapMenu->SetItemActive(position, valid);
}

extern bool g_e3_Build;

/**
 * Offset/Address/Size: 0x29C | 0x800C1990 | size: 0x7C
 */
void ICaptainGridComponent::UpdateSuperTeamIconState()
{
    if (g_e3_Build)
    {
        return;
    }

    if (GameInfoManager::Instance()->IsSuperTeamUnlocked())
    {
        if (mMapMenu->IsItemActive(8))
        {
            mMapMenu->SetItemActive(8, true);
            return;
        }
    }
    mMapMenu->SetItemActive(8, false);
}

/**
 * Offset/Address/Size: 0x318 | 0x800C1A0C | size: 0x264
 */
void ICaptainGridComponent::Update(eFEINPUT_PAD)
{
}

/**
 * Offset/Address/Size: 0x57C | 0x800C1C70 | size: 0x150
 */
void ICaptainGridComponent::RebuildInstanceTable()
{
    TLSlide* slide;
    int i;

    slide = mParentComponent->GetActiveSlide();

    for (i = 0; i < (int)NUM_CAPTAIN_CELL_ITEMS; i++)
    {
        TLInstance* inst = FEFinder<TLInstance, 2>::Find(slide,
            InlineHasher(nlStringLowerHash((const char*)CaptainCellItems[i * 2 + 1])),
            InlineHasher(0),
            InlineHasher(0),
            InlineHasher(0),
            InlineHasher(0),
            InlineHasher(0));
        mInstanceTable[CaptainCellItems[i * 2]] = inst;
        mMapMenu->ChangeItem((int)CaptainCellItems[i * 2], mInstanceTable[CaptainCellItems[i * 2]]);
    }

    if (!g_e3_Build)
    {
        if (GameInfoManager::Instance()->IsSuperTeamUnlocked() && mMapMenu->IsItemActive(8))
        {
            mMapMenu->SetItemActive(8, true);
        }
        else
        {
            mMapMenu->SetItemActive(8, false);
        }
    }

    mMapMenu->UpdateAllItems();
}

/**
 * Offset/Address/Size: 0x6CC | 0x800C1DC0 | size: 0x1F0
 * TODO: 98.10% match - r22/r24 activeslide/pCell register swap in first loop,
 * r25/r28 i/cellIndex register swap in second loop
 */
#pragma opt_strength_reduction off
void ICaptainGridComponent::BuildMapMenu()
{
    TLSlide* activeslide = mParentComponent->GetActiveSlide();

    mInstanceTable = (TLInstance**)nlMalloc(NUM_CAPTAIN_CELL_ITEMS * 4, 8, false);

    unsigned long* pCell = CaptainCellItems;
    int i;
    for (i = 0; i < (int)NUM_CAPTAIN_CELL_ITEMS; i++, pCell += 2)
    {
        mInstanceTable[pCell[0]] = FEFinder<TLInstance, 2>::Find(activeslide,
            InlineHasher(nlStringLowerHash((const char*)pCell[1])),
            InlineHasher(0),
            InlineHasher(0),
            InlineHasher(0),
            InlineHasher(0),
            InlineHasher(0));
    }

    int numRows = g_e3_Build ? 2 : 3;
    int numCols = g_e3_Build ? 2 : 3;
    int base = 0;
    int NUM_ELEMENTS = numRows * numCols;

    for (i = 0; i < numRows; i++)
    {
        int cellIndex = base;
        for (int j = 0; j < numCols; j++)
        {
            int col = cellIndex % numCols;

            int left = cellIndex - 1;
            if (col - 1 < 0)
                left = cellIndex + numCols - 1;

            int right = cellIndex + 1;
            if (col + 1 >= numCols)
                right = cellIndex - numCols + 1;

            int up = (cellIndex - numCols + NUM_ELEMENTS) % NUM_ELEMENTS;
            int down = (cellIndex + numCols) % NUM_ELEMENTS;

            int itemID = (int)CaptainCellItems[cellIndex * 2];
            mMapMenu->AddItem(
                itemID,
                mInstanceTable[itemID],
                (int)CaptainCellItems[left * 2],
                (int)CaptainCellItems[right * 2],
                (int)CaptainCellItems[up * 2],
                (int)CaptainCellItems[down * 2],
                true);
            cellIndex++;
        }
        base += numCols;
    }

    mMapMenu->SetSelectedItem((int)CaptainCellItems[0]);
}
#pragma opt_strength_reduction on

/**
 * Offset/Address/Size: 0x8BC | 0x800C1FB0 | size: 0x94
 */
ICaptainGridComponent::~ICaptainGridComponent()
{
}

/**
 * Offset/Address/Size: 0x950 | 0x800C2044 | size: 0x228
 */
ICaptainGridComponent::ICaptainGridComponent(TLComponentInstance*, bool)
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x800C226C | size: 0x38
//  */
// void FEFinder<TLInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800C22A4 | size: 0x84
//  */
// void FEFinder<TLInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800C2328 | size: 0x15C
//  */
// void FEFinder<TLInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800C2484 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800C24BC | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800C2540 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800C269C | size: 0x84
//  */
// void IGridComponent<eTeamID>::~IGridComponent()
// {
// }

// /**
//  * Offset/Address/Size: 0x84 | 0x800C2720 | size: 0xF0
//  */
// void IGridComponent<eTeamID>::IGridComponent(TLComponentInstance*, const char*, bool)
// {
// }

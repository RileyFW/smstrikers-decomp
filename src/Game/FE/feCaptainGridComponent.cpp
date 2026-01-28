#include "Game/FE/feCaptainGridComponent.h"

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

    switch (teamID) {
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

    for (; i < count; pItems += 2, i++) {
        if (selectedItem != (int)pItems[0]) {
            continue;
        }
        switch (pItems[0]) {
            case 0: result = TEAM_DAISY; break;
            case 1: result = TEAM_DONKEYKONG; break;
            case 2: result = TEAM_LUIGI; break;
            case 3: result = TEAM_MARIO; break;
            case 4: result = TEAM_PEACH; break;
            case 5: result = TEAM_WARIO; break;
            case 6: result = TEAM_WALUIGI; break;
            case 7: result = TEAM_YOSHI; break;
            case 8: result = TEAM_MYSTERY; break;
            default: result = TEAM_MARIO; break;
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

    switch (teamID) {
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

    switch (teamID) {
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

/**
 * Offset/Address/Size: 0x29C | 0x800C1990 | size: 0x7C
 */
void ICaptainGridComponent::UpdateSuperTeamIconState()
{
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
}

/**
 * Offset/Address/Size: 0x6CC | 0x800C1DC0 | size: 0x1F0
 */
void ICaptainGridComponent::BuildMapMenu()
{
}

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

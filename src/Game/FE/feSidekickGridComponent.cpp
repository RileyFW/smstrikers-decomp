#include "Game/FE/feSidekickGridComponent.h"
#include "Game/FE/feMapMenu.h"

/**
 * Offset/Address/Size: 0x0 | 0x800C2810 | size: 0x34
 */
void ISidekickGridComponent::SetVisibleInstanceTable(bool visible)
{
    mInstanceTable[0]->m_bVisible = visible;
    mInstanceTable[1]->m_bVisible = visible;
    mInstanceTable[2]->m_bVisible = visible;
    mInstanceTable[3]->m_bVisible = visible;
}

/**
 * Offset/Address/Size: 0x34 | 0x800C2844 | size: 0x70
 */
void ISidekickGridComponent::MoveHighlightToTarget(eSidekickID id)
{
    int item;
    switch (id) {
        case SK_TOAD:
            item = 0;
            break;
        case SK_HAMMERBROS:
            item = 1;
            break;
        case SK_BIRDO:
            item = 2;
            break;
        case SK_KOOPA:
            item = 3;
            break;
        default:
            item = 0;
            break;
    }
    mMapMenu->SetSelectedItem(item);
}

/**
 * Offset/Address/Size: 0xA4 | 0x800C28B4 | size: 0x70
 */
eSidekickID ISidekickGridComponent::GetSelectedItem() const
{
    int position = mMapMenu->GetSelectedItem();

    switch (position) {
    case 0:
        return SK_TOAD;
    case 1:
        return SK_HAMMERBROS;
    case 2:
        return SK_BIRDO;
    case 3:
        return SK_KOOPA;
    default:
        return SK_TOAD;
    }
}

/**
 * Offset/Address/Size: 0x114 | 0x800C2924 | size: 0x210
 */
void ISidekickGridComponent::Update(eFEINPUT_PAD)
{
}

/**
 * Offset/Address/Size: 0x324 | 0x800C2B34 | size: 0xE4
 */
void ISidekickGridComponent::RebuildInstanceTable()
{
}

/**
 * Offset/Address/Size: 0x408 | 0x800C2C18 | size: 0x1AC
 */
void ISidekickGridComponent::BuildMapMenu()
{
}

/**
 * Offset/Address/Size: 0x5B4 | 0x800C2DC4 | size: 0x94
 */
ISidekickGridComponent::~ISidekickGridComponent()
{
}

/**
 * Offset/Address/Size: 0x648 | 0x800C2E58 | size: 0x48
 */
ISidekickGridComponent::ISidekickGridComponent(TLComponentInstance*, bool)
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x800C2EA0 | size: 0x38
//  */
// void FEFinder<TLInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800C2ED8 | size: 0x84
//  */
// void FEFinder<TLInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800C2F5C | size: 0x15C
//  */
// void FEFinder<TLInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800C30B8 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800C30F0 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800C3174 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800C32D0 | size: 0x84
//  */
// void IGridComponent<eSidekickID>::~IGridComponent()
// {
// }

// /**
//  * Offset/Address/Size: 0x84 | 0x800C3354 | size: 0xF0
//  */
// void IGridComponent<eSidekickID>::IGridComponent(TLComponentInstance*, const char*, bool)
// {
// }

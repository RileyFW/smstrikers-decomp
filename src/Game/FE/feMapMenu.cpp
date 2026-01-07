#include "Game/FE/feMapMenu.h"

/**
 * Offset/Address/Size: 0xF80 | 0x80098280 | size: 0x2C
 */
FEMapMenu::FEMapMenu(TLInstance*, bool)
{
}

/**
 * Offset/Address/Size: 0xF44 | 0x80098244 | size: 0x3C
 */
FEMapMenu::~FEMapMenu()
{
}

/**
 * Offset/Address/Size: 0xDA4 | 0x800980A4 | size: 0x1A0
 */
void FEMapMenu::AddItem(int, TLInstance*, int, int, int, int, bool)
{
}

/**
 * Offset/Address/Size: 0xC88 | 0x80097F88 | size: 0x11C
 */
void FEMapMenu::UpdateAllItems()
{
}

/**
 * Offset/Address/Size: 0x814 | 0x80097B14 | size: 0x474
 */
void FEMapMenu::Update(float)
{
}

/**
 * Offset/Address/Size: 0x714 | 0x80097A14 | size: 0x100
 */
bool FEMapMenu::MoveRight(bool)
{
    return false;
}

/**
 * Offset/Address/Size: 0x614 | 0x80097914 | size: 0x100
 */
bool FEMapMenu::MoveLeft(bool)
{
    return false;
}

/**
 * Offset/Address/Size: 0x514 | 0x80097814 | size: 0x100
 */
bool FEMapMenu::MoveDown(bool)
{
    return false;
}

/**
 * Offset/Address/Size: 0x414 | 0x80097714 | size: 0x100
 */
bool FEMapMenu::MoveUp(bool)
{
    return false;
}

/**
 * Offset/Address/Size: 0x3FC | 0x800976FC | size: 0x18
 */
int FEMapMenu::GetSelectedItem() const
{
    return 0;
}

/**
 * Offset/Address/Size: 0x3E4 | 0x800976E4 | size: 0x18
 */
bool FEMapMenu::IsSelectedItemActive() const
{
    return false;
}

/**
 * Offset/Address/Size: 0x3A4 | 0x800976A4 | size: 0x40
 */
bool FEMapMenu::IsItemActive(int) const
{
    return false;
}

/**
 * Offset/Address/Size: 0x304 | 0x80097604 | size: 0xA0
 */
void FEMapMenu::SetSelectedItem(int)
{
}

/**
 * Offset/Address/Size: 0x298 | 0x80097598 | size: 0x6C
 */
void FEMapMenu::UpdateHighlighter()
{
    signed char selectedItem = m_currentSelectIndex;
    TLInstance* pItemInstance = m_items[selectedItem].Icon;
    feVector3 pos = pItemInstance->GetPosition();
    m_highlighter->SetAssetPosition(pos.f.x, pos.f.y, pos.f.z);
}

/**
 * Offset/Address/Size: 0x170 | 0x80097470 | size: 0x128
 */
void FEMapMenu::SetItemActive(int, bool)
{
}

/**
 * Offset/Address/Size: 0x4C | 0x8009734C | size: 0x124
 */
void FEMapMenu::SetAllItemsActive()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80097300 | size: 0x4C
 */
void FEMapMenu::ChangeItem(int itemID, TLInstance* pInstance)
{
    int result = -1;

    for (int i = 0; i < m_numItems; i++)
    {
        if (m_items[i].ItemID == itemID)
        {
            result = i;
            break;
        }
    }

    m_items[result].Icon = pInstance;
}

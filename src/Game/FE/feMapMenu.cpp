#include "Game/FE/feMapMenu.h"

static const char* NavDirection2SoundMap[4] = {
    "sfx_option_scroll_right",
    "sfx_option_scroll_left",
    "sfx_option_scroll_down",
    "sfx_option_scroll_up"
};

/**
 * Offset/Address/Size: 0xF80 | 0x80098280 | size: 0x2C
 */
FEMapMenu::FEMapMenu(TLInstance* pHighlighter, bool makeSounds)
{
    m_highlighter = pHighlighter;
    m_numItems = 0;
    m_currentSelectIndex = 0;
    m_numCyclesRemaining = 0;
    m_isRandomizing = false;
    m_hasRandomizeJustFinished = false;
    m_disabledMultColor = 0.0f;
    m_makeSounds = makeSounds;
}

/**
 * Offset/Address/Size: 0xF44 | 0x80098244 | size: 0x3C
 */
FEMapMenu::~FEMapMenu()
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0xDA4 | 0x800980A4 | size: 0x1A0
 * TODO: r29/r30 register allocation difference
 */
void FEMapMenu::AddItem(int itemID, TLInstance* pIcon, int leftID, int rightID, int upID, int downID, bool active)
{
    m_items[m_numItems].ItemID = itemID;
    m_items[m_numItems].Icon = pIcon;
    m_items[m_numItems].Active = active;
    m_items[m_numItems].Left = leftID;
    m_items[m_numItems].Right = rightID;
    m_items[m_numItems].Up = upID;
    m_items[m_numItems].Down = downID;

    FEMapMenu* pBase;
    s32 offset;

    offset = m_numItems * (s32)sizeof(ItemEntry);
    pBase = (FEMapMenu*)((s32)this + offset);

    nlColour color = pBase->m_items[0].Icon->m_component->GetColour();

    if (!pBase->m_items[0].Active)
    {
        color.c[0] = (u8)(color.c[0] * m_disabledMultColor);
        color.c[1] = (u8)(color.c[1] * m_disabledMultColor);
        color.c[2] = (u8)(color.c[2] * m_disabledMultColor);
        pBase->m_items[0].Icon->SetAssetColour(color);
    }
    else
    {
        pBase->m_items[0].Icon->SetAssetColour(color);
    }

    m_numItems++;
}

/**
 * Offset/Address/Size: 0xC88 | 0x80097F88 | size: 0x11C
 */
void FEMapMenu::UpdateAllItems()
{
    for (int i = 0; i < m_numItems; i++)
    {
        ItemEntry* pItem = (ItemEntry*)&m_items[i];
        nlColour color = pItem->Icon->m_component->GetColour();

        if (pItem->Active == false)
        {
            color.c[0] = (u8)(color.c[0] * m_disabledMultColor);
            color.c[1] = (u8)(color.c[1] * m_disabledMultColor);
            color.c[2] = (u8)(color.c[2] * m_disabledMultColor);
            pItem->Icon->SetAssetColour(color);
        }
        else
        {
            pItem->Icon->SetAssetColour(color);
        }
    }
}

/**
 * Offset/Address/Size: 0x814 | 0x80097B14 | size: 0x474
 * TODO: Implement...
 */
void FEMapMenu::Update(float)
{
}

/**
 * Offset/Address/Size: 0x714 | 0x80097A14 | size: 0x100
 */
bool FEMapMenu::MoveRight(bool playSound)
{
    int rightItemID = m_items[m_currentSelectIndex].Right;

    if (rightItemID != -1)
    {
        SetCurrentSelectByID(rightItemID);

        feVector3 pos = m_items[m_currentSelectIndex].Icon->GetPosition();
        m_highlighter->SetAssetPosition(pos.f.x, pos.f.y, pos.f.z);

        if (playSound && m_makeSounds)
        {
            FEAudio::PlayAnimAudioEvent(NavDirection2SoundMap[0], false);
        }

        return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0x614 | 0x80097914 | size: 0x100
 */
bool FEMapMenu::MoveLeft(bool playSound)
{
    int leftItemID = m_items[m_currentSelectIndex].Left;

    if (leftItemID != -1)
    {
        SetCurrentSelectByID(leftItemID);

        feVector3 pos = m_items[m_currentSelectIndex].Icon->GetPosition();
        m_highlighter->SetAssetPosition(pos.f.x, pos.f.y, pos.f.z);

        if (playSound && m_makeSounds)
        {
            FEAudio::PlayAnimAudioEvent(NavDirection2SoundMap[1], false);
        }

        return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0x514 | 0x80097814 | size: 0x100
 */
bool FEMapMenu::MoveDown(bool playSound)
{
    int downItemID = m_items[m_currentSelectIndex].Down;

    if (downItemID != -1)
    {
        SetCurrentSelectByID(downItemID);

        feVector3 pos = m_items[m_currentSelectIndex].Icon->GetPosition();
        m_highlighter->SetAssetPosition(pos.f.x, pos.f.y, pos.f.z);

        if (playSound && m_makeSounds)
        {
            FEAudio::PlayAnimAudioEvent(NavDirection2SoundMap[2], false);
        }

        return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0x414 | 0x80097714 | size: 0x100
 */
bool FEMapMenu::MoveUp(bool playSound)
{
    int upItemID = m_items[m_currentSelectIndex].Up;

    if (upItemID != -1)
    {
        SetCurrentSelectByID(upItemID);

        feVector3 pos = m_items[m_currentSelectIndex].Icon->GetPosition();
        m_highlighter->SetAssetPosition(pos.f.x, pos.f.y, pos.f.z);

        if (playSound && m_makeSounds)
        {
            FEAudio::PlayAnimAudioEvent(NavDirection2SoundMap[3], false);
        }

        return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0x3FC | 0x800976FC | size: 0x18
 */
int FEMapMenu::GetSelectedItem() const
{
    return m_items[m_currentSelectIndex].ItemID;
}

/**
 * Offset/Address/Size: 0x3E4 | 0x800976E4 | size: 0x18
 */
bool FEMapMenu::IsSelectedItemActive() const
{
    return m_items[m_currentSelectIndex].Active;
}

/**
 * Offset/Address/Size: 0x3A4 | 0x800976A4 | size: 0x40
 */
bool FEMapMenu::IsItemActive(int itemID) const
{
    int result = 0;
    int i = 0;

    while (i < m_numItems)
    {
        if (itemID == m_items[i].ItemID)
        {
            break;
        }
        i++;
        result++;
    }

    return m_items[result].Active;
}

/**
 * Offset/Address/Size: 0x304 | 0x80097604 | size: 0xA0
 */
void FEMapMenu::SetSelectedItem(int itemID)
{
    signed char i = 0;
    int count = 0;

    while (count < m_numItems)
    {
        if (m_items[count].ItemID == itemID)
        {
            m_currentSelectIndex = i;
            break;
        }
        count++;
        i++;
    }

    TLInstance* pIcon = m_items[m_currentSelectIndex].Icon;
    feVector3 pos = pIcon->GetPosition();
    m_highlighter->SetAssetPosition(pos.f.x, pos.f.y, pos.f.z);
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
void FEMapMenu::SetItemActive(int itemID, bool active)
{
    int i = 0;

    for (; i < m_numItems; i++)
    {
        if (itemID == m_items[i].ItemID)
        {
            break;
        }
    }

    m_items[i].Active = active;

    nlColour color = m_items[i].Icon->m_component->GetColour();

    if (m_items[i].Active == false)
    {
        color.c[0] = (u8)(color.c[0] * m_disabledMultColor);
        color.c[1] = (u8)(color.c[1] * m_disabledMultColor);
        color.c[2] = (u8)(color.c[2] * m_disabledMultColor);
        m_items[i].Icon->SetAssetColour(color);
    }
    else
    {
        m_items[i].Icon->SetAssetColour(color);
    }
}

/**
 * Offset/Address/Size: 0x4C | 0x8009734C | size: 0x124
 */
void FEMapMenu::SetAllItemsActive()
{
    int i = 0;

    for (; i < m_numItems; i++)
    {
        ItemEntry* pItem = (ItemEntry*)&m_items[i];
        pItem->Active = true;
        nlColour color = pItem->Icon->m_component->GetColour();

        if (!pItem->Active)
        {
            color.c[0] = (u8)(color.c[0] * m_disabledMultColor);
            color.c[1] = (u8)(color.c[1] * m_disabledMultColor);
            color.c[2] = (u8)(color.c[2] * m_disabledMultColor);
            pItem->Icon->SetAssetColour(color);
        }
        else
        {
            pItem->Icon->SetAssetColour(color);
        }
    }
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

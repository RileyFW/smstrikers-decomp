#ifndef _FEMAPMENU_H_
#define _FEMAPMENU_H_

#include "Game/FE/tlInstance.h"

struct ItemEntry
{
    /* 0x00 */ int ItemID;
    /* 0x04 */ TLInstance* Icon;
    /* 0x08 */ bool Active;
    /* 0x09 */ char pad[3];
    /* 0x0C */ int Left;
    /* 0x10 */ int Right;
    /* 0x14 */ int Up;
    /* 0x18 */ int Down;
}; // total size: 0x1C

class FEMapMenu
{
public:
    FEMapMenu(TLInstance*, bool);
    ~FEMapMenu();
    void AddItem(int, TLInstance*, int, int, int, int, bool);
    void UpdateAllItems();
    void Update(float);
    bool MoveRight(bool);
    bool MoveLeft(bool);
    bool MoveDown(bool);
    bool MoveUp(bool);
    int GetSelectedItem() const;
    bool IsSelectedItemActive() const;
    bool IsItemActive(int) const;
    void SetSelectedItem(int);
    void UpdateHighlighter();
    void SetItemActive(int, bool);
    void SetAllItemsActive();
    void ChangeItem(int, TLInstance*);

    inline void SetCurrentSelectByID(int itemID)
    {
        for (int i = 0; i < m_numItems; i++)
        {
            if (m_items[i].ItemID == itemID)
            {
                m_currentSelectIndex = i;
                break;
            }
        }
    }

    /* 0x000 */ TLInstance* m_highlighter;
    /* 0x004 */ ItemEntry m_items[32];
    /* 0x384 */ signed char m_numItems;
    /* 0x385 */ signed char m_currentSelectIndex;
    /* 0x386 */ signed char m_numCyclesRemaining;
    /* 0x388 */ float m_randDeltaTime;
    /* 0x38C */ bool m_isRandomizing;
    /* 0x38D */ bool m_hasRandomizeJustFinished;
    /* 0x390 */ float m_disabledMultColor;
    /* 0x394 */ bool m_makeSounds;
}; // total size: 0x398

#endif // _FEMAPMENU_H_

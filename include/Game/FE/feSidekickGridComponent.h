#ifndef _FESIDEKICKGRIDCOMPONENT_H_
#define _FESIDEKICKGRIDCOMPONENT_H_
#include "Game/FE/feInput.h"

#include "Game/DB/Cup.h"

class TLComponentInstance;
class TLInstance;
class TLSlide;
class InlineHasher;

class FEMapMenu;

class IGridComponent
{
public:
    virtual ~IGridComponent() { }

    /* 0x00 */ // vtable
    /* 0x04 */ TLInstance** mInstanceTable;
    /* 0x08 */ FEMapMenu* mMapMenu;
    /* 0x0C */ bool mHighliteVisibilityAtAnimEnd;
    /* 0x10 */ TLComponentInstance* mParentComponent;
    /* 0x14 */ TLComponentInstance* mHighliteComponent;
    /* 0x18 */ bool mIsMirrored;
    /* 0x19 */ bool mHasChangedSinceLastUpdate;
}; // total size: 0x1C

class ISidekickGridComponent : public IGridComponent
{
public:
    void SetVisibleInstanceTable(bool);
    void MoveHighlightToTarget(eSidekickID);
    void GetSelectedItem() const;
    void Update(eFEINPUT_PAD);
    void RebuildInstanceTable();
    void BuildMapMenu();
    ~ISidekickGridComponent();
    ISidekickGridComponent(TLComponentInstance*, bool);
};

// class FEFinder<TLInstance, 2>
// {
// public:
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// };

// class FEFinder<TLComponentInstance, 4>
// {
// public:
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// };

// class IGridComponent<eSidekickID>
// {
// public:
//     void ~IGridComponent();
//     void IGridComponent(TLComponentInstance*, const char*, bool);
// };

#endif // _FESIDEKICKGRIDCOMPONENT_H_

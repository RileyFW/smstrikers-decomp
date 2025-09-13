#ifndef _FESIDEKICKGRIDCOMPONENT_H_
#define _FESIDEKICKGRIDCOMPONENT_H_
#include "Game/FE/feInput.h"

class TLComponentInstance;
class TLInstance;
class TLSlide;
class InlineHasher;

enum eSidekickID
{
    SIDEKICK_ID_0 = 0,
};

class ISidekickGridComponent
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

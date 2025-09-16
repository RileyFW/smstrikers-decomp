#ifndef _FEBUTTONCOMPONENT_H_
#define _FEBUTTONCOMPONENT_H_

// void nlStrLen<unsigned short>(const unsigned short*);

#include "Game/FE/feRender.h"
#include "Game/FE/tlComponentInstance.h"
class ButtonComponent
{
public:
    enum ButtonState
    {
        BUTTON_STATE_0 = 0,
    };

    void CentreButtons();
    void SetState(ButtonComponent::ButtonState);
    ~ButtonComponent();
    ButtonComponent();

    TLComponentInstance* mButtonInstance; // offset 0x0, size 0x4
    TLImageInstance* mButtonImages[3];    // offset 0x4, size 0xC
    TLTextInstance* mButtonLabels[3];     // offset 0x10, size 0xC
    int mNumButtons;                      // offset 0x1C, size 0x4
    bool mAlreadyCentred;                 // offset 0x20, size 0x1
};

// class FontCharString
// {
// public:
//     void FontCharString<unsigned short>(const unsigned short*, const nlFont*, unsigned short*);
// };

// class FEFinder<TLImageInstance, 2>
// {
// public:
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// };

// class FEFinder<TLTextInstance, 3>
// {
// public:
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// };

#endif // _FEBUTTONCOMPONENT_H_
